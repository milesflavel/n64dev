#include <stdio.h>
#include <math.h>

// Structure of box
typedef struct
{
    double xPos;
    double yPos;
    int xSize;
    int ySize;
    
    float velocity;
    float direction;
    float turnAngle;
}box;

box* Box(int _xPos, int _yPos, int _xSize, int _ySize);

// Constructor method
box* Box(int _xPos, int _yPos, int _xSize, int _ySize)
{
    box* boxPtr = malloc(sizeof(box));
    
    //boxPtr = &_box;
    
    //double xPosD = 0;
    //xPosD = (double)_xPos;
    
    // Variables
    boxPtr->xPos = _xPos;
    boxPtr->yPos = _yPos;
    boxPtr->xSize = _xSize;
    boxPtr->ySize = _ySize;
    
    boxPtr->velocity = 0.5;
    boxPtr->direction = 0;
    boxPtr->turnAngle = 0.01;
    
    return boxPtr;
}

void moveBox(box* _box)
{
    _box->xPos += _box->velocity * sin(_box->direction);
    _box->yPos += _box->velocity * cos(_box->direction);
    _box->direction += _box->turnAngle;
}

// Render method
void renderBox(box* _box)
{
    //rdp_draw_filled_rectangle((int)*_box.xPos+100, (int)*_box.yPos+100, (int)(*_box.xPos+*_box.xSize)+100, (int)(*_box.yPos+*_box.ySize)+100);
    rdp_draw_filled_rectangle((int)_box->xPos, (int)_box->yPos, (int)(_box->xPos + _box->xSize), (int)(_box->yPos + _box->ySize));
}