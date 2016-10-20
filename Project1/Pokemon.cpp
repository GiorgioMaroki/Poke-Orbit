/**
 * \file Pokemon.cpp
 *
 * \author Giorgio Maroki
 */

#include "stdafx.h"
#include "Pokemon.h"

/**
 * Main constructor
 *
 * \param orbit Orbit containing this pokemon
 * \param filename Image filename
 */
CPokemon::CPokemon(COrbit *orbit, const std::wstring &filename) : COrbiter(orbit, filename)
{

}
