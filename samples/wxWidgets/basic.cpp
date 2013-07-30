
#include "easylogging++.h"
#include <wx/string.h>
#include <wx/list.h>


_INITIALIZE_EASYLOGGINGPP

WX_DECLARE_LIST(int, wxListInt);
WX_DEFINE_LIST(wxListInt);

int main(int argc, char** argv) {
 
    wxString mystring = "Hello EasyLogging++ support for wxWidgets";
//    LINFO << mystring; 


    wxListInt list1;
    int dummy[5];
    size_t i;

    for ( i = 0; i < WXSIZEOF(dummy); ++i )
        list1.Append(dummy + i);

//    LINFO << list1;
    return 0;
}
