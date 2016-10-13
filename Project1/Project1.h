
// Project1.h : main header file for the Project1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CProject1App:
// See Project1.cpp for the implementation of this class
//


/**
 * Project1 App Dervied from CWinApp
 */
class CProject1App : public CWinApp
{
public:
	CProject1App();


// Overrides
public:
	/// Virtual bool function for the initial instance
	virtual BOOL InitInstance();
	/// Virtual int function for the exit instance
	virtual int ExitInstance();

// Implementation
public:
	/// OnAppAbout for GDI+
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	/// Private member to import GDI plus
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	/// Private member to import GDI plus
	ULONG_PTR gdiplusToken;
};



extern CProject1App theApp;
