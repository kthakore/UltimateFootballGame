#ifndef ENECONTROLLER_H
#define ENECONTROLLER_H



#include "Vector.h"


class EnemyController
{
    public:     
        EnemyController(float x, float y, float z);
        ~EnemyController();
        void move();
        void reset();
    
        Vector currentPosition;

    
    private:
    
    
};

#endif
