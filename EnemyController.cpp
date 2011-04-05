//
//  EnemyController.cpp
//  UFG
//
//  Created by Leke Akinyele on 11-04-05.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "EnemyController.h"


EnemyController::EnemyController(float x, float y, float z){
    currentPosition = Vector(x,y,z);
}

EnemyController::~EnemyController(){
    
    
}

void EnemyController::move(){
    this->currentPosition + Vector(0,0,0.001);
}

void EnemyController::reset(){
    currentPosition = Vector(0,0,0);
}
