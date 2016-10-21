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

/**
*  Test to see if pokeball hits an object

* \param x X position to test
* \param y Y position to test
* \return true if hit.
*/
bool CItem::HitTest(int x, int y)
{
	double wid = mItemImage->GetWidth();
	double hit = mItemImage->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the center of the image.
	// Adding half the size makes x, y relative to the top corner of the image
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	auto format = mItemImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mItemImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}



