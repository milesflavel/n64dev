#include <stdio.h>
#include <math.h>
#include "box.h"

// Move method
void moveBox(box* _box)
{
    _box->xPos += _box->velocity * sin(_box->direction);
    _box->yPos += _box->velocity * cos(_box->direction);
    _box->direction += _box->turnAngle;
}

// Render method
void renderBox(box* _box)
{
    rdp_draw_filled_rectangle((int)_box->xPos, (int)_box->yPos, (int)(_box->xPos + _box->xSize), (int)(_box->yPos + _box->ySize));
}

// Constructor method (Must come after other methods due to scope constraints)
box* newBox(int _xPos, int _yPos, int _xSize, int _ySize)
{
    // Allocate space in memory
    box* boxPtr = malloc(sizeof(box));

    // Initialise functions
    boxPtr->move = moveBox;
    boxPtr->render = renderBox;

    // Initialise variables
    boxPtr->xPos = _xPos;
    boxPtr->yPos = _yPos;
    boxPtr->xSize = _xSize;
    boxPtr->ySize = _ySize;

    boxPtr->velocity = 0.5;
    boxPtr->direction = 0;
    boxPtr->turnAngle = 0.01;

    //Return pointer to entity
    return boxPtr;
}
