#include <gtest/gtest.h>
#include "StringDataSink.h"
#include "StringDataSource.h"
#include "DSVWriter.h"
#include "DSVReader.h"
#include <iostream>



TEST(DSVWriter, WriteTest){
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');  //quoteall = false
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!");  //no values quoted
    


    auto Sink1 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer1(Sink1,'&', false);  //quoteall = false, same as previous -> no values quoted
    input = {"Hello", "World!"};

    EXPECT_TRUE(Writer1.WriteRow(input));
    EXPECT_EQ(Sink1->String(),"Hello&World!");  //no values quoted


    auto Sink2 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer2(Sink2,'&', true);  //quoteall = true
    input = {"Hello", "World!"};

    EXPECT_TRUE(Writer2.WriteRow(input));
    EXPECT_EQ(Sink2->String(),"\"Hello\"&\"World!\"");  //all values quoted



    auto Sink3 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer3(Sink3, ',', false);   //only delimiter including values quoted
    input = {"This", "is", "an, example", "string"};
    EXPECT_TRUE(Writer3.WriteRow(input));
    EXPECT_EQ(Sink3->String(),"This,is,\"an, example\",string"); 


    auto Sink4 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer4(Sink4, ',');   //only delimiter including values quoted
    input = {"This", "is", "an, example", "string"};
    EXPECT_TRUE(Writer4.WriteRow(input));
    EXPECT_EQ(Sink4->String(),"This,is,\"an, example\",string"); 


    auto Sink5 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer5(Sink5, ',', true);   //all values quoted
    input = {"This", "is", "an, example", "string"};
    EXPECT_TRUE(Writer5.WriteRow(input));
    EXPECT_EQ(Sink5->String(),"\"This\",\"is\",\"an, example\",\"string\""); 


    auto Sink6 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer6(Sink6, ',');   //only special values quoted
    input = {"This", "is", "a \"nother\" example", "string"};
    EXPECT_TRUE(Writer6.WriteRow(input));
    EXPECT_EQ(Sink6->String(), "This,is,\"a \"\"nother\"\" example\",string"); 


    auto Sink7 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer7(Sink7, ',', true);   //all values quoted
    input = {"This", "is", "a \"nother\" example", "string"};
    EXPECT_TRUE(Writer7.WriteRow(input));
    EXPECT_EQ(Sink7->String(), "\"This\",\"is\",\"a \"\"nother\"\" example\",\"string\"");    


    auto Sink8 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer8(Sink8, ',');   //only special values quoted
    input = {"This", "is", "a \"no\nther\" example", "st\nring"};
    EXPECT_TRUE(Writer8.WriteRow(input));
    EXPECT_EQ(Sink8->String(), "This,is,\"a \"\"no\nther\"\" example\",\"st\nring\""); 


    auto Sink9 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer9(Sink9, ',');   //only special values quoted
    input = {"", "line", "", "", "empty", ","};
    EXPECT_TRUE(Writer9.WriteRow(input));
    EXPECT_EQ(Sink9->String(), ",line,,,empty,\",\"");

    auto Sink10 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer10(Sink10, ',', true);
    input = {"third, row", "has \n delimiter"};
     EXPECT_TRUE(Writer10.WriteRow(input));
     EXPECT_EQ(Sink10->String(),"\"third, row\",\"has \n delimiter\"");


/*     auto Sink10 = std::make_shared<CStringDataSink[10]>();
    CDSVWriter Writer10(Sink10, ',');  
    input = {"this", "is", "more", "longer", "than", "allocated"};
    EXPECT_FALSE(Writer10.WriteRow(input)); */

    //sink with a finite size, and it would overflow to do the put or write.

/*
Values that have either the delimiter, double quote character, or newline must be quoted 
with double quotes.  
Double quote character in the cell must be replace with two double quotes. 
An empty line is a valid row where there are not values 
*/
}


