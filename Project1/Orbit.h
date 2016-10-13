/**
* \file Orbit.h
*
* \author Noah Hirvela
*
*
*/

#pragma once
class COrbit
{
public:
	COrbit();
	virtual ~COrbit();
	void COrbit::OnDraw(Gdiplus::Graphics *graphics, int width, int height);
	void COrbit::Update(double elapsed);
private:
	/// Playing area width in virtual pixels
	const static int Width = 1400;

	/// Playing area height in virtual pixels
	const static int Height = 1100;

	/// Radius of the playing read in virtual pixels
	const static int Radius = 500;
};

