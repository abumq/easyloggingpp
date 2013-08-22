#include <wx/list.h>
#include <wx/listimpl.cpp>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

WX_DECLARE_LIST(int, MyList);

WX_DEFINE_LIST(MyList);

// Following enables MyList to be log-friendly
ELPP_WX_ENABLED(MyList)

int main() {
    MyList list;
    list.Append(new int (17));
    LOG(INFO) << list;
}
