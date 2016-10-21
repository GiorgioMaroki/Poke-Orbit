/**
* \file Pokeball.h
*
* \author Noah Hirvela
*
* Pokeball class
*/

#pragma once
#include "Item.h"

// Forward referrence
class COrbit;

class CPokeball
{
public:
	CPokeball() = delete;
	virtual ~CPokeball();
	CPokeball::CPokeball(COrbit *orbit, double x, double y);
	void Update(double elapsed);
	/**
	* The X location of the item
	*
	* \returns X location in pixels
	*/
	double GetX() const { return mRadius * cos(mAngularDisplacement); }

	/**
	* The Y location of the item
	*
	* \returns Y location in pixels
	*/
	double GetY() const { return mRadius * -sin(mAngularDisplacement); }

	void Draw(Gdiplus::Graphics *graphics);

private:
	std::unique_ptr<Gdiplus::Bitmap> mPokeballImage;
	double mRadius = 0;
	double mAngularDisplacement;
	double mVelocity;
	COrbit *mOrbit;
};
