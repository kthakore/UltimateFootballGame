#include "Physics.h"
float ms_time()
{
	const double t = glutGet(GLUT_ELAPSED_TIME);
	return t;
}
