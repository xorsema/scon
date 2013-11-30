/*
    The MIT License (MIT)

    Copyright (c) 2013 Max Rose

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

    This file is part of scon.
*/
#include <SFML\Graphics.hpp>
#include "Cell.h"

bool CellGrid::isCellAlive( int x, int y ) const 
{
	return mGrid[ ( x * mWidth ) + y ];
}

bool CellGrid::isCellAlive( sf::Vector2i v ) const
{
	return isCellAlive( v.x, v.y );
}

void CellGrid::setCellState( int x, int y, bool state )
{
	mGrid[ ( x * mWidth ) + y ] = state;
}

void CellGrid::setNextCellState( int x, int y, bool state )
{
	mGridNext[ ( x * mWidth ) + y ] = state;
}

int CellGrid::getNumLiveNeighbors( int px, int py )
{
	int ln = ( isCellAlive( px, py ) ) ? -1 : 0;

	for( int x = px - 1, xc = 0; xc < 3; xc++, x++ )
	{
		for( int y = py - 1, yc = 0; yc < 3; yc++, y++ )
		{
			if( isValidPos( x, y ) && isCellAlive( x, y ) )
			{
				ln++;
			}
		}
	}

	return ln;
}

void CellGrid::iterateCell( int x, int y )
{
	int ln = getNumLiveNeighbors( x, y );

	if( isCellAlive( x, y ) )
	{
		if( ln < 2 )
			setNextCellState( x, y, false );
		else if( ln == 2 || ln == 3 )
			setNextCellState( x, y, true ); 
		else if( ln > 3 )
			setNextCellState( x, y, false );
	}
	else
	{
		if( ln == 3 )
			setNextCellState( x, y, true );
	}
}

CellGrid::CellGrid( int w, int h )
{
	mWidth = w;
	mHeight = h;

	mGrid = new bool[ mWidth * mHeight ];
	memset( mGrid, 0, mWidth * mHeight * sizeof(bool) );

	mGridNext = new bool[ mWidth * mHeight ];
	memset( mGridNext, 0, mWidth * mHeight * sizeof(bool) );
}

CellGrid::~CellGrid()
{
	delete [] mGrid;
	delete [] mGridNext;
}

bool CellGrid::isValidPos( int x, int y )
{
	return (
		x >= 0 && x < mWidth &&
		y >= 0 && y < mHeight );
}

void CellGrid::iterate( int count )
{
	for( int c = 0; c < count; c++ )
	{
		for( int i = 0; i < mWidth; i++ )
		{
			for( int j = 0; j < mHeight; j++ )
			{
				iterateCell( i, j );
			}
		}

		memcpy( mGrid, mGridNext, sizeof(bool) * mWidth * mHeight );
	}
}

void CellGrid::draw( sf::RenderWindow& w, float cellSize, float cellSpacing, sf::Color deadColor, sf::Color aliveColor, sf::Vector2f offset )
{
	sf::RectangleShape s;

	s.setSize( sf::Vector2f( cellSize, cellSize ) );

	for( int i = 0; i < mWidth; i++ )
	{
		for( int j = 0; j < mHeight; j++ )
		{
			if( isCellAlive( i, j ) )
				s.setFillColor( aliveColor );
			else 
				s.setFillColor( deadColor );

			s.setPosition( sf::Vector2f( i * ( cellSize + cellSpacing), j * ( cellSize + cellSpacing) ) + offset );

			w.draw( s );
		}
	}
}
