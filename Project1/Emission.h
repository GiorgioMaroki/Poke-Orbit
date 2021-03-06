/**
 * \file Emission.h
 *
 * \author Steven Kneiser & Giorgio Maroki
 *
 * Emission abstract base class
 */

#pragma once
#include "stdafx.h"
#include <random>
#include <string>
#include <memory>

#include "Item.h"
#include "Orbit.h"

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
	CEmission(COrbit *orbit, const std::wstring &filename);

	/// Virtual destructor
	virtual ~CEmission() {};

	/// Test this emission to see if it exists here
	bool HitTest(double x, double y);

	/// Updates emission animation
	void Update(double elapsed);

	/// Updates emission animation (overridable)
	virtual void UpdateTime(double elapsed) {};

	/// Updates the time until a pokestop dissapears
	virtual double TimerUpdate(double elapsed) { return 0; }


	/// Draws emission
	void Draw(Gdiplus::Graphics * graphics);

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

	/// Determine whether derived class is pokemon
	virtual bool IsPokemon() { return false; }

	/// Update the orbit's score map
	virtual void ChangeScore(std::map<std::wstring, int> &orbitScore) = 0;

	/// Handle click event
	virtual void Click(std::map<std::wstring, int> &orbitScore) {};

	/// Change Emission Image
	void SetImage(const std::wstring &filename);

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
