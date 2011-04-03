#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdlib.h>
#include <stdio.h>

class Vector
{

	public:
		Vector( )
		{
			this->x = 0; this->y = 0; this->z = 0;
		}
		Vector & operator + (const Vector &other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;

			return *this;
		}
		Vector& operator=(const Vector &rhs) {
			if (this == &rhs)      // Same object?
				return *this;        // Yes, so skip assignment, and just return *this.

			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;

		}
		Vector& operator*(const float &rhs) {
			this->x = this->x * rhs;
			this->y = this->y * rhs;
			this->z = this->z * rhs;

		}
		Vector( float X, float Y, float Z ){
			this->x = X;
			this->y = Y;
			this->z = Z;
		}
		void debug( const char* val)
		{
			fprintf( stderr, " %s %f %f %f", val, x, y, z);
		}
		float x;
		float y;
		float z;

};

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
			fprintf( stderr, " %s \n", val);
			position.debug("position \n");
			velocity.debug("\n velocity \n");
			fprintf( stderr, " \n %s ", val);
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

