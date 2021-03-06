#ifndef PHYSICSMAN_H
#define PHYSICSMAN_H

#include "Physics.h"

class PhysicsManager
{

	public:
		PhysicsManager( );

			
		//Whill be overloaded by child class
		virtual void reset();

		State get_current();
		State get_previous();

	protected:
		//Interporlates between states and the alpha value of the time changes
		State interpolate( const State &previous, const State &current, float alpha );
		//Evaluates the derivatives 
		Derivative evaluate( const State &initial, float t);
		//Overloads Evaluate 
		Derivative evaluate( const State &initial, float t, float dt, const Derivative &d);
		//Integrate the position and velocity using rungekutta
		void integrate(State &state, float t, float dt);

		//Time Attributes
		float t; float dt; float currentTime; float accumulator;

		State current; State previous;

		//Will be overloaded by child class
		virtual Vector acceleration( const State &state, float t);



}; 

#endif 
