#ifndef TYPED_CONFIGURATIONS_TEST_H_
#define TYPED_CONFIGURATIONS_TEST_H_

#include "test.h"

const char* getConfFile(void) {
    const char* file = "/tmp/temp-test.conf";
    std::fstream confFile(file, std::fstream::out);
    confFile << " * GLOBAL:\n"
    << "    FILENAME             =  /tmp/my-test.log\n"
    << "    FORMAT               =  %datetime %level %msg\n"
    << "    MAX_LOG_FILE_SIZE        =  1\n"
    << "    TO_STANDARD_OUTPUT   =  TRUE\n"
    << "* DEBUG:\n"
    // NOTE escaped %level and %host below
    << "    FORMAT               =  %datetime %%level %level [%user@%%host] [%func] [%loc] %msg\n"
    // INFO and WARNING uses is defined by GLOBAL
    << "* ERROR:\n"
    << "    FILENAME             =  /tmp/my-test-err.log\n"
    << "    FORMAT               =  %%logger %%logger %logger %%logger %msg\n"
    << "    MAX_LOG_FILE_SIZE        =  10\n"
    << "* FATAL:\n"
    << "    FORMAT               =  %datetime %%datetime{%H:%m} %level %msg\n"
    << "* VERBOSE:\n"
    << "    FORMAT               =  %%datetime{%h:%m} %datetime %level-%vlevel %msg\n"
    << "* TRACE:\n"
    << "    FORMAT               =  %datetime{%h:%m} %%level %level [%func] [%loc] %msg\n";
    confFile.close();
    return file;
}

TEST(TypedConfigurationsTest, Initialization) {
    Configurations c(getConfFile());
    TypedConfigurations tConf(&c, ELPP->registeredLoggers()->logStreamsReference());

    EXPECT_TRUE(tConf.enabled(Level::Global));

    EXPECT_EQ("%datetime %level %msg", tConf.logFormat(Level::Info).userFormat());
    EXPECT_EQ("%datetime INFO  %msg", tConf.logFormat(Level::Info).format());
    EXPECT_EQ("%d/%M/%Y %h:%m:%s,%g", tConf.logFormat(Level::Info).dateTimeFormat());

    EXPECT_EQ("%datetime %%level %level [%user@%%host] [%func] [%loc] %msg", tConf.logFormat(Level::Debug).userFormat());
    EXPECT_EQ("%datetime %level DEBUG [%user@%%host] [%func] [%loc] %msg", tConf.logFormat(Level::Debug).format());
    EXPECT_EQ("%d/%M/%Y %h:%m:%s,%g", tConf.logFormat(Level::Debug).dateTimeFormat());

    // This double quote is escaped at run-time for %date and %datetime
    EXPECT_EQ("%datetime %%datetime{%H:%m} %level %msg", tConf.logFormat(Level::Fatal).userFormat());
    EXPECT_EQ("%datetime %%datetime{%H:%m} FATAL %msg", tConf.logFormat(Level::Fatal).format());
    EXPECT_EQ("%d/%M/%Y %h:%m:%s,%g", tConf.logFormat(Level::Fatal).dateTimeFormat());

    EXPECT_EQ("%datetime{%h:%m} %%level %level [%func] [%loc] %msg", tConf.logFormat(Level::Trace).userFormat());
    EXPECT_EQ("%datetime %level TRACE [%func] [%loc] %msg", tConf.logFormat(Level::Trace).format());
    EXPECT_EQ("%h:%m", tConf.logFormat(Level::Trace).dateTimeFormat());

    EXPECT_EQ("%%datetime{%h:%m} %datetime %level-%vlevel %msg", tConf.logFormat(Level::Verbose).userFormat());
    EXPECT_EQ("%%datetime{%h:%m} %datetime VER-%vlevel %msg", tConf.logFormat(Level::Verbose).format());
    EXPECT_EQ("%d/%M/%Y %h:%m:%s,%g", tConf.logFormat(Level::Verbose).dateTimeFormat());

    EXPECT_EQ("%%logger %%logger %logger %%logger %msg", tConf.logFormat(Level::Error).userFormat());
    EXPECT_EQ("%%logger %%logger %logger %logger %msg", tConf.logFormat(Level::Error).format());
    EXPECT_EQ("", tConf.logFormat(Level::Error).dateTimeFormat());
}

TEST(TypedConfigurationsTest, SharedFileStreams) {
    Configurations c(getConfFile());
    TypedConfigurations tConf(&c, ELPP->registeredLoggers()->logStreamsReference());
    // Make sure we have only two unique file streams for ALL and ERROR
    unsigned short lIndex = LevelHelper::kMinValid;
    std::fstream* prev = nullptr;
    LevelHelper::forEachLevel(lIndex, [&]() -> bool {
        if (prev == nullptr) {
            prev = tConf.fileStream(LevelHelper::castFromInt(lIndex));
        } else {
            if (LevelHelper::castFromInt(lIndex) == Level::Error) {
                EXPECT_NE(prev, tConf.fileStream(LevelHelper::castFromInt(lIndex)));
            } else {
                EXPECT_EQ(prev, tConf.fileStream(LevelHelper::castFromInt(lIndex)));
            }
        }
        return false;
    });
}

TEST(TypedConfigurationsTest, WriteToFiles) {
    Configurations c(getConfFile());
    TypedConfigurations tConf(&c, ELPP->registeredLoggers()->logStreamsReference());
    {
        EXPECT_TRUE(tConf.fileStream(Level::Info)->is_open());
        EXPECT_EQ("/tmp/my-test.log", tConf.filename(Level::Info));
        *tConf.fileStream(Level::Info) << "-Info";
        *tConf.fileStream(Level::Debug) << "-Debug";
        tConf.fileStream(Level::Debug)->flush();
        *tConf.fileStream(Level::Error) << "-Error";
        tConf.fileStream(Level::Error)->flush();
    }
    std::ifstream reader(tConf.filename(Level::Info), std::fstream::in);
    std::string line = std::string();
    std::getline(reader, line);
    EXPECT_EQ("-Info-Debug", line);
}

#endif /* TYPED_CONFIGURATIONS_TEST_H_ */
