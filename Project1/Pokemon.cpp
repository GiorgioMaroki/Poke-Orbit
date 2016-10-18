/**
 * \file Pokemon.cpp
 *
 * \author Giorgio Maroki
 */

#include "stdafx.h"
#include "Pokemon.h"
#include "Orbit.h"
#include "Item.h"


CPokemon::CPokemon(COrbit *orbit, const std::wstring & filename)
	:COrbiter(orbit, filename)
{
}


CPokemon::~CPokemon()
{
}

void CPokemon::Update(double elapsed)
{
}


