
#include "MyMaths.h"

_INITIALIZE_EASYLOGGINGPP

el::base::type::StoragePointer sharedLoggingRepository() {
	return el::Helpers::storage();
}

namespace Math
{
    int MyMaths::add(int x, int y)
    {
        return x + y;
    }

	void MyMaths::logAdd(int x, int y) {
		LOG(INFO) << add(x, y);
	}
}