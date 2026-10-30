*This project has been created as part of the 42 curriculum by mekaplan, enesaydi, irakdemi*

## Description

cub3D is a Linux/X11 raycasting maze viewer built with MiniLibX. A `.cub`
scene selects four wall textures (`NO`, `SO`, `WE`, `EA`), floor (`F`) and
ceiling (`C`) RGB colors, and an enclosed map with exactly one starting
direction (`N`, `S`, `E`, or `W`). The renderer casts one ray per screen column
and samples each wall texture at its own dimensions. The supplied textures
have distinct north/south/west/east patterns and different sizes.

The bonus build adds a player-centered circular minimap, solid interactive doors,
animated `P` sprites, mouse turning, and a ray/DDA teaching overlay using
the rays calculated for the main view. The bonus example includes `D` doors
and a `P` sprite; the mandatory example uses only mandatory tiles.

## Project Layout

```text
include/         Shared game types and mandatory/bonus declarations
src/core/        Application lifecycle, graphics, input, and movement
src/parser/      Scene elements, map loading, and validation
src/render/      DDA raycasting and textured wall rendering
src/mandatory/   Mandatory feature implementations
src/bonus/       Bonus features and their integration
assets/          Wall textures
maps/            Example mandatory and bonus scenes
build/           Generated objects and separate build executables
minilibx-linux/  Bundled third-party MiniLibX
```

The runnable `cub3D` remains at the project root as required by the subject.

## Instructions

Requires `cc`, `make`, an X11 display, and the X11/Xext development libraries
needed to build the bundled `minilibx-linux` library. Run from the project
root so relative texture paths resolve:

```sh
make
./cub3D maps/mandatory.cub

make bonus
./cub3D maps/bonus.cub
```

`make` selects the mandatory binary; `make bonus` selects the bonus binary.
Both builds keep separate objects and staged executables in `build/mandatory`
and `build/bonus`, so switching back with `make` does not recompile unchanged
files. `make clean` removes build objects and cleans MiniLibX; `make fclean`
also removes `cub3D`; `make re` performs a full mandatory rebuild.

Controls: `W`/`S` move forward/back, `A`/`D` strafe, left/right arrows turn,
and `Esc` or the window close button quits. Bonus: move the mouse horizontally
to turn, press `E` to toggle a nearby door in front of the player, and press
`Tab` to toggle the ray-debug overlay. With the overlay active, `J`/`K`
select the screen-column ray, `[`/`]` change the displayed ray sampling
interval, and `V` toggles the animated DDA-cell highlighting. The circular
minimap is visible even with the debug overlay off: a pixel is drawn only
when `(x - cx)^2 + (y - cy)^2 <= r^2` for the player-centered circle
(`src/bonus/bonus_circle_bonus.c`), and the ray overlay is clipped the same way.
Outside the debug overlay the minimap shows the player's field of view as a
fan of yellow rays (every `width / 24`-th screen column), each one ending
exactly where the 3D view's ray hit a wall.

Map legend: `1` wall, `0` floor, space void, `N`/`S`/`E`/`W` player facing,
and (bonus only) `D` closed door and `P` animated sprite. The player start
becomes floor after parsing. A scene must contain every texture and color
identifier once, followed by a closed map; ragged rows are allowed, but no
walkable tile may share an edge with void. Paths in the sample scenes
are relative to the working directory, not the `.cub` file. The bonus sprite
is drawn procedurally, not loaded from an extra texture. This build targets
Linux/X11 MiniLibX; it is not a portable macOS/Wayland-native application.

## Raycasting

For each screen column `x`, `ray.c` derives `camera_x = 2*x/width - 1`,
combines the player's direction and camera plane, then walks the map grid
by DDA until it hits a wall. The first crossed vertical or horizontal grid
boundary determines the wall face; the DDA side distances give the
perpendicular distance used for perspective projection, avoiding fisheye.
`render.c` uses the fractional hit coordinate for the texture's horizontal
position and scales its vertical coordinate from that texture's actual size.
Both direction and camera plane use the same rotation matrix. The bonus
records these very ray results for its depth-tested sprites and minimap;
sampling only changes which already-cast rays the minimap draws.

## Resources

- `minilibx-linux/README.md`: MiniLibX setup and platform details.
- Lode Vandevenne, [Raycasting](https://lodev.org/cgtutor/raycasting.html):
  camera-plane, DDA, texture coordinates, and sprite-projection reference.
- [Xlib Programming Manual](https://tronche.com/gui/x/xlib/): X11 events and
  window lifecycle used by MiniLibX.
- AI helped implement and test all modules, including the build setup and
  sample assets. Peer review is important: verify parsing, math, input,
  resource ownership, and bonus behavior independently before evaluation.
