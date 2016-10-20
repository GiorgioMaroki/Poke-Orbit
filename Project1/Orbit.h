/**
* \file Orbit.h
*
* \author Noah Hirvela
*
* Orbit Class.
*/

#pragma once
#include "stdafx.h"
#include <memory>
#include <vector>
#include "Item.h"
#include "Emission.h"

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

	void Add(std::shared_ptr<CItem> item);

	void AddPokeBall(std::shared_ptr<CItem> item);

	void MovetoFront(std::shared_ptr<CItem> item);

	bool RemoveItem(std::shared_ptr<CItem> item);

	void Clear();

	//void Add(std::shared_ptr<CItem> item);

private:
	/// Playing area width in virtual pixels
	const static int Width = 1400;

	/// Playing area height in virtual pixels
	const static int Height = 1100;

	/// Radius of the playing read in virtual pixels
	const static int Radius = 500;

	/// All of the emissions in our orbit
	std::vector<std::shared_ptr<CEmission> > mEmissions;

	std::vector<std::shared_ptr<CItem> > mItems; ///< All of the items to populate our orbit

	std::vector<std::pair<std::shared_ptr<CItem>, int>> mScore;

	std::vector<std::shared_ptr<CItem>> mPokeballs;
};

