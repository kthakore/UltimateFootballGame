#ifndef PHYSICS_H
#define PHYSICS_H
#include "Vector.h"
#include <cstdlib>
#include <stdio.h>
class State
{
	public:
		State() {};
		State& operator=(const State &rhs) {
			// Check for self-assignment!
			if (this == &rhs)      // Same object?
				return *this;        // Yes, so skip assignment, and just return *this.

			this->position = rhs.position;
			this->velocity = rhs.velocity;
			return *this;
		}

		void debug( const char* val)
		{
			fprintf( stderr, "%s\n", val);
			position.debug("position \n");
			velocity.debug("velocity \n");
			fprintf( stderr, "\n");
		}

		Vector position;
		Vector velocity; 
};

class Derivative
{
	public:
		Derivative() {};
		Derivative& operator=(const Derivative &rhs) {
			if (this == &rhs)      // Same object?
				return *this;        // Yes, so skip assignment, and just return *this.


		}
		Vector d_pos;
		Vector d_vel;

};

#endif 

