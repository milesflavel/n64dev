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

int main(void)
{
    init();

    //box* boxOne = newBox(150, 100, 20, 20);
    //boxcar* boxTwo = newBoxCar(100, 120, 10, 10);

    entity* entOne = newEntity(BOX, newBox(150, 100, 20, 20));
    entity* entTwo = newEntity(BOXCAR, newBoxCar(100, 120, 10, 10));

    int entitiesCount = 2;
    entity* entities[entitiesCount];
    entities[0] = entOne;
    entities[1] = entTwo;

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

        /* Attach RDP to display */
        rdp_attach_display( disp );

        rdp_enable_primitive_fill();

        for(int e=0; e<entitiesCount; e++)
        {
            entities[e]->doLogic(entities[e]);
            entities[e]->render(entities[e]);
        }

        boxcar* bc = entities[1]->data;
        sprintf(directionst, "%f", bc->debugval);
        graphics_draw_text( disp, 100, 20, directionst );

        /* Inform the RDP we are finished drawing and that any pending operations should be flushed */
        rdp_detach_display();

        /* Force backbuffer flip */
        display_show(disp);
    }
}
