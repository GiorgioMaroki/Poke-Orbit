/**
 * \file Pokemon.h
 *
 * \author Giorgio Maroki
 *
 * 
 */
#pragma once

#include "Orbiter.h"


/**
 * Base class for the pokemon
 */
class CPokemon : public COrbiter
{
public:
	/// Default constructor (disabled)
	CPokemon() = delete;
	
	/// Copy constructor (disable)
	CPokemon(const CPokemon &) = delete;

	virtual ~CPokemon();

	void Update(double elapsed);


protected:
	CPokemon(COrbit * orbit, const std::wstring &filename);


private:

};

