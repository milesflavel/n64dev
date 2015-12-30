// Structure of box
typedef struct
{
    void (*control)();
    void (*move)();
    void (*render)();

    float xPos;
    float yPos;
    int xSize;
    int ySize;

    float debugval;

    float velocity;
    float velocityMax;
    float direction;
    float turnAngle;
} boxcar;

boxcar* newBoxCar(int _xPos, int _yPos, int _xSize, int _ySize);
