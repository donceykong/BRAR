# B.R.A.R. - Bipedal Robotic Arm Runner

BRAR is an OpenGL-based game that kinematically simulates a bipedal 5-DOF robotic arm that tries to capure objects in the scene. The goal of this project is fuse my interest in robotics with concepts learned in the course. The majority of this project has focused on functionality and user interaction up to this point. There are still bugs that I am resolving within the funtionality itself, but it has come a very long way. Here are some of the major functionalities:

### Game Modes:

0) User plays as robot arm and collects items to prevent a countdown timer from reaching zero.

1) User plays as item to run from robot arm as the arm gains speed and accuracy over time.


---

## DEPENDENCIES:

FreeType

>> sudo apt-get install libfreetype6-dev

--- 

## Game Modes:

0) User plays as robot and runs around while arm automatically adjusts to collect items. This is all done in an effort to prevent a countdown timer from reaching zero.

1) User plays as item to run from robot arm as the arm gains speed and accuracy over time.

--- 

### Item Values:

$$ RED SQUARE $$

    - Increses speed of robot with arm by 1, decreases runner robot speed by 1.

$$ BLUE CIRCLE $$

    - Increases runner by 1 and does not affect other robot.

$$ GREEN PARALLELOGRAM $$

    - Increases runner by 1 and decreaes speed of robot with arm by 1.

--- 

### Key bindings:

$$ Lighting $$

    - 0: Turn off or on lighting (Default is on)

$$ Moving around $$

    - ARROW KEYS: Using the arrow keys on your keyboard, you will be able to move the runner robot in game mode 0 and the collector robot in game mode 1.

$$ Views Modes $$

    - 1: Orbiting camera view
    - 2: Top-Down View

$$ Runner Speed $$

    - 4: Increase runner speed 
    - 5: Decrease runner speed

--- 
