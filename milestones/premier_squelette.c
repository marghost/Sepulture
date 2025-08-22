#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

/*
=============================================================
 Sépulture (GBC RPG)
 Minimal Game Boy Color RPG foundation using GBDK-2020.
 - Background: bordered dungeon walls
 - Player: 8x16 sprite (square shape)
 - Movement: D-Pad with simple collision
=============================================================
*/

// --- Background tiles ---
// Tile 0: floor (checkerboard stone)
const unsigned char floorTile[] = {
    0x18,0x18,0x24,0x24,0x18,0x18,0x24,0x24,
    0x18,0x18,0x24,0x24,0x18,0x18,0x24,0x24,
    0x18,0x18,0x24,0x24,0x18,0x18,0x24,0x24,
    0x18,0x18,0x24,0x24,0x18,0x18,0x24,0x24
};

// Tile 1: wall (solid brick)
const unsigned char wallTile[] = {
    0xFF,0xFF,0x81,0x81,0xBD,0xBD,0x81,0x81,
    0xFF,0xFF,0x81,0x81,0xBD,0xBD,0x81,0x81,
    0xFF,0xFF,0x81,0x81,0xBD,0xBD,0x81,0x81,
    0xFF,0xFF,0x81,0x81,0xBD,0xBD,0x81,0x81
};

// -----------------------------------------------------------
// Player sprite: 8x16 (two stacked tiles)
// -----------------------------------------------------------
const unsigned char hero_tiles[] = {
    // Tile 0: upper half (square outline)
    0xFF,0xFF,0x81,0x81,0x81,0x81,0x81,0x81,
    0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
    0xFF,0xFF,0x81,0x81,0x81,0x81,0x81,0x81,
    0x81,0x81,0x81,0x81,0x81,0x81,0xFF,0xFF,

    // Tile 1: lower half
    0xFF,0xFF,0x81,0x81,0x81,0x81,0x81,0x81,
    0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
    0xFF,0xFF,0x81,0x81,0x81,0x81,0x81,0x81,
    0x81,0x81,0x81,0x81,0x81,0x81,0xFF,0xFF
};

// -----------------------------------------------------------
// CGB palettes (4 colors each)
// -----------------------------------------------------------
const UWORD bg_palettes[] = {
    RGB_WHITE, RGB_LIGHTGRAY, RGB_DARKGRAY, RGB_BLACK
};

const UWORD spr_palettes[] = {
    RGB_WHITE, RGB_LIGHTGRAY, RGB_DARKGRAY, RGB_BLACK
};

// -----------------------------------------------------------
// Map data: 20x18 tiles, with wall borders
// -----------------------------------------------------------
#define MAP_W 20
#define MAP_H 18
unsigned char map[MAP_W * MAP_H];

// Build map with walls on the edges
void build_map(void) {
    for (uint8_t y = 0; y < MAP_H; y++) {
        for (uint8_t x = 0; x < MAP_W; x++) {
            if (x == 0 || y == 0 || x == MAP_W-1 || y == MAP_H-1) {
                map[y*MAP_W + x] = 1; // wall
            } else {
                map[y*MAP_W + x] = 0; // floor
            }
        }
    }
}

/**
 * Check if a pixel position collides with a wall tile.
 * Returns 1 if blocked, 0 if free.
 */
uint8_t is_blocked(uint8_t px, uint8_t py) {
    uint8_t tx = px >> 3;
    uint8_t ty = py >> 3;
    if (tx >= MAP_W || ty >= MAP_H) return 1;
    return map[ty * MAP_W + tx] == 1;
}

void main(void) {
    // Enable 8x16 sprite mode
    SPRITES_8x16;

    // Enable Color Game Boy features if available
    cgb_compatibility();

    // Load background tiles into VRAM
    set_bkg_data(0, 2, floorTile);
    build_map();
    set_bkg_tiles(0, 0, MAP_W, MAP_H, map);

    // Apply palettes if running on CGB
    if (_cpu == CGB_TYPE) {
        set_bkg_palette(0, 1, bg_palettes);
        set_sprite_palette(0, 1, spr_palettes);
    }

    // Load player sprite
    set_sprite_data(0, 2, hero_tiles);
    set_sprite_tile(0, 0); // upper tile
    set_sprite_tile(1, 1); // lower tile
    uint8_t x = 80, y = 72; // player position
    move_sprite(0, x, y);
    move_sprite(1, x, y + 8);

    SHOW_BKG; SHOW_SPRITES; DISPLAY_ON;

    uint8_t speed = 1;

    while (1) {
        wait_vbl_done();

        uint8_t keys = joypad();

        int8_t dx = 0, dy = 0;
        if (keys & J_LEFT)  dx = -speed;
        if (keys & J_RIGHT) dx =  speed;
        if (keys & J_UP)    dy = -speed;
        if (keys & J_DOWN)  dy =  speed;

        // Candidate new position
        uint8_t new_x = x + dx;
        uint8_t new_y = y + dy;

        // Collision check: top and bottom of sprite
        if (!is_blocked(new_x - 4, new_y - 8) && !is_blocked(new_x - 4, new_y)) {
            x = new_x;
        }
        if (!is_blocked(x - 4, new_y - 8) && !is_blocked(x - 4, new_y)) {
            y = new_y;
        }

        move_sprite(0, x, y);
        move_sprite(1, x, y + 8);
    }
}
