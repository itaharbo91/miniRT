# miniRT

A simple **raytracer** written in C using the miniLibX graphics library. This project renders 3D scenes with spheres, planes, and cylinders, featuring realistic lighting, shadows, and interactive camera controls.

> **👥 Collaborative project by 2 developers**
> 
> ⭐ **Project completed with bonus features: cones, specular reflection, checkerboard textures, and multiple colored lights**

## 📋 Description

**miniRT** is a raytracing engine that generates photorealistic images from `.rt` scene description files. The project implements:

### Mandatory Part ✅
- **Ray tracing algorithm** - Generate rays from camera through each pixel
- **3 geometric objects**:
  - **Spheres** (`sp`) - Perfect spheres with position and diameter
  - **Planes** (`pl`) - Infinite planes with normal vector
  - **Cylinders** (`cy`) - Finite cylinders with axis, diameter, and height
- **Camera** (`C`) - Position, orientation (look-at vector), and FOV
- **Ambient lighting** (`A`) - Global illumination with intensity and color
- **Point light sources** (`L`) - Positioned lights with brightness ratio
- **Phong lighting model** - Ambient + diffuse lighting
- **Shadows** - Ray casting to light sources
- **Color management** - RGB colors for objects and lights
- **Interactive controls** - Camera movement and rotation
- **Scene parsing** - `.rt` file format with validation

### Bonus Part ⭐
- **Cone primitive** (`co`) - Cone geometric object with apex and angle
- **Specular reflection** - Phong specular component (shininess parameter)
- **Checkerboard texture** - Procedural checkerboard pattern for all objects
- **Multiple colored lights** (`li`) - Support for multiple light sources with individual colors
- **Enhanced object controls** - Translate, rotate, and resize objects in real-time

## 🚀 Compilation

```bash
make          # Compile mandatory version
make bonus    # Compile bonus version with extra features
make clean    # Remove object files
make fclean   # Remove everything including binary
make re       # Recompile from scratch
```

### Requirements

**Linux (Ubuntu/Debian):**

First, install X11 development libraries:
```bash
sudo apt-get install libx11-dev libxext-dev libxrandr-dev \
                     libxrender-dev libxfixes-dev libxinerama-dev \
                     libbsd-dev
```

Then, clone MinilibX-Linux:
```bash
cd others
git clone https://github.com/42Paris/minilibx-linux.git
cd ..
```

MinilibX will be compiled automatically with `make`.

**macOS:**
```bash
# MinilibX is included, no additional packages needed
make -f Makefile_mac
```

## 💻 Usage

```bash
# Mandatory version
./miniRT others/test/mandatory.rt

# Bonus version
./miniRT_bonus others/test/bonus.rt
```

### Scene File Format (`.rt`)

```
A  0.2                                    255,255,255

C  -50,0,20          0,0,1               70
L  -40,0,30                      0.7     255,255,255

pl 0,0,0             0,1.0,0             255,0,225
sp 0,0,20                        20      255,0,0
cy 50.0,0.0,20.6     0,0,1.0     14.2    21.42    10,0,255
```

**Element format:**
- `A` - Ambient lighting: `ratio (0.0-1.0)` `R,G,B (0-255)`
- `C` - Camera: `x,y,z` `orientation_x,y,z (-1.0 to 1.0)` `FOV (0-180)`
- `L` - Light: `x,y,z` `brightness (0.0-1.0)` `R,G,B`
- `sp` - Sphere: `x,y,z` `diameter` `R,G,B`
- `pl` - Plane: `x,y,z` `normal_x,y,z` `R,G,B`
- `cy` - Cylinder: `x,y,z` `axis_x,y,z` `diameter` `height` `R,G,B`

**Bonus elements:**
- `co` - Cone: `x,y,z` `axis_x,y,z` `diameter` `height` `R,G,B` `specular` `checkerboard`
- `li` - Additional colored light: `x,y,z` `brightness (0.0-1.0)` `R,G,B` (multiple lights supported)

**Bonus format (additional parameters):**
```
pl 0,0,0    0,1.0,0    255,0,225    5      0
sp 0,0,20              20          255,0,0      9      0
cy 50,0,20  0,0,1.0    14.2  21.4  10,0,255     500    1
co -15,0,15 0,1.0,0    20    31.9  255,255,255  100    0

li -30,0,20                        0.5          255,255,255
li 20,0,1                          0.2          005,255,225
```
- **4th parameter (Specular)**: Shininess value `0.0-500.0` for specular highlights
- **5th parameter (Checkerboard)**: `1` = enabled, `0` = disabled

