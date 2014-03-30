 //
 // This file is part of Easylogging++ samples
 // PostPerformanceTrackingHandler sample
 //
 // Revision 1.0
 // @author mkhan3189
 //

#define _ELPP_HANDLE_POST_PERFORMANCE_TRACKING // we need this!
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP
void handler(const el::PerformanceTrackingData* data) {
    // ELPP_COUT is cout when not using unicode otherwise wcout
    ELPP_COUT << "I am from handler: " << data->blockName()->c_str() << " in " << *data->formattedTimeTaken() << std::endl;
}

int main(void) {

    TIMED_BLOCK(mainBlock, "main");

    el::Helpers::installPostPerformanceTrackingHandler(handler);

    {
        TIMED_SCOPE(timer, "my-block");
        for (int i = 0; i <= 500; ++i) {
            LOG(INFO) << "This is iter " << i;
        }
    } 
    LOG(INFO) << "By now, you should get performance result of above scope";

    return 0;
}
