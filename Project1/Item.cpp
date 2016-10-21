/**
* \file Item.cpp
*
* \author Giorgio Maroki
*/

#include "stdafx.h"
#include <string>
#include "Item.h"
#include "Orbit.h"

using namespace Gdiplus;
using namespace std;

/** Constructor
* \param orbit the orbit this item is a member of
*/
CItem::CItem(COrbit *orbit, const std::wstring &filename) :
	mOrbit(orbit)
{
	mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mItemImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}

/**
* Desctuctor
*/
CItem::~CItem() 
{
}

/**
 * Draw our item
 * \param graphics (The graphics context to draw on) 
 */
void CItem::Draw(Gdiplus::Graphics * graphics)
{
	double wid = mItemImage->GetWidth();
	double hit = mItemImage->GetHeight();

	graphics->DrawImage(mItemImage.get(), float(GetX() + wid / 2), float(GetY() - hit / 2),
		(float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
}



