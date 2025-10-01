# miniRT - Ray Tracing Project

A 3D ray tracer built in C using the miniLibX library, following 42 School norminette standards.

## Project Structure

### Core Components

```
├── includes/
│   └── minirt.h          # Main header with all structures and prototypes
├── srcs/minirt/
│   ├── minirt.c          # Main program entry point
│   ├── vector/           # Vector mathematics
│   │   ├── vector_ops.c
│   │   └── vector_utils.c
│   ├── color/            # Color operations
│   │   ├── color_ops.c
│   │   └── color_utils.c
│   ├── ray/              # Ray utilities
│   │   └── ray_utils.c
│   ├── camera/           # Camera functionality
│   │   └── camera.c
│   ├── objects/          # Object intersection and management
│   │   ├── intersect_sphere.c
│   │   ├── intersect_plane.c
│   │   ├── intersect_cylinder.c
│   │   ├── intersect_scene.c
│   │   └── object_utils.c
│   ├── lighting/         # Lighting calculations
│   │   └── lighting.c
│   ├── renderer/         # Rendering engine
│   │   └── renderer.c
│   ├── mlx/             # MLX window management
│   │   └── mlx_utils.c
│   ├── parser/          # Scene file parsing
│   │   ├── parser.c
│   │   ├── parse_scene_elements.c
│   │   └── parse_objects.c
│   └── utils/           # General utilities
│       └── utils.c
├── libft/               # Custom C library
├── libmlx/              # MiniLibX for Linux
├── libmlx_macos/        # MiniLibX for macOS
└── scenes/              # Scene files
    └── sample.rt        # Sample scene
```

## Key Structures

### Core Data Types

- **t_vec3**: 3D vector for positions, directions, and normals
- **t_color**: RGB color representation (0.0-1.0 range)
- **t_ray**: Ray with origin and direction
- **t_hit**: Intersection information
- **t_material**: Surface material properties

### Scene Elements

- **t_camera**: Camera with position, direction, and field of view
- **t_light**: Point light source
- **t_ambient**: Ambient lighting
- **t_scene**: Complete scene container

### Objects

- **t_sphere**: Sphere with center and radius
- **t_plane**: Infinite plane with point and normal
- **t_cylinder**: Finite cylinder with center, axis, radius, and height

## Features Implemented

### Mandatory Features

- [x] Sphere, plane, and cylinder primitives
- [x] Camera with configurable FOV
- [x] Point light source
- [x] Ambient lighting
- [x] Diffuse and specular lighting (Phong model)
- [x] Hard shadows
- [x] Scene file parsing (.rt format)
- [x] MLX window management
- [x] ESC key and window close handling

### Rendering Features

- [x] Ray-object intersection
- [x] Phong lighting model
- [x] Shadow ray casting
- [x] Anti-aliasing ready structure
- [x] Configurable materials

## Scene File Format

The program accepts `.rt` files with the following elements:

### Ambient Light
```
A [ratio] [R,G,B]
A 0.2 255,255,255
```

### Camera
```
C [position] [direction] [FOV]
C -50,0,20 0,0,1 70
```

### Light
```
L [position] [brightness] [R,G,B]
L -40,0,30 0.7 255,255,255
```

### Sphere
```
sp [center] [diameter] [R,G,B]
sp 0,0,20 20 255,0,0
```

### Plane
```
pl [point] [normal] [R,G,B]
pl 0,0,0 0,1,0 255,0,225
```

### Cylinder
```
cy [center] [axis] [diameter] [height] [R,G,B]
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

## Building and Running

### Prerequisites
- GCC compiler
- Make
- X11 development libraries (Linux)
- MiniLibX

### Build Commands
```bash
make          # Build the project
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild everything
make run      # Build and run with sample scene
```

### Usage
```bash
./miniRT [scene_file.rt]
```

## Technical Implementation

### Ray Tracing Pipeline

1. **Camera Setup**: Initialize camera with proper viewport calculations
2. **Ray Generation**: Create rays for each pixel through the viewport
3. **Intersection Testing**: Test rays against all scene objects
4. **Lighting Calculation**: Apply Phong lighting model with shadows
5. **Color Output**: Convert final color to RGB and display

### Mathematical Foundation

- Vector operations (add, subtract, multiply, normalize, dot product, cross product)
- Ray-sphere intersection using quadratic formula
- Ray-plane intersection using plane equation
- Ray-cylinder intersection with caps handling
- Phong reflection model for realistic lighting

### Memory Management

- Proper allocation and deallocation of scene objects
- Linked list structure for dynamic object storage
- Clean exit handling for all resources

## Architecture Benefits

This structure provides:
- **Modularity**: Each component is isolated and testable
- **Extensibility**: Easy to add new object types or features
- **Maintainability**: Clear separation of concerns
- **Performance**: Efficient ray-object intersection algorithms
- **Compliance**: Follows 42 norminette standards

## Adding New Features

To add new object types:
1. Define structure in `minirt.h`
2. Add enum value to `t_object_type`
3. Implement intersection function in `objects/`
4. Add parsing logic in `parser/`
5. Update object management functions

To add new lighting models:
1. Add material properties to `t_material`
2. Implement lighting function in `lighting/`
3. Update `calculate_lighting()` function

## Controls

- **ESC**: Exit the program
- **Red X**: Close window and exit

This foundation provides a solid base for a complete ray tracing implementation with room for advanced features like reflections, refractions, textures, and more complex geometries.