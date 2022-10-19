#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest) {
    EXPECT_EQ(StringUtils::Slice("Hello World!", 0, 11), "Hello World");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 5, 5), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 6, 4), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 5, 22), " World!");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 0), "Hello World!");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 3, -5), "lo W");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 3, -10), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 3, -22), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -12, -11), "H");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -5, -5), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -5, -6), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -5, -17), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -10), "llo World!");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -11, 5), "ello");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -7, 1), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -5, 12), "orld!");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 12), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -13), "Hello World!");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -15, 5), "Hello");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -20, -5), "Hello W");
    EXPECT_EQ(StringUtils::Slice("H", -1, 0), "H");
    EXPECT_EQ(StringUtils::Slice("H", -10, 10), "H");
    EXPECT_EQ(StringUtils::Slice("", 0), "");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 1), "ello World!");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 0, 5), "Hello");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 0, -1), "Hello World");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 3, -2), "lo Worl");
    EXPECT_EQ(StringUtils::Slice("Hello World!", -5, -2), "orl");
    EXPECT_EQ(StringUtils::Slice("Hello World!", 14), "");
}

TEST(StringUtilsTest, Capitalize) {
    EXPECT_EQ(StringUtils::Capitalize("testing testing 123"), "Testing testing 123");
    EXPECT_EQ(StringUtils::Capitalize("hello WORLD!"), "Hello world!");
    EXPECT_EQ(StringUtils::Capitalize("   Hello World!"), "   hello world!");
    EXPECT_EQ(StringUtils::Capitalize("99 bottles of Beer"), "99 bottles of beer");
    EXPECT_EQ(StringUtils::Capitalize("...and then it Hit me"), "...and then it hit me");
    EXPECT_EQ(StringUtils::Capitalize(""), "");
    EXPECT_EQ(StringUtils::Capitalize("hello world!"), "Hello world!");
    EXPECT_EQ(StringUtils::Capitalize("HELLO WORLD!"), "Hello world!");
    EXPECT_EQ(StringUtils::Capitalize(" HELLO WORLD!"), " hello world!");
}

TEST(StringUtilsTest, Upper) {
    EXPECT_EQ(StringUtils::Upper("testing testing 123\n"), "TESTING TESTING 123\n");
    EXPECT_EQ(StringUtils::Upper("HELLo wORLd!"), "HELLO WORLD!");
    EXPECT_EQ(StringUtils::Upper("I AM UPPERCASE"), "I AM UPPERCASE");
    EXPECT_EQ(StringUtils::Upper(""), "");
    EXPECT_EQ(StringUtils::Upper("hello world!"), "HELLO WORLD!");
    EXPECT_EQ(StringUtils::Upper("Hello World!"), "HELLO WORLD!");
    EXPECT_EQ(StringUtils::Upper("HELLO WORLD!"), "HELLO WORLD!");
    EXPECT_EQ(StringUtils::Upper(" HELLO WORLD!"), " HELLO WORLD!");
}

TEST(StringUtilsTest, Lower) {
    EXPECT_EQ(StringUtils::Lower("TESTING TESTING 123\n"), "testing testing 123\n");
    EXPECT_EQ(StringUtils::Lower("HELLo wORLd!"), "hello world!");
    EXPECT_EQ(StringUtils::Lower("i am lowercase"), "i am lowercase");
    EXPECT_EQ(StringUtils::Lower(""), "");
    EXPECT_EQ(StringUtils::Lower("hello world!"), "hello world!");
    EXPECT_EQ(StringUtils::Lower("Hello World!"), "hello world!");
    EXPECT_EQ(StringUtils::Lower("HELLO WORLD!"), "hello world!");
    EXPECT_EQ(StringUtils::Lower(" HELLO WORLD!"), " hello world!");
}

