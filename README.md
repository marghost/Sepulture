# Sépulture
This GBC game is designed for learning and serves as a foundation for a small but complete RPG project on the Game Boy Color.

## Requirements
- GBDK-2020 installed: https://github.com/gbdk-2020/gbdk-2020
- `make` (cygwin) and a working C compiler (GCC/Clang)
- A Game Boy emulator (SameBoy)

## Building
```bash
# Set this if GBDK is not in your PATH
export GBDK_HOME=/path/to/gbdk
make
```
The compiled ROM will be generated in `build/Sepulture.gbc`.

## Running
- SameBoy: `c:/sameboy/sameboy.exe build/Sepulture.gbc`

## Controls
- **D-Pad**: Move the hero (basic wall collision)
- **Start**: Toggle movement speed (normal/turbo) - demo purpose
- **Select**: Reset player position

## Project Structure
- `src/main.c` — main game loop, GBC palette initialization, simple map, player sprite, input handling.
- `assets/` — future location for tilesets, maps, and audio data.
- `include/` — custom headers.
- `build/` — compiled output.
- `Makefile` — build system for GBDK.

# Licence
[![CC BY-NC-SA 4.0][cc-by-nc-sa-shield]][cc-by-nc-sa]

This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg
