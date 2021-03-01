# Particle-Swarm-Optimization-Neighborhood-Based
Hybrid implementation with c ++ and python
![swarm1](https://user-images.githubusercontent.com/75484097/109506006-d82dba00-7aa5-11eb-8878-b044e688297e.jpg)

written by Niv Nagli free code to use and I will be happy to help anyone who wants: itsniv@gmail.com 


GIF from my program:

![ezgif com-gif-maker](https://user-images.githubusercontent.com/75484097/109510449-b1be4d80-7aaa-11eb-98d8-63062a25cba4.gif)



# Introduction:
"Particle swarm optimization (PSO) is a population-based optimization technique inspired by the motion of bird flocks and schooling fish. PSO shares many similarities with evolutionary computation techniques. The system is initialized with a population of random solutions, and the search for the optimal solution is performed by updating generations."
Quote: 
https://www.sciencedirect.com/topics/engineering/particle-swarm-optimization

"PSO is a metaheuristic as it makes few or no assumptions about the problem being optimized and can search very large spaces of candidate solutions. However, metaheuristics such as PSO do not guarantee an optimal solution is ever found."
Quote: https://en.wikipedia.org/wiki/Particle_swarm_optimization

# The formula:

![swarmf](https://user-images.githubusercontent.com/75484097/109508250-555a2e80-7aa8-11eb-9f7a-67906e311e10.png). ![swarmf2](https://user-images.githubusercontent.com/75484097/109508261-58551f00-7aa8-11eb-8f55-0dc2c13458cf.png)

     *                                          Legend:ֿ
     * x_id(k) = current location,  x_id(k+1) = next location
     *
     * v_id(k) = velocity => in our program known as Speed..  v_id(k+1) = next velocity
     *
     * k = the latest time point,  k+1 = next time point
     * 
     *
     * P_id(k) = the location of the personal_best in the same time point.
     *
     * P_gd(k) = the location of the global_best in the same time point.
     *
     * r1 & r2 = random numbers we creating "randomly" in each time point for the calculate of the algorithm.
     *
     * c1, c2 = constants that produce acceleration to the next direction.
     *
     * w = "Inertia Weight": " The role of the inertia weight  is considered very important in PSO convergence behavior.
     * the inertia weight is applied to control the impact of the previous history of velocities on the current velocity. "
     * Quoted: "https://www.researchgate.net/publication/275066387_Novel_Particle_Swarm_Optimization_and_Its_Application_in_Calibrating_the_Underwater_Transponder_Coordinates"

In fact what we see in the first line is the calculation of the next velocity of the particle and in the second line what appears is the formula for updating the position.




# My design :

The implementation I chose for my program is a hybrid that combines the use of c++ and python code languages,
All calculations for the particle location will take place in the c++ executable file, and the central program management and visualization will take place in python.

the c++ executable files works with input files that must meet the standards of the program:
------
1)  init.txt || init2.txt:

The boot file will be either init.txt or init2.txt depending on what stage of visualization we are in,
I created this separation because our python program will need to update and change the contents of the input file for the c++ program 
so we will only use init.txt in the first run of the visualization, 
and will use init2 in all other runs thus ensuring that init.txt will not change at any stage of the program.
The number of particles should appear in the first row of files, followed by the coordinates of their initial location and initial velocity.

2) target.csv:

target.csv will contain the location of our target in the 2d surface, that will be obtained using the python program or through manual entry.

----------------------
The program in c++ was written using the term "Drone" instead of a "Particle" and our search surface was called "Forest" because I originally got the task as a home exercise that partially implement the current implementation ...

I invested a lot of time in documenting the code in c ++ so if anyone is interested in delving deeper I recommend him read the documentation in the code.
-------
----------------------

python files:
------------
1) Draggable_Target.py






2) main.py











