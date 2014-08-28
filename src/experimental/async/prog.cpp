
#include "async-logging.h"
#include "easylogging++.h"
#include "mymath.h"

_INITIALIZE_EASYLOGGINGPP
AsyncLogQueue logQueue;
AsyncDispatchWorker asyncDispatchWorker;

TIMED_SCOPE(benchmark, "benchmark");

int main(int argc, char *argv[])
{
    AsyncLogDispatchCallback::removeDefaultAndInstall();

    std::cout << "Starting program..." << std::endl;
    int MAX_LOOP = 10000;
    for (int i = 0; i <= MAX_LOOP; ++i) {
        LOG(INFO) << "Log message " << i;
        ELPP_COUT << "Added async log " << i << std::endl;
    }
    usleep(10000); // 10 sec
    for (int i = 0; i <= MAX_LOOP; ++i) {
        LOG(INFO) << "Log message PART 2 [" << i << "]";
        ELPP_COUT << "Added async log PART 2 [" << i << "]" << std::endl;
    }
    int result = MyMath::sum(1, 2);
    result = MyMath::sum(1, 3);
    usleep(10000); // 10 sec
    for (int i = 0; i <= MAX_LOOP; ++i) {
        LOG(INFO) << "Log message PART 3 [" << i << "]";
        ELPP_COUT << "Added async log PART 3" << "[" << i << "]" << std::endl;
    }
    return asyncDispatchWorker.clean();
}
