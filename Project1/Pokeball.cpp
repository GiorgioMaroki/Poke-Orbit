#include "stdafx.h"
#include "Pokeball.h"
#include "Orbit.h"
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace Gdiplus;

const wstring PokeballImageName(L"images/pokeball.png");

CPokeball::CPokeball(COrbit *orbit, double x, double y)
{
	mPokeballImage = unique_ptr<Bitmap>(Bitmap::FromFile(PokeballImageName.c_str()));
	if (mPokeballImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += PokeballImageName;
		AfxMessageBox(msg.c_str());
	}

	
	mAngularDisplacement = atan2(y, x);

	double radius = sqrt(pow(x, 2.0) + pow(y, 2.0));

	mVelocity = radius*2;
}

CPokeball::~CPokeball()
{

}

void CPokeball::Update(double elapsed)
{
	mRadius += elapsed * mVelocity;
}

void CPokeball::Draw(Gdiplus::Graphics * graphics)
{
	double wid = mPokeballImage->GetWidth();
	double hit = mPokeballImage->GetHeight();

	graphics->DrawImage(mPokeballImage.get(), float((GetX() + wid / 2) - 50), float(GetY() - hit / 2),
		(float)mPokeballImage->GetWidth(), (float)mPokeballImage->GetHeight());
}