TEST(StringUtilsTest, LStrip) {
    EXPECT_EQ(StringUtils::LStrip("   \t\nHello World!\t\n   "), "Hello World!\t\n   ");
    EXPECT_EQ(StringUtils::LStrip("testing   testing 123"), "testing   testing 123");
    EXPECT_EQ(StringUtils::LStrip("    "), "");
    EXPECT_EQ(StringUtils::LStrip(""), "");
    std::string Str1 = "    Test String    ";
    std::string Str2 = " \t \r\n Test String";
    std::string Str3 = "Test String \t \r\n ";
    EXPECT_EQ(StringUtils::LStrip(Str1), "Test String    ");
    EXPECT_EQ(StringUtils::LStrip(Str2), "Test String");
    EXPECT_EQ(StringUtils::LStrip(Str3), Str3);
}

TEST(StringUtilsTest, RStrip) {
    EXPECT_EQ(StringUtils::RStrip("   \t\nHello World!\t\n   "), "   \t\nHello World!");
    EXPECT_EQ(StringUtils::RStrip("testing   testing 123"), "testing   testing 123");
    EXPECT_EQ(StringUtils::RStrip("    "), "");
    EXPECT_EQ(StringUtils::RStrip(""), "");
    std::string Str1 = "    Test String    ";
    std::string Str2 = " \t \r\n Test String";
    std::string Str3 = "Test String \t \r\n ";
    EXPECT_EQ(StringUtils::RStrip(Str1), "    Test String");
    EXPECT_EQ(StringUtils::RStrip(Str2), Str2);
    EXPECT_EQ(StringUtils::RStrip(Str3), "Test String");
}

TEST(StringUtilsTest, Strip) {
    EXPECT_EQ(StringUtils::Strip("   \t\nHello World!\t\n   "), "Hello World!");
    EXPECT_EQ(StringUtils::Strip("testing   testing 123"), "testing   testing 123");
    EXPECT_EQ(StringUtils::Strip("    "), "");
    EXPECT_EQ(StringUtils::Strip(""), "");
    std::string Str1 = "    Test String    ";
    std::string Str2 = " \t \r\n Test String";
    std::string Str3 = "Test String \t \r\n ";
    EXPECT_EQ(StringUtils::Strip(Str1), "Test String");
    EXPECT_EQ(StringUtils::Strip(Str2), "Test String");
    EXPECT_EQ(StringUtils::Strip(Str3), "Test String");
    EXPECT_EQ(StringUtils::Strip(Str1), StringUtils::RStrip(StringUtils::LStrip(Str1)));

    EXPECT_EQ(StringUtils::Strip(Str2), StringUtils::RStrip(StringUtils::LStrip(Str2)));

    EXPECT_EQ(StringUtils::Strip(Str3), StringUtils::RStrip(StringUtils::LStrip(Str3)));
}

TEST(StringUtilsTest, Center) {
    EXPECT_EQ(StringUtils::Center("Hello World!", 14), " Hello World! ");
    EXPECT_EQ(StringUtils::Center("Hello World!", 20, 'x'), "xxxxHello World!xxxx");
    EXPECT_EQ(StringUtils::Center("testing", 10), "  testing ");
    EXPECT_EQ(StringUtils::Center("testing", 7), "testing");
    EXPECT_EQ(StringUtils::Center("testing", 4), "testing");
    EXPECT_EQ(StringUtils::Center("", 6, '\n'), "\n\n\n\n\n\n");
    EXPECT_EQ(StringUtils::Center("abc", -3), "abc");
    EXPECT_EQ(StringUtils::Center("abc ", 8), "  abc   ");
    EXPECT_EQ(StringUtils::Center("Test String", 19), "    Test String    ");
    EXPECT_EQ(StringUtils::Center("Test String", 5, '-'), "Test String");
}

TEST(StringUtilsTest, LJust) {
    EXPECT_EQ(StringUtils::LJust("Hello World!", 14), "Hello World!  ");
    EXPECT_EQ(StringUtils::LJust("Hello World!", 20, 'x'), "Hello World!xxxxxxxx");
    EXPECT_EQ(StringUtils::LJust("testing", 7), "testing");
    EXPECT_EQ(StringUtils::LJust("testing", 4), "testing");
    EXPECT_EQ(StringUtils::LJust("", 6, '\n'), "\n\n\n\n\n\n");
    EXPECT_EQ(StringUtils::LJust("abc", -3), "abc");
    EXPECT_EQ(StringUtils::LJust("abc ", 8), "abc     ");
    EXPECT_EQ(StringUtils::LJust("Test String", 19), "Test String        ");
    EXPECT_EQ(StringUtils::LJust("Test String", 5), "Test String");
}

