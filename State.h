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
#ifndef STATE_H
#define STATE_H

class State;
class StateManager;

class FPS
{
public:
    void start();
    void onFrame();
    float getFPS();

private:
    sf::Clock mClock;
    int mFrames;
    float mFPS;
};

class StateManager
{
public:
    StateManager();
    void doLoop( sf::RenderWindow& );
    void setState( State* );
	sf::Time getDelta();
	float getFPS();
	void quit();

private:
    State *mCurrentState;
    FPS mFPS;
	sf::Clock mFrameTimer;
	sf::Time mFrameDelta;
	bool mShouldQuit;
};

class State
{
public:
    friend class StateManager;

private:
    virtual void doInput( sf::RenderWindow& ) = 0;
    virtual void doThink() = 0;
    virtual void doRender( sf::RenderWindow& ) = 0;
};

class GameState : public State
{
public:
	GameState();

private:
	virtual void doInput( sf::RenderWindow& );
    virtual void doThink();
    virtual void doRender( sf::RenderWindow& );

	CellGrid *mDisplayGrid;
	CellGrid mCG;

	sf::Clock mIterateClock;
	sf::Time mIterateTime;
	bool mPaused;

	float mCellSize;
	float mCellSpace;
};

extern StateManager gStateManager;

#endif // STATE_H
