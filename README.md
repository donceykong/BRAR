# B.R.A.R. - Bipedal Robotic Arm Runner

BRAR is an OpenGL-based game that simulates a bipedal 5-DOF robotic arm that tries to capure objects in the scene. 

BRAR has been tested and verified on macOS Sonoma and Ubuntu 22.04.

--- 

## Timeline 
### Oct 29 - Nov 4
- Ground scene and joint limit.
- Self-collision detection.
- Use spheres as initial objects (for testing).

### Nov 5 - Nov 11
- Design baby robot legs onto robot. These will follow some simple back-and-fourth pattern when the robot moves.
- Test initial tracking algorithms for the robot to chase the ball.

### Nov 12 - Nov 18
- Inverse kinematics. Will verify through user-controlled item that the robot attempts to grab.

### Nov 19 - Nov 25

### Nov 26 - Dec 02

--- 
## Game Modes:

1) 

2) 

--- 

### Key bindings:
$$ Lighting $$
    - 0: Turn off or on lighting (Default is off)
    - t: Move light upwards
    - f: Move light to the left
    - g: Move light to the right
    - v: Move light to the downwards

$$ Texture $$
    - 4: Turn textures on/off
    - 5: Switch texture to have different Bitmap as texture

$$ Views Modes $$
    - 1: Orthographic view (Default)
    - 2: Perspective view
    - 3: First-person view (Use keys to move about scene)

$$ Joint 0 $$
    - A: Move base clockwise about Z
    - D: Move base joint counterclockwise about Z

$$ Joint 1 $$
    - W: Tilt joint1 up
    - K: Tilt joint1 down

$$ Joint 2 $$
    - Y: Tilt joint2 up
    - H: Tilt joint2 down

$$ End Effector $$
    - UP: tilt gripper UP
    - DOWN: tilt gripper DOWN
    - LEFT: rotate gripper Counterclockwise
    - RIGHT: rotate gripper Clockwise
    - J: close gripper
    - K: open gripper

--- 