/**
 * \file Pikachu.h
 *
 * \author Steven Kneiser
 *
 * Pikachu class
 */

#pragma once
#include "Pokemon.h"

const std::wstring PikachuImage(L"images/pikachu.png"); ///< Pikachu Image

/**
 * Class that implements a Pikachu
 */
class CPikachu : public CPokemon
{
public:
	/// Default constructor (disabled)
	CPikachu() = delete;
	
	/// Copy constructor (disabled)
	CPikachu(const CPikachu&) = delete;

	/// Main constructor
	CPikachu(COrbit *orbit) : CPokemon(orbit, PikachuImage) {};

	/// Virtual Destructor
	virtual ~CPikachu() {};

	/// Update the orbit's score map
	virtual void ChangeScore(std::map<std::wstring, int> &orbitScore) { orbitScore[L"pikachu"]++; };
};