
#ifndef UTILITIES_TEST_H_
#define UTILITIES_TEST_H_

#include "test-helpers.h"

TEST(UtilitiesTest, SafeDelete) {
    int* i = new int(12);
    ASSERT_TRUE(i != nullptr);
    safeDelete(i);
    ASSERT_EQ(nullptr, i);
}

TEST(StringUtilsTest, WildCardMatch) {
    EXPECT_TRUE(Str::wildCardMatch("main", "m*"));
    EXPECT_TRUE(Str::wildCardMatch("mei.cpp", "m*cpp"));
    EXPECT_TRUE(Str::wildCardMatch("me.cpp", "me.cpp"));
    EXPECT_TRUE(Str::wildCardMatch("me.cpp", "m?.cpp"));
    EXPECT_TRUE(Str::wildCardMatch("m/f.cpp", "m??.cpp"));
    EXPECT_TRUE(Str::wildCardMatch("", "*"));
    EXPECT_FALSE(Str::wildCardMatch("", "?"));
    EXPECT_TRUE(Str::wildCardMatch("fastquery--and anything after or before", "*****************fast*****query*****"));
    EXPECT_FALSE(Str::wildCardMatch("some thing not matching", "some * matching all"));
}

TEST(StringUtilsTest, Trim) {
    std::string strLeftWhiteSpace(" string 1");
    std::string strLeftRightWhiteSpace(" string 2 ");
    std::string strRightWhiteSpace("string 3 ");
    std::string strLeftRightWhiteSpaceWithTabAndNewLine("  string 4 \t\n");
    EXPECT_EQ("string 1", Str::trim(strLeftWhiteSpace));
    EXPECT_EQ("string 2", Str::trim(strLeftRightWhiteSpace));
    EXPECT_EQ("string 3", Str::trim(strRightWhiteSpace));
    EXPECT_EQ("string 4", Str::trim(strLeftRightWhiteSpaceWithTabAndNewLine));
}

TEST(StringUtilsTest, StartsAndEndsWith) {
    EXPECT_TRUE(Str::startsWith("Dotch this", "Dotch"));
    EXPECT_FALSE(Str::startsWith("Dotch this", "dotch"));
    EXPECT_FALSE(Str::startsWith("    Dotch this", "dotch"));
    EXPECT_TRUE(Str::endsWith("Dotch this", "this"));
    EXPECT_FALSE(Str::endsWith("Dotch this", "This"));
}

TEST(StringUtilsTest, ReplaceAll) {
    std::string str = "This is cool";
    char replaceWhat = 'o';
    char replaceWith = '0';
    EXPECT_EQ("This is c00l", Str::replaceAll(str, replaceWhat, replaceWith));
}

TEST(StringUtilsTest, ToUpper) {
    std::string str = "This iS c0ol";
    EXPECT_EQ("THIS IS C0OL", Str::toUpper(str));
    str = "enabled = ";
    EXPECT_EQ("ENABLED = ", Str::toUpper(str));
}

TEST(StringUtilsTest, CStringEq) {
    EXPECT_TRUE(Str::cStringEq("this", "this"));
    EXPECT_FALSE(Str::cStringEq(nullptr, "this"));
    EXPECT_TRUE(Str::cStringEq(nullptr, nullptr));
}

TEST(StringUtilsTest, CStringCaseEq) {
    EXPECT_TRUE(Str::cStringCaseEq("this", "This"));
    EXPECT_TRUE(Str::cStringCaseEq("this", "this"));
    EXPECT_TRUE(Str::cStringCaseEq(nullptr, nullptr));
    EXPECT_FALSE(Str::cStringCaseEq(nullptr, "nope"));
}

TEST(StringUtilsTest, Contains) {
    EXPECT_TRUE(Str::contains("the quick brown fox jumped over the lazy dog", 'a'));
    EXPECT_FALSE(Str::contains("the quick brown fox jumped over the lazy dog", '9'));
}

