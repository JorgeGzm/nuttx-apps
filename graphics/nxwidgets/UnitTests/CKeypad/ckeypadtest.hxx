/////////////////////////////////////////////////////////////////////////////
// apps/graphics/nxwidgets/UnitTests/CKeypad/ckeypadtest.hxx
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed to the Apache Software Foundation (ASF) under one or more
// contributor license agreements.  See the NOTICE file distributed with
// this work for additional information regarding copyright ownership.  The
// ASF licenses this file to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance with the
// License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
// License for the specific language governing permissions and limitations
// under the License.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPS_GRAPHICS_NXWIDGETS_UNITTESTS_CKEYPAD_CKEYPADTEST_HXX
#define __APPS_GRAPHICS_NXWIDGETS_UNITTESTS_CKEYPAD_CKEYPADTEST_HXX

/////////////////////////////////////////////////////////////////////////////
// Included Files
/////////////////////////////////////////////////////////////////////////////

#include <nuttx/config.h>

#include <nuttx/init.h>
#include <cstdio>
#include <semaphore.h>
#include <debug.h>

#include <nuttx/nx/nx.h>

#include "graphics/nxwidgets/nxconfig.hxx"
#include "graphics/nxwidgets/cwidgetcontrol.hxx"
#include "graphics/nxwidgets/ccallback.hxx"
#include "graphics/nxwidgets/cbgwindow.hxx"
#include "graphics/nxwidgets/cnxserver.hxx"
#include "graphics/nxwidgets/cnxfont.hxx"
#include "graphics/nxwidgets/cnxstring.hxx"
#include "graphics/nxwidgets/ctextbox.hxx"
#include "graphics/nxwidgets/ckeypad.hxx"

/////////////////////////////////////////////////////////////////////////////
// Definitions
/////////////////////////////////////////////////////////////////////////////
// Configuration ////////////////////////////////////////////////////////////

#ifndef CONFIG_HAVE_CXX
#  error "CONFIG_HAVE_CXX must be defined"
#endif

#ifndef CONFIG_CKEYPADTEST_BGCOLOR
#  define CONFIG_CKEYPADTEST_BGCOLOR CONFIG_NXWIDGETS_DEFAULT_BACKGROUNDCOLOR
#endif

// This is the size of the keypad

#define KEYPAD_NROWS    7
#define KEYPAD_NCOLUMNS 4

/////////////////////////////////////////////////////////////////////////////
// Public Classes
/////////////////////////////////////////////////////////////////////////////

using namespace NXWidgets;

class CKeypadTest : public CNxServer
{
private:
  CWidgetControl     *m_widgetControl;  // The widget control for the window
  CBgWindow          *m_bgWindow;       // Background window instance
  CTextBox           *m_textbox;        // TextBox to show the key presses
  nxgl_coord_t        m_buttonWidth;    // The width of one button
  nxgl_coord_t        m_buttonHeight;   // The height of one button
  nxgl_coord_t        m_displayHeight;  // The height of the display

  // Pick size of the display

  void setDisplaySize(void);

  // Start with left text alignment.  When the text reaches the right sice
  // of the text box, switch to right text alignment.

  void reverseAlignment(void);

  // Create a CTextBox instance so that we can see the keypad output

  CTextBox *createTextBox(void);

public:

  // Constructor/destructors

  CKeypadTest();
  ~CKeypadTest();

  // Initializer/unitializer.  These methods encapsulate the basic steps for
  // starting and stopping the NX server

  bool connect(void);
  void disconnect(void);

  // Create a window.  This method provides the general operations for
  // creating a window that you can draw within.
  //
  // Those general operations are:
  // 1) Create a dumb CWigetControl instance
  // 2) Pass the dumb CWidgetControl instance to the window constructor
  //    that inherits from INxWindow.  This will "smarten" the CWidgetControl
  //    instance with some window knowlede
  // 3) Call the open() method on the window to display the window.
  // 4) After that, the fully smartened CWidgetControl instance can
  //    be used to generate additional widgets by passing it to the
  //    widget constructor

  bool createWindow(void);

  // Create a CKeypad instance.  This method will show you how to create
  // a CKeypad widget

  CKeypad *createKeypad(void);

  // Draw the keypad.  This method illustrates how to draw the CKeypad widget.

  void showKeypad(CKeypad *keypad);

  // Perform a simulated mouse click on a button in the array.  This method injects
  // the mouse click through the NX hierarchy just as would real mouse
  // hardware.

  void click(CKeypad *keypad, int column, int row);

  // The counterpart to click.  This simulates a button release through
  // the same mechanism.

  void release(CKeypad *keypad, int column, int row);

  // Widget events are normally handled in a model loop (by calling goModel()).
  // However, for this case we know when there should be press and release
  // events so we don't have to poll.  We can just perform a one pass poll
  // then check if the event was processed corredly.

  void poll(CKeypad *keypad);
};

/////////////////////////////////////////////////////////////////////////////
// Public Data
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Public Function Prototypes
/////////////////////////////////////////////////////////////////////////////

#endif // __APPS_GRAPHICS_NXWIDGETS_UNITTESTS_CKEYPAD_CKEYPADTEST_HXX
