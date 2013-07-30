/***************************************************************
 * Name:      WxSampleApp.cpp
 * Purpose:   Code for Application Class
 * Author:    mkhan3189 (mkhan3189 at gmail dot com)
 * Created:   2013-06-14
 * Copyright: mkhan3189 (http://www.icplusplus.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "WxSampleApp.h"
#include "WxSampleMain.h"

IMPLEMENT_APP(WxSampleApp);

bool WxSampleApp::OnInit()
{
    
    WxSampleDialog* dlg = new WxSampleDialog(0L, _("wxWidgets Application Template"));
    
    dlg->Show();
    return true;
}
