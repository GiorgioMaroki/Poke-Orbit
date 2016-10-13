#include "stdafx.h"
#include "Orbit.h"
#include "Pikachu.h"
#include "Bulbasaur.h"
#include "Charmander.h"
#include <gdiplus.h>
#include <stdio.h>  
#include <math.h>  

using namespace Gdiplus;

#define PI 3.14159265

COrbit::COrbit()
{
}


COrbit::~COrbit()
{
}

/**
* Draw the game area
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

	// From here on you are drawing virtual pixels...

	//
	// And the circle so you can see how this works...
	//
	Pen pen(Color::Green);
	graphics->DrawArc(&pen, -radius, -radius, radius * 2, radius * 2, 0, 360);
}

void COrbit::Update(double elapsed)
{
	
	/*
	double PokeAngle = atan2(y, x) * 180 / PI;
	double PokeSin = sin(PokeAngle);
	double PokeCos = cos(PokeAngle);

	//needs to be multiplied by rads per sec and time elapsed
	double newX = PokeCos * x + PokeSin * y;
	double newY = -PokeSin * x + PokeCos * y;
	*/
}