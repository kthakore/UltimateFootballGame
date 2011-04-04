#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Physics.h"
#include "BarController.h"
#include "BallController.h"

/*
Class: GameController
Purpose: Watch the Ball, Enemy and FieldGoal for Collisons and manage the game state
 */

class GameController
{
	public:
		//Initiate
		GameController();
		virtual ~GameController();

		//Call once per glut display
		void update();

		//Handle state specific key presses
		void handle_key( unsigned char key, int x, int y );

	private:
		BallController ball;
		BarController* kick_angle;
		BarController* kick_power;

		Vector enemy;
		Vector current_wind;

		char state;
		int goals;
		int misses; 
		int chances_left;

		void check_collisions();
		void update_wind();
		void render_bars();
		void render_wind();
	
		
};

#endif // GAMECONTROLLER_H
