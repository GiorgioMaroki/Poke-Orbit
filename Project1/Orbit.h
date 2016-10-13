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

private:
	/// Playing area width in virtual pixels
	const static int Width = 1400;

	/// Playing area height in virtual pixels
	const static int Height = 1100;

	/// Radius of the playing read in virtual pixels
	const static int Radius = 500;

	/// All of the emissions in our orbit
	std::vector<std::shared_ptr<CEmission> > mEmissions;
};

