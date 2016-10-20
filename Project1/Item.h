/**
 * \file Item.h
 *
 * \author Giorgio
 *
 *  Base class for any item in our orbit
 */

#pragma once


#include <string>
#include <memory>
//#include "XmlNode.h"

class COrbit;



/**
 *  Base class for any item in our aquarium
 */
class CItem
{
public:
	/// Default constructor (disable)
	CItem() = delete;

	/// Copy constructor (disable)
	CItem(const CItem &) = delete;

	/// Destructor
	virtual ~CItem();

	/** The x Location of the item 
	* \returns X location in pixels */
	double GetX() const { return mX; }

	/** The y Location of the item
	* \returns Y location in pixels */
	double GetY() const { return mY; }


	/** Set the item location
	* \param x X location
	* \param y Y location */
	void SetLocation(double x, double y) { mX = x; mY = y; }

	virtual void Draw(Gdiplus::Graphics *graphics);

	/// Handle updates for animation
	/// \param elapsed the time since the last update
	virtual void Update(double elapsed) {}

	/// Get the orbit this item is in
	/// \returns Orbit pointer
	COrbit *GetOrbit() { return mOrbit; }


	/** The height of the item 
	* \returns height in pixels */
	int ImageHeight() const { return mItemImage->GetHeight(); }

	/** The height of the item
	* \returns height in pixels */
	int ImageWidth() const { return mItemImage->GetWidth(); }

	/// Set the mirror status
	/// \param m New mirror flag
	void SetMirror(bool m) { mMirror = m;  }


protected:
	/** Set the item in the orbit
	* \param *orbit the obj in aquarium
	* \param &filename the file in the aquarium obj selected in the 1st pointer */
	CItem(COrbit *orbit, const std::wstring &filename);


private:
	/// The orbit this item is contained in
	COrbit *mOrbit;

	// Item location in the orbit
	double mX = 0; ///< X location for the center of the item
	double mY = 0; ///< Y location for the center of the item 

	/// Vertical reflection for turning around
	bool mMirror = false;

	/// The image of the item in the orbit
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

};

