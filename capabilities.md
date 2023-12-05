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