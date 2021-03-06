#include "GameController.h"
#include <cstdlib>

#include <string>
#include <sstream>
#include <iostream>

#include "Physics.h"
#include "BarController.h"
#include "BallController.h"
#include "EnemyController.h"

/* Helper functions */
using namespace std; 
	template <class T>
string to_string(T t, ios_base & (*f)(ios_base&))
{
	ostringstream oss;
	oss << f << t;
	return oss.str();	
}

void draw_text(string str, float x, float y)
{
	glPushMatrix();
	glTranslated(x,y,16);
	glScaled(0.001,0.001,0.001);
	for( int i = 0; i < str.length(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str.at(i));
	}
	glPopMatrix();


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
	this->kick_angle = new BarController( -0.01, 0.01, 0.0, 0.00001);
	this->kick_power = new BarController( 0.0, 0.04, 0.0, 0.00001);

	this->state = 'g'; //Just started so just go to game. We don't have a menu yet
	this->goals = 0; this->misses = 0; this->chances_left = 5; 

	this->enemy = new EnemyController(0,0,0);


	this->update_wind();



}


GameController::~GameController()
{

	delete this->kick_angle;
	delete this->kick_power;
	delete this->enemy;
}

void GameController::update()
{

	//Draw the field
	glColor3d(0,0.7,0);
	glPushMatrix();
	glTranslated(0,-2,0);
	glScaled(8,0.01,100);
	glutSolidCube(1);
	glPopMatrix();

	//field white sidelines
	glColor3d(1.0,1.0,1.0);
	glPushMatrix();
	glTranslated(0,-2.1,0);
	glScaled(10,0.01,100);
	glutSolidCube(1);
	glPopMatrix();





	//cutout for the middle of the field goal
	glColor3d(0.3,0.3,1.0);
	glPushMatrix();
	glTranslated(0,15,-20);
	glScaled(8,26,0.1);
	glutSolidCube(1);
	glPopMatrix();

	//cutouts for the bottom of the field goal -- the middle bit
	glColor3d(0.3,0.3,1.0);
	glPushMatrix();
	glTranslated(-3.2,-.75,-20);
	glScaled(3.7,3.7,0.1);
	glutSolidCube(1);
	glPopMatrix();

	glColor3d(0.3,0.3,1.0);
	glPushMatrix();
	glTranslated(3.2,-.75,-20);
	glScaled(3.7,3.7,0.1);
	glutSolidCube(1);
	glPopMatrix();

	//Draw the goal post --- yellow background
	glColor3d(1,1,0);
	glPushMatrix();
	glTranslated(0,0,-20);
	glScaled(10,30,0.1);
	glutSolidCube(1);
	glPopMatrix();

	glColor3d(1,1,0);
	glPushMatrix();
	glTranslated(0,0,-20);
	glScaled(10,30,0.1);
	glutSolidCube(1);
	glPopMatrix();

	//Render bars and wind 
	if( this->state == 'g' )
	{


		this->render_enemies();

		this->render_bars();

		this->render_wind();

		this->kick_power->update();

		this->kick_angle->update();

	}
	else if( this->state == 'k')
	{

		this->ball.update();

		this->check_collisions();

	}

	this->render_score();

}

//DRAWS AND MOVES THE ENEMIES
void GameController::render_enemies()
{
	glColor3d(1.0,0,0);
	glPushMatrix();
	glTranslated(0,-2,this->enemy->currentPosition.z);
	glScaled(2,1,1);
	glutSolidCube(1);
	glPopMatrix();

	this->enemy->move();


}

void GameController::update_wind()
{
	this->current_wind = Vector ( randDouble( -0.00006, 0.00006), 0.0f, 0.0f);

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

	float currentPower = this->kick_angle->value();
	currentPower = currentPower * 75;

	glColor3d(1,0,0);
	glPushMatrix();
	glTranslated(currentPower,1.6,17);
	glScaled(0.05,0.5,0.00001);
	glutSolidCube(1);
	glPopMatrix();


	currentPower = this->kick_power->value();
	currentPower = currentPower * 37.5;

	glColor3d(1,0,0);
	glPushMatrix();
	glTranslated(1.6,-1.5 + (currentPower),17);
	glScaled(0.5,0.01 + (currentPower*2),0.00001);
	glutSolidCube(1);
	glPopMatrix();
}

void GameController::render_wind()
{

	/* On the top left corner render
	   this->current_wind; (x,y,z) as an arrow
	 */
	float wind_x = this->current_wind.x;
	int direction;
	if( wind_x < 0 )
	{
		//Draw left arrow
		glColor3d(1,0,0);
		glPushMatrix();
		glTranslated(-1.9, 0.2, 17);
		glScaled(0.2,0.2,0.00001);
		glRotated(-90,0,1,0);
		glutSolidCone(0.5,1,10,10);
		glPopMatrix();

	}
	else if ( wind_x > 0 )
	{
		//Draw right arrow
		glColor3d(1,0,0);
		glPushMatrix();
		glTranslated(-2.0, 0.2, 17);
		glScaled(0.2,0.2,0.00001);
		glRotated(90,0,1,0);
		glutSolidCone(0.5,1,10,10);
		glPopMatrix();

	}


	wind_x *= 100000;

	if(wind_x < 0 )
		wind_x *= -1; 

	string windString = to_string<int>((int)wind_x, dec);
	windString.append(" km/h");
	draw_text(windString, -2.9, -0.2);
}


void GameController::render_score()
{
	string misses_str = "Misses: ";
	misses_str.append(to_string<int>(this->misses, dec));


	glColor3d(1,0,0);
	draw_text( misses_str, -2.5f, -1.9f);

	string goals_str = "Goals: ";
	goals_str.append(to_string<int>(this->goals, dec));

	glColor3d(0,1,0);
	draw_text( goals_str, -2.5f, 1.8f);


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
					Vector initial_velocity = Vector( this->kick_angle->value(), 0.02 + this->kick_power->value() , - 0.05  -this->kick_power->value() );

					this->ball.kick(  initial_velocity, this->current_wind );
					this->state = 'k';
					break;


			}

	}

}


void GameController::check_collisions()
{

	Vector ball_position = this->ball.current.position;

	double football_top = ball_position.y;
	double football_right = ball_position.x ;

	double goalpost_bottom = -2;
	double goalpost_left = -4.6;
	double goalpost_right = 4.75;

	// Reset the ball if we hit the backwall or the ground
	if( ball_position.y < -10  || ball_position.z < -20 || ball_position.x < -15 || ball_position.x > 15)
	{
		this->ball.reset();
		this->state = 'g';
		this->update_wind();
		this->enemy->reset();

		if(football_top > goalpost_bottom && football_right > goalpost_left && football_right < goalpost_right     ) {

			this->goals++;

		}	
		else
		{
			this->misses++;
		}

	}
}
