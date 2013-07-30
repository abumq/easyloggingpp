/***************************************************************
 * Name:      WxSampleMain.h
 * Purpose:   Defines Application Frame
 * Author:    mkhan3189 (mkhan3189 at gmail dot com)
 * Created:   2013-06-14
 * Copyright: mkhan3189 (http://www.icplusplus.com)
 * License:
 **************************************************************/

#ifndef WXSAMPLEMAIN_H
#define WXSAMPLEMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "WxSampleApp.h"


#include <wx/button.h>
#include <wx/statline.h>
class WxSampleDialog: public wxDialog
{
    public:
        WxSampleDialog(wxDialog *dlg, const wxString& title);
        ~WxSampleDialog();

    protected:
        enum
        {
            idBtnQuit = 1000,
            idBtnAbout
        };
        wxStaticText* m_staticText1;
        wxButton* BtnAbout;
        wxStaticLine* m_staticline1;
        wxButton* BtnQuit;

    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // WXSAMPLEMAIN_H
