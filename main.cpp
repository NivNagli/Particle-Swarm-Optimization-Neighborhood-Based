/* Author: Niv Nagli
 * Project: Drone_Rescue
 * File: main.cpp
 * Contact Information: itsniv@gmail.com
 */


#include "Forest.h"
#include <ctime>
#include <fstream>
using namespace std;
/*------------------------------------------ MiniReadMe: ------------------------------------------
 * I chose to implement the code with four classes and a main.cpp file,
 * each class will have a general explanation of its use at the beginning of the .h file, the methods will have
 * short comments in case I thought the code was not clear there and sometimes full documentation.
 * ------------------------------------------------------------------------------------------------
 */


int main(int argc, char** argv) {

    srand(time(NULL));
    /* to generate "random" numbers we need to reset the time count in our device, because in some of the calculation
     * for our "random number" we use methods that uses the time counter in our device.
     * so we will reset it in order to try mimic a random number much as possible.
     * */

    /*------------------------------------------ Tests for file existence: ------------------------------------------*/

    ifstream f1("init2.txt");
    ofstream  f2("moves.txt"), f3("iterations.txt");

    if(!f1 || !f2 || !f3){
        cerr << "Error; One of the files failed to open.\n Please check the file names and try again. " << endl;
        f1.close();
        f2.close();
        f3.close();
        return -1;
    }

    /*--------------------------------------- Initial tests for the init file ---------------------------------------*/
    string str; // string variable that going to help us to determine if we got a valid input
    stringstream stream; // stringstream variable that will also help us to determine if we got valid input

    str.clear(); // clean the string variable for safety
    getline(f1, str); // now we try to read the init file of the particles, first we check if we receive a valid number of drones.
    stream.clear();  // in the next two lines we clean the stringstream variable.
    stream.str(str);  // ^^
    int drones_num = -1;  // int variable that gonna contain the number of drones sent for the search.
    stream >> drones_num;
    if(drones_num < 2 || !(stream.eof())) {  // check if the user has entered the correct number of drones
        //  in order for a search to be performed the user must enter at least two drones.
        cerr << "Error; invalid input\n at init.txt the first line must contain the number of particles at least 2. " << endl;
        f1.close();
        f2.close();
        f3.close();
        return -1;
    }

    string* drones_str = new string[drones_num+1];  // string array, each variable at the array will get the drones take off coordinates
    // we allocate dynamically because the number of variables is unknown.
    drones_str[0] = str;
    if(drones_str[0].empty()){
        cerr << "Error; invalid input.\n check the init file." << endl;
        f1.close();
        f2.close();
        f3.close();
        return -1;
    }

    for(int i = 1 ; i < drones_num+1 ; i++) {  // for loop to read all the drones coordinates
        getline(f1, drones_str[i]);
        if(drones_str[i].empty())  {  // if one of the line is empty that mean we got a invalid input.
            cerr << "Error; invalid input.\n mismatch between the number of drones to the coordinates" << endl;
            cerr << " Check the init file." << endl;
            f1.close();
            f2.close();
            f3.close();
            delete [] drones_str;  // need to clear the dynamic memory on the heap we used so far.
            return -1;
        }
    }

    str.clear();
    getline(f1, str);  // here we check if the the init file contain more then the number of drones he provide.
    if(!str.empty()) {  // in case it does contain we stop the program and notify the user.
        cerr << "Error; invalid input.\n mismatch between the number of drones to the coordinates" << endl;
        f1.close();
        f2.close();
        f3.close();
        delete [] drones_str;
        return -1;
    }


    /*------------------------------------------ Last test for the inputs ------------------------------------------*/
    try{
        Forest f = Forest(-500, 500, drones_str);  // Explanation below -->
    }
    catch (const std::invalid_argument& e) {
        /* In the constructor i made tests for each variable in specific line from the inputs,
         * in case we found something is invalid we throw invalid argument_error that we are catching over here,
         * i chose to implement this way in order for the program to work effectively,
         * because if we find an incorrect value the builder will stop his work,
         * and we will delete everything he has created up to the moment of the error appear.
         * Full documentation in the custom constructor of "Forest" class. */
        cerr << "Error; invalid input,\n please check the inputs files." << endl;
        f1.close();
        f2.close();
        f3.close();
        delete [] drones_str;
        return -1;
    }


    /*------------------------------------------ Running the program ------------------------------------------*/
    int num_iterations = 0;  // int variable that gonna count how many iterations made in the program.
    Forest f = Forest(-500, 500, drones_str);  // create our forest object
    int iterations = 60;  // int variable that contain the number of time iterations for our program.

    for(int i = 0 ; (i < iterations  ) ; i++ ) {
        /* for loop that will represent a single time move in each iteration,
         * in each iterations we print all the drones moves for the exact time iteration to the moves.txt file
         * and afterwards we will move all the drones with moveDrones method.
         * */
        if(i > 1) {  // we dont need the first iteration moves..
            f.printLocations(f2);
        }
        f.moveDrones();  // move all the drones together
        num_iterations = i;  // counter for the iterations.txt file.
    }
    if(iterations > 0 ) // the only case we not require to update the iterations counter is when got 0 moves to do.
    num_iterations++; // we adding for the the num iterations + 1 because we use the postfix in the for loop.

    f.printLocations(f2);  // write the last locations to the moves.txt file.
    f3 << num_iterations << endl; // write the num of time iterations to the iterations.txt file
    f3 << num_iterations * drones_num << endl;  // write to iterations.txt the total moves for all the drones.
    f.printLocations(f3); // write the final locations to the iterations file.

    f1.close();
    f2.close();
    f3.close();
    delete [] drones_str;
}
