/**
* \file Orbit.h
*
* \author Noah Hirvela & Giorgio Maroki
*
* Orbit Class
*/

#pragma once
#include "stdafx.h"
#include <memory>
#include <vector>

#include "Item.h"
#include "Emission.h"

class CEmission;

/**
 * Class that defines the PokeOrbit
 */
class COrbit 
{
public:
	COrbit();
	virtual ~COrbit();
	
	/// Draws orbit
	void COrbit::OnDraw(Gdiplus::Graphics *graphics, int width, int height);

	/// Updates orbit
	void COrbit::Update(double elapsed);

	void Add(const std::shared_ptr<CItem>& item);

	/// Move item to front
	void MovetoFront(std::shared_ptr<CItem> item);

	/// Removes item from orbit
	bool RemoveItem(std::shared_ptr<CItem> item);

	/// Clear all orbit items
	void Clear();

	/// Add a pokeball
	void AddPokeBall(std::shared_ptr<CItem> item);

private:
	/// Playing area width in virtual pixels
	const static int Width = 1400;

	/// Playing area height in virtual pixels
	const static int Height = 1100;

	/// Radius of the playing read in virtual pixels
	const static int Radius = 500;

	/// All of the emissions in our orbit
	std::vector<std::shared_ptr<CEmission> > mEmission;

	/// All of the items to populate our orbit
	std::vector<std::shared_ptr<CItem> > mItems;

	/// Scoreboard values
	std::vector<std::pair<std::shared_ptr<CItem>, int>> mScore;

	/// Pokeball
	std::vector<std::shared_ptr<CItem>> mPokeballs;

	/// Emitter
	CEmission *mEmitter;
};
