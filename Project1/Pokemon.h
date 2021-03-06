/**
 * \file Pokemon.h
 *
 * \author Steven Kneiser
 *
 * Pokemon abstract base class
 */

#pragma once
#include "Emission.h"

/**
 * Abstract base class for Pokemon
 */
class CPokemon : public CEmission
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

	/// Pokemon ...IS Pokemon
	bool IsPokemon() { return true; }
	
	/// Update the orbit's score map
	virtual void ChangeScore(std::map<std::wstring, int> &orbitScore) {};

private:
	/// The orbit this emission is contained in
	COrbit *mOrbit;
};
