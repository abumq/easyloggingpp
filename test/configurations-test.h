#ifndef CONFIGURATIONS_TEST_H_
#define CONFIGURATIONS_TEST_H_

#include "test.h"

TEST(ConfigurationsTest, Set) {
    Configurations c;
    c.set(Level::Info, el::ConfigurationType::Enabled, "true");
    c.set(Level::Info, el::ConfigurationType::Enabled, "true");
    EXPECT_EQ(c.size(), 1);
    Configurations c2;
    c2 = c;
    c2.set(Level::Info, el::ConfigurationType::Enabled, "false");
    EXPECT_EQ(c.get(Level::Info, el::ConfigurationType::Enabled)->value(), "true");
    EXPECT_EQ(c2.get(Level::Info, el::ConfigurationType::Enabled)->value(), "false");
    EXPECT_EQ(c2.size(), 1);
}

TEST(ConfigurationsTest, HasConfiguration) {
    Configurations c;
    c.set(Level::Info, el::ConfigurationType::Enabled, "true");
    c.set(Level::Debug, el::ConfigurationType::Enabled, "false");
    c.set(Level::Info, el::ConfigurationType::Format, "%level: %log");

    EXPECT_TRUE(c.hasConfiguration(ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(ConfigurationType::Format));
    EXPECT_FALSE(c.hasConfiguration(ConfigurationType::Filename));
    EXPECT_FALSE(c.hasConfiguration(ConfigurationType::MaxLogFileSize));

    EXPECT_TRUE(c.hasConfiguration(Level::Debug, ConfigurationType::Enabled));
    EXPECT_FALSE(c.hasConfiguration(Level::Verbose, ConfigurationType::Format));
}

TEST(ConfigurationsTest, SetForAllLevels) {
    Configurations c;
    c.setGlobally(el::ConfigurationType::Enabled, "true");
    EXPECT_FALSE(c.hasConfiguration(Level::Global, ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(Level::Debug, ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(Level::Info, ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(Level::Warning, ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(Level::Error, ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(Level::Fatal, ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(Level::Verbose, ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(Level::Trace, ConfigurationType::Enabled));
}

TEST(ConfigurationsTest, ParsingFromFile) {
    std::fstream confFile("/tmp/temp-test.conf", std::fstream::out);
    confFile << " * GLOBAL:\n"
    << "    FORMAT               =  %datetime %level %log\n"
    << "* INFO:\n"
    // Following should be included in format because its inside the quotes
    << "    FORMAT               =  \"%datetime %level [%user@%host] [%func] [%loc] %log## This should be included in format\" ## This should be excluded\n"
    << "* DEBUG:\n"
    << "    FORMAT               =  %datetime %level [%user@%host] [%func] [%loc] %log ## Comment before EOL char\n"
    << "## Comment on empty line\n"
    // WARNING is defined by GLOBAL
    << "* ERROR:\n"
    << "    FORMAT               =  %datetime %level %log\n"
    << "* FATAL:\n"
    << "    FORMAT               =  %datetime %level %log\n"
    << "* VERBOSE:\n"
    << "    FORMAT               =  %datetime %level-%vlevel %log\n"
    << "* TRACE:\n"
    << "    FORMAT               =  %datetime %level [%func] [%loc] %log\n";
    confFile.close();

    Configurations c("/tmp/temp-test.conf", false, nullptr);
    EXPECT_FALSE(c.hasConfiguration(Level::Debug, ConfigurationType::Enabled));
    EXPECT_FALSE(c.hasConfiguration(Level::Global, ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(Level::Global, ConfigurationType::Format));
    EXPECT_TRUE(c.hasConfiguration(Level::Info, ConfigurationType::Format));
    EXPECT_EQ("%datetime %level %log", c.get(Level::Global, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level [%user@%host] [%func] [%loc] %log## This should be included in format", c.get(Level::Info, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level [%user@%host] [%func] [%loc] %log", c.get(Level::Debug, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level %log", c.get(Level::Warning, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level %log", c.get(Level::Error, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level %log", c.get(Level::Fatal, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level-%vlevel %log", c.get(Level::Verbose, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level [%func] [%loc] %log", c.get(Level::Trace, ConfigurationType::Format)->value());
}

TEST(ConfigurationsTest, ParsingFromText) {
    std::stringstream ss;
    ss << " * GLOBAL:\n"
    << "    FORMAT               =  %datetime{%d/%M/%Y %h:%m:%s,%g} %level %log\n"
    << "* DEBUG:\n"
    << "    FORMAT               =  %datetime %level [%user@%host] [%func] [%loc] %log\n"
    // INFO and WARNING uses is defined by GLOBAL
    << "* ERROR:\n"
    << "    FORMAT               =  %datetime %level %log\n"
    << "* FATAL:\n"
    << "    FORMAT               =  %datetime %level %log\n"
    << "* VERBOSE:\n"
    << "    FORMAT               =  %datetime %level-%vlevel %log\n"
    << "* TRACE:\n"
    << "    FORMAT               =  %datetime %level [%func] [%loc] %log\n";

    Configurations c;
    c.parseFromText(ss.str());
    EXPECT_FALSE(c.hasConfiguration(Level::Debug, ConfigurationType::Enabled));
    EXPECT_FALSE(c.hasConfiguration(Level::Global, ConfigurationType::Enabled));
    EXPECT_TRUE(c.hasConfiguration(Level::Global, ConfigurationType::Format));
    EXPECT_TRUE(c.hasConfiguration(Level::Info, ConfigurationType::Format));
    EXPECT_EQ("%datetime{%d/%M/%Y %h:%m:%s,%g} %level %log", c.get(Level::Global, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime{%d/%M/%Y %h:%m:%s,%g} %level %log", c.get(Level::Info, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime{%d/%M/%Y %h:%m:%s,%g} %level %log", c.get(Level::Warning, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level [%user@%host] [%func] [%loc] %log", c.get(Level::Debug, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level %log", c.get(Level::Error, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level %log", c.get(Level::Fatal, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level-%vlevel %log", c.get(Level::Verbose, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level [%func] [%loc] %log", c.get(Level::Trace, ConfigurationType::Format)->value());
}

TEST(ConfigurationsTest, ParsingFromTextWithEscape) {
    std::stringstream ss;
    ss << " * GLOBAL:\n"
    << "    FORMAT               =  %datetime{%d/%M/%Y %h:%m:%s,%g} %level %log\n"
    << "* DEBUG:\n"
    << "    FORMAT               =  \"%datetime %level [%user@%host] [%func] [%loc] \\\"inside quotes\\\" %log\"\n"
    // INFO and WARNING uses is defined by GLOBAL
    << "* ERROR:\n"
    << "    FORMAT               =  \"%datetime %level \\\"##hash##\\\" %log\"\n"
    << "* FATAL:\n"
    << "    FORMAT               =  %datetime %level ## Comment out log format specifier temporarily %log\n"
    << "* VERBOSE:\n"
    << "    FORMAT               =  %datetime %level-%vlevel %log\n"
    << "* TRACE:\n"
    << "    FORMAT               =  %datetime %level [%func] [%loc] %log\n";

    Configurations c;
    c.parseFromText(ss.str());
    EXPECT_EQ("%datetime{%d/%M/%Y %h:%m:%s,%g} %level %log", c.get(Level::Global, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime{%d/%M/%Y %h:%m:%s,%g} %level %log", c.get(Level::Info, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime{%d/%M/%Y %h:%m:%s,%g} %level %log", c.get(Level::Warning, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level [%user@%host] [%func] [%loc] \"inside quotes\" %log", c.get(Level::Debug, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level \"##hash##\" %log", c.get(Level::Error, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level", c.get(Level::Fatal, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level-%vlevel %log", c.get(Level::Verbose, ConfigurationType::Format)->value());
    EXPECT_EQ("%datetime %level [%func] [%loc] %log", c.get(Level::Trace, ConfigurationType::Format)->value());
}
#endif // CONFIGURATIONS_TEST_H_






























