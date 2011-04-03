#ifndef BALLCONTROLLER_H
#define BALLCONTROLLER_H
/*
Class: BallController
Purpose: Control and apply the game loop physics to the ball 
*/

#include "Physics.h"

class BallController
{
    public:
		//Initiate one
        BallController();
        virtual ~BallController();

		//Call once per glut display
		void update();
 
    private:
		//Interporlates between states and the alpha value of the time changes
		State interpolate( const State &previous, const State &current, float alpha );
		//The acceleration of the ball
		Vector acceleration( const State &state, float t);
		//Evaluates the derivatives 
		Derivative evaluate( const State &initial, float t);
		//Overloads Evaluate 
		Derivative evaluate( const State &initial, float t, float dt, const Derivative &d);
		//Integrate the position and velocity using rungekutta
		void integrate(State &state, float t, float dt);

		//Time Attributes
		float t; float dt; float currentTime; float accumulator;

		State current; State previous;
};

#endif // BALLCONTROLLER_H
