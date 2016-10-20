/**
 * \file Bulbasaur.h
 *
 * \author Steven Kneiser
 *
 * Bulbasaur class
 */

#pragma once
#include "Pokemon.h"

const std::wstring BulbasaurImage(L"images/bulbasaur.png"); ///< Bulbasaur image

/**
 * Class that implements a bulbasaur
 */
class CBulbasaur : public CPokemon
{
public:
	/// Default constructor (disabled)
	CBulbasaur() = delete;

	/// Default constructor (disabled)
	CBulbasaur(const CBulbasaur&) = delete;

	/// Main constructor
	CBulbasaur(COrbit *orbit) : CPokemon(orbit, BulbasaurImage) {};

	/// Virtual destructor
	virtual ~CBulbasaur() {};
};
