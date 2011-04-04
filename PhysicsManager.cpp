#include "Physics.h"
#include "PhysicsManager.h"
#include <iostream>
#include <cstdlib>



PhysicsManager::PhysicsManager( )
{


}




//Interporlates between states and the alpha value of the time changes
State PhysicsManager::interpolate( const State &previous, const State &current, float alpha )
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
//Evaluates the derivatives 
Derivative PhysicsManager::evaluate( const State &initial, float t)
{
	Derivative output;
	output.d_pos = initial.velocity;
	Vector accel = acceleration(initial, t);
	output.d_vel = accel;

	return output;
}
//Overloads Evaluate 
Derivative PhysicsManager::evaluate( const State &initial, float t, float dt, const Derivative &d)
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
void PhysicsManager::integrate(State &state, float t, float dt)
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

Vector PhysicsManager::acceleration( const State &state, float t) { return Vector(0,0,0); }

void PhysicsManager::reset ( ) { 

this->t=0; 
this->currentTime=0.0f; 
this->accumulator=0.0f;

}
