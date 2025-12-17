# Cub3D - 3D Game Engine

A raycasting-based 3D game engine inspired by Wolfenstein 3D, built in C using the MiniLibX graphics library. This project is part of the 42 School curriculum.

## 🎮 Description

Cub3D is a first-person perspective game engine that uses raycasting techniques to render a 3D maze from a 2D map. Navigate through the environment using keyboard controls and experience real-time 3D rendering with textured walls.

## ✨ Features

- **Raycasting Engine**: Efficient DDA (Digital Differential Analysis) algorithm for ray-wall intersection
- **Textured Walls**: Four directional wall textures (North, South, East, West)
- **Customizable Colors**: Configurable floor and ceiling colors
- **Smooth Movement**: Fluid player movement and rotation
- **Map Validation**: Comprehensive map parsing with flood-fill algorithm for enclosed space verification
- **Error Handling**: Robust validation for map files, textures, and colors

## 🛠️ Technical Details

### Technologies
- **Language**: C99
- **Graphics Library**: MiniLibX (X11)
- **Build System**: Make

### Key Algorithms
- **DDA Raycasting**: For efficient ray-wall collision detection
- **Flood Fill**: For map validation and boundary checking
- **Texture Mapping**: Per-pixel texture rendering on walls

## 📋 Requirements

- GCC compiler
- Make
- X11 development libraries
- MiniLibX library

## 🚀 Installation

1. Clone the repository:
```bash
git clone https://github.com/AelElz/3Dgame.git
cd 3Dgame
```

2. Compile the project:
```bash
make
```

3. Run the game:
```bash
./cub3d map/map.cub
```

## 🎯 Usage

### Controls
- **W/A/S/D**: Move forward/left/backward/right
- **Left/Right Arrow Keys**: Rotate camera
- **ESC**: Exit game
- **X (Close button)**: Exit game

### Map File Format

The map file (`.cub`) must contain:

1. **Texture Paths**:
```
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm
```

2. **Colors** (RGB format):
```
F 220,100,0    # Floor color
C 225,30,0     # Ceiling color
```

3. **Map Grid**:
```
1111111111
1000000001
1000N00001
1000000001
1111111111
```

### Map Rules
- `1`: Wall
- `0`: Empty space (walkable)
- `N/S/E/W`: Player start position and orientation
- Map must be enclosed by walls
- Only one player spawn point allowed
- Spaces within enclosed walls are treated as floor tiles

### Example Map
```
NO ./src/texture/north.xpm
SO ./src/texture/south.xpm
WE ./src/texture/west.xpm
EA ./src/texture/east.xpm
F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## 🏗️ Project Structure

```
3Dgame/
├── src/
│   ├── cub3d.c              # Main entry point
│   ├── events.c             # Event handling (keyboard, window)
│   ├── img.c                # Image management
│   ├── init_game/           # Game initialization
│   ├── move/                # Player movement logic
│   ├── ray/                 # Raycasting engine
│   ├── render/              # Rendering pipeline
│   ├── parsing/             # Map and config parsing
│   │   ├── colors/          # Color validation
│   │   ├── maps/            # Map parsing and validation
│   │   ├── player/          # Player spawn handling
│   │   └── textures/        # Texture loading
│   └── texture/             # Texture files (.xpm)
├── includes/
│   ├── cub3d.h              # Main header
│   ├── mlx.h                # MiniLibX header
│   └── libft/               # Custom C library
├── map/                     # Example map files
├── Makefile
└── README.md
```

## 🔧 Compilation Flags

```makefile
CFLAGS = -g -Wall -Wextra -Werror -I. -Iincludes
```

## 🧪 Testing

Test with different map configurations:
```bash
./cub3d map/test_spaces.cub
./cub3d map/valid_test.cub
```

## 📝 Map Validation

The engine performs comprehensive validation:
- ✅ File extension must be `.cub`
- ✅ All textures must exist and be valid `.xpm` files
- ✅ Colors must be valid RGB values (0-255)
- ✅ Map must be enclosed by walls
- ✅ Exactly one player spawn point
- ✅ No invalid characters in map
- ✅ No gaps or holes in map boundaries
- ✅ Empty lines between map sections are rejected

## 🐛 Common Issues

### Texture Loading Fails
- Ensure texture paths are correct
- Verify `.xpm` files are valid
- Check file permissions

### Map Validation Errors
- Ensure map is fully enclosed by walls (`1`)
- Check for only one player spawn (`N/S/E/W`)
- Verify no invalid characters in map
- Ensure proper spacing (spaces within walls are treated as floor)

### Compilation Errors
- Install X11 development libraries
- Ensure MiniLibX is properly installed
- Check that all required libraries are present

## 🤝 Contributing

This is a 42 School project. While direct contributions are not accepted for academic integrity, suggestions and bug reports are welcome.

## 📄 License

This project is part of the 42 School curriculum and follows their academic policies.

## 👥 Authors

- **ael-azha** - [@AelElz](https://github.com/AelElz)

## 🙏 Acknowledgments

- 42 School for the project subject
- Lode Vandevenne for raycasting tutorials
- Wolfenstein 3D for inspiration

## 📚 Resources

- [Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)

---

