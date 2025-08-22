/*
=============================================================
 Sépulture (GBC RPG)
 Minimal Game Boy Color RPG built using GBDK-2020.
 - Background: bordered dungeon walls
 - Player: 8x8 sprite (winking sample sprite)
 - Movement: D-Pad without collision
 - Sample Map made with GBMB
 - Sprites created with GBTD
=============================================================
*/

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <gbdk/font.h>

//LOADING SPRITES
#include "../assets/sprites/smileysprite.c"
#include "../assets/sprites/basicbackgrounds.c"

//LOADING MAPS
#include "../assets/maps/samplemap.c"

//LOADING WINDOW MAP
#include "../assets/maps/windowmap.c"

// -----------------------------------------------------------
// CGB palettes (4 colors each)
// -----------------------------------------------------------
const UWORD bg_palettes[] = {
    RGB_WHITE, RGB_LIGHTGRAY, RGB_DARKGRAY, RGB_BLACK
};

const UWORD spr_palettes[] = {
    RGB_WHITE, RGB_LIGHTGRAY, RGB_DARKGRAY, RGB_BLACK
};

void main() {
    // Set sprite state
    UINT8 currentspriteindex = 0;

    //Variable to load the font
    font_t min_font;

    //initialise font library
    //load onto our variable the font we want and set it
    font_init();
    min_font = font_load(font_min);
    font_set(min_font);

    // Enable Color Game Boy features if available
    cgb_compatibility();

    // Apply palettes if running on CGB
    if (_cpu == CGB_TYPE) {
        set_bkg_palette(0, 1, bg_palettes);
        set_sprite_palette(0, 1, spr_palettes);
    }

    //Loading data from sprite (2 tiles)
    //Set "0" first sprite and "0" first tile in the memory
    //Place the sprite were we want it to be, the center of the screen (80x78)
    set_sprite_data(0, 2, smileysprite);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);

    //Loading background data
    //We start at 37 to give place to our font from 0 to 36
    //Set background in memory
    set_bkg_data(37, 7, basicbackgrounds);
    set_bkg_tiles(0, 0, 40, 18, samplemap);

    //Loading window layer data at 0x0.  Select long. 11.  Select high 1.
    //Display : HELLO WORLD
    set_win_tiles(0,0,11,1,windowmap);
    move_win(7,120);

    //Display the background layer, window layer, sprite layer, power on the display (set flags)
    SHOW_BKG; SHOW_WIN; SHOW_SPRITES; DISPLAY_ON;

    while(1){
        //Detect joypad presses and move sprite by 10 and move background by 1
        switch(joypad()){
            case J_LEFT:
                scroll_sprite(0,-10,0);
                scroll_bkg(-1,0);
                break;
            case J_RIGHT:
                scroll_sprite(0,10,0);
                scroll_bkg(1,0);
                break;
            case J_UP:
                scroll_sprite(0,0,-10);
                scroll_bkg(0,-1);
                break;
            case J_DOWN:
                scroll_sprite(0,0,10);
                scroll_bkg(0,1);
                break;
        }

        //cycle through the two sprites
        if(currentspriteindex==0){
            currentspriteindex = 1;
        }else{
            currentspriteindex = 0;
        }
        set_sprite_tile(0, currentspriteindex);

        //Create a delay to slow down slow the loop
        delay(100);
    }
}

/*
=============================================================
 LICENCE : CC BY-NC-SA 4.0
 LICENCE URL : http://creativecommons.org/licenses/by-nc-sa/4.0/
=============================================================
*/