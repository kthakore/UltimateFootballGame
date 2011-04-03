#ifndef BARCONTROLLER_H
#define BARCONTROLLER_H
/*
Class: BarController
Purpose: Move between too values  
 */

class BarController
{
	public:
		//Initiate
		BarController( float min, float max, float initial_val, float increment);

		//Call once per glut display
		void update();

		//Get the value	
		float value();

	private:
		float val;
		float increment; 
		float min;
		float max;
};

#endif // BARCONTROLLER_H
