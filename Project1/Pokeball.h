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

/**
 * Class that implements Pokeball
 */
class CPokeball
{
public:
	/// Default constructor (disabled)
	CPokeball() = delete;

	/// Copy constructor (disabled)
	CPokeball(const CPokeball &) = delete;

	/// Main constructor
	CPokeball::CPokeball(COrbit *orbit, double x, double y);
	
	/// Virtual destructor
	virtual ~CPokeball() {};

	/// Updates coordinates
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

	/// Draw pokeball graphic
	void Draw(Gdiplus::Graphics *graphics);

private:
	/// Pokeball image
	std::unique_ptr<Gdiplus::Bitmap> mPokeballImage;

	/// Orbit radius
	double mRadius = 0;

	/// Angular displacement in orbit
	double mAngularDisplacement;

	/// Ball velocity
	double mVelocity;

	/// Orbit containing ball
	COrbit *mOrbit;
};
