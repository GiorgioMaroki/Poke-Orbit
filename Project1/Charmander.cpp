/**
* \file Charmander.cpp
*
* \author Giorgio Maroki
*
*/


#include "stdafx.h"
#include <string>
#include "Charmander.h"
#include "Pokemon.h"

using namespace Gdiplus;
using namespace std;


const wstring CharmanderImage(L"images/charmander.png");

/**
* Constructor.
*/
CCharmander::CCharmander(COrbit * orbit) :
	CPokemon(orbit, CharmanderImage)
{

}

/**
* Destructor.
*/
CCharmander::~CCharmander()
{
}