**Bonus elements:**
- `co` - Cone: `x,y,z` `axis_x,y,z` `diameter` `height` `R,G,B` `specular` `checkerboard`
- `li` - Multiple colored lights: `x,y,z` `brightness (0.0-1.0)` `R,G,B` (unlimited count)

## 🎮 Interactive Controls

### Camera Controls (Mode 1)
```
Arrow Keys (←↑↓→)     Move camera horizontally and vertically
X / Z                  Move camera forward / backward
W / S                  Rotate camera up / down (pitch)
A / D                  Rotate camera left / right (yaw)
Q / E                  Roll camera left / right
```

### Object Controls (Modes 2-5)
```
TAB / Shift+TAB       Cycle through objects of selected type
Arrow Keys             Translate selected object
X / Z                  Move object forward / backward
W / S / A / D / Q / E  Rotate object on all axes
+ (keypad)             Increase object diameter/radius
- (keypad)             Decrease object diameter/radius
N / M                  Increase / decrease cylinder/cone height (modes 3/4)
```

### Mode Selection
```
1                      Camera mode
2                      Sphere selection mode
3                      Cylinder selection mode
4                      Plane selection mode
5                      Light source mode
```

### General
```
ESC                    Exit program
```

## 🧠 Architecture

### 1. Scene Parser

Reads `.rt` files and validates scene description:
```
Input: scene.rt file
↓
Tokenization: Split lines, parse identifiers
↓
Validation: Check value ranges, format correctness
↓
Scene structure: Populate t_scene with objects
```

**Key files:**
- `srcs/parser/parser.c` - Main parsing loop
- `srcs/parser/parse_camera.c` - Camera parsing
- `srcs/parser/parse_light.c` - Light source parsing
- `srcs/parser/parse_sphere.c` - Sphere parsing
- `srcs/parser/parse_plane.c` - Plane parsing
- `srcs/parser/parse_cylinder.c` - Cylinder parsing
- `bonus/parser/parse_cone_bonus.c` - Cone parsing (bonus)

### 2. Ray Generation

Generates rays from camera through viewport:
```
For each pixel (x, y):
  ↓
Compute viewport coordinates (u, v)
  ↓
Ray origin = camera position
Ray direction = normalize(viewport_point - camera)
  ↓
Cast ray into scene
```

**Implementation:**
- `srcs/render/generate_ray.c` - Ray construction
- `srcs/render/viewport.c` - Viewport setup with FOV calculation

### 3. Ray-Object Intersection

Tests ray intersection with all scene objects:

**Sphere intersection:**
```
Equation: ||P - C||² = r²
where P = ray.origin + t * ray.direction

Quadratic: a*t² + b*t + c = 0
Discriminant Δ = b² - 4ac
If Δ > 0: Two intersections (entry/exit)
Return closest positive t
```

**Plane intersection:**
```
Equation: (P - P₀) · N = 0
t = ((P₀ - ray.origin) · N) / (ray.direction · N)
If t > 0: Intersection exists
```

**Cylinder intersection:**
```
Parametric form with axis vector
Solve quadratic equation for body
Check endcap intersections
Return closest valid t
```

**Files:**
- `srcs/render/sphere_intersections.c` - Sphere ray casting
- `srcs/render/plane_intersections.c` - Plane ray casting
- `srcs/render/cylinder_intersections.c` - Cylinder ray casting
- `bonus/render/cone_intersections_bonus.c` - Cone ray casting (bonus)

### 4. Lighting Model (Phong Shading)

**Mandatory (Ambient + Diffuse):**
```
I = I_ambient + I_diffuse

I_ambient = K_a * L_ambient
I_diffuse = K_d * (N · L) * L_light

where:
  K_a = ambient coefficient (scene ambient ratio)
  K_d = diffuse coefficient (1.0)
  N = surface normal at intersection
  L = normalized light direction
  L_ambient = ambient light color
  L_light = point light color × brightness
```

**Bonus (+ Specular):**
```
I = I_ambient + I_diffuse + I_specular

I_specular = K_s * (R · V)^shininess * L_light

where:
  K_s = specular coefficient (1.0)
  R = reflected light direction: 2(N·L)N - L
  V = view direction (ray towards camera)
  shininess = specular parameter from .rt file
```

**Shadow rays:**
```
For each light source:
  Cast ray from intersection point to light
  If ray hits object before reaching light:
    → Point is in shadow, skip diffuse/specular
  Else:
    → Point is lit, add light contribution
```

**Files:**
- `srcs/colors/colors_calculations.c` - Phong lighting computation
- `srcs/colors/colors_utils.c` - Color manipulation utilities

### 5. Rendering Pipeline

