/*
 * Copyright (c) 2001, 2002, 2003 Gary R. Van Sickle.
 *
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *
 *     A copy of the GNU General Public License can be found at
 *     http://www.gnu.org/
 *
 * Written by Gary R. Van Sickle <g.r.vansickle@worldnet.att.net>
 *
 */

/* This is the implementation of the SplashPage class.  Since the splash page
 * has little to do, there's not much here. */

#include "setup_version.h"
#include "dialog.h"
#include "resource.h"
#include "splash.h"
#include "state.h"
#include "io_stream.h"
#include <cstdlib>
#include "UserSettings.h"
#include "getopt++/GetOption.h"
#include "getopt++/BoolOption.h"
#include "ini.h"
#include "msg.h"
#include "String++.h"

static BoolOption TestOption( false, 't', "test", "Use setup_test.ini" );
static BoolOption ExpressOption( true, 'A', "advanced", "Advanced install (as opposed to Express)" );
static BoolOption SafeModeOption( false, 'S', "safe", "Safe Mode (Skip some admin actions)" );

static int splash_mode = 0;

SplashSetting::SplashSetting()
{
  const char *m = UserSettings::instance().get("last-mode");
  if( !m )
    return;

  if ( !ExpressOption )
    splash_mode = IDC_ADVANCED;
  else
    splash_mode =
      casecompare( m, "Desktop" ) ? IDC_EXPRESS_D :
      casecompare( m, "Internet" ) ? IDC_EXPRESS_I :
      IDC_ADVANCED;
}

SplashSetting::~SplashSetting()
{
  UserSettings::instance().set("last-mode",
                               splash_mode == IDC_EXPRESS_D ? "Desktop" :
                               splash_mode == IDC_EXPRESS_I ? "Internet" :
                               "Advanced" );
}

static ControlAdjuster::ControlInfo SplashControlsInfo[] = {
  { IDC_SPLASH_TEXT,        CP_STRETCH,   CP_STRETCH },
  { IDC_EXPRESS_D,          CP_CENTERED,  CP_CENTERED },
  { IDC_EXPRESS_I,          CP_CENTERED,  CP_CENTERED },
  { IDC_ADVANCED,           CP_CENTERED,  CP_CENTERED },
  { 0, CP_LEFT, CP_TOP }
};

SplashPage::SplashPage ()
{
  sizeProcessor.AddControlInfo (SplashControlsInfo);
}

bool
SplashPage::Create ()
{
  return PropertyPage::Create (IDD_SPLASH);
}

long
SplashPage::OnNext()
{
  HWND h = GetHWND ();

  if (IsDlgButtonChecked (h, IDC_EXPRESS_D) == BST_CHECKED)
    {
      // add new global for control EXPRESS_DESKTOP INSTALL mode
      // int express_mode_option (state.cc) 
      splash_mode = IDC_EXPRESS_D;
      unattended_mode = unattended;
      express_mode_option = IDD_EXP_DPACKAGES;
    }
  else if (IsDlgButtonChecked (h, IDC_EXPRESS_I) == BST_CHECKED)
    {
      // add new global for control EXPRESS_DESKTOP_AND_INTERNET INSTALL mode
      // int express_mode_option (state.cc) 
      splash_mode = IDC_EXPRESS_I;
      unattended_mode = unattended;
      express_mode_option = IDD_EXP_IPACKAGES;
    }
  else
    {
      splash_mode = IDC_ADVANCED;
      unattended_mode = attended;
      express_mode_option = 0;
    }

  return IDD_SOURCE;
}

void
SplashPage::OnInit ()
{
  HWND h = GetHWND();

  std::string ver = "Setup.exe version ";
  ver += (setup_version[0] ? setup_version : "[unknown]");
  ver += is_64bit ? " (64 bit)" : " (32 bit)";
  SetDlgItemFont(IDC_VERSION, "Arial", 10, FW_BOLD);
  ::SetWindowText (GetDlgItem (IDC_VERSION), ver.c_str());
  makeClickable (IDC_SPLASH_URL, "http://osgeo4w.osgeo.org");

  test_mode = TestOption;
  safe_mode = SafeModeOption;

  if ( splash_mode )
    {
      CheckDlgButton (h, IDC_EXPRESS_D, splash_mode == IDC_EXPRESS_D ? BST_CHECKED : BST_UNCHECKED );
      CheckDlgButton (h, IDC_EXPRESS_I, splash_mode == IDC_EXPRESS_I ? BST_CHECKED : BST_UNCHECKED );
      CheckDlgButton (h, IDC_ADVANCED, splash_mode == IDC_ADVANCED ? BST_CHECKED : BST_UNCHECKED );
    }
  else if( !test_mode )
    {
      CheckDlgButton (h, IDC_EXPRESS_D, BST_CHECKED );
      CheckDlgButton (h, IDC_EXPRESS_I, BST_UNCHECKED );
      CheckDlgButton (h, IDC_ADVANCED, BST_UNCHECKED );
    }
  else
    {
      CheckDlgButton (h, IDC_EXPRESS_D, BST_UNCHECKED );
      CheckDlgButton (h, IDC_EXPRESS_I, BST_UNCHECKED );
      CheckDlgButton (h, IDC_ADVANCED, BST_CHECKED );
    }
}
