# FreeKLAX
The UNIX port of an arcade puzzle game from 1990 (the original game developed by Dave Akers and Mark Stephen Pierce)

compile with GCC:
g++ klax.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -std=gnu++11 -o klax

The current version features basic game functionality including completing a stage.

Bricks have less pseudo-3D aspects than on the arcade version. This matter could be improved (it requires not just additional graphics but some new code as well) though very few players will notice anything. Also home computer ports seemed to have been lacking in this respect.

The functioning of algorithms that pick removed tiles, is not properly tested.

Known bugs:
Score values are negative
