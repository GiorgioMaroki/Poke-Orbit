#include "stdafx.h"
#include "Orbiter.h"
#include "Item.h"
#include "Orbit.h"

using namespace Gdiplus;

COrbiter::COrbiter(COrbit * orbit, const std::wstring & filename) :
	CItem(orbit, filename)
{

	mOrbitImage = std::unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mOrbitImage->GetLastStatus() != Ok) {

		std::wstring msg(L"Failed to open.");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}

	mOrbit = orbit;
	mAngularDisplacement = 5;

	// Randomly set angular velocity (1 - 4)
	mAngularVelocity = 1; // rand() % 4 + 1;

						  // Randomly set distance(10 - 90)
	mRadius = 300; //rand() & 81 + 10;
}


COrbiter::~COrbiter()
{
}

void COrbiter::ChangeSpeed(int SpeedX, int SpeedY)
{
}



/**
* Update emission animation
*
* \param elapsed time elapsed
*/
void COrbiter::Update(double elapsed)
{
	mAngularDisplacement += mAngularVelocity * elapsed;
}