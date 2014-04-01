 //
 // This file is part of Easylogging++ samples
 // PostPerformanceTrackingHandler sample to customize performance output
 //
 // Revision 1.0
 // @author mkhan3189
 //

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

void handler(const el::PerformanceTrackingData* data) {
    if (data->firstCheckpoint()) { return; } // ignore first check point
    el::base::type::stringstream_t ss;
    ss << data->blockName()->c_str() << " took " <<  *data->formattedTimeTaken() << " to run";
    if (data->dataType() == el::PerformanceTrackingData::DataType::Checkpoint) {
        ss << " [CHECKPOINT ONLY] ";
    }
    CLOG(INFO, data->loggerId().c_str()) << ss.str();
}

int main(void) {

    el::Loggers::addFlag(el::LoggingFlag::DisablePerformanceTrackingDispatch);

    TIMED_BLOCK(mainBlock, "main");

    el::Helpers::installPostPerformanceTrackingHandler(handler);

    {
        TIMED_SCOPE(timer, "my-block");
        for (int i = 0; i <= 500; ++i) {
            // Spend time
            for (int j = 0; j < 10000; ++j) { std::string tmp; }
            if (i % 100 == 0) {
                timer.checkpoint(std::string(std::string("checkpoint at ") + std::to_string(static_cast<unsigned long long>(i))).c_str());
            }
        }
    } 
    LOG(INFO) << "By now, you should get performance result of above scope";

    return 0;
}
