/**
 * \file Pokestop.h
 *
 * \author Steven Kneiser
 *
 * Pokestop class
 */

#pragma once

#include "Item.h"
#include "Emission.h"

 /// Pokestop image
const std::wstring PokestopImage(L"images/pokestop.png");

// Forward referrence
class COrbit;

/**
 * Class that implements Pokestop
 */
class CPokestop : public CEmission
{
public:
	/// Default constructor (disabled)
	CPokestop() = delete;

	/// Copy constructor (disable)
	CPokestop(const CPokestop &) = delete;

	/// Image name cosntructor
	CPokestop(COrbit *orbit) : CEmission(orbit, PokestopImage) {};

	/// Virtual destructor
	virtual ~CPokestop() {};

	/// Update Pokestop
	void Update(double elapsed) {};

	/// Test this emission to see if it exists here
	bool HitTest(double x, double y);

	///  Update the orbit's score map
	void ChangeScore(std::map<std::wstring, int> &orbitScore) {};

private:
	COrbit *mOrbit; ///< orbit
};

