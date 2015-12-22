#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <libdragon.h>
#include "entities/box.h"

static volatile uint32_t animcounter = 0;

void update_counter( int ovfl )
{
    animcounter++;
}

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
    //init();
    /* enable interrupts (on the CPU) */
    init_interrupts();

    /* Initialize peripherals */
    display_init( RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE );
    dfs_init( DFS_DEFAULT_LOCATION );
    rdp_init();
    controller_init();
    timer_init();
    
    box* boxOne = Box(150, 100, 20, 20);
    box* boxTwo = Box(100, 120, 10, 10);
    boxTwo->velocity = 0.8;
    boxTwo->turnAngle = -0.02;
    
    /* Read in single sprite */
    int fp = dfs_open("/mudkip.sprite");
    sprite_t *mudkip = malloc( dfs_size( fp ) );
    dfs_read( mudkip, 1, dfs_size( fp ), fp );
    dfs_close( fp );
    
    fp = dfs_open("/earthbound.sprite");
    sprite_t *earthbound = malloc( dfs_size( fp ) );
    dfs_read( earthbound, 1, dfs_size( fp ), fp );
    dfs_close( fp );

    fp = dfs_open("/plane.sprite");
    sprite_t *plane = malloc( dfs_size( fp ) );
    dfs_read( plane, 1, dfs_size( fp ), fp );
    dfs_close( fp );

    int redr = 0;
    char directionst[3];
    /* Main loop test */
    while(1) 
    {
        static display_context_t disp = 0;

        /* Grab a render buffer */
        while( !(disp = display_lock()) );
       
        uint32_t bgColor = graphics_make_color(redr, 127, 127, 255); 
        redr++;
        if(redr>255) redr=0;
       
      
        /*Fill the screen */
        graphics_fill_screen( disp, bgColor );

        /* Set the text output color */
        graphics_set_color( 0xFFFFFFFF, bgColor );
        
        moveBox(boxOne);
        moveBox(boxTwo);
        renderBox(boxOne);
        renderBox(boxTwo);
    
        sprintf(directionst, "%f", boxOne->xPos);
    
        graphics_draw_text( disp, 100, 20, directionst );
        
        /* Hardware spritemap test */
        //graphics_draw_text( disp, 20, 20, "Hardware spritemap test" );

        /* Assure RDP is ready for new commands */
        rdp_sync( SYNC_PIPE );

        /* Remove any clipping windows */
        rdp_set_default_clipping();

        /* Enable sprite display instead of solid color fill */
        rdp_enable_texture_copy();

        /* Attach RDP to display */
        rdp_attach_display( disp );
            
        /* Ensure the RDP is ready to receive sprites */
        rdp_sync( SYNC_PIPE );

        /* Load the sprite into texture slot 0, at the beginning of memory, without mirroring */
        rdp_load_texture( 0, 0, MIRROR_DISABLED, plane );
        
        /* Display a stationary sprite of adequate size to fit in TMEM */
        rdp_draw_sprite( 0, 20, 50 );

        /* Since the RDP is very very limited in texture memory, we will use the spritemap feature to display
            all four pieces of this sprite individually in order to use the RDP at all */
        for( int i = 0; i < 4; i++ )
        {
            /* Ensure the RDP is ready to receive sprites */
            rdp_sync( SYNC_PIPE );

            /* Load the sprite into texture slot 0, at the beginning of memory, without mirroring */
            rdp_load_texture_stride( 0, 0, MIRROR_DISABLED, mudkip, i );
        
            /* Display a stationary sprite to demonstrate backwards compatibility */
            rdp_draw_sprite( 0, 50 + (20 * (i % 2)), 50 + (20 * (i / 2)) );
        }
        
        rdp_enable_primitive_fill();
        //rdp_set_primitive_color(graphics_make_color(255-bgColorR, bgColor/2, 180, 255));
        //rdp_draw_filled_rectangle(150, 150, 150+(animcounter%50), 200-(animcounter%50));

        /* Inform the RDP we are finished drawing and that any pending operations should be flushed */
        rdp_detach_display();

        /* Force backbuffer flip */
        display_show(disp);

        /* Do we need to switch video displays? */
        controller_scan();
        struct controller_data keys = get_keys_down();

        if( keys.c[0].A )
        {
            /* Lazy switching */
            //mode = 1 - mode;
        }
    }
}