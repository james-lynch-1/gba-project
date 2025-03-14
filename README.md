# GBA project
A game implemented in C. In progress. Winner of the "Exists and is playable" award ~0.2 years running  
Use mGBA https://mgba.io/ to run it, or actual hardware I suppose  
The blue squid thing is named squinky ![squinky](https://github.com/james-lynch-1/gba-project/raw/master/src/squinky.png "Squinky")  

## CONTROLS:
D-pad: move character  
Spin D-pad clockwise: charge basic attack (max. 4 attacks active at once)  
A/B: Move crosshair down/up  
L/R: Move crosshair left/right  
Select: Change area  
You can also go to the left/right edge of the screen to load a new area (you may become stuck)  

## BUILDING:
Get the DevKitPro toolchain first, then run "make" to build the project  
GBA file is included in the repo so just run that if you want  

## IMPLEMENTED:
Collision detection for player/enemies and player/environment  
Reticle works and can be used to destroy enemies (red dots)  
Dynamic memory allocation for enemies and player attacks  
Countdown/time remaining UI for attacks  
Multiple areas  

## TO BE IMPLEMENTED:
Collectible weapons/attacks from enemies/item pickups  
Other types of attacks (screen filling, topleft/topright/bottomleft/bottomright quadrant area of effect)  
Shell script to convert exported Usenti maps to condensed collision maps  
Inventory system  
More detailed UI for player health, attacks, inventory etc.  
Removing copyright infringement  

## HOW TO MAKE A LEVEL
1. Import tileset into Tiled https://www.mapeditor.org/ and make a level using those tiles  
2. Export from Tiled as a png  
3. Use Usenti https://www.coranac.com/projects/usenti/ to export as a map (4bpp, u16, appropriate palette length)  
4. Collision: to make a collision map, simply export your map as a metatiled map. Make sure non-collision tiles are of value 0. Follow the format in the brin.c file

## THANKS TO
GBA guide "Tonc" https://gbadev.net/tonc/ and libtonc https://github.com/devkitPro/libtonc  
GBATEK https://problemkaputt.de/gbatek.htm  
gbadev discord  
