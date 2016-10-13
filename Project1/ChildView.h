// ChildView.h : interface of the CChildView class
//
#include "Orbit.h"

#pragma once


// CChildView window

/**
* The child window our program draws in.
*/
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	/// OnPaint function to import all the objects onto the screen
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	/// An object that describes our orbit
	COrbit  mOrbit;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
private:
	long long mLastTime;    ///< Last time we read the timer
	double mTimeFreq;       ///< Rate the timer updates
	bool mFirstDraw = true;	///< Whether this is the first draw
};

