#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest){
    std::string ReturnString = "";

    ReturnString = StringUtils::Slice("Hello World", 0);  //start to end
    EXPECT_EQ(ReturnString, "Hello World");

    ReturnString = StringUtils::Slice("Hello World", 5);  
    EXPECT_EQ(ReturnString, " World");

    ReturnString = StringUtils::Slice("Hello World", 0, 8);  
    EXPECT_EQ(ReturnString, "Hello Wo");

    ReturnString = StringUtils::Slice("Hello World", 5, 8);  
    EXPECT_EQ(ReturnString, " Wo");

    ReturnString = StringUtils::Slice("Hello World", -8, 7);  
    EXPECT_EQ(ReturnString, "lo W");

    ReturnString = StringUtils::Slice("Hello World", 0, -3);  
    EXPECT_EQ(ReturnString, "Hello Wo");

    ReturnString = StringUtils::Slice("Hello World", -3, 5);  //start > end
    EXPECT_EQ(ReturnString, "");

    ReturnString = StringUtils::Slice("Hello World", 5, 5);  
    EXPECT_EQ(ReturnString, "");

    ReturnString = StringUtils::Slice("Hello World", 0, 0);  
    EXPECT_EQ(ReturnString, "Hello World");

    ReturnString = StringUtils::Slice("Hello World", 30);  
    EXPECT_EQ(ReturnString, "");

    ReturnString = StringUtils::Slice("Hello World", 0, 30);  
    EXPECT_EQ(ReturnString, "Hello World");

    ReturnString = StringUtils::Slice("Hello World", 5, 30);  
    EXPECT_EQ(ReturnString, " World");

    ReturnString = StringUtils::Slice("", 5);  
    EXPECT_EQ(ReturnString, "");

}

TEST(StringUtilsTest, Capitalize){
    std::string ReturnString = "";

    ReturnString = StringUtils::Capitalize("hello");
    EXPECT_EQ(ReturnString, "Hello");

    ReturnString = StringUtils::Capitalize("Hello");
    EXPECT_EQ(ReturnString, "Hello");

    ReturnString = StringUtils::Capitalize("hello world");
    EXPECT_EQ(ReturnString, "Hello world");

    ReturnString = StringUtils::Capitalize("Hello World");
    EXPECT_EQ(ReturnString, "Hello World");

    ReturnString = StringUtils::Capitalize("");
    EXPECT_EQ(ReturnString, ""); 

   

}

TEST(StringUtilsTest, Upper){
    std::string ReturnString = "";

    ReturnString = StringUtils::Upper("hello world");
    EXPECT_EQ(ReturnString, "HELLO WORLD");

    ReturnString = StringUtils::Upper("hello wORlD");
    EXPECT_EQ(ReturnString, "HELLO WORLD");

    ReturnString = StringUtils::Upper("HELLO");
    EXPECT_EQ(ReturnString, "HELLO");

    ReturnString = StringUtils::Upper("");
    EXPECT_EQ(ReturnString, "");

    ReturnString = StringUtils::Upper("1234?!");
    EXPECT_EQ(ReturnString, "1234?!");
}

TEST(StringUtilsTest, Lower){
    std::string ReturnString = "";

    ReturnString = StringUtils::Lower("hello world");
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::Lower("hello wORlD");
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::Lower("HELLO");
    EXPECT_EQ(ReturnString, "hello");

    ReturnString = StringUtils::Lower("");
    EXPECT_EQ(ReturnString, "");

    ReturnString = StringUtils::Lower("1234?!");
    EXPECT_EQ(ReturnString, "1234?!");
    
}

TEST(StringUtilsTest, LStrip){
    std::string ReturnString = "";

    ReturnString = StringUtils::LStrip("hello world");
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::LStrip(" \t\f\v\n\rhello world");
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::LStrip(" \t\f\v\n\rhello world \t\f\v\n\r");
    EXPECT_EQ(ReturnString, "hello world \t\f\v\n\r");

    ReturnString = StringUtils::LStrip("");
    EXPECT_EQ(ReturnString, "");

}

TEST(StringUtilsTest, RStrip){

    std::string ReturnString = "";

    ReturnString = StringUtils::RStrip("hello world");
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::RStrip("hello world \t\f\v\n\r");
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::RStrip(" \t\f\v\n\rhello world \t\f\v\n\r");
    EXPECT_EQ(ReturnString, " \t\f\v\n\rhello world");

    ReturnString = StringUtils::RStrip("");
    EXPECT_EQ(ReturnString, "");
    
}

TEST(StringUtilsTest, Strip){

    std::string ReturnString = "";

    ReturnString = StringUtils::Strip("hello world");
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::Strip("hello world \t\f\v\n\r");
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::Strip(" \t\f\v\n\rhello world \t\f\v\n\r");
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::Strip("");
    EXPECT_EQ(ReturnString, "");
    
}

