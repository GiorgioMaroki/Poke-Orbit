/**
 * \file Pokestop.cpp
 *
 * \author Steven Kneiser
 */

#include "stdafx.h"
#include "Pokestop.h"

double CPokestop::TimerUpdate(double elapsed)
{
	mElapsed += abs(elapsed);
	return mElapsed;
}

/**
 * Update pokestop
 *
 * \param elapsed Time since last update
 */
void CPokestop::UpdateTime(double elapsed)
{
	mRefresh += abs(elapsed);

	// Used-pokestop timeout
	if (mUsed && mRefresh >= 15)
	{
		this->FlipState();
	}
}


/**
 * Handle click event
 *
 * \param orbitScore Score map to update
 */
void CPokestop::Click(std::map<std::wstring, int> &orbitScore)
{
	if (!mUsed)
	{
		// Add random number pokeballs
		if (orbitScore[L"pokeballs"] < 13)
		{
			orbitScore[L"pokeballs"] += 3;
		}

		// Reset timer
		mRefresh = 0;

		// Flip state
		this->FlipState();
	}
}


/**
 * Change pokestop active status
 */
void CPokestop::FlipState()
{
	mUsed = !mUsed;
	this->SetImage(mImages[mUsed]);
}


