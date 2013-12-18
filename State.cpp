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
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

#include "Cell.h"
#include "State.h"

StateManager gStateManager;

void FPS::start()
{
	mClock.restart();
}

void FPS::onFrame()
{
	float t;
	if( ( t = mClock.getElapsedTime().asSeconds() ) >= 1 )
	{
		mFPS = mFrames / t;
		mFrames = 0;
		mClock.restart();
	}
	else
	{
		mFrames++;
	}
}

float FPS::getFPS()
{
	return mFPS;
}

StateManager::StateManager()
{
	mCurrentState = NULL;
	mShouldQuit = false;
	mFPS.start();
}

void StateManager::doLoop( sf::RenderWindow& w )
{
	if( mShouldQuit )
		w.close();

	if( mCurrentState == NULL )
		return;

	mFrameDelta = mFrameTimer.restart();
	mCurrentState->doInput( w );
	mCurrentState->doThink();
	mCurrentState->doRender( w );
	mFPS.onFrame();
}

float StateManager::getFPS()
{
	return mFPS.getFPS();
}

sf::Time StateManager::getDelta()
{
	return mFrameDelta;
}

void StateManager::setState( State* s )
{
	mCurrentState = s;
}

void StateManager::quit()
{
	mShouldQuit = true;
}

GameState::GameState() : mCG( 25, 25 )
{
	mCG;
	mIterateTime = sf::seconds( 1 );
	mPaused = true;
	mCellSize = 25;
	mCellSpace = 10;
}

void GameState::doInput( sf::RenderWindow& w )
{
	sf::Event event;

	while( w.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed )
			gStateManager.quit();
		if( event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Return)
			mPaused = !mPaused;

		if( event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left )
		{
			sf::Vector2f p = w.mapPixelToCoords( sf::Vector2i( event.mouseButton.x, event.mouseButton.y ) );
			sf::Vector2f np = p / ( mCellSize + mCellSpace );
			int x = (int)floor(np.x);
			int y = (int)floor(np.y);

			if( abs( np.x ) - abs( x ) < mCellSize / ( mCellSize + mCellSpace ) &&
				abs( np.y ) - abs( y ) < mCellSize / ( mCellSize + mCellSpace ) && 
				mCG.isValidPos( x, y ) )
				mCG.setCellState( x, y, !mCG.isCellAlive( x, y ) );
		}
	}
}

void GameState::doRender( sf::RenderWindow& w )
{
	w.clear( sf::Color::Black );

	mCG.draw( w, mCellSize, mCellSpace, sf::Color(255, 255, 255, 50), sf::Color::White );

	w.display();
}

void GameState::doThink()
{
	if( !mPaused && mIterateClock.getElapsedTime() > mIterateTime )
	{
		mCG.iterate();
		mIterateClock.restart();
	}
}
