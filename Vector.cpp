#include "Vector.h"
#include <cstdlib>
#include <stdio.h>

Vector::Vector( )
{
	this->x = 0; this->y = 0; this->z = 0;
}
Vector::Vector( float X, float Y, float Z ){
	this->x = X;
	this->y = Y;
	this->z = Z;
}
void Vector::debug( const char* val)
{
	fprintf( stderr, " %s %f %f %f \n", val, x, y, z);
}


