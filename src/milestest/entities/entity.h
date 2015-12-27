// Entity type enum
typedef enum {BOX, BOXCAR} entityType;

// Structure of entity container
typedef struct
{
    void (*doLogic)();
    void (*render)();

    entityType type;
    void* data;
} entity;

entity* newEntity(entityType _type, void* _entity);
