/**
 * \file Orbit.h
 *
 * \author Noah Hirvela
 *
 *
 */

#pragma once
#include <memory>

#include "Emission.h"

class COrbit
{
public:
	COrbit();
	virtual ~COrbit();

	/// Draw the orbit
	void COrbit::OnDraw(Gdiplus::Graphics *graphics, int width, int height);

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
