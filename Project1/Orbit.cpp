#include "stdafx.h"
#include "Orbit.h"
#include "Pikachu.h"
#include "Bulbasaur.h"
#include "Charmander.h"
#include "Emission.h"

using namespace Gdiplus;

/// Trainer image filename
const std::wstring TrainerImageName(L"images/ash.png");

/// Sample emission image
const std::wstring RandomImageName(L"images/slowbro.png");

COrbit::COrbit()
{
	// Make sample emission
	//std::shared_ptr<CEmission> emission(this, &RandomImageName);
	auto emission = std::make_shared<CEmission>(this, RandomImageName);
	mEmissions.push_back(emission);
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
	//graphics->DrawImage(TrainerImageName (can't be imagepath), 0, 0, asdfdvc);

	// Draw the Orbit
	Pen pen(Color::Green);
	graphics->DrawArc(&pen, -radius, -radius, radius * 2, radius * 2, 0, 360);

	// Draw the Emissions
	for (auto emission : mEmissions)
	{
		emission->Draw(graphics);
	}
}

/**
 * Updates orbit
 *
 * \param elapsed time elapsed
 */
void COrbit::Update(double elapsed)
{
}
