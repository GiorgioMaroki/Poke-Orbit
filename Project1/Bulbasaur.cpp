 /**
 * \file Bulbasaur.cpp
 *
 * \author Giorgio Maroki
 *
 */


#include "stdafx.h"
#include <string>
#include "Bulbasaur.h"
#include "Pokemon.h"

using namespace Gdiplus;
using namespace std;


const wstring BulbasaurImage(L"images/bulbasaur.png");

/**
* Constructor.
*/
CBulbasaur::CBulbasaur(COrbit * orbit) :
	CPokemon(orbit, BulbasaurImage)
{

}

/**
* Destructor.
*/
CBulbasaur::~CBulbasaur()
{
}

