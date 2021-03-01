"""
Author: Niv Nagli
Project: Particle Swarm Optimization
File: Draggable_Target.py
Contact Information: itsniv@gmail.com

Sources I used:
https://jakevdp.github.io/blog/2012/08/18/matplotlib-animation-tutorial/
https://jakevdp.github.io/blog/2012/08/18/matplotlib-animation-tutorial/
https://stackoverflow.com/questions/21654008/matplotlib-drag-overlapping-points-interactively
https://pyshine.com/
https://stackoverflow.com/questions/29379502/how-get-a-x-y-position-pointing-with-mouse-in-a-interactive-plot-python
"""

import random
import math
import numpy as np
import csv
import os
import _thread
import matplotlib.pyplot as plt
import subprocess
import sys
import matplotlib

bilt = False
matplotlib.use('TKAgg')  # set the backend standard needed only for mac environment


class Drone:
    """
    The object that will hold the coordinates of each particle.
    """

    def __init__(self, initial_pos):
        self.location = []
        self.location.append(initial_pos[0])
        self.location.append(initial_pos[1])

    def update_pos(self, new_pos):
        self.location[0] = new_pos[0]
        self.location[1] = new_pos[1]

    def get_pos(self):
        return float(self.location[0]), float(self.location[1])


def getTarget(filename):
    x = 0
    y = 0
    with open(filename) as csvDataFile:
        csvReader = csv.reader(csvDataFile)
        for row in csvReader:
            x = row[0]
            y = row[1]
    return x, y


def newTarget(prev_x, prev_y, new_x, new_y):
    if new_x == prev_x and new_y == prev_y:
        return False
    return True


colors = np.array([
    (31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),
    (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),
    (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),
    (227, 119, 194), (247, 182, 210), (127, 127, 127), (199, 199, 199),
    (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229),

    (31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),
    (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),
    (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),
    (227, 119, 194), (247, 182, 210), (127, 127, 127), (199, 199, 199),
    (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229),

    (31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),
    (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),
    (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),
    (227, 119, 194), (247, 182, 210), (127, 127, 127), (199, 199, 199),
    (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229),

    (31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),
    (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),
    (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),
    (227, 119, 194), (247, 182, 210), (127, 127, 127), (199, 199, 199),
    (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229)

]) / 255.


