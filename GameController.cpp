#include "GameController.h"

#include "BarController.h"
#include "BallController.h"
#include "EnemyController.h"


GameController::GameController()
{

	//Do this based on player attributes 
	this->kick_angle = new BarController( -10.0, 10.0, 1);
	this->kick_power = new BarController( -10.0, 10.0, 1);

}


GameController::~GameController()
{

	delete this->kick_angle;
	delete this->kick_power;

}

void GameController::update()
{



}


void check_collisions()
{


}
