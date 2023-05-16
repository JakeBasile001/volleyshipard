#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <random>
#include <chrono>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <gtest/gtest.h>

#include "colors.h"
#include "read.h"

using std::cout, std::endl, std::cin, std::string, std::vector;

int jeopardy(int player, int &seconds2) {  //Jeopardy function! this performs one wuestion of jeop
    std::ifstream myfile("questions.txt");  // open file
    srand(time(NULL)); //seeding time for rng
    auto rng = std::default_random_engine {}; // rng engine (ignore)
    auto old = std::chrono::steady_clock::now(); //TIME POINT 1
    cout << CYAN << "PLAYER " << player << endl; 
    std::vector<string> qstack = {}; // holds our question and answer pool
    string garbage; //wuite literally garbage
    int v1 = rand() % 91;            //91 questions (maybe 92?)
    for (int i = 0; i < v1; i++) {for(int j = 0; j < 5; j++) garbage = readline(myfile);} //eats up a random amount of questions (decided above)
    for (int i = 0; i < 5; i++) qstack.push_back(readline(myfile)); //Reads our actual question
    string answer = qstack.at(1);
    string bruh = qstack.at(0);
    boost::replace_all(bruh, "\\n", "\n"); // formating 
    cout << YELLOW << bruh << endl;
    qstack.erase(qstack.begin()); //Removes the wuestion prompt
    shuffle(qstack.begin(), qstack.end(), rng); //Shuffles answers
    for (int i = 0; i < qstack.size(); i++) cout << WHITE << char(65+i) << ") " <<  qstack.at(i) << endl; //Question output
    cout << CYAN << "Answer: ";
    string uans = readline(cin); //read in user answer
    auto ptime = std::chrono::steady_clock::now() - old; // 	TIME POINT 2
    int btime = duration_cast<std::chrono::seconds>(ptime).count(); // TIMEPOINT 2 - TIMEPOINT 1 = USED TIME
    if (abs(btime) > seconds2) {
    	cout << RED <<"Took too long!" << endl;
    	return 0; //RETURN 0 SECONDS LEFT, TRIGGERING A LOSS
    }
    if (uans == "a" or uans == "A") uans = qstack.at(0);
    if (uans == "b" or uans == "B") uans = qstack.at(1); //Jank but it works
    if (uans == "c" or uans == "C") uans = qstack.at(2);
    if (uans == "d" or uans == "D") uans = qstack.at(3); 
    if (uans == answer) {
    	cout << GREEN << "Correct!" << endl;
    	return abs(btime); //RETURN HOWEVER MANY SECONDS LEFT, NOT TRIGGERING A LOSS
    }else {
        cout << RED << "Wrong!" << endl;
        return 0; // 0 SEC = LOSS
    }
    }