#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <libdragon.h>
#include "files.in" //Possibly the most ghetto workaround to use the existing makefile (seriously can't stay this way)

void init()
{
    /* enable interrupts (on the CPU) */
    init_interrupts();

    /* Initialize peripherals */
    display_init( RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE );
    dfs_init( DFS_DEFAULT_LOCATION );
    rdp_init();
    controller_init();
    timer_init();
}

typedef struct
{
    void (*control)();
    void (*move)();
    void (*render)();
} entity;

int main(void)
{
    init();

    box* boxOne = Box(150, 100, 20, 20);
    boxcar* boxTwo = BoxCar(100, 120, 10, 10);

    //int entitiesCount = 2;
    //void* entities[entitiesCount];
    //entities[0] = boxOne;
    //entities[1] = boxTwo;

    char directionst[3];

    /* Main loop test */
    while(1)
    {
        static display_context_t disp = 0;

        /* Grab a render buffer */
        while( !(disp = display_lock()) );

        controller_scan();

        uint32_t bgColor = graphics_make_color(127, 127, 127, 255);

        /*Fill the screen */
        graphics_fill_screen( disp, bgColor );

        /* Set the text output color */
        graphics_set_color( 0xFFFFFFFF, bgColor );

        /* Assure RDP is ready for new commands */
        rdp_sync( SYNC_PIPE );

        /* Remove any clipping windows */
        rdp_set_default_clipping();

        graphics_draw_text( disp, 100, 20, directionst );

        /* Attach RDP to display */
        rdp_attach_display( disp );

        rdp_enable_primitive_fill();

        /*
        for(int ent=0; ent<entitiesCount; ent++)
        {
            entities[ent]->move(entities[ent]);
            entities[ent]->render(entities[ent]);
        }
        */

        boxOne->move(boxOne);
        boxOne->render(boxOne);
        boxTwo->control(boxTwo);
        boxTwo->move(boxTwo);
        boxTwo->render(boxTwo);


        sprintf(directionst, "%f", boxTwo->turnAngle);

        /* Inform the RDP we are finished drawing and that any pending operations should be flushed */
        rdp_detach_display();

        /* Force backbuffer flip */
        display_show(disp);
    }
}