TEST(StringUtilsTest, ReplaceFirstWithEscape) {
    std::string str = "Rolling in the deep";
    Str::replaceFirstWithEscape(str, "Rolling", "Swimming");
    EXPECT_EQ("Swimming in the deep", str);
    str = "this is great and this is not";
    Str::replaceFirstWithEscape(str, "this is", "that was");
    EXPECT_EQ("that was great and this is not", str);
    str = "%this is great and this is not";
    Str::replaceFirstWithEscape(str, "this is", "that was");
    EXPECT_EQ("this is great and that was not", str);
    str = "%datetime %level %log";
    Str::replaceFirstWithEscape(str, "%level", LevelHelper::convertToString(Level::Info));
    EXPECT_EQ("%datetime INFO %log", str);
}

#if _ELPP_OS_UNIX
TEST(OSUtilsTest, GetBashOutput) {
    const char* bashCommand = "echo 'test'";
    std::string bashResult = OS::getBashOutput(bashCommand);
    EXPECT_EQ("test", bashResult);
}
#endif

TEST(OSUtilsTest, GetEnvironmentVariable) {
    std::string variable = OS::getEnvironmentVariable("PATH", "pathResult");
    EXPECT_FALSE(variable.empty());
}

TEST(OSUtilsTest, ExtractPathFromFilename) {
    EXPECT_EQ("/this/is/path/on/unix/", File::extractPathFromFilename("/this/is/path/on/unix/file.txt"));
    EXPECT_EQ("C:\\this\\is\\path\\on\\win\\", File::extractPathFromFilename("C:\\this\\is\\path\\on\\win\\file.txt", "\\"));
}

TEST(LogFormatAndDateUtilsTest, ParseFormatTest) {

    LogFormat format(Level::Info, "%logger %thread");
    EXPECT_EQ("%logger %thread", format.userFormat());
    EXPECT_EQ("%logger %thread", format.format());
    EXPECT_EQ("", format.dateTimeFormat());

    LogFormat format2(Level::Info, "%logger %datetime{%d/%M/%Y %h:%m:%s  } %thread");
    EXPECT_EQ("%logger %datetime{%d/%M/%Y %h:%m:%s  } %thread", format2.userFormat());
    EXPECT_EQ("%logger %datetime %thread", format2.format());
    EXPECT_EQ("%d/%M/%Y %h:%m:%s  ", format2.dateTimeFormat());

    LogFormat format3(Level::Info, "%logger %datetime{%d/%M/%Y} %thread");
    EXPECT_EQ("%logger %datetime{%d/%M/%Y} %thread", format3.userFormat());
    EXPECT_EQ("%logger %datetime %thread", format3.format());
    EXPECT_EQ("%d/%M/%Y", format3.dateTimeFormat());

    LogFormat defaultFormat(Level::Info, "%logger %datetime %thread");
    EXPECT_EQ("%logger %datetime %thread", defaultFormat.userFormat());
    EXPECT_EQ("%logger %datetime %thread", defaultFormat.format());
    EXPECT_EQ("%d/%M/%Y %h:%m:%s,%g", defaultFormat.dateTimeFormat());

    LogFormat escapeTest(Level::Info, "%logger %datetime{%%H %H} %thread");
    EXPECT_EQ("%logger %datetime{%%H %H} %thread", escapeTest.userFormat());
    EXPECT_EQ("%logger %datetime %thread", escapeTest.format());
    EXPECT_EQ("%%H %H", escapeTest.dateTimeFormat());
    EXPECT_EQ("%%H %H", escapeTest.dateTimeFormat());
    EXPECT_TRUE(Str::startsWith(DateTime::getDateTime(escapeTest.dateTimeFormat().c_str()), "%H"));

    LogFormat defaultFormat2(Level::Info, "%logger %datetime %thread");
    EXPECT_EQ("%logger %datetime %thread", defaultFormat2.userFormat());
    EXPECT_EQ("%logger %datetime %thread", defaultFormat2.format());
    EXPECT_EQ("%d/%M/%Y %h:%m:%s,%g", defaultFormat2.dateTimeFormat());

    LogFormat defaultFormat4(Level::Verbose, "%logger %level-%vlevel %datetime %thread");
    EXPECT_EQ("%logger %level-%vlevel %datetime %thread", defaultFormat4.userFormat());
    EXPECT_EQ("%logger VER-%vlevel %datetime %thread", defaultFormat4.format());
    EXPECT_EQ("%d/%M/%Y %h:%m:%s,%g", defaultFormat4.dateTimeFormat());
}

#endif // UTILITIES_TEST_H_
