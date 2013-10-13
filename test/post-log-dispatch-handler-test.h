#ifndef POST_LOG_DISPATCH_HANDLER_TEST_H
#define POST_LOG_DISPATCH_HANDLER_TEST_H

#include "test.h"

static std::vector<std::string> loggedMessages;

void postLogHandler(const LogMessage* msg) {
    loggedMessages.push_back(msg->message());
}

TEST(PostLogDispatchHandlerTest, Installation) {
    LOG(INFO) << "Log before handler installed";
    EXPECT_TRUE(loggedMessages.empty());
    
    // Install handler
    Helpers::installPostLogDispatchHandler(postLogHandler);
    LOG(INFO) << "Should be part of loggedMessages - 1";
    EXPECT_EQ(1, loggedMessages.size());
    std::string expectedMessage = "Should be part of loggedMessages - 1";
    EXPECT_EQ(expectedMessage, loggedMessages.at(0));
}

TEST(PostLogDispatchHandlerTest, Uninstallation) {
    
    // Uninstall handler
    Helpers::uninstallPostLogDispatchHandler();
    LOG(INFO) << "This is not in list";
    EXPECT_EQ(loggedMessages.end(), std::find(loggedMessages.begin(), loggedMessages.end(), "This is not in list"));
}

#endif // POST_LOG_DISPATCH_HANDLER_TEST_H
