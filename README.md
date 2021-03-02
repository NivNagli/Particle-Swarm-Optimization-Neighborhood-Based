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

![swarmf2](https://user-images.githubusercontent.com/75484097/109508261-58551f00-7aa8-11eb-8f55-0dc2c13458cf.png)





# My design :

The implementation I chose for my program is a hybrid design that combines the use of c++ and python code languages,
All calculations for the particles locations will take place in the c++ executable file, and the central program management and visualization will take place in python.

the c++ executable files works with input files that must meet the standards of the program:
------
1)  init.txt || init2.txt:

The boot file will be either init.txt or init2.txt depending on what stage of visualization we are in,
I created this separation because our python program will need to update and change the contents of the input file for the c++ program 
so we will only use init.txt in the first run of the visualization, 
and will use init2 in all other runs thus ensuring that init.txt will not change at any stage of the program.
The number of particles should appear in the first row of files, followed by the coordinates of their initial location and initial velocity.

Example for init files:

[init.txt](https://github.com/NivNagli/Particle-Swarm-Optimization-Neighborhood-Based/files/6064250/init.txt)

[init2.txt](https://github.com/NivNagli/Particle-Swarm-Optimization-Neighborhood-Based/files/6064252/init2.txt)




2) target.csv:

target.csv will contain the location of our target in the 2d surface, that will be obtained using the python program "Draggable_Target.py" or through manual entry.

# output files in case of valid inputs:

1) "moves.txt" : a file that will contain all the particle moves for 60 iterations of time as an input file for the python script


2) "iterations.txt": a file that will contain a genral control data for the Python script, 
the file will contain information about the number of iterations that the algorithm performed and the last locations of all the particles.



----------------------

The executable file created by our c ++ program is the implementation of the PSO algorithm under "Neighbors Standard":

 
 * " This topology allows all particles to communicate with all the other particles,
 * thus the whole swarm share the same best position "g" from a single particle. However,
 * this approach might lead the swarm to be trapped into a local minimum. "
 * Quoted: "https://en.wikipedia.org/wiki/Particle_swarm_optimization"
 

clarification:
The c++ program was written using the term "Drone" instead of a "Particle" and our search surface was called "Forest" because I originally got the task as a home exercise that partially implement the current implementation ...

I invested a lot of time in documenting the code in the c++ files so if anyone is interested in delving deeper I recommend him read the documentation in the code.
-------
----------------------

# python files:
------------
1) Draggable_Target.py :

This script will be responsible for determining the target location for the particles,
The purpose of this script is to run in parallel with the main script and actually create a type of controller that the user can use to move the target for our swarm.


in a brief description the program will use the matplotlib library and create an external container of our search surface where the user can stick a target on the space and its location will be written to an external output file that the algorithm I wrote in the c++ language can receive and work with.



2) main.py :

This script is the operator of all our programs, he will determine which method will work and when and at the same time he will check end cases and close the program if necessary.

The script will work with all the files I mentioned earlier,
I tried to document in a minimal and understandable way the structure of the script within the code itself and here I will describe it briefly.


at the start of the run the script will run the Draggable_Target.py script in another process\thread,
and then it will create the main object that manages all our processes named "Drones_Visualization" which will be responsible for all the processes that need to be performed and will try to handle end cases.



# Examples for the program:
![ezgif com-gif-maker (1)](https://user-images.githubusercontent.com/75484097/109566428-878d7f80-7aec-11eb-955e-e8b7af2d28a8.gif)

![ezgif com-gif-maker (2)](https://user-images.githubusercontent.com/75484097/109567142-8c066800-7aed-11eb-878c-1b226eb454f8.gif)






Because the natural behavior of particles is to move to extremes, care must be taken not to lead the swarm to extremes because it can sometimes get stuck there.

![ezgif com-gif-maker (3)](https://user-images.githubusercontent.com/75484097/109567035-62e5d780-7aed-11eb-9f35-4f6526e34c37.gif)



# Final words


Thats it! thank you if you have read this far this is my first mini project, with his preparation I exposed to the metaheuristics algorithms and to the optimization problems they are trying to solve, i hope that i will make another one in the near futare...


And for those who are looking for an algorithm for this version of the PSO Algorithm I would be more than happy if you use my algorithm and if you find any way to improve it I would love to get an update on that,
Thanks.

-----------

# Important to say!
The files I upload are free to use and were written on the macbook air with the m1 processor. In order to use the code on Windows, all the Python files must be delete the lines that contain "matplotlib.use('TKAgg')" Also!!

You need to re-compile the c ++ files twice once the input file is init.txt and the second time with the init2.txt file under the names "PSO_ALG_LOCKING",
"PSO_ALG_LOCKING2"

# for mac environment :

i made a Mac_Run_Pack.zip that contain all the files that you need to run the program on your mac i compile the files on the macbook air with the m1 chip so I'm not one hundred percent sure the version will fit everyone


compilation commands for the c++ files
first with init.txt at main.cpp as the boot input:
1) g++ -c -Wall Vec2D.cpp Square.cpp Drone.cpp Forest.cpp main.cpp
2) g++ -o PSO_ALG_LOCKING -Wall Vec2D.o Square.o Drone.o Forest.o main.o

now go to the main.cpp and change the boot file to init2.txt and compile with this lines:
1) g++ -c -Wall Vec2D.cpp Square.cpp Drone.cpp Forest.cpp main.cpp
2) g++ -o PSO_ALG_LOCKING2 -Wall Vec2D.o Square.o Drone.o Forest.o main.o

after you did that put the exe files in the python files folders...


# for windows environment :
compilation commands for c++ files
first with init.txt at main.cpp as the boot input:
1) g++ -c -Wall Vec2D.cpp Square.cpp Drone.cpp Forest.cpp main.cpp
2) g++ -o PSO_ALG_LOCKING.exe -Wall Vec2D.o Square.o Drone.o Forest.o main.o

now go to the main.cpp and change the boot file to init2.txt and compile with this lines:
1) g++ -c -Wall Vec2D.cpp Square.cpp Drone.cpp Forest.cpp main.cpp
2) g++ -o PSO_ALG_LOCKING2.exe -Wall Vec2D.o Square.o Drone.o Forest.o main.o

after you did that put the exe files in the python files folders and go to the python script and update the algorithm files that will have the .exe extension 
















