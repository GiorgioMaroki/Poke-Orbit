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

 /** Class that describes a bulbasaur.
 */
class CBulbasaur : public CPokemon
{
public:
	CBulbasaur();
	virtual ~CBulbasaur();


	void ObtainBulbasaurInformation();

	/// This displays the animal information
	void DisplayPokemon();


private:



};
