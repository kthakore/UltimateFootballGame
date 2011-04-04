#include "Vector.h"
#include <cstdlib>
#include <iostream>

using namespace std;

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
	cerr << val << " " << x << " " << y << " " << z <<endl;
}


