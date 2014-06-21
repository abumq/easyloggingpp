#ifndef RUNTIME_VMODULE_CONFIG_CHANGE_TEST_H
#define RUNTIME_VMODULE_CONFIG_CHANGE_TEST_H

TEST(RuntimeVmoduleConfigChangeTest, DynamicVmodule) {
    Configurations c;
    c.setGlobally(el::ConfigurationType::Format, "%datetime{%a %b %d, %H:%m} %msg");
    el::Loggers::reconfigureLogger(consts::kDefaultLoggerId, c);
    
    const char * c_sentinel = "RuntimeVmoduleConfigChangeTest Sentinel";
    const char * c_verbose2 = "Test at verbose = 2";
    std::string s_sentinel = BUILD_STR(getDate() << " " << c_sentinel << "\n");
    std::string s_verbose2 = BUILD_STR(getDate() << " " << c_verbose2 << "\n");

    // VLOG(2) not logged
    LOG(INFO) << c_sentinel;
    VLOG(2) << c_verbose2;
    EXPECT_EQ(s_sentinel, tail(1));
    
    // VLOG(2) logged
    ELPP->vRegistry()->setModules("*runtime-vmodule-config-change-test=3");
    LOG(INFO) << c_sentinel;
    VLOG(2) << c_verbose2;
    EXPECT_EQ(s_verbose2, tail(1));

    // Clear! VLOG(2) not logged
    ELPP->vRegistry()->clearModules();
    LOG(INFO) << c_sentinel;
    VLOG(2) << c_verbose2;
    EXPECT_EQ(s_sentinel, tail(1));

    // Reset back
    reconfigureLoggersForTest();
}


#endif // RUNTIME_VMODULE_CONFIG_CHANGE_TEST_H
