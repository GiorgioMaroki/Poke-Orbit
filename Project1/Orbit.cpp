#include "stdafx.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Orbit.h"
#include "Pikachu.h"
#include "Bulbasaur.h"
#include "Charmander.h"
#include "Emission.h"
#include "Item.h"

using namespace Gdiplus;
using namespace std; 

/// Trainer image filename
const std::wstring TrainerImageName(L"images/ash.png");

/// Sample emission image
const std::wstring RandomImageName(L"images/pikachu.png");

COrbit::COrbit()
{
	/* initialize random seed: */
	srand(time(NULL));

	// Make sample emissions
	for (int i = 0; i < 5; i++)
	{
		auto pika = std::make_shared<CPikachu>(this);
		auto bulb = std::make_shared<CBulbasaur>(this);
		auto mand = std::make_shared<CCharmander>(this);
		mEmissions.push_back(pika);
		mEmissions.push_back(bulb);
		mEmissions.push_back(mand);
	}
}


/**
 * Destructor
 */
COrbit::~COrbit()
{
}


/**
 * Draw the game area
 *
 * \param graphics The GDI+ graphics context to draw on
 * \param width Width of the client window
 * \param height Height of the client window
 */
void COrbit::OnDraw(Gdiplus::Graphics *graphics, int width, int height)
{
	// Fill the background with black
	SolidBrush brush(Color::Black);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	//
	// Automatic Scaling
	//
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	float scale = min(scaleX, scaleY);
	float radius = COrbit::Radius;

	float xOffset = width / 2.0f;
	float yOffset = height / 2.0f;

	graphics->TranslateTransform(xOffset, yOffset);
	graphics->ScaleTransform(scale, scale);
	
	// Draw the Trainer
	auto trainerImage = std::unique_ptr<Bitmap>(Bitmap::FromFile(TrainerImageName.c_str()));
	double tWidth = trainerImage->GetWidth();
	double tHeight = trainerImage->GetHeight();
		graphics->DrawImage(trainerImage.get(),
		float(0 - tWidth / 2), float(0 - tHeight / 2),
		(float)tWidth, (float)tHeight);

	// Draw the Orbit
	Pen pen(Color::Green);
	graphics->DrawArc(&pen, -radius, -radius, radius * 2, radius * 2, 0, 360);

	auto AshEmission = std::make_shared<CEmission>(this, TrainerImageName);

	// Draw the Emissions
	for (auto emission : mEmissions)
	{
		emission->Draw(graphics);
	}
}

/**
 * Updates orbit
 *
 * \param elapsed time elapsed
 */
void COrbit::Update(double elapsed)
{
	for (auto emission : mEmissions)
	{
		emission->Update(elapsed);
	}
}

// FOR POKEMON
void COrbit::Add(std::shared_ptr<CItem> item) 
{
	mItems.push_back(item);
}


// FOR POKEBALL





/** the item that is clicked is moved to the back of the vector
*\param item
*/


void COrbit::MovetoFront(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
		mItems.push_back(item);
	}
}



bool COrbit::RemoveItem(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
		return 1;
	}
	return 0;
}


/**
*  
* Clears data for the system/game & deletes everything
* 
*/


void COrbit::Clear()
{

	mItems.clear();
}

