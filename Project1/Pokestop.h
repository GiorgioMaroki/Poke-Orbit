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
	CPokestop(COrbit *orbit) : CEmission(orbit, PokestopImage) { mElapsed = 0; };

	/// Virtual destructor
	virtual ~CPokestop() {};

	/// Update Pokestop
	void UpdateTime(double elapsed);

	///  Update the orbit's score map
	void ChangeScore(std::map<std::wstring, int> &orbitScore) {};

	/// Handle click event
	void Click(std::map<std::wstring, int> &orbitScore);

	/// Change pokestop active status
	void FlipState();

private:
	COrbit *mOrbit; ///< orbit

	bool mUsed = false; ///< whether pokestop is active

	double mElapsed; ///< time since spawn
	double mRefresh; ///< time since last click

	/// Pokestop images
	std::wstring mImages[2] = { L"images/pokestop.png", L"images/pokestop-used.png" };
};

