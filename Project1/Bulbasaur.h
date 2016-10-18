/**
 * \file Bulbasaur.h
 *
 * \author Giorgio Maroki
 *
 * 
 */
#pragma once
#include <string>
#include "Pokemon.h"

 /**
  * Class that describes a bulbasaur.
  */
class CBulbasaur : public CPokemon
{
public:
	CBulbasaur(COrbit *orbit);

	/// Default constructor (disabled)
	CBulbasaur() = delete;

	/// Default constructor (disabled)
	CBulbasaur(const CBulbasaur&) = delete;

	virtual ~CBulbasaur();

private:
	/// Bulbasaur velocity
	long const mVelocity = 10;
};
