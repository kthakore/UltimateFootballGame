#include "GameController.h"
#include <cstdlib>

#include <string>
#include <sstream>
#include <iostream>

#include "Physics.h"
#include "BarController.h"
#include "BallController.h"

/* Helper functions */
using namespace std; 
template <class T>
string to_string(T t, ios_base & (*f)(ios_base&))
{
	ostringstream oss;
	oss << f << t;
	return oss.str();	
}

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
	this->kick_angle = new BarController( -0.01, 0.01, 0.0, 0.001);
	this->kick_power = new BarController( 0.0, 0.04, 0.0, 0.01);

	this->state = 'g'; //Just started so just go to game. We don't have a menu yet
	this->goals = 0; this->misses = 0; this->chances_left = 5; 

}


GameController::~GameController()
{

	delete this->kick_angle;
	delete this->kick_power;

}

void GameController::update()
{

	//Draw the field
	glColor3d(0,0.7,0);
	glPushMatrix();
	glTranslated(0,-2,0);
	glScaled(10,0.01,100);
	glutSolidCube(1);
	glPopMatrix();

	//Draw the goal post
	glColor3d(0.1,0.1,0.1);
	glPushMatrix();
	glTranslated(0,0,-20);
	glScaled(10,30,0.1);
	glutSolidCube(1);
	glPopMatrix();

	//Render bars and wind 

	this->render_bars();

	this->render_wind();

	this->render_score();

	this->update_wind();

	this->kick_power->update();
	
	this->kick_angle->update();

	this->ball.update();

	this->check_collisions();
	
}


void GameController::update_wind()
{

	this->current_wind = Vector ( randDouble( -0.000150, 0.000150), 0.0000001, randDouble(-0.0001,0.0001));
	
}

void GameController::render_bars()
{

	/* On the bottom center left to right render 
	this->kick_angle;
		use 
		this->kick_angle->value();
		this->kick_angle->getMax();
		this->kick_angle->getMin();
	*/

	/* On the left render 
	this->kick_power;
	*/


}

void GameController::render_wind()
{

	/* On the top left corner render 
			this->current_wind; (x,y,z) as an arrow
	*/

}

void GameController::render_score()
{

	string misses = to_string<int>(this->misses, dec);

	glColor3d(0,1,0);
	glPushMatrix();
	glTranslated(-2.5,-1.9,16);
	glScaled(0.005,0.005,0.005);
	for( int i = 0; i < misses.length(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, misses.at(i));
	}
	glPopMatrix();
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
					Vector initial_velocity = Vector( 0, 0.02 + this->kick_power->value() , - 0.05  -this->kick_power->value() );
					initial_velocity.debug("Kick initial velocity");
					Vector wind_affect_angle = Vector ( randDouble( -0.000150, 0.000150), 0.0000001, randDouble(-0.0001,0.0001));
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