TEST(StringUtilsTest, Center){
    
    std::string ReturnString = "";

    ReturnString = StringUtils::Center("hello world", 5);
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::Center("hello world", 27);
    EXPECT_EQ(ReturnString, "        hello world        ");   
    
    ReturnString = StringUtils::Center("hello world", 26);
    EXPECT_EQ(ReturnString, "       hello world        ");

    ReturnString = StringUtils::Center("hello world", 26, 'a');
    EXPECT_EQ(ReturnString, "aaaaaaahello worldaaaaaaaa");

    ReturnString = StringUtils::Center("", 3);
    EXPECT_EQ(ReturnString, "   ");

    ReturnString = StringUtils::Center("hello", -20);
    EXPECT_EQ(ReturnString, "hello");


}

TEST(StringUtilsTest, LJust){

    std::string ReturnString = "";

    ReturnString = StringUtils::LJust("hello world", 5);
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::LJust("hello world", 27);
    EXPECT_EQ(ReturnString, "hello world                ");   
    

    ReturnString = StringUtils::LJust("hello world", 26, 'a');
    EXPECT_EQ(ReturnString, "hello worldaaaaaaaaaaaaaaa");

    ReturnString = StringUtils::LJust("", 3);
    EXPECT_EQ(ReturnString, "   ");

    ReturnString = StringUtils::LJust("hello", -20);
    EXPECT_EQ(ReturnString, "hello");
}

TEST(StringUtilsTest, RJust){
    
    std::string ReturnString = "";

    ReturnString = StringUtils::RJust("hello world", 5);
    EXPECT_EQ(ReturnString, "hello world");

    ReturnString = StringUtils::RJust("hello world", 27);
    EXPECT_EQ(ReturnString, "                hello world");   

    ReturnString = StringUtils::RJust("hello world", 26, 'a');
    EXPECT_EQ(ReturnString, "aaaaaaaaaaaaaaahello world");

    ReturnString = StringUtils::RJust("", 3);
    EXPECT_EQ(ReturnString, "   ");

    ReturnString = StringUtils::RJust("hello", -20);
    EXPECT_EQ(ReturnString, "hello");
}

TEST(StringUtilsTest, Replace){
    
    std::string ReturnString = "";

    ReturnString = StringUtils::Replace("is what is going on in is going it going is", "going", "dl");
    EXPECT_EQ(ReturnString, "is what is dl on in is dl it dl is");

    ReturnString = StringUtils::Replace("is what is going on in is going it going is", "is", "foobar");
    EXPECT_EQ(ReturnString, "foobar what foobar going on in foobar going it going foobar");

    ReturnString = StringUtils::Replace("is what is going on in is going it going is", "is", "as");
    EXPECT_EQ(ReturnString, "as what as going on in as going it going as");

    ReturnString = StringUtils::Replace("is what is going on in is going it going is", "is", "t");
    EXPECT_EQ(ReturnString, "t what t going on in t going it going t");

    ReturnString = StringUtils::Replace("is what is going on in is going it going is", "foo", "bar");
    EXPECT_EQ(ReturnString, "is what is going on in is going it going is");

    ReturnString = StringUtils::Replace("is what is going on in is going it going is", "go", "goose");
    EXPECT_EQ(ReturnString, "is what is gooseing on in is gooseing it gooseing is");

    ReturnString = StringUtils::Replace("", "", "goose");
    EXPECT_EQ(ReturnString, "goose");

    ReturnString = StringUtils::Replace("", "", "goose");
    EXPECT_EQ(ReturnString, "goose");

    ReturnString = StringUtils::Replace("is what is going on in is going it going is", "go", "");
    EXPECT_EQ(ReturnString, "is what is ing on in is ing it ing is");


}

