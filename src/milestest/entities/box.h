// Structure of box
typedef struct
{
    void (*move)();
    void (*render)();

    double xPos;
    double yPos;
    int xSize;
    int ySize;

    float velocity;
    float direction;
    float turnAngle;
} box;

box* newBox(int _xPos, int _yPos, int _xSize, int _ySize);
