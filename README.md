# cub3d
This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting.
Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

## Program Execution
`./cub3D <map.cub>`


### Map content
The program must take as a first argument a scene description file with the `.cub`
extension.
- The map must be composed of only 6 possibles characters
  - `0` - empty space
  - `1` - wall
  - `N, S, E, W` - player start position and spawning orientation
- The map must be closed/surrounded by walls, if not the program must return an error.
- Except for the map content, each type of element can be separated by one or
  more empty line(s).
- Except for the map content which always has to be the last, each type of
  element can be set in any order in the file.
- Except for the map, each type of information from an element can be separated
  by one or more space(s).

#### Textures
- `NO ./path_to_the_north_texture`
- `SO ./path_to_the_south_texture`
- `WE ./path_to_the_west_texture`
- `EA ./path_to_the_east_texture`

#### Colors
Floor and ceiling colors. **RGB** colors in range [0,255]
- `F 200,100,0`
- `C 225,30,0`

### Controls
- `W, A, S, D` - move the point of view through the maze
- `Left and right arrow keys` - look left and right in the maze
- `Esc` - close the window
- `Red cross` - close the window

## Resources
- [cub3d - 42 Docs](https://harm-smits.github.io/42docs/projects/cub3d.html)
- [Cube3d](https://b-bischoff.github.io/web/cube3d.html)