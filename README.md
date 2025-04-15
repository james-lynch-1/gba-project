# GBA project <img align="center" src="https://raw.githubusercontent.com/james-lynch-1/gba-project/refs/heads/main/squinky.png">
A game implemented in C. In progress. Winner of the "Exists and is playable" award  
Use mGBA https://mgba.io/ to run it, or actual hardware I suppose  

## CONTROLS:
D-pad: move crosshair  
Spin D-pad: charge cross attack (max. 4 attacks active at once)  
L: Increase crosshair movement speed  
R: Fire basic attack  
A: Move character in direction of reticle  
Start: Add new attack to attack list (debug feature)  
(Hold one of the eight directions to change the attack type (cardinal + diagonals), or no direction for a cross-shaped attack.)  
Select: Change area  
You can also go to the left/right edge of the screen to load a new area (you may become stuck).  

## BUILDING:
Get the DevKitPro toolchain first https://devkitpro.org/wiki/Getting_Started, then run "make" to build the project  
GBA file is included in the repo so just run that if you want  

## IMPLEMENTED:
Collision detection for player/enemies and player/environment  
Reticle works and can be used to destroy enemies (red dots)  
Different attack types (screen filling, top-left/top-right/bottom-left/bottom-right quadrant area of effect)  
Dynamic memory allocation for enemies and player attacks  
Countdown/time remaining UI for attacks  
Multiple areas  
Item pickups  

## TO BE IMPLEMENTED:
Memory manager for sprite VRAM  
Collectible weapons/attacks from enemies  
Basic enemy AI/movement  
Shell script to convert exported Usenti maps to condensed collision maps  
Inventory system  
Detailed UI for player health, attacks, inventory etc.  
Audio  
Fun  

## HOW TO MAKE A LEVEL
1. Import tileset into Tiled https://www.mapeditor.org/ and make a level using those tiles  
2. Export from Tiled as a png  
3. Use Usenti https://www.coranac.com/projects/usenti/ to export as a map (4bpp, u16, appropriate palette length)  
4. Collision: to make a collision map, simply export your map as a metatiled map. Make sure non-collision tiles are of value 0. Follow the format in the brin.c file

## THANKS TO
GBA guide "Tonc" https://gbadev.net/tonc/ and libtonc https://github.com/devkitPro/libtonc  
GBATEK https://problemkaputt.de/gbatek.htm  
gbadev discord  