```
Initialize window (1200×900 resolution)
  ↓
For each pixel (x, y):
  ↓
  Generate camera ray
  ↓
  Find closest intersection with scene objects
  ↓
  If intersection found:
    ↓
    Compute surface normal
    ↓
    Apply Phong lighting (ambient + diffuse + specular)
    ↓
    Cast shadow rays to all lights
    ↓
    Apply checkerboard texture if enabled (bonus)
    ↓
    Clamp color to [0, 255]
  Else:
    ↓
    Set pixel to black (background)
  ↓
Put pixel to image buffer
  ↓
Display image to window
```

**Files:**
- `srcs/render/render_ray.c` - Main rendering loop
- `srcs/window/window.c` - MLX window management
- `srcs/window/controls_infos.c` - HUD information display

### 6. Matrix Transformations

Used for camera and object rotations:
```
Rotation matrices (X, Y, Z axes):

R_x(θ) = | 1    0        0     |
         | 0  cos(θ)  -sin(θ) |
         | 0  sin(θ)   cos(θ) |

R_y(θ) = | cos(θ)   0  sin(θ) |
         |   0      1    0    |
         | -sin(θ)  0  cos(θ) |

R_z(θ) = | cos(θ)  -sin(θ)  0 |
         | sin(θ)   cos(θ)  0 |
         |   0        0     1 |
```

**Files:**
- `srcs/matrix/matrix.c` - Matrix operations
- `srcs/matrix/matrix_transformations.c` - Rotation matrices
- `srcs/math/vectors_calculations.c` - Vector math (dot, cross, normalize)
- `srcs/math/vectors_calc_bis.c` - Additional vector operations

## 📊 Technical Details

### Coordinate System
- **Right-handed coordinate system**
- X-axis: Right
- Y-axis: Up
- Z-axis: Forward (into the screen)

### FOV (Field of View)
```
tan(FOV/2) = (viewport_width/2) / focal_length
```

### Normal Vectors
- **Sphere**: `N = normalize(P - center)`
- **Plane**: `N = plane.normal` (from .rt file)
- **Cylinder**: 
  - Body: `N = normalize((P - axis_point) - ((P - axis_point)·axis)axis)`
  - Endcaps: `N = ±axis`

### Checkerboard Pattern (Bonus)
```c
// 3D procedural texture
bool checker = (int)(floor(x/size) + floor(y/size) + floor(z/size)) % 2;
if (checker)
    color = color_swap; // Alternate color
```

## 🧪 Testing

```bash
# Compile
make

# Test mandatory scenes
./miniRT others/test/mandatory.rt
./miniRT others/test/scene1_spheres.rt
./miniRT others/test/scene2_mixed.rt

# Compile bonus
make bonus

# Test bonus scenes
./miniRT_bonus others/test/bonus.rt
./miniRT_bonus others/test/specular_test.rt
./miniRT_bonus others/test/scene3_complex.rt
```

### Sample Test Scenes

**Mandatory scenes:**
- `mandatory.rt` - Basic scene with sphere, plane, cylinder
- `test_mandatory_visible.rt` - Visible mandatory elements
- `scene1_spheres.rt` - Multiple spheres testing
- `scene2_mixed.rt` - Mixed objects
- `test_sphere_origin.rt` - Sphere at origin
- `test_cylinder_y_axis.rt` - Cylinder along Y axis
- `test_plane_z_null.rt` - Plane with Z=0

**Bonus scenes:**
- `bonus.rt` - Specular reflection + checkerboard textures
- `test_bonus_centered.rt` - Bonus features with cones and multiple lights
- `specular_test.rt` - Specular highlight testing
- `scene3_complex.rt` - Complex scene with multiple objects
- `scene4_cylinders.rt` - Cylinder variations
- `scene5_perspective.rt` - Perspective testing
- `lighting_debug.rt` - Lighting validation

## 📚 Project Structure

