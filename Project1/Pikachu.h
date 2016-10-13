/**
 * \file Pikachu.h
 *
 * \author Giorgio Maroki
 *
 * 
 */

#pragma once

 /**
 * Class about the Pikachu pokemoon
 */
class CPikachu
{
public:
	CPikachu();
	virtual ~CPikachu();

private:
	/// Pikachu velocity
	long const mVelocity = 50;
};