TEST(StringUtilsTest, RJust) {
    EXPECT_EQ(StringUtils::RJust("Hello World!", 14), "  Hello World!");
    EXPECT_EQ(StringUtils::RJust("Hello World!", 20, 'x'), "xxxxxxxxHello World!");
    EXPECT_EQ(StringUtils::RJust("testing", 7), "testing");
    EXPECT_EQ(StringUtils::RJust("testing", 4), "testing");
    EXPECT_EQ(StringUtils::RJust("", 6, '\n'), "\n\n\n\n\n\n");
    EXPECT_EQ(StringUtils::RJust("abc", -3), "abc");
    EXPECT_EQ(StringUtils::RJust("abc ", 8), "    abc ");
    EXPECT_EQ(StringUtils::RJust("Test String", 19), "        Test String");
    EXPECT_EQ(StringUtils::RJust("Test String", 5), "Test String");
}

TEST(StringUtilsTest, Replace) {
    EXPECT_EQ(StringUtils::Replace("Hello World!", "l", "X"), "HeXXo WorXd!");
    EXPECT_EQ(StringUtils::Replace("red blue red blue red red green", "red", "white"), "white blue white blue white white green");
    EXPECT_EQ(StringUtils::Replace("qwertyuiop", "a", "b"), "qwertyuiop");
    EXPECT_EQ(StringUtils::Replace("", "", "a"), "a");
    EXPECT_EQ(StringUtils::Replace("", "b", "a"), "");
    EXPECT_EQ(StringUtils::Replace("goose", "", "a"), "agaoaoasaea");
    EXPECT_EQ(StringUtils::Replace("hiediekiegieie", "ie", "grief"), "hgriefdgriefkgriefggriefgrief");
    EXPECT_EQ(StringUtils::Replace("\\Path\\To\\A\\Directory", "\\", "/"), "/Path/To/A/Directory");
        EXPECT_EQ(StringUtils::Replace("a = b + c * b + d", "b", "e"), "a = e + c * e + d");
            EXPECT_EQ(StringUtils::Replace("aabbccaaabbbcccaaaa", "aa", "ee"),
                "eebbcceeabbbccceeee");
}

TEST(StringUtilsTest, Split) {
    std::vector< std::string > test1 = { "The", "quick", "brown", "fox" };
    std::vector< std::string > test2 = { "His", "Hers", "Yours", "Mine" };
    std::vector< std::string > test3 = { "testing" };
    std::vector< std::string > test4 = { "" };
    std::vector< std::string > test5 = { "The", "quick", "brown", "\n", "fox" };
    EXPECT_EQ(StringUtils::Split("The quick brown \n fox"), test1);
    EXPECT_EQ(StringUtils::Split("His and Hers and Yours and Mine", " and "), test2);
    EXPECT_EQ(StringUtils::Split("testing", "a"), test3);
    EXPECT_EQ(StringUtils::Split("", "a"), test4);
    EXPECT_EQ(StringUtils::Split("The quick brown \n fox", " "), test5);
    auto PathComponents = StringUtils::Split("/Path/To/A/Directory", "/");
    ASSERT_EQ(PathComponents.size(), 5);
    EXPECT_EQ(PathComponents[0], "");
    EXPECT_EQ(PathComponents[1], "Path");
    EXPECT_EQ(PathComponents[2], "To");
    EXPECT_EQ(PathComponents[3], "A");
    EXPECT_EQ(PathComponents[4], "Directory");

    auto SentenceComponents = StringUtils::Split("A  tougher\ttest\nto   pass!");
    ASSERT_EQ(SentenceComponents.size(), 5);
    EXPECT_EQ(SentenceComponents[0], "A");
    EXPECT_EQ(SentenceComponents[1], "tougher");
    EXPECT_EQ(SentenceComponents[2], "test");
    EXPECT_EQ(SentenceComponents[3], "to");
    EXPECT_EQ(SentenceComponents[4], "pass!");
}

