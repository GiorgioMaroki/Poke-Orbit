#include "stdafx.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Orbit.h"
#include "Pikachu.h"
#include "Bulbasaur.h"
#include "Charmander.h"
#include "Pokemon.h"
#include "Emission.h"
#include "Item.h"
#include "Pokeball.h"
#include "Pokestop.h"

using namespace Gdiplus;
using namespace std; 

/// Trainer image filename
const std::wstring TrainerImageName(L"images/ash.png");

/// Sample emission image
const std::wstring RandomImageName(L"images/pikachu.png");

COrbit::COrbit()
{
	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	auto pokemon = make_shared<CItem>(this, L"images/bulbasaur.png");
	auto pokemon1 = make_shared<CItem>(this, L"images/pikachu.png");
	auto pokemon2 = make_shared<CItem>(this, L"images/charmander.png");
	std::pair<std::shared_ptr<CItem>, int>  poke(pokemon, 0);
	std::pair<std::shared_ptr<CItem>, int>  poke1(pokemon1, 0);
	std::pair<std::shared_ptr<CItem>, int>  poke2(pokemon2, 0);
	mScore.push_back(poke);
	mScore.push_back(poke1);
	mScore.push_back(poke2);

	// Start game with3 pokeballs 
	for (int i = 0; i < 3; i++)
	{
		auto pokeBall = make_shared<CItem>(this, L"images/pokeball.png");
		pokeBall->SetLocation(80, 80);
		this->AddPokeBall(pokeBall);
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

	mCenterX = xOffset;
	mCenterY = yOffset;


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

	//auto AshEmission = std::make_shared<CEmission>(this, TrainerImageName);

	// Draw the Emissions
	for (auto emission : mEmissions)
	{
		emission->Draw(graphics);
	}

	// Draw the items
	for (auto item : mItems)
	{
		item->Draw(graphics);
	}

	//Draw the scoreboard
	int pokeY = 220;
	int scoreY = 235;
	SolidBrush white(Color(255, 255, 255));
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 30);

	// Draw the score
	for (auto item : mScore)
	{
		(item.first)->SetLocation(530, -pokeY);
		(item.first)->Draw(graphics);

		wstring score;
		score = std::to_wstring(item.second);

		(*graphics).DrawString(score.c_str(), -1, &font, PointF((Gdiplus::REAL)720, (Gdiplus::REAL)-scoreY), &white);
		pokeY = pokeY + 115;
		scoreY = scoreY + 115;
	}

	int pokeballY = 300;
	for (auto item : mBallCount)
	{
		item->SetLocation(-700, -pokeballY);
		item->Draw(graphics);
		pokeballY = pokeballY + 70;
	}

	/// Moving pokeballs
	for (auto pokeball : mMovePokeballs)
	{
		pokeball->Draw(graphics);

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

	// add elapsed to total time elapsed
	mTimeElapsed += abs(elapsed);

	// Spawn items
	if (mTimeElapsed > mNextSpawn)
	{
		mTimeElapsed = 0;
		mNextSpawn = rand() % 6 + 3;

		switch (rand() % 4)
		{
		case 0:
			mEmissions.push_back(make_shared<CPikachu>(this));
			break;
		case 1:
			mEmissions.push_back(make_shared<CBulbasaur>(this));
			break;
		case 2:
			mEmissions.push_back(make_shared<CCharmander>(this));
			break;
		case 3:
			mEmissions.push_back(make_shared<CPokestop>(this));
			break;
		}
	}

	vector<shared_ptr<CPokeball> > toDelete;

	// Find out which pokeballs need to be deleted
	for (auto pokeball : mMovePokeballs)
	{
		pokeball->Update(elapsed);
		double radius = sqrt(pow(pokeball->GetX(), 2.0) + pow(pokeball->GetY(), 2.0));
		if (radius > Radius)
		{
			toDelete.push_back(pokeball);
		}
	}

	// Delete pokeballs
	for (auto ball : toDelete)
	{
		for (auto iter = mMovePokeballs.begin(); iter != mMovePokeballs.end();)
		{
			if ((*iter) == ball)
			{
				iter = mMovePokeballs.erase(iter);
			}
			else {
				++iter;
			}
		}
	}
	
}

// ADD FOR POKEMON
void COrbit::Add(const std::shared_ptr<CItem> &item) 
{
	mItems.push_back(item);
}

// ADD FOR POKEBALL
void COrbit::AddPokeBall(std::shared_ptr<CItem> item)
{
	mBallCount.push_back(item);
}

void COrbit::Click(double x, double y)
{
	auto pokeball = make_shared<CPokeball>(this, x - mCenterX, mCenterY - y);
	mMovePokeballs.push_back(pokeball);
}

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

/**
* See if this fish is eaten. We test it against the other fish
* and if it is over a Carp, it is eaten and ceases to exist.
* \param item Item we are testing
* \returns bool
*/
bool COrbit::Caught(std::shared_ptr<CEmission> item)
{
	for (auto other : mEmissions)
	{
		// Do not compare to ourselves
		if (other == item) {
			continue;
		}

		if (other->IsPokemon() &&
			other->HitTest((int)item->GetX(), (int)item->GetY()))
		{
			auto loc = find(begin(mEmissions), end(mEmissions), item);
			if (loc != end(mEmissions))
			{
				mEmissions.erase(loc);
			}

			return true;
		}

	}
	return false;
}