class Drones_Visualization:
    def __init__(self, target_file, config_file, config_file2, database1, database2):

        # Fields:
        self.database2 = database2
        self.config2 = config_file2
        self.database1 = database1
        self.target_file = target_file
        self.swarm = []
        self.numOfDrones = 0
        self.target = []
        self.indicator = True
        self.iterations = 0
        self.counter = 1
        subprocess.call("./PSO_ALG_LOCKING")  # call the exe file "PSO_ALG_1" for the first calculation for the
        # drones moves.
        init_database = open(self.database1, 'r')  # Read our first moves
        self.lines = init_database.readlines()
        init_database.close()
        ''' Initialize: '''
        file = open(config_file, 'r')
        self.numOfDrones = int(file.readline())
        for i in range(self.numOfDrones):  # Here we enter the first locations of the particles from the input file
            initial_loc = []
            line = file.readline().split(' ')
            for j in range(2):
                initial_loc.append(float(line[j]))
            self.swarm.append(Drone(initial_loc))

        x, y = getTarget(target_file)  # Read the first target coordinates the user enter or the default one's
        self.target.append(float(x))
        self.target.append(float(y))
        file.close()
        """
        until this point we just initialize the drones take off locations and also the target the user pointed to..
        now we going to run the c++ algorithm that will convert for us 2 main outputs:
        moves.txt: all the moves the drones did until one of them reach to the target or until the stop term
        iterations.txt: a txt file that will contain a general information about the program,
        in the first line we will see the total iterations took for us to find the target in the second line we will see
        the total iterations for all the drones and afterwards we will see all the locations the drones were in the end
        of the program.
        """
        self.newTarget()

    def start(self):
        """
        The main method that determines the sequence of the program
        """
        while True:
            if not self.indicator:  # the indicator will tell us if we reach to the end of the move file.
                if self.newTargetCheck():  # first we check if we got a new target
                    self.indicator = True
                else:
                    self.printLastLocations()  # if we didnt got a new target we will generate new moves for our swarm.
                    open(self.database1, "w").close()  # clear the old moves file
                    subprocess.call("./PSO_ALG_LOCKING2")  # try to generate a new moves
                    self.indicator = True
                    self.newTarget()

            self.newTargetCheck()

            plt.xlim([-500, 500])  # set borders
            plt.ylim([-500, 500])

            for i in range(self.numOfDrones):
                # this loop will draw the particles in their new location
                try:
                    x, y = self.swarm[i].get_pos()
                except ValueError:  # edge case...
                    print("Input not ready yet,\nClose the program in case of infinite loop!\n")
                    self.start()
                x, y = self.swarm[i].get_pos()
                plt.plot(x, y, color=colors[i], marker='o')
            plt.plot(self.target[0], self.target[1], color='k', marker='o')
            plt.pause(0.02)

            plt.clf()

            if self.counter != (self.iterations - 1) * self.numOfDrones:
                self.updateLocations()
                if self.counter == (self.iterations - 1) * self.numOfDrones:
                    self.indicator = False
            else:
                self.indicator = False

    # side-Methods >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    def printLastLocations(self):

        try:
            for i in range(self.numOfDrones):
                x, y = self.swarm[i].get_pos()
        except ValueError:
            return

        open(self.config2, "w").close()  # Clear the file first
        f = open(self.config2, "a")
        f.write(str(self.numOfDrones) + '\n')

        for i in range(self.numOfDrones):
            x, y = self.swarm[i].get_pos()
            new_velocity_X = random.random()
            new_velocity_Y = random.random()
            if i < self.numOfDrones - 1:
                f.write(str(x) + " " + str(y) + " " + str(new_velocity_X) + " " + str(new_velocity_Y) + "\n")
            else:
                f.write(str(x) + " " + str(y) + " " + str(new_velocity_X) + " " + str(new_velocity_Y))
        f.close()
        return

    def updateLocations(self):
        if (self.counter + 1) == (self.iterations - 1) * self.numOfDrones:
            self.indicator = False
            return

        for i in range(self.numOfDrones):
            new_coordinates = self.lines[self.counter][:-1].split(' ')
            new_location = []
            for j in range(2):
                new_location.append(new_coordinates[j])
            self.swarm[i].update_pos(new_location)
            self.counter += 1
        return

    def newTarget(self):
        file = open(self.database2, 'r')  # now after we ran the algorithm we read the num of iterations that took the
        # drones to find the target
        test = file.readline()
        while test == '':  # we will enter this while loop in case all the swarm in on the target.
            file.close()
            open(self.database2, "w").close()  # clear the old iterations file from the NULL value
            p = subprocess.Popen('./PSO_ALG_LOCKING2')
            file = open(self.database2, 'r')  # reopen
            stdout = p.stdout
            stderr = p.stderr
            print(stdout, stderr)
            test = file.readline()

        self.iterations = int(test)
        file.close()
        self.counter = 0
        init_database = open(self.database1, 'r')
        self.lines = init_database.readlines()
        init_database.close()

    def newTargetCheck(self):
        x, y = getTarget(self.target_file)
        if newTarget(float(x), float(y), self.target[0], self.target[1]):
            '''
            if the user enter a new target we need to make a new calculations for the moves, 
            so first we print all the last locations of the drones to a new init file and update the target field,
            after we did that we ran the same algorithm but now with the last locations so that why i make a 2 
            copies of the algorithm...
            '''
            self.target[0] = float(x)
            self.target[1] = float(y)
            self.printLastLocations()
            open(self.database1, "w").close()  # clear the old moves file
            subprocess.call("./PSO_ALG_LOCKING2")
            self.newTarget()
            return True
        return False


def start_drag():
    os.system('python Draggable_Target.py')


try:
    file = open("target.csv", 'w')
    file.write(str(float(250)) + ',' + str(float(250)))
    file.close()
    _thread.start_new_thread(start_drag, ())
    Drones_Visualization("target.csv", "init.txt", "init2.txt", "moves.txt", "iterations.txt").start()

except RuntimeError:
    file = open("target.csv", 'w')
    file.write(str(float(5)) + ',' + str(float(5)))
    file.close()
    sys.stderr.write("The program reach to her Limit,\n Run again.")
    exit(-1)
