#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Physics.h"
#include "BarController.h"
#include "BallController.h"
#include "EnemyController.h"

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

		EnemyController* enemy;
		Vector current_wind;

		char state;
		int goals;
		int misses;			
		int chances_left;	//default is 5

		void check_collisions();
		void update_wind();
		void render_bars();
		void render_wind();
		void render_score();
		void render_enemies();
	
		
};

#endif // GAMECONTROLLER_H
