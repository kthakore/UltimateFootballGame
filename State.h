#ifndef STATE_H
#define STATE_H

#include <cstdlib>
#include <stdio.h>

#include "Vector.h"

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

#endif 
