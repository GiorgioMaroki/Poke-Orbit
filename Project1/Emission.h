/**
 * \file Emission.h
 *
 * \author Steven Kneiser
 *
 * Emission abstract base class
 */

#pragma once


#include "stdafx.h"
#include <memory>
#include <random>
#include <string>

// Forward reference
class COrbit;

/**
 * Abstract base class that implements an Emission
 */
class CEmission
{
public:
	/// Default constructor (disabled)
	CEmission() = delete;

	/// Copy constructor (disabled)
	CEmission(const CEmission &) = delete;

	/// Image name constructor
	CEmission(COrbit *orbit);

	/// Virtual destructor
	virtual ~CEmission() {};

	/// Test this emission to see if it has been clicked on
	bool HitTest(double x, double y);

	/// Updates emission animation
	void Update(double elapsed);

	void AddPikachu();

	void AddBulbasaur();

	void AddCharmander();


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

private:
	/// The orbit this emission is contained in
	COrbit *mOrbit;

	/// Path to image representation
	std::unique_ptr<Gdiplus::Bitmap> mEmissionImage;

	/// Displacement from center
	double mRadius;

	/// Current angular displacement (radians)
	double mAngularDisplacement;

	/// Angular Velocity
	double mAngularVelocity;
};
