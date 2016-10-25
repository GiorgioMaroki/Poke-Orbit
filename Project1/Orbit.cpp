#include "stdafx.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iterator>

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

	// Populate the score map
	mScore[L"pokeballs"] = 3;
	mScore[L"pikachu"] = 0;
	mScore[L"bulbasaur"] = 0;
	mScore[L"charmander"] = 0;

	// Start with one pokestop & one pokemon
	mEmissions.push_back(make_shared<CPokestop>(this));
	
	switch (rand() % 3)
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
	}
	
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

	mScale = scale;
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

	// Draw the pokemon for score
	auto bulbasaurItem = make_shared<CItem>(this, L"images/bulbasaur.png");
	bulbasaurItem->SetLocation(530, -220);
	bulbasaurItem->Draw(graphics);

	auto pikachuItem = make_shared<CItem>(this, L"images/pikachu.png");
	pikachuItem->SetLocation(530, -335);
	pikachuItem->Draw(graphics);

	auto charmanderItem = make_shared<CItem>(this, L"images/charmander.png");
	charmanderItem->SetLocation(530, -450);
	charmanderItem->Draw(graphics);
	
	/// Draw the Score
	std::wstring bulbasaurScore = std::to_wstring(mScore[L"bulbasaur"]);
	(*graphics).DrawString(bulbasaurScore.c_str(), -1, &font, PointF((Gdiplus::REAL)720, (Gdiplus::REAL) - 220), &white);

	std::wstring pikachuScore = std::to_wstring(mScore[L"pikachu"]);
	(*graphics).DrawString(pikachuScore.c_str(), -1, &font, PointF((Gdiplus::REAL)720, (Gdiplus::REAL) - 335), &white);

	std::wstring charmanderScore = std::to_wstring(mScore[L"charmander"]);
	(*graphics).DrawString(charmanderScore.c_str(), -1, &font, PointF((Gdiplus::REAL)720, (Gdiplus::REAL) - 450), &white);

	int pokeballY = -450;
	for (int _ = 0; _ < mScore[L"pokeballs"]; _++)
	{
		auto pokeball = make_shared<CItem>(this, L"images/pokeball.png");
		pokeball->SetLocation(-700, pokeballY);
		pokeball->Draw(graphics);
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
	vector<shared_ptr<CEmission> > Deletes;
	for (auto emission : mEmissions)
	{
		if (emission->IsPokemon())
		{
			emission->Update(elapsed);
		}
		else if (!(emission->IsPokemon()))
		{
			emission->Update(elapsed);
			emission->UpdateTime(elapsed);
			double TotalTime = abs(emission->TimerUpdate(elapsed));
			if (TotalTime > 60)
			{
				Deletes.push_back(emission);
			}
		}
	}
	for (auto emission : Deletes)
	{
		RemoveEmission(emission);
	}

	// add elapsed to total time elapsed
	mTimeElapsed += abs(elapsed);

	// Spawn items
	if (mTimeElapsed > mNextSpawn)
	{
		mTimeElapsed = 0;
		mNextSpawn = rand() % 2 + 3;

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

	// Check for collisions
	vector<std::shared_ptr<CEmission>> toDeleteEmission;
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

		for (auto emission : mEmissions)
		{
			if (emission->IsPokemon() && emission->HitTest(pokeball->GetX(), pokeball->GetY()))
			{
				emission->ChangeScore(mScore);
				toDeleteEmission.push_back(emission);
				toDelete.push_back(pokeball);
			}
		}
	}

	// Delete pokeballs & collisions
	for (auto emission : toDeleteEmission)
	{
		this->Caught(emission);
	}

	for (auto ball : toDelete)
	{
		this->RemovePokeball(ball);
		/*	for (auto iter = mMovePokeballs.begin(); iter != mMovePokeballs.end();)
		{
			if ((*iter) == ball)
			{
				iter = mMovePokeballs.erase(iter);
			}
			else {
				++iter;
			}
		}*/
	}
	
}


/**
 * Add item to orbit
 *
 * \param item Item to add
 */
void COrbit::Add(const std::shared_ptr<CItem> &item) 
{
	mItems.push_back(item);
}


/**
 * Add pokeball to orbit
 *
 * \param pokeball Pokeball to add 
 */
void COrbit::AddPokeBall(std::shared_ptr<CItem> pokeball)
{
	mBallCount.push_back(pokeball);
}


/**
 * Simulate click event in orbit
 *
 * \param x X-coordinate clicked
 * \param y Y-coordinate clicked
 */
void COrbit::Click(double x, double y)
{
	bool pokestopClicked = false;
	for (auto emission : mEmissions)
	{
		if (!emission->IsPokemon()) {

			if (emission->HitTest((x - mCenterX) / mScale, (y - mCenterY) / mScale)) {
				emission->Click(mScore);
				pokestopClicked = true;
			}
		}
	}

	if (!pokestopClicked && mScore[L"pokeballs"])
	{
		auto pokeball = make_shared<CPokeball>(this, x - mCenterX, mCenterY- y);
		mMovePokeballs.push_back(pokeball);
		mScore[L"pokeballs"]--;
	}
}


/**
 * Move item in orbit to front
 *
 *\param item Item to move to front
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


/**
 * Removes emission from orbit
 *
 * \param emission Emission to remove from orbit
 * \returns true Whether item is removed
 */
bool COrbit::RemoveEmission(std::shared_ptr<CEmission> emission)
{
	auto loc = find(begin(mEmissions), end(mEmissions), emission);
	if (loc != end(mEmissions))
	{
		mEmissions.erase(loc);
		return true;
	}
	return false;
}


/**
 * Removes pokeball from orbit
 *
 * \param ball Pokeball to remove
 * \returns true Whether ball is removed
 */
bool COrbit::RemovePokeball(std::shared_ptr<CPokeball> ball)
{
	auto loc = find(begin(mMovePokeballs), end(mMovePokeballs), ball);
	if (loc != end(mMovePokeballs))
	{
		mMovePokeballs.erase(loc);
		return true;
	}
	return false;
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
		if (other->IsPokemon())
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

