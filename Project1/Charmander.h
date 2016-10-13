/**
 * \file Charmander.h
 *
 * \author Giorgio Maroki
 *
 * 
 */

#pragma once

/**
 * Class about the charmander pokemoon
 */
class CCharmander
{
public:
	CCharmander();
	virtual ~CCharmander();

private:
	/// Charmander velocity
	long const mVelocity = 30;
};
