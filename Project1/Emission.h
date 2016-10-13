/**
 * \file Emission.h
 *
 * \author Steven Kneiser
 *
 * Emission class.
 */

#pragma once
#include "stdafx.h"
#include <memory>
#include <random>

// Forward referrence
class COrbit;

/**
 * Class that implements an Emission.
 */
class CEmission
{
public:
	/// Default constructor (disabled)
	CEmission() = delete;

	/// Copy constructor (disabled)
	CEmission(const CEmission &) = delete;

	/// Image path constructor
	CEmission(COrbit *orbit, const std::wstring &filename);

	/// Virtual destructor
	virtual ~CEmission() {};

	/**
	 * The X location of the item
	 *
	 * \returns X location in pixels
	 */
	double GetX() const { return mRadius * cos(mRotation); }

	/**
	 * The Y location of the item
	 *
	 * \returns Y location in pixels
	 */
	double GetY() const { return mRadius * -sin(mRotation); }

	/// Draw this item
	virtual void Draw(Gdiplus::Graphics *graphics);

	/// Test this emission to see if it has been clicked on
	virtual bool HitTest(double x, double y);

private:
	/// The orbit this emission is contained in
	COrbit *mOrbit;

	/// Angular Velocity
	double mAngularVelocity;

	/// Displacement from center
	double mRadius;

	/// Current rotation (radians)
	double mRotation;

	/// Path to image representation
	std::unique_ptr<Gdiplus::Bitmap> mEmissionImage;
};
