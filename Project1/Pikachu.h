/**
 * \file Pikachu.h
 *
 * \author Giorgio Maroki
 *
 * 
 */

#pragma once
#include <string>
#include "Pokemon.h"

 /**
 * Class that describes a Pikachu.
 */
class CPikachu : public CPokemon
{
public:
	CPikachu(COrbit *orbit);

	/// Default constructor (disabled)
	CPikachu() = delete;

	/// Default constructor (disabled)
	CPikachu(const CPikachu&) = delete;

	virtual ~CPikachu();

private:
	/// Pikachu velocity
	long const mVelocity = 10;
};