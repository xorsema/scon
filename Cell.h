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
#pragma once

class CellGrid
{
public:
	CellGrid( int = 512, int = 512 );
	~CellGrid();
	bool isCellAlive( int, int ) const;
	bool isCellAlive( sf::Vector2i ) const;
	sf::Vector2i getSize();
	bool isValidPos( int, int );
	void iterate( int = 1 );
	void iterateCell( int, int );
	int getNumLiveNeighbors( int, int );
	void draw( sf::RenderWindow&, float, float, sf::Color, sf::Color, sf::Vector2f = sf::Vector2f( 0, 0 ) );
	void setCellState( int, int, bool );
	void setNextCellState( int, int, bool );

private:
	int mWidth, mHeight;
	bool *mGrid;
	bool *mGridNext;
};
