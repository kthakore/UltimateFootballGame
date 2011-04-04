#include "BarController.h"

BarController::BarController( float min, float max, float initial_val, float increment)
{
	//nothing too complicated here, we are simply creating the BarController object
	//the parameters passed will be used to set the initial parameters for this object
	//this includes min value, max value, initial value, and increment value
	this->min = min;
	this->max = max;
	this->val = initial_val;
	this->increment = increment;
}

void BarController::update()
{
	//since the bar will be constantly updating, this function is essential
	//we need to update the current information of the bar
	this->val += this->increment;	//increment the total power by the speed
        
	if(this->val >= this->max || this->val <= this->min)	//the end values
    {
		//when you reach one end, the speed needs to flip so you can go back to the other end
		this->increment *= -1;// switch between -1 and 1
    }

}


float BarController::value(){ return this->val; }

