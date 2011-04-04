#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

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

	private:
		BallController ball;
		BarController* kick_angle;
		BarController* kick_power;

//		EnemyController enemy;

		char state;
		int goals;
		int misses; 
		int chances_left;

		void check_collisions();
	
		
};

#endif // GAMECONTROLLER_H
