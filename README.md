# cub3d
Basic subject version of cub3d project from 42 cursus.
Run with .cub file as first argument. If second argument is "--save", a .bmp file of the first rendered image will be created.

Example format for a .cub file:

R 1920 1080
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
S ./path_to_the_sprite_texture
F 220,100,0
C 225,30,0
11111111111111111111111111111
10000000001100000000000000001
10010000000000000000000010001
10000000001100000111011110001
11110111111111011101010010001
10002000000000001100000010001
11000000110101011111011110N01
11111111111111111111111111111