```
miniRT/
├── Makefile                      # Build configuration
├── Makefile_mac                  # macOS specific build
├── includes/
│   └── minirt.h                  # Main header (mandatory)
├── includes_bonus/
│   └── minirt_bonus.h            # Bonus header
│
├── srcs/                         # Mandatory (43 C files)
│   ├── main/
│   │   ├── main.c                # Entry point
│   │   ├── error.c               # Error handling
│   │   └── clean.c               # Memory cleanup
│   │
│   ├── parser/                   # Scene file parsing (7 files)
│   │   ├── parser.c              # Main parser
│   │   ├── parse_camera.c        # Camera (C)
│   │   ├── parse_light.c         # Light source (L)
│   │   ├── parse_ambi_light.c    # Ambient light (A)
│   │   ├── parse_sphere.c        # Sphere (sp)
│   │   ├── parse_plane.c         # Plane (pl)
│   │   └── parse_cylinder.c      # Cylinder (cy)
│   │
│   ├── parser_utils/             # Parsing utilities (4 files)
│   │   ├── init_objects_memory.c # Memory allocation
│   │   ├── conv_value.c          # Value conversion
│   │   ├── conv_pointer_values.c # Pointer conversion
│   │   └── color_parse.c         # RGB parsing
│   │
│   ├── render/                   # Ray tracing engine (6 files)
│   │   ├── render_ray.c          # Main rendering loop
│   │   ├── generate_ray.c        # Ray generation
│   │   ├── viewport.c            # Viewport setup
│   │   ├── sphere_intersections.c   # Sphere ray casting
│   │   ├── plane_intersections.c    # Plane ray casting
│   │   └── cylinder_intersections.c # Cylinder ray casting
│   │
│   ├── colors/                   # Lighting calculations (2 files)
│   │   ├── colors_calculations.c # Phong shading
│   │   └── colors_utils.c        # Color utilities
│   │
│   ├── math/                     # Vector/matrix math (4 files)
│   │   ├── vectors_calculations.c   # Vector operations
│   │   ├── vectors_calc_bis.c       # Additional vector ops
│   │   ├── sphere_equations.c       # Sphere math
│   │   └── cylinder_equations.c     # Cylinder math
│   │
│   ├── matrix/                   # Transformation matrices (2 files)
│   │   ├── matrix.c                 # Matrix operations
│   │   └── matrix_transformations.c # Rotation matrices
│   │
│   ├── controls/                 # Interactive controls (6 files)
│   │   ├── key_handler.c         # Keyboard input handler
│   │   ├── key_controls.c        # Control logic
│   │   ├── choose_object.c       # Object selection
│   │   ├── object_translations.c # Object movement
│   │   ├── object_rotations.c    # Object rotation
│   │   └── object_resize.c       # Object scaling
│   │
│   ├── window/                   # MLX window management (2 files)
│   │   ├── window.c              # Window initialization
│   │   └── controls_infos.c      # HUD display
│   │
│   ├── utils/                    # Utilities (5 files)
│   │   ├── utils.c               # General utilities
│   │   ├── ft_atoi.c             # String to integer
│   │   ├── ft_strtof.c           # String to float
│   │   ├── ft_calloc.c           # Memory allocation
│   │   └── is_utils.c            # Character checks
│   │
│   └── get_next_line/            # File reading (2 files)
│       ├── get_next_line.c       # Line reader
│       └── get_next_line_utils.c # GNL utilities
│
├── bonus/                        # Bonus (53 C files)
│   ├── [Same structure as srcs/]
│   ├── parser/
│   │   └── parse_cone_bonus.c    # Cone primitive (co)
│   ├── parser_utils/
│   │   └── [Specular & checkerboard parsing]
│   └── render/
│       └── cone_intersections_bonus.c  # Cone ray casting
│
├── others/
│   ├── minilibx-linux/           # Graphics library
│   └── test/                     # Scene files (.rt)
│       ├── mandatory.rt          # Basic mandatory scene
│       ├── bonus.rt              # Bonus features demo
│       ├── scene1_spheres.rt     # Sphere test
│       ├── scene2_mixed.rt       # Mixed objects
│       ├── scene3_complex.rt     # Complex scene
│       ├── specular_test.rt      # Specular lighting
│       └── [additional test scenes]
│
└── README.md                     # This file
```

**Total:**
- **Mandatory:** 43 C files
- **Bonus:** 53 C files (includes cone, specular, checkerboard)

## 🎓 42 School

Common Core Project - Cercle 4

## 📌 Key Concepts

✅ **Ray Tracing Algorithm** - Photorealistic rendering technique
✅ **Geometric Intersections** - Sphere, plane, cylinder, cone equations
✅ **Phong Lighting Model** - Ambient, diffuse, specular components
✅ **Shadow Casting** - Ray casting to light sources
✅ **Vector Mathematics** - Dot product, cross product, normalization
✅ **Matrix Transformations** - Rotation matrices for camera/objects
✅ **Scene Description Language** - Custom `.rt` file format parser
✅ **Interactive Graphics** - Real-time camera and object manipulation
✅ **Memory Management** - Proper allocation/deallocation, leak-free
✅ **Error Handling** - Robust input validation and error messages

## 👤 Author

[@itaharbo91](https://github.com/itaharbo91)

---

**GitHub Description**: Ray tracing engine developed by 2 students in C with Phong shading, shadows, and interactive controls. Renders spheres, planes, cylinders, and cones with specular reflection and procedural textures - 96 C files implementing photorealistic 3D rendering.
