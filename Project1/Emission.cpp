/**
 * \file Emission.cpp
 *
 * \author Steven Kneiser
 */

#include "stdafx.h"
#include <algorithm>
#include <random>

#include "Emission.h"
#include "Pokemon.h"
#include "Bulbasaur.h"
#include "Pikachu.h"
#include "Charmander.h"
#include "Orbit.h"
#include "Item.h"

using namespace Gdiplus;
using namespace std;

const int InitialX = 200; ///< Initial X

const int InitialY = 200; ///< Initial Y

const int FrameDuration = 30; ///< Frame duration

 /**
  * Image name constructor
  *
  * \param orbit pointer to greater orbit
  * \param filename path to image
  */
CEmission::CEmission(COrbit *orbit)
{
	mOrbit = orbit;

	// Randomly set angular displacement (0 - 6)
	mAngularDisplacement = rand() % 100;

	// Randomly set angular velocity (1 - 4)
	mAngularVelocity = rand() % 4 + 1;

	// Randomly set distance (25 - 474)
	mRadius = rand() % 450 + 25;

	AddPikachu();
}


/**
 * Test this emission to see if it has been clicked on
 *
 * \param x X location on the orbit to test
 * \param y Y location on the orbit to test
 * \return true if clicked on
 */
bool CEmission::HitTest(double x, double y)
{
	double width = mEmissionImage->GetWidth();
	double height = mEmissionImage->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the center of the image.
	// Adding half the size makes x, y relative to the top corner of the image
	double testX = x - (double)GetX() + (double)width / 2;
	double testY = y - (double)GetY() + (double)height / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= width || testY >= height)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	auto format = mEmissionImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mEmissionImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}


/**
 * Update emission animation
 *
 * \param elapsed time elapsed
 */
void CEmission::Update(double elapsed)
{
	mAngularDisplacement += mAngularVelocity * elapsed;
}


/*
void CEmission::SpawnPokemon()
{
	// Make sample emissions
	for (int i = 0; i < 5; i++)
	{
		auto pika = std::make_shared<CPikachu>(this);
		auto bulb = std::make_shared<CBulbasaur>(this);
		auto mand = std::make_shared<CCharmander>(this);
		//mEmissions.push_back(pika);
		//mEmissions.push_back(bulb);
		//mEmissions.push_back(mand);
	}
}
*/

void CEmission::AddPikachu()
{
	auto pokemon = make_shared<CPikachu>(mOrbit);
	pokemon->SetLocation(InitialX, InitialY);
	mOrbit->Add(pokemon);
}

void CEmission::AddBulbasaur()
{
	auto pokemon = make_shared<CBulbasaur>(mOrbit);
	pokemon->SetLocation(InitialX, InitialY);
	mOrbit->Add(pokemon);
}

void CEmission::AddCharmander()
{
	auto pokemon = make_shared<CCharmander>(mOrbit);
	pokemon->SetLocation(InitialX, InitialY);
	mOrbit->Add(pokemon);
}

