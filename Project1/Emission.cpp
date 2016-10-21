/**
 * \file Emission.cpp
 *
 * \author Steven Kneiser
 */

#include "stdafx.h"
#include <algorithm>
#include <memory>
#include <random>
#include <time.h> 
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

const int xCenter = 550;
const int yCenter = 450;
const int xyCenter = 300;

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



void CEmission::SpawnPokemon()
{
	int randomNum = rand();
	int NumberOfPokemon = 3;

	if(randomNum % NumberOfPokemon == 0)
	{
		AddBulbasaur();
	}

	else if (randomNum % NumberOfPokemon == 1)
	{
		AddPikachu();
	}

	else if(randomNum % NumberOfPokemon == 2)
	{
		AddCharmander();
	}

}



void CEmission::GenerateRandomSpot()
{
	int x, y;
	bool c = false;
	while (!c)
	{
		x = mDisX(mRandom);
		y = mDisY(mRandom);

		if ((x*x) + (y*y) <= (xyCenter * xyCenter))
		{
			mX = xCenter + x;
			mY = yCenter + y;
			mRadius = sqrt((x*x) + (y*y));
			c = true;
		}
	}
}

std::shared_ptr<CItem> CEmission::CheckEmission(double elapsed)
{
	if (int(elapsed) >= (mTime + mPreviousEmission))
	{
		GenerateRandomSpot();
		if (mDisItem(mRandom) == 0)
		{
			auto item = make_shared<CBulbasaur>(mOrbit);
			item->SetAngle(mDisAng(mRandom));
			item->SetRadius(mRadius);
			mTime = mDisTime(mRandom);
			mPreviousEmission = int(elapsed);
			return item;
		}

		else if (mDisItem(mRandom) == 1)
		{
			auto item1 = make_shared<CPikachu>(mOrbit);
			item1->SetAngle(mDisAng(mRandom));
			item1->SetRadius(mRadius);
			mTime = mDisTime(mRandom);
			mPreviousEmission = int(elapsed);
			return item1;

		}

		else if (mDisItem(mRandom) == 2)
		{
			auto item2 = make_shared<CCharmander>(mOrbit);
			item2->SetAngle(mDisAng(mRandom));
			item2->SetRadius(mRadius);
			mTime = mDisTime(mRandom);
			mPreviousEmission = int(elapsed);
			return item2;

		}
		else
		{
			return nullptr;
		}
	}

	else
	{
		return nullptr;
	}
}

