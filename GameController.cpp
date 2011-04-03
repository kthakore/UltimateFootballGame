#include "GameController.h"
#include "Physics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#ifdef _WIN32

#define VC_EXTRALEAN 
#define WIN32_LEAN_AND_MEAN 

#include <windows.h>
#include <windowsx.h>
float ms_time()
{
	static __int64 start = 0;
	static __int64 frequency = 0;

	if (start==0)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		return 0.0f;
	}

	__int64 counter = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter);
	return (float) ((counter - start) / double(frequency));
}
#elif __APPLE__

#include <Carbon/Carbon.h>

float ms_time()
{
	static UInt64 start = 0;

	if (start==0)
	{
		Microseconds((UnsignedWide*)&start);
		return 0.0f;
	}

	UInt64 counter = 0;
	Microseconds((UnsignedWide*)&counter);
	return (counter - start) / 1000000.0f;
}


#else
float ms_time()
{

	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec;
}

#endif

GameController::GameController()
{
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
	// Render::draw_ball( render_ball_state );

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
	Vector change;
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

	state.position = i_p + d_pos*dt;
	state.velocity = i_v + d_vel*dt;

	Derivative output;

	output.d_pos = state.position;
	Vector dVel_step = acceleration(state, t+dt);

	output.d_vel = dVel_step;

	return output;
}
//Integrate the position and velocity using rungekutta
void GameController::integrate(State &state, float t, float dt)
{

}

