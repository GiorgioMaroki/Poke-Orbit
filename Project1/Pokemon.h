/**
 * \file Pokemon.h
 *
 * \author Steven Kneiser
 *
 * Pokemon abstract base class
 */

#pragma once
#include "Emission.h"
#include "Orbiter.h"

/**
 * Abstract base class for Pokemon
 */
class CPokemon : public COrbiter
{
public:
	/// Default constructor
	CPokemon() = delete;
	
	/// Copy constructor (disable)
	CPokemon(const CPokemon &) = delete;

	/// Main constructor
	CPokemon(COrbit *orbit, const std::wstring &filename);

	/// Virtual destructor
	virtual ~CPokemon() {};

	/** Set the item location
	* \param x X location
	* \param y Y location */
	void SetLocation(double x, double y) { mX = x; mY = y; }


private:
	/// The orbit this emission is contained in
	COrbit *mOrbit;


	// Item location in the orbit
	double mX = 0; ///< X location for the center of the item
	double mY = 0; ///< Y location for the center of the item 
};
