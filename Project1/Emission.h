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

	void SpawnPokemon();

	void GenerateRandomSpot();

	std::shared_ptr<COrbit> CheckEmission(double elapsed);


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

	std::mt19937_64 mRandom;

	/// Path to image representation
	std::unique_ptr<Gdiplus::Bitmap> mEmissionImage;

	/// Displacement from center
	double mRadius;

	/// Current angular displacement (radians)
	double mAngularDisplacement;

	/// Angular Velocity
	double mAngularVelocity;


	int mX;
	int mY;
	int mTime;
	int mPreviousEmission = 0;


	std::uniform_int_distribution<int> mDisTime{ 0, 8 };
	std::uniform_int_distribution<int> mDisX{ -300, 300 };
	std::uniform_int_distribution<int> mDisY{ -300, 300 };
	std::uniform_int_distribution<int> mDisItem{ 0, 6 };
	std::uniform_int_distribution<int> mDisAng{ 0, 361 };


};