TEST(StringUtilsTest, Split){

    std::vector< std::string > ReturnVector;

    ReturnVector = StringUtils::Split("How are you today?");
    ASSERT_EQ(ReturnVector.size(), 4);
    EXPECT_EQ(ReturnVector[0], "How");
    EXPECT_EQ(ReturnVector[1], "are");
    EXPECT_EQ(ReturnVector[2], "you");
    EXPECT_EQ(ReturnVector[3], "today?");

    ReturnVector = StringUtils::Split("How|are|you||today?", "|");
    ASSERT_EQ(ReturnVector.size(), 5);
    EXPECT_EQ(ReturnVector[0], "How");
    EXPECT_EQ(ReturnVector[1], "are");
    EXPECT_EQ(ReturnVector[2], "you");
    EXPECT_EQ(ReturnVector[3], "");
    EXPECT_EQ(ReturnVector[4], "today?");

    ReturnVector = StringUtils::Split("How|are|you| |today?", "|");
    ASSERT_EQ(ReturnVector.size(), 5);
    EXPECT_EQ(ReturnVector[0], "How");
    EXPECT_EQ(ReturnVector[1], "are");
    EXPECT_EQ(ReturnVector[2], "you");
    EXPECT_EQ(ReturnVector[3], " ");
    EXPECT_EQ(ReturnVector[4], "today?");

     ReturnVector = StringUtils::Split("||How|are|you| |today?||", "|");  
    ASSERT_EQ(ReturnVector.size(), 9);
    EXPECT_EQ(ReturnVector[0], "");
    EXPECT_EQ(ReturnVector[1], "");
    EXPECT_EQ(ReturnVector[2], "How");
    EXPECT_EQ(ReturnVector[3], "are");
    EXPECT_EQ(ReturnVector[4], "you");
    EXPECT_EQ(ReturnVector[5], " ");
    EXPECT_EQ(ReturnVector[6], "today?");
    EXPECT_EQ(ReturnVector[7], "");
    EXPECT_EQ(ReturnVector[8], ""); 

 
    ReturnVector = StringUtils::Split("  How are you  today?  ");
    ASSERT_EQ(ReturnVector.size(), 4);
    EXPECT_EQ(ReturnVector[0], "How");
    EXPECT_EQ(ReturnVector[1], "are");
    EXPECT_EQ(ReturnVector[2], "you");
    EXPECT_EQ(ReturnVector[3], "today?");
 

    ReturnVector = StringUtils::Split("Hoarew areare you  are today", "are");   
    ASSERT_EQ(ReturnVector.size(), 5);
    EXPECT_EQ(ReturnVector[0], "Ho");
    EXPECT_EQ(ReturnVector[1], "w ");
    EXPECT_EQ(ReturnVector[2], "");
    EXPECT_EQ(ReturnVector[3], " you  ");
    EXPECT_EQ(ReturnVector[4], " today"); 

    ReturnVector = StringUtils::Split("Hoarew areare you  are today areare", "are");   
    ASSERT_EQ(ReturnVector.size(), 7);
    EXPECT_EQ(ReturnVector[0], "Ho");
    EXPECT_EQ(ReturnVector[1], "w ");
    EXPECT_EQ(ReturnVector[2], "");
    EXPECT_EQ(ReturnVector[3], " you  ");
    EXPECT_EQ(ReturnVector[4], " today "); 
    EXPECT_EQ(ReturnVector[5], ""); 
    EXPECT_EQ(ReturnVector[6], ""); 

     
    ReturnVector = StringUtils::Split("", "are"); 
    ASSERT_EQ(ReturnVector.size(), 1);
    EXPECT_EQ(ReturnVector[0], "");   
 
}

TEST(StringUtilsTest, Join){
    
    std::string ReturnString = "";


    std::vector<std::string> v = { "this", "is", "now", "a", "string"};
    ReturnString = StringUtils::Join("", v);
    EXPECT_EQ(ReturnString, "thisisnowastring");

    ReturnString = StringUtils::Join("BLANK", v);
    EXPECT_EQ(ReturnString, "thisBLANKisBLANKnowBLANKaBLANKstring");

    v = {};
    ReturnString = StringUtils::Join("BLANK", v);
    EXPECT_EQ(ReturnString, "");

    v = {" "};
    ReturnString = StringUtils::Join("BLANK", v);
    EXPECT_EQ(ReturnString, " ");

    v = {" ", " "};
    ReturnString = StringUtils::Join("BLANK", v);
    EXPECT_EQ(ReturnString, " BLANK "); 


}

TEST(StringUtilsTest, ExpandTabs){
    
    std::string ReturnString = "";

    ReturnString = StringUtils::ExpandTabs(" this is an \n example\r");
    EXPECT_EQ(ReturnString, " this is an \n example\r");
 
     ReturnString = StringUtils::ExpandTabs("    this is an      example");
    EXPECT_EQ(ReturnString, "    this is an      example");

      ReturnString = StringUtils::ExpandTabs("this     is an exam     ple     ", 2);
    EXPECT_EQ(ReturnString, "this     is an exam     ple     ");
}

TEST(StringUtilsTest, EditDistance){
    int ReturnVal;

    ReturnVal = StringUtils::EditDistance("alp", "ecs", true);
    EXPECT_EQ(ReturnVal, 3);

    ReturnVal = StringUtils::EditDistance("ALP", "ecs", false);
    EXPECT_EQ(ReturnVal, 3);

     ReturnVal = StringUtils::EditDistance("ALP", "alp", true);   
    EXPECT_EQ(ReturnVal, 0); 

    ReturnVal = StringUtils::EditDistance("alp", "ALP", false);
    EXPECT_EQ(ReturnVal, 3);   

    ReturnVal = StringUtils::EditDistance("alp g", "alp", false);   
    EXPECT_EQ(ReturnVal, 2);   

    ReturnVal = StringUtils::EditDistance("aLp g", "alp", false);   
    EXPECT_EQ(ReturnVal, 3);

    ReturnVal = StringUtils::EditDistance("alp", "", true);
    EXPECT_EQ(ReturnVal, 3);

    ReturnVal = StringUtils::EditDistance("", "ecs", false);
    EXPECT_EQ(ReturnVal, 3);


    ReturnVal = StringUtils::EditDistance(" ", "ecs", false);
    EXPECT_EQ(ReturnVal, 3);
}

