/**
* \file Pikachu.cpp
*
* \author Giorgio Maroki
*
*/


#include "stdafx.h"
#include <string>
#include "Pikachu.h"
#include "Pokemon.h"

using namespace Gdiplus;
using namespace std;


const wstring PikachuImage(L"images/pikachu.png");

/**
* Constructor.
*/
CPikachu::CPikachu(COrbit * orbit) :
	CPokemon(orbit, PikachuImage)
{

}

/**
* Destructor.
*/
CPikachu::~CPikachu()
{
}

