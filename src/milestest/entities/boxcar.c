#include <stdio.h>
#include <math.h>
#include "boxcar.h"

// Control method
void controlBoxCar(boxcar* _box)
{
    struct controller_data keys = get_keys_pressed();
    if( !keys.c[0].A )
    {
        //if(_box->velocity < _box->velocityMax)
            _box->velocity += 0.05;
    }
    else
    {
        //if(_box->velocity >= 0)
            _box->velocity -= 0.05;
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
    _box->direction -= _box->turnAngle;
}

// Render method
void renderBoxCar(boxcar* _box)
{
    float originx = _box->xPos;
    float originy = _box->yPos;
    float p1x = 0;
    float p1y = -8;
    float p2x = 8;
    float p2y = 8;
    float p3x = -8;
    float p3y = 8;

    float s = sin(_box->direction);
    float c = cos(_box->direction);

    int p1xnew = (int)(p1x * c + p1y * s);
    int p1ynew = (int)(-p1x * s + p1y * c);
    int p2xnew = (int)(p2x * c + p2y * s);
    int p2ynew = (int)(-p2x * s + p2y * c);
    int p3xnew = (int)(p3x * c + p3y * s);
    int p3ynew = (int)(-p3x * s + p3y * c);

    _box->debugval = originx+p1xnew;

    rdp_draw_filled_triangle((int)(originx+p1xnew), (int)(originy+p1ynew), (int)(originx+p2xnew), (int)(originy+p2ynew), (int)(originx+p3xnew), (int)(originy+p3ynew));
    //rdp_draw_filled_rectangle((int)*_box.xPos+100, (int)*_box.yPos+100, (int)(*_box.xPos+*_box.xSize)+100, (int)(*_box.yPos+*_box.ySize)+100);
    //rdp_draw_filled_rectangle((int)_box->xPos, (int)_box->yPos, (int)(_box->xPos + _box->xSize), (int)(_box->yPos + _box->ySize));
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
    boxPtr->xPos = (float)_xPos;
    boxPtr->yPos = (float)_yPos;
    boxPtr->xSize = _xSize;
    boxPtr->ySize = _ySize;

    boxPtr->debugval = 0;

    boxPtr->velocity = 0;
    boxPtr->velocityMax = 80;
    boxPtr->direction = 1.5;
    boxPtr->turnAngle = 0.0;

    //Return pointer to entity
    return boxPtr;
}
