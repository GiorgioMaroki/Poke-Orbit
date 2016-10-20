#pragma once

#include "Item.h"

/**
 * Class that implements Pokestop
 */
class CPokestop :public CItem
{
public:
	/// Default constructor (disabled)
	CPokestop() = delete;

	/// Copy constructor (disable)
	CPokestop(const CPokestop &) = delete;

	/// Image name cosntructor
	CPokestop(COrbit * orbit, const std::wstring & filename);

	/// Virtual destructor
	virtual ~CPokestop();

	/// Update Pokestop
	void Update(double elapsed);
};

