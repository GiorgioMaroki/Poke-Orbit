


#include "stdafx.h"
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
	// Make sample emission
	// std::shared_ptr<CEmission> emission(this, &RandomImageName);
	auto emission = std::make_shared<CEmission>(this, RandomImageName);
	mEmissions.push_back(emission);

	auto pokemon = make_shared<CItem>(this, L"images/bulbasaur.png");
	auto pokemon1 = make_shared<CItem>(this, L"images/pikachu.png");
	auto pokemon2 = make_shared<CItem>(this, L"images/charmander.png");
	std::pair<std::shared_ptr<CItem>, int>  poke(pokemon, 0);
	std::pair<std::shared_ptr<CItem>, int>  poke1(pokemon1, 0);
	std::pair<std::shared_ptr<CItem>, int>  poke2(pokemon2, 0);
	mScore.push_back(poke);
	mScore.push_back(poke1);
	mScore.push_back(poke2);


	for (int i = 0; i < 3; i++)
	{
		auto pokeBall = make_shared<CItem>(this, L"images/pokeball.png");
		pokeBall->SetLocation(80, 80);
		this->AddPokeBall(pokeBall);
	}


}


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

	//Draw the scoreboard
	int pokeY = 220;
	int scoreY = -20;
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

		(*graphics).DrawString(score.c_str(), -1, &font, PointF(720, -pokeY), &white);
		pokeY = pokeY + 115;
	}

	int pokeballY = 300;
	for (auto item : mPokeballs)
	{
		item->SetLocation(-700, -pokeballY);
		item->Draw(graphics);
		pokeballY = pokeballY + 70;

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

// ADD FOR POKEMON
void COrbit::Add(std::shared_ptr<CItem> item) 
{
	mItems.push_back(item);
}


// ADD FOR POKEBALL
void COrbit::AddPokeBall(std::shared_ptr<CItem> item)
{
	mPokeballs.push_back(item);
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

