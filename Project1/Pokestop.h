#pragma once

#include "Item.h"



class CPokestop :public CItem
{
public:
	/// Default constructor (disabled)
	CPokestop() = delete;

	/// Copy constructor (disable)
	CPokestop(const CPokestop &) = delete;

	virtual ~CPokestop();

	void Update(double elapsed);

	CPokestop(COrbit * orbit, const std::wstring & filename);

private:


};

