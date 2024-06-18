# Game Design Document

## Section 0: Summary
Team Members: Ashiria, Emily, Sani 
The game we choose to create will be called “Beaver Jump”. Beaver Jump is a variation of Doodle Jump with more features and a beaver instead of the doodle. The game's goal is to jump as far high as possible without falling to the ground or getting hit by enemy bullets. In doing so, the beaver will collect points or power-ups that will make the game more interesting. 

## Section 1: Gameplay
Like Doodle Jump, the game progresses with the Beaver jumping on tiles and moving up the screen. As the beaver continues to jump higher, the screen will be moved up to create an animated background effect. The higher the beaver goes, the more points will accumulate. Furthermore, we will have one attacker that will invade the beaver from the sky. It will shoot bullets from random locations as it moves across the top of the screen. It will remain moving horizontally across the top of the screen, such that the beaver will never come in contact with it. While there is no winning condition, the user will lose when the beaver falls off a tile off the screen or when it gets shot by the invader. As the beaver collects points and moves higher up, some graphics appear to make the game more interesting. 

We will be using the keyboard to control the beaver’s motion side to side when navigating the tiles to jump higher. Our game will incorporate the physics engine by using collisions, springs, gravity, and keyboard navigation, where we have implemented most of these functionalities in previous weeks. We will be drawing polygons for the tiles and bullets, but use sprites for the beaver and invader. 


## Section 2: Feature Set

# Beaver Game Features

| Developer | Priority 1 Features                                      | Priority 2 Features                                             | Priority 3 Features                  | Priority 4 Features                                      |
|-----------|----------------------------------------------------------|-----------------------------------------------------------------|--------------------------------------|----------------------------------------------------------|
| Ashiria   | - tiles spawn randomly and score counting   |  Disappearing and moving tiles  | - Implementing home screen for single vs multiplayer    | -  - Add text when the game is over | - Add text when the game is over and restart game                 |
| Sani      | - Multiplayer beavers (arrow keys and AWD keys) and jumping elastically off tiles|     Create enemy invaders and shoot at random intervals and score of the player updates depending on height | - Spring tiles | - Trampolines, and parachutes                    |
| Emily     | - Scroll the screen up (only tiles, beaver stays const at max) as the beaver jumps, remove old and generate new tiles      | - Game ends when player is shot by attacker bullet or falls off platform (falling beaver) |  - Sound effects | Powerups to shield from enemy bullets |

- Graphics and sprites: the beaver, costumes, different kinds of tiles, background, springs and power-ups, invader, bullets
- Sound effects: sound when beaver jumps, gets hit, and falls
- Scrolling: scrolling when beaver jumps so that tiles are being generated
- Rendering of text: keeping track of the score in the top corner, as well as the “you lose” message when the beaver falls
- Key handlers: arrow keys for controlling where the beaver moves to
- Enemy: invader that moves across the screen shooting bullets


## Section 3: Timeline
| Deadline  | Task Description                        |
|-----------|-----------------------------------------|
| Week 1    | Finish Priority 1 tasks                 |
| Week 2    | Finish Priority 2 tasks                 |
| Week 3    | Finish Priority 3 and 4 tasks           |

## Section 4: Disaster Recovery
Sani - In case I fall behind, I plan to get back on track by working on weekends and attending office hours in case I am stuck on any conceptual complications. In the worst case, me and my teammates will plan on redistributing some tasks if any particular functionality ends up being harder than we expected. 

Ashiria - If I fall behind I plan to use office hours to fix my specific bugs. I will also reference the previous code from projects which could be relevant to use in our beaver jump project. I will discuss my challenges with my team members so they can provide a new perspective and help me move forward with the problem.

Emily - If I fall behind, I plan to get back on track by attending office hours for the challenges I face in my task, whether it be debugging or conceptual questions. I will reference past projects for better understanding of the tasks I did not implement in previous weeks, as well as refer to group mates' knowledge in previous tasks. In the worst case, my teammates and I will redistribute tasks if neither the TAs or my group members could help me in understanding or completing this task. 


