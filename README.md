# Breakout
A (very rough) prototype Breakout game made with SDL2.0

## Dependencies:

**SDL2-2.07:**

* SDL2.lib

* SDL2main.lib

* SDL2_image.lib

* SDL2_ttf.lib

* SDL2_mixer.lib

### Known Bugs/Shortcomings:
* Bottom right block being destroyed without getting hit
* Paddle physics only has 3 hit areas
* Ball physics very limited (limited collider logic currently on ball to block collision so direction change is not based on hit location)

#### Basic Controls:
* Move paddle with mouse or keyboard arrows, launch ball with mouseclick or spacebar press
