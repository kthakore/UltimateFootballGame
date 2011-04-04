#include "BallController.h"
#include "PhysicsManager.h"
#include "Physics.h"
#include <iostream>
#include <cstdlib>


BallController::BallController()
{

	this->reset();

}



BallController::~BallController()
{
	//dtor
}

void BallController::update()
{	

	if( this->kicked )
	{
		const float newTime = ms_time();
		float deltaTime = newTime - this->currentTime;
		this->currentTime = newTime;

		if( deltaTime > 0.25f )
			deltaTime = 0.25f;

		this->accumulator += deltaTime;

		while( this->accumulator >= this->dt )
		{
			this->accumulator -= this->dt;
			this->previous = this->current;
			this->integrate( this->current, this->t, this->dt );
			this->t += this->dt;	

		}

		State render_ball_state = interpolate( this->previous, this->current, this->accumulator/this->dt ); 

		//Draw ball here
		this->render(render_ball_state.position);

	}
	else
	{

		this->render( this->current.position );

	}



}

void BallController::render( Vector position)
{

	glColor3d(1,0,0);

	glPushMatrix();
	glTranslated(position.x, position.y, position.z);
	glScaled(0.1,0.1,0.3);
	glRotated(60,0.4,0,0);
	glutSolidSphere(1,16,16);
	glPopMatrix();



}

void BallController::kick(Vector velocity, Vector windspeed)
{

	this->current.position = Vector(0.0f, -2.0f, 18.0f);
	this->current.velocity = velocity;
	this->wind = windspeed;

	this->previous = current;

	t = 0.0f;
	dt = 0.1f;

	currentTime = 0.0f;
	accumulator = 0.0f;

	kicked = true;

}

void BallController::reset()
{

	this->current.position = Vector(0.0f, -2.0f, 18.0f);
	kicked = false;

}
