# B.R.A.R. - Bipedal Robotic Arm Runner

BRAR is an OpenGL-based game that kinematically simulates a bipedal 5-DOF robotic arm that tries to capure objects in the scene. The goal of this project is fuse my interest in robotics with concepts learned in the course. The majority of this project has focused on functionality and user interaction up to this point. There are still bugs that I am resolving within the funtionality itself, but it has come a very long way. Here are some of the major functionalities:

A. Forward kinematics - based controller to guide "chaser robot" to follow "runner robot." This was a pretty tricky concept to wrap my head around, but after many rounds of testing, it is working well. The utility of forward kinematics is extremly useful in robotics and robotics-based games, such as this one. The utility of forward kinematics is best observed in game mode 1, where the user needs to move around and collect items.

B. Orbiting lights on player's robot. These are now turned on by default.

C. Main menu with different game modes to choose from. 

D. Procedural object generation and object culling. As the robot(s) traverses through the scene, objects within a specified radius are removed and new ones are generated with random speeds, positions and values.  

E. Runner is no longer a simple ball. A small robot dog has been designed for runner.

### Future work:

A. Coundown clock and timer for game modes (chaser will become faster over time, item values will be worth less over time, too).

B. Scoreboard (using txt file).

C. While a redesign of the robot's legs has been completed, the arm will need more work. Also, the gripper will likely be larger, so that it will better appear to "clamp" items. 

D. Redesign of value-based items. The items have been primarily tested for function up to this point, so now I will be redesigning them to have a bit cooler appearence. Can I use obj files for these?

E. Redesign of more realistic terrain and simulate surface contact normal to it.

F. Add objects user (and computer) needs to navigate around. This will be a set of three objects.

G. RRT* algorithm for chaser (computer) to move around obstacles to get runner robot autonomously. This will serve as another integration of robotics into the course. RRT* is a very famous path-finding algorithm in robotics and implementing it correctly in the project would be great.

H. Many bug/functionality resolutions. For example, the objects go beyond intended as I generate them. Another example is that the runner robot can simple leave the chaser's grip - that's a new one. 

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