TEST(DSVReader, ReadTest){
      auto Source = std::make_shared<CStringDataSource>("Hello&World!");
      CDSVReader Reader (Source, '&');
      std::vector<std::string> output;

      EXPECT_TRUE(Reader.ReadRow(output));
      EXPECT_TRUE(Reader.End());
      ASSERT_EQ(output.size(), 2);
      EXPECT_EQ(output[0], "Hello");
      EXPECT_EQ(output[1], "World!");



      auto Source1 = std::make_shared<CStringDataSource>("this&is&an&&example&");
      CDSVReader Reader1 (Source1, '&');

      EXPECT_TRUE(Reader1.ReadRow(output));
      EXPECT_TRUE(Reader1.End());
      ASSERT_EQ(output.size(), 6);
      EXPECT_EQ(output[0], "this");
      EXPECT_EQ(output[1], "is");
      EXPECT_EQ(output[2], "an");
      EXPECT_EQ(output[3], "");
      EXPECT_EQ(output[4], "example");
      EXPECT_EQ(output[5], "");



      auto Sink = std::make_shared<CStringDataSink>();
      CDSVWriter Writer(Sink, ',');   //only delimiter including values quoted
      std::vector<std::string> input = {"This", "is", "an, example", "string"};
      EXPECT_TRUE(Writer.WriteRow(input));
    
      auto Source2 = std::make_shared<CStringDataSource>(Sink->String());
      CDSVReader Reader2 (Source2, ',');

      EXPECT_TRUE(Reader2.ReadRow(output));
      EXPECT_TRUE(Reader2.End());
      ASSERT_EQ(output.size(), 4);
      EXPECT_EQ(output[0], "This");
      EXPECT_EQ(output[1], "is");
      EXPECT_EQ(output[2], "\"an, example\"");
      EXPECT_EQ(output[3], "string");




    auto Sink1 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer1(Sink1, ',', true);   //all values quoted
    input = {"This", "is", "an, example", "string"};
    EXPECT_TRUE(Writer1.WriteRow(input));
    EXPECT_EQ(Sink1->String(),"\"This\",\"is\",\"an, example\",\"string\""); 
 
    auto Source3 = std::make_shared<CStringDataSource>(Sink1->String());
      CDSVReader Reader3 (Source3, ',');

      EXPECT_TRUE(Reader3.ReadRow(output));
      EXPECT_TRUE(Reader3.End());
      ASSERT_EQ(output.size(), 4);
      EXPECT_EQ(output[0], "\"This\"");
      EXPECT_EQ(output[1], "\"is\"");
      EXPECT_EQ(output[2], "\"an, example\"");
      EXPECT_EQ(output[3], "\"string\"");


      //two double quotes, newline
      

 }  

 TEST(DSVReader, WriteReadTest)
 {
    std::vector<std::string> output;

    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');  //quoteall = false
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!");  //no values quoted

    auto Source = std::make_shared<CStringDataSource>(Sink->String());
    CDSVReader Reader(Source, ',');

      EXPECT_TRUE(Reader.ReadRow(output));
      EXPECT_TRUE(Reader.End());
      ASSERT_EQ(output.size(), 1);
      EXPECT_EQ(output[0], "Hello&World!");




    auto Sink1 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer1(Sink1,'&');  //quoteall = false
    input = {"Hello", "World!"};

    EXPECT_TRUE(Writer1.WriteRow(input));
    EXPECT_EQ(Sink1->String(),"Hello&World!");  //no values quoted

    auto Source1 = std::make_shared<CStringDataSource>(Sink1->String());
    CDSVReader Reader1(Source1, '&');

      EXPECT_TRUE(Reader1.ReadRow(output));
      EXPECT_TRUE(Reader1.End());
      ASSERT_EQ(output.size(), 2);
      EXPECT_EQ(output[0], "Hello");
      EXPECT_EQ(output[1], "World!");




    auto Sink2 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer2(Sink2,'&', true);  //quoteall = true
    input = {"Hello", "World!"};

    EXPECT_TRUE(Writer2.WriteRow(input));
    EXPECT_EQ(Sink2->String(),"\"Hello\"&\"World!\"");  //all values quoted

    auto Source2 = std::make_shared<CStringDataSource>(Sink2->String());
    CDSVReader Reader2(Source2, '&');

      EXPECT_TRUE(Reader2.ReadRow(output));
      EXPECT_TRUE(Reader2.End());
      ASSERT_EQ(output.size(), 2);
      EXPECT_EQ(output[0], "\"Hello\"");
      EXPECT_EQ(output[1], "\"World!\"");





    auto Sink6 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer6(Sink6, ',');   //only special values quoted
    input = {"This", "is", "a \"nother\" example", "string"};
    EXPECT_TRUE(Writer6.WriteRow(input));
    EXPECT_EQ(Sink6->String(), "This,is,\"a \"\"nother\"\" example\",string"); 

    auto Source6 = std::make_shared<CStringDataSource>(Sink6->String());
    CDSVReader Reader6(Source6, ',');

      EXPECT_TRUE(Reader6.ReadRow(output));
      EXPECT_TRUE(Reader6.End());
      ASSERT_EQ(output.size(), 4);
      EXPECT_EQ(output[0], "This");
      EXPECT_EQ(output[1], "is");
      EXPECT_EQ(output[2], "\"a \"\"nother\"\" example\"");
      EXPECT_EQ(output[3], "string");



    auto Sink7 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer7(Sink7, ',', true);   //all values quoted
    input = {"This", "is", "a \"nother\" example", "string"};
    EXPECT_TRUE(Writer7.WriteRow(input));
    EXPECT_EQ(Sink7->String(), "\"This\",\"is\",\"a \"\"nother\"\" example\",\"string\"");  

    auto Source7 = std::make_shared<CStringDataSource>(Sink7->String());
    CDSVReader Reader7(Source7, ',');

      EXPECT_TRUE(Reader7.ReadRow(output));
      EXPECT_TRUE(Reader7.End());
      ASSERT_EQ(output.size(), 4);
      EXPECT_EQ(output[0], "\"This\"");
      EXPECT_EQ(output[1], "\"is\"");
      EXPECT_EQ(output[2], "\"a \"\"nother\"\" example\"");
      EXPECT_EQ(output[3], "\"string\""); 


    auto Sink8 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer8(Sink8, ',');   //only special values quoted
    input = {"This", "is", "a \"no\nther\" example", "st\nring"};
    EXPECT_TRUE(Writer8.WriteRow(input));
    EXPECT_EQ(Sink8->String(), "This,is,\"a \"\"no\nther\"\" example\",\"st\nring\""); 


    auto Source8 = std::make_shared<CStringDataSource>(Sink8->String());
    CDSVReader Reader8(Source8, ',');

      EXPECT_TRUE(Reader8.ReadRow(output));
      EXPECT_TRUE(Reader8.End());
      ASSERT_EQ(output.size(), 4);
      EXPECT_EQ(output[0], "This");
      EXPECT_EQ(output[1], "is");
      EXPECT_EQ(output[2], "\"a \"\"no\nther\"\" example\"");
      EXPECT_EQ(output[3], "\"st\nring\""); 



    auto Sink9 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer9(Sink9, ',');   //only special values quoted
    input = {"", "line", "", "", "empty", ","};
    EXPECT_TRUE(Writer9.WriteRow(input));
    EXPECT_EQ(Sink9->String(), ",line,,,empty,\",\""); 

    auto Source9 = std::make_shared<CStringDataSource>(Sink9->String());
    CDSVReader Reader9(Source9, ',');

      EXPECT_TRUE(Reader9.ReadRow(output));
      EXPECT_TRUE(Reader9.End());
      ASSERT_EQ(output.size(), 6);
      EXPECT_EQ(output[0], "");
      EXPECT_EQ(output[1], "line");
      EXPECT_EQ(output[2], "");
      EXPECT_EQ(output[3], ""); 
      EXPECT_EQ(output[4], "empty"); 
      EXPECT_EQ(output[5], "\",\""); 


 }


 TEST(DSVWriter, WriteTest2)
 {

    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');  //quoteall = false
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!");  //no values quoted

    //writing second row

    input = {"this", "is", "the second row"};
    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!\nthis&is&the second row");


    //writing third row

    input = {"welcome", "to", "row 3"};
    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!\nthis&is&the second row\nwelcome&to&row 3");

 }

 TEST(DSVReader, ReadTest2)
 {

      auto Source = std::make_shared<CStringDataSource>("Hello, World!\nMy Name,Bob\n this, is \"the\n third\", row\n ");
      CDSVReader Reader (Source, ',');
      std::vector<std::string> output1;
      std::vector<std::string> output2;
      std::vector<std::string> output3;
      std::vector<std::string> output4;


      EXPECT_TRUE(Reader.ReadRow(output1));
      EXPECT_FALSE(Reader.End());
      ASSERT_EQ(output1.size(), 2);
      EXPECT_EQ(output1[0], "Hello");
      EXPECT_EQ(output1[1], " World!");

      EXPECT_TRUE(Reader.ReadRow(output2));
      EXPECT_FALSE(Reader.End());
      ASSERT_EQ(output2.size(), 2);
      EXPECT_EQ(output2[0], "My Name");
      EXPECT_EQ(output2[1], "Bob");

      EXPECT_TRUE(Reader.ReadRow(output3));
      EXPECT_FALSE(Reader.End());
      ASSERT_EQ(output3.size(), 3);
      EXPECT_EQ(output3[0], " this");
      EXPECT_EQ(output3[1], " is \"the\n third\"");
      EXPECT_EQ(output3[2], " row");


      EXPECT_TRUE(Reader.ReadRow(output4));
      EXPECT_TRUE(Reader.End());
      ASSERT_EQ(output4.size(), 1);
      EXPECT_EQ(output4[0], " ");





      auto Source1 = std::make_shared<CStringDataSource>("Hello, World!\nMy Name,Bob\n this, is \"the\n third\"\n\n row\n ");  //empty row
      CDSVReader Reader1 (Source1, ',');
      std::vector<std::string> Output1;
      std::vector<std::string> Output2;
      std::vector<std::string> Output3;
      std::vector<std::string> Output4;
      std::vector<std::string> Output5;
      std::vector<std::string> Output6;


      EXPECT_TRUE(Reader1.ReadRow(Output1));
      EXPECT_FALSE(Reader1.End());
      ASSERT_EQ(Output1.size(), 2);
      EXPECT_EQ(Output1[0], "Hello");
      EXPECT_EQ(Output1[1], " World!");

      EXPECT_TRUE(Reader1.ReadRow(Output2));
      EXPECT_FALSE(Reader1.End());
      ASSERT_EQ(Output2.size(), 2);
      EXPECT_EQ(Output2[0], "My Name");
      EXPECT_EQ(Output2[1], "Bob");

      EXPECT_TRUE(Reader1.ReadRow(Output3));
      EXPECT_FALSE(Reader1.End());
      ASSERT_EQ(Output3.size(), 2);
      EXPECT_EQ(Output3[0], " this");
      EXPECT_EQ(Output3[1], " is \"the\n third\"");

      EXPECT_TRUE(Reader1.ReadRow(Output4));
      EXPECT_FALSE(Reader1.End());
      ASSERT_EQ(Output4.size(), 1);
      EXPECT_EQ(Output4[0], "");

      EXPECT_TRUE(Reader1.ReadRow(Output5));
      EXPECT_FALSE(Reader1.End());
      ASSERT_EQ(Output5.size(), 1);
      EXPECT_EQ(Output5[0], " row");

      EXPECT_TRUE(Reader1.ReadRow(Output6));
      EXPECT_TRUE(Reader1.End());
      ASSERT_EQ(Output6.size(), 1);
      EXPECT_EQ(Output6[0], " ");

  /*
  single source that has newline characters in it that separate rows. 
  Ex. source would look like ("Hello, World!\nMy Name,Bob") with "," as delimiter. 
  In this example in order to reach the end of the source you would have to call readrow twice. 
  The first call would read in  {"Hello", " World!"} 
  the second call would read in {"My Name", "Bob"}.
  */
 }



 TEST(DSVReader, WriteReadTest2)
 {
    std::vector<std::string> output;


    auto Sink7 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer7(Sink7, ',', true);   //all values quoted
    std::vector<std::string> input = {"This", "is", "a \"nother\" example", "string"};
    EXPECT_TRUE(Writer7.WriteRow(input));
    EXPECT_EQ(Sink7->String(), "\"This\",\"is\",\"a \"\"nother\"\" example\",\"string\""); 

    //writing second row

    input = {"this", "is", "the second row"};
    EXPECT_TRUE(Writer7.WriteRow(input));
    EXPECT_EQ(Sink7->String(),"\"This\",\"is\",\"a \"\"nother\"\" example\",\"string\"\n\"this\",\"is\",\"the second row\"");

    //writing third row

     input = {"third, row", "has \n delimiter"};
     EXPECT_TRUE(Writer7.WriteRow(input));
     EXPECT_EQ(Sink7->String(),"\"This\",\"is\",\"a \"\"nother\"\" example\",\"string\"\n\"this\",\"is\",\"the second row\"\n\"third, row\",\"has \n delimiter\"");

     //read all 3 rows

     auto Source = std::make_shared<CStringDataSource>(Sink7->String());
     CDSVReader Reader (Source, ',');
     std::vector<std::string> output1;
    std::vector<std::string> output2;
    std::vector<std::string> output3;

    //reading first row

    EXPECT_TRUE(Reader.ReadRow(output1));
    EXPECT_FALSE(Reader.End());
    ASSERT_EQ(output1.size(), 4);
    EXPECT_EQ(output1[0], "\"This\"");
    EXPECT_EQ(output1[1], "\"is\"");
    EXPECT_EQ(output1[2], "\"a \"\"nother\"\" example\"");   //when there is two double quotes, SHOULD read only return 1????
    EXPECT_EQ(output1[3], "\"string\"");


    //reading second row

    EXPECT_TRUE(Reader.ReadRow(output2));
    EXPECT_FALSE(Reader.End());
    ASSERT_EQ(output2.size(), 3);
    EXPECT_EQ(output2[0], "\"this\"");
    EXPECT_EQ(output2[1], "\"is\"");
    EXPECT_EQ(output2[2], "\"the second row\"");   

    //reading third row


    EXPECT_TRUE(Reader.ReadRow(output3));
    EXPECT_TRUE(Reader.End());
    ASSERT_EQ(output3.size(), 2);
    EXPECT_EQ(output3[0], "\"third, row\"");
    EXPECT_EQ(output3[1], "\"has \n delimiter\"");

 }