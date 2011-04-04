#ifndef STATE_H
#define STATE_H

#include "Vector.h"
#include <iostream>

using namespace std;
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
			cerr << val << "n" << endl;	
			position.debug("position \n");
			velocity.debug("velocity \n");
			cerr << endl;
		}

		Vector position;
		Vector velocity; 
};

#endif 
