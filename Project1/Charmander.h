/**
 * \file Charmander.h
 *
 * \author Steven Kneiser
 *
 * Charmander class
 */

#pragma once
#include "Pokemon.h"

const std::wstring CharmanderImage(L"images/charmander.png"); ///< Charmander Image

/**
 * Class that describes a bulbasaur
 */
class CCharmander : public CPokemon
{
public:
	/// Default constructor (disabled)
	CCharmander() = delete;

	/// Default constructor (disabled)
	CCharmander(const CCharmander&) = delete;

	/// Main constructor
	CCharmander(COrbit *orbit) : CPokemon(orbit, CharmanderImage) {};

	/// Virtual destructor
	virtual ~CCharmander() {};

	/// Update the orbit's score map
	virtual void ChangeScore(std::map<std::wstring, int> &orbitScore) { orbitScore[L"charmander"]++; };
};
