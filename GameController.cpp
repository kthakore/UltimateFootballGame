#include "GameController.h"


#include "Physics.h"
#include "BarController.h"
#include "BallController.h"

double randDouble(double low, double high)
{
	double temp;

	/* swap low & high around if the user makes no sense */
	if (low > high)
	{
		temp = low;
		low = high;
		high = temp;
	}

	/* calculate the random number & return it */
	temp = (rand() / (static_cast<double>(RAND_MAX) + 1.0))
		* (high - low) + low;
	return temp;
}

GameController::GameController()
{

	//Do this based on player attributes 
	this->kick_angle = new BarController( -10.0, 10.0, 0.0, 1.0);
	this->kick_power = new BarController( -10.0, 10.0, 0.0, 1.0);

	this->state = 'g'; //Just started so just go to game. We don't have a menu yet
	this->goals = 0; this->misses = 0; this->chances_left = 0; 

}


GameController::~GameController()
{

	delete this->kick_angle;
	delete this->kick_power;

}

void GameController::update()
{


	this->kick_power->update();
	this->kick_angle->update();

	this->ball.update();

	this->check_collisions();
}


//handle key presses for different game states
void GameController::handle_key( unsigned char key, int x, int y )
{

	switch( this->state )
	{
		case 'g':
			switch (key)
			{
				case ' ':
					//TODO: use the stuff from the bars kick_angle and kick_power
					float angle =  randDouble( -0.000150, 0.000150) ;
					Vector initial_velocity = Vector(randDouble( -0.000150, 0.000150),0.02 + randDouble( 0, 0.05) ,-( 0.05+randDouble(0.0,0.04) ) );
		//			initial_velocity.debug("Kick initial velocity");
					Vector wind_affect_angle = Vector ( randDouble( -0.000150, 0.000150), 0.0000001, randDouble(-0.0001,0.0001));
		//			wind_affect_angle.debug("Affect of Wind and Kick Angle");
					this->ball.kick(  initial_velocity, wind_affect_angle );
					this->state = 'k';
					break;


			}

	}

}


void GameController::check_collisions()
{

	Vector ball_position = this->ball.current.position;

	// Reset the ball if we hit the backwall or the ground
	if( ball_position.y < -10  || ball_position.z < -20)
	{
		ball.reset();
		this->state = 'g';
	}
}
