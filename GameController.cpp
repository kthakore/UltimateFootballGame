#include "GameController.h"
#include "Physics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


float ms_time()
{
	const double t = glutGet(GLUT_ELAPSED_TIME);
	return t;
}


GameController::GameController()
{

	Vector initial( 0.0f, -2.0f, 18.0f );
	this->current.position = initial;
	this->current.velocity = Vector(0.0,0.04,-0.025);

	this->previous = current;

	t = 0.0f;
	dt = 0.1f;

	currentTime = 0.0f;
	accumulator = 0.0f;

}

GameController::~GameController()
{
	//dtor
}

void GameController::game_loop()
{	const float newTime = ms_time();
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
	// Render::draw_ball( render_ball_state );

	glColor3d(1,0,0);

	glPushMatrix();
	glTranslated(render_ball_state.position.x, render_ball_state.position.y, render_ball_state.position.z);
	glScaled(0.1,0.3,0.1);
	glRotated(60,1,0,0);
	glutSolidSphere(1,16,16);
	glPopMatrix();

}

//Interporlates between states and the alpha value of the time changes
State GameController::interpolate( const State &previous, const State &current, float alpha )
{
	State state;

	Vector c_p = current.position;
	Vector p_p = previous.position;

	Vector c_v = current.velocity;
	Vector p_v = previous.velocity;
	state.position  =  c_p*alpha + p_p*(1-alpha);
	state.velocity  = c_v*alpha + p_v*(1-alpha);

	return state;
}
//The acceleration of the ball
Vector GameController::acceleration( const State &state, float t)
{
	Vector change( 0, -0.000098, 0);

	//Apply Wind to X,Y,Z

	//Apply Power and Angle to X,Y,Z
	return change; 
}
//Evaluates the derivatives 
Derivative GameController::evaluate( const State &initial, float t)
{
	Derivative output;
	output.d_pos = initial.velocity;
	Vector accel = acceleration(initial, t);
	output.d_vel = accel;

	return output;
}
//Overloads Evaluate 
Derivative GameController::evaluate( const State &initial, float t, float dt, const Derivative &d)
{
	State state;
	Vector i_p = initial.position;
	Vector d_pos = d.d_pos;

	Vector i_v = initial.velocity;
	Vector d_vel = d.d_vel;

	state.position = i_p + (d_pos*dt);

	state.velocity = i_v + (d_vel*dt);

	Derivative output;

	output.d_pos = state.velocity;

	Vector dVel_step = acceleration(state, t+dt);

	output.d_vel = dVel_step;

	return output;
}
//Integrate the position and velocity using rungekutta
void GameController::integrate(State &state, float t, float dt)
{
	Derivative a = evaluate(state, t);
	Derivative b = evaluate(state, t, dt*0.5f, a);
	Derivative c = evaluate(state, t, dt*0.5f, b);
	Derivative d = evaluate(state, t, dt, c);

	Vector dpos_dt =  ( a.d_pos + ( ( b.d_pos + c.d_pos ) *2.0f  ) + d.d_pos ) * (1.0f/6.0f); 
	Vector dvel_dt =  ( a.d_vel + ( ( b.d_vel + c.d_vel ) *2.0f  ) + d.d_vel ) * (1.0f/6.0f); 

	state.position = state.position + dpos_dt*dt;
	state.velocity = state.velocity + dvel_dt*dt;

}

