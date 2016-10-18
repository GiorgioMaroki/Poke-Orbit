/**
 * \file Charmander.h
 *
 * \author Giorgio Maroki
 *
 * 
 */
#pragma once
#include <string>
#include "Pokemon.h"

 /**
 * Class that describes a charmander.
 */
class CCharmander : public CPokemon
{
public:
	CCharmander(COrbit *orbit);

	/// Default constructor (disabled)
	CCharmander() = delete;

	/// Default constructor (disabled)
	CCharmander(const CCharmander&) = delete;

	virtual ~CCharmander();

private:
	/// Bulbasaur velocity
	long const mVelocity = 10;
};
