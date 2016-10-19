/**
 * \file Orbiter.h
 *
 * \author Giorgio
 *
 * This class defines the movement for the Pokemon & Pokestops around the orbit
 * items in the orbit
 */

#pragma once
#include "Item.h"

class COrbiter :
	public CItem
{
public:
	/// Default constructor (disabled)
	COrbiter() = delete;

	/// Copy constructor (disable)
	COrbiter(const COrbiter &) = delete;
	virtual ~COrbiter();

	void Update(double elapsed);


	void ChangeSpeed(int SpeedX, int SpeedY);

protected:
	COrbiter(COrbit *orbit, const std::wstring &filename);


private:
	/// The orbit it is contained in
	COrbit *mOrbit;

	/// Path to image representation
	std::unique_ptr<Gdiplus::Bitmap> mOrbitImage;

	/// Displacement from center
	double mRadius;

	/// Current angular displacement (radians)
	double mAngularDisplacement;

	/// Angular Velocity
	double mAngularVelocity;

};

