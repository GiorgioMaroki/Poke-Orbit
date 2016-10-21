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

	//Overrides the base class so the pokemon get caught (Base class is false this is true)
	virtual bool IsPokemon() { return true; }

private:
	/// The orbit this emission is contained in
	COrbit *mOrbit;
};
