/**
* \file Orbit.h
*
* \author Noah Hirvela & Giorgio Maroki
*
* Orbit Class
*/

#pragma once
#include "stdafx.h"
#include <map>
#include <memory>
#include <vector>

#include "Pokeball.h"
#include "Item.h"
#include "Emission.h"

class CEmission;

/**
 * Class that defines the PokeOrbit
 */
class COrbit 
{
public:
	// Default constructor
	COrbit();
	
	/// Destructor
	virtual ~COrbit() {};
	
	/// Draws orbit
	void COrbit::OnDraw(Gdiplus::Graphics *graphics, int width, int height);

	/// Updates orbit
	void COrbit::Update(double elapsed);

	/// Adds item to orbit
	void Add(const std::shared_ptr<CItem>& item);

	/// Move item to front
	void MovetoFront(std::shared_ptr<CItem> item);

	bool RemoveEmission(std::shared_ptr<CEmission> emission);

	/// Removes pokeball from orbit
	bool RemovePokeball(std::shared_ptr<CPokeball> ball);

	/// Clear all orbit items
	void Clear();

	/// Handles pokeball-catch event
	bool Caught(std::shared_ptr<CEmission> emission);

	/// Add a pokeball
	void AddPokeBall(std::shared_ptr<CItem> item);

	/// Handles click event
	virtual void Click(double x, double y);

private:
	double mCenterX; ///< Central X-coordinate
	double mCenterY; ///< Central Y-coordinate
	double mScale;  ///< X & Y scale

	/// Playing area width in virtual pixels
	const static int Width = 1400;

	/// Playing area height in virtual pixels
	const static int Height = 1100;

	/// Radius of the playing read in virtual pixels
	const static int Radius = 500;

	/// All of the emissions in our orbit
	std::vector<std::shared_ptr<CEmission> > mEmissions;

	/// All of the items to populate our orbit
	std::vector<std::shared_ptr<CItem> > mItems;

	/// Scoreboard values
	std::map<std::wstring, int> mScore;

	/// Pokeball
	std::vector<std::shared_ptr<CItem>> mBallCount;

	/// Total time elapsed
	double mTimeElapsed = 0;

	/// Time before next spawn
	double mNextSpawn = rand() % 8 + 3;
	
	/// Vector of moving pokeballs
	std::vector<std::shared_ptr<CPokeball>> mMovePokeballs;
};