TEST(StringUtilsTest, Join) {
    std::vector< std::string > test1 = { "The", "quick", "brown", "fox" };
    std::vector< std::string > test2 = { "His", "Hers", "Yours", "Mine" };
    std::vector< std::string > test3 = { "testing" };
    std::vector< std::string > test4 = { "" };
    std::vector< std::string > test5 = { "The", "quick", "brown", "\n", "fox" };
    EXPECT_EQ(StringUtils::Join(" ", test1), "The quick brown fox");
    EXPECT_EQ(StringUtils::Join(" and ", test2), "His and Hers and Yours and Mine");
    EXPECT_EQ(StringUtils::Join("a", test3), "testing");
    EXPECT_EQ(StringUtils::Join("a", test4), "");
    EXPECT_EQ(StringUtils::Join("", test5), "Thequickbrown\nfox");
    std::vector<std::string> PathComponents = { "", "Path", "To", "A", "Directory" };
    EXPECT_EQ(StringUtils::Join("/", PathComponents), "/Path/To/A/Directory");

    std::vector<std::string>  SentenceComponents =
    { "A","tougher","test","to","pass!" };
    EXPECT_EQ(StringUtils::Join(" ", SentenceComponents), "A tougher test to pass!");
}

TEST(StringUtilsTest, ExpandTabs) {
    EXPECT_EQ(StringUtils::ExpandTabs("testing\t", 3), "testing  ");
    EXPECT_EQ(StringUtils::ExpandTabs("01\t012\t0123\t01234"), "01  012 0123    01234");
    EXPECT_EQ(StringUtils::ExpandTabs("ab\nab\tcde\tfg\th", 5), "ab\nab   cde  fg   h");
    EXPECT_EQ(StringUtils::ExpandTabs("testing", 3), "testing");
    EXPECT_EQ(StringUtils::ExpandTabs("", 10), "");
    EXPECT_EQ(StringUtils::ExpandTabs("1\t2\t3\t4"), "1   2   3   4");
    EXPECT_EQ(StringUtils::ExpandTabs("1\t12\t123\t1234"), "1   12  123 1234");
    EXPECT_EQ(StringUtils::ExpandTabs("1234\t123\t12\t1"), "1234    123 12  1");
    EXPECT_EQ(StringUtils::ExpandTabs("1234\t123\t12\t1", 3), "1234  123   12 1");
    EXPECT_EQ(StringUtils::ExpandTabs("1234\t123\t12\t1", 0), "1234123121");
}

TEST(StringUtilsTest, EditDistance) {
    /*EXPECT_EQ(StringUtils::EditDistance("GAry", "May"), 3);
    EXPECT_EQ(StringUtils::EditDistance("GAry", "May", true), 2);
    EXPECT_EQ(StringUtils::EditDistance("", "World!"), 6);
    EXPECT_EQ(StringUtils::EditDistance("", ""), 0);
    EXPECT_EQ(StringUtils::EditDistance("Hello", "Hello"), 0);
    EXPECT_EQ(StringUtils::EditDistance("Hello", "World!"), 5);
    EXPECT_EQ(StringUtils::EditDistance("HeLLo", "World!", true), 5);
    EXPECT_EQ(StringUtils::EditDistance("HeLLo", "World!"), 6);
    EXPECT_EQ(StringUtils::EditDistance("1234", "1234"), 0);
    EXPECT_EQ(StringUtils::EditDistance("Test", "test"), 1);
    EXPECT_EQ(StringUtils::EditDistance("Test", "test", true), 0);
    EXPECT_EQ(StringUtils::EditDistance("12345", "52341"), 2);
    EXPECT_EQ(StringUtils::EditDistance("This is an example", "This is a sample"),
        3);
    EXPECT_EQ(StringUtils::EditDistance("int Var = Other + 3.4;", "int x = y + 3.4;"), 8);*/
}
