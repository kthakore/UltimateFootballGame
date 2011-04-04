#ifndef BALLCONTROLLER_H
#define BALLCONTROLLER_H
/*
Class: BallController
Purpose: Control and apply the game loop physics to the ball 
 */

#include "Physics.h"
#include "PhysicsManager.h"

class BallController : PhysicsManager 
{
	public:
		//Initiate one
		BallController();
		virtual ~BallController();

		void kick( Vector v, Vector w);

		//Call once per glut display
		void update();

		State current; State previous;

		//reset the ball
		void reset();



	private:
		//Render the BALL
		void render( Vector p );
		//kick
		bool kicked;

		//wind
		Vector wind;	
};

#endif // BALLCONTROLLER_H
