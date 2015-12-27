#include <stdio.h>
#include "entity.h"

// Render method
void doLogicEntity(entity* _entity)
{
    switch (_entity->type)
    {
        case BOX:
        {
            box* e = (box*)_entity->data;
            e->move(e);
            break;
        }
        case BOXCAR:
        {
            boxcar* e = (boxcar*)_entity->data;
            e->control(e);
            e->move(e);
            break;
        }
        default:
            break;
    }
}

// Render method
void renderEntity(entity* _entity)
{
    switch (_entity->type)
    {
        case BOX:
        {
            box* e = (box*)_entity->data;
            e->render(e);
            break;
        }
        case BOXCAR:
        {
            boxcar* e = (boxcar*)_entity->data;
            e->render(e);
            break;
        }
        default:
            break;
    }
}

// Constructor method (Must come after other methods due to scope constraints)
entity* newEntity(entityType _type, void* _entity)
{
    // Allocate space in memory
    entity* entityPtr = malloc(sizeof(entity));

    // Initialise functions
    entityPtr->doLogic = doLogicEntity;
    entityPtr->render = renderEntity;

    // Initialise variables
    entityPtr->type = _type;
    entityPtr->data = _entity;

    //Return pointer to entity
    return entityPtr;
}
