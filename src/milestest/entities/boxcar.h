// Structure of box
typedef struct
{
    void (*control)();
    void (*move)();
    void (*render)();

    double xPos;
    double yPos;
    int xSize;
    int ySize;

    float velocity;
    float velocityMax;
    float direction;
    float turnAngle;
} boxcar;

boxcar* newBoxCar(int _xPos, int _yPos, int _xSize, int _ySize);
