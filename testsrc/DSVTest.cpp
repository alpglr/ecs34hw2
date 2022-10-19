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