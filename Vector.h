#ifndef VEC_H
#define VEC_H
#include <cstdlib>
#include <stdio.h>


class Vector
{

	public:
		Vector( );	
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

			return *this;
		}
		Vector& operator*(const float &rhs){
			this->x *= rhs;
			this->y *= rhs;
			this->z *= rhs;
			return *this;
		}
		Vector( float X, float Y, float Z );
		void debug( const char* val);
		float x;
		float y;
		float z;

};

#endif 
