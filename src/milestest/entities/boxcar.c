#include <stdio.h>
#include <math.h>
#include "boxcar.h"

// Control method
void controlBoxCar(boxcar* _box)
{
    struct controller_data keys = get_keys_pressed();
    if( keys.c[0].A )
    {
        //if(_box->velocity < _box->velocityMax)
            _box->velocity -= 0.05;
    }
    else
    {
        //if(_box->velocity >= 0)
            _box->velocity += 0.05;
    }
    if(_box->velocity > 0) _box->velocity = 0;
    if(_box->velocity > _box->velocityMax) _box->velocity = _box->velocityMax;

    float joyTurn = (float)keys.c[0].x * 0.05 / 100;
    _box->turnAngle = joyTurn;
}

// Move method
void moveBoxCar(boxcar* _box)
{
    _box->xPos += _box->velocity * sin(_box->direction);
    _box->yPos += _box->velocity * cos(_box->direction);
    _box->direction += _box->turnAngle;
}

// Render method
void renderBoxCar(boxcar* _box)
{
    //rdp_draw_filled_rectangle((int)*_box.xPos+100, (int)*_box.yPos+100, (int)(*_box.xPos+*_box.xSize)+100, (int)(*_box.yPos+*_box.ySize)+100);
    rdp_draw_filled_rectangle((int)_box->xPos, (int)_box->yPos, (int)(_box->xPos + _box->xSize), (int)(_box->yPos + _box->ySize));
}

// Constructor method
boxcar* newBoxCar(int _xPos, int _yPos, int _xSize, int _ySize)
{
    // Allocate space in memory
    boxcar* boxPtr = malloc(sizeof(boxcar));

    // Initialise functions
    boxPtr->control = controlBoxCar;
    boxPtr->move = moveBoxCar;
    boxPtr->render = renderBoxCar;


    // Initialise variables
    boxPtr->xPos = _xPos;
    boxPtr->yPos = _yPos;
    boxPtr->xSize = _xSize;
    boxPtr->ySize = _ySize;

    boxPtr->velocity = 0;
    boxPtr->velocityMax = 80;
    boxPtr->direction = 0;
    boxPtr->turnAngle = 0.0;

    //Return pointer to entity
    return boxPtr;
}
