#include "stdafx.h"
#include "Pokestop.h"
#include "Orbiter.h"
#include "Item.h"
#include "Orbit.h"

CPokestop::CPokestop(COrbit *orbit, const std::wstring & filename)
	:COrbiter(orbit, filename)
{


}

CPokestop::~CPokestop()
{
}

void CPokestop::Update(double elapsed)
{
}
