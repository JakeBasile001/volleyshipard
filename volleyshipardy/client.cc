//
// daytime_client.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "/public/read.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <random>
#include<map>
#include <boost/algorithm/string.hpp>
#include <chrono>
using boost::replace_all;
using namespace std;
using boost::asio::ip::tcp;
using  namespace chrono;
int jeopardy(int player, int &seconds2) {
 		ifstream myfile("questions.txt");
        //string line;
        //getline(s, line);           //Testing lines commented out.
        //cout << line << endl;
        auto rng = default_random_engine {};
        cout <<"Welcome to Volleyshipardy! You are player 1 so you will start first.\n" << "You will have 5 second for each question. Game begins in: ";
        for (int i = 1; i < 6 ; i++) {
        cout << i << " "; }
        cout << endl;
			auto old = steady_clock::now();
            cout << "PLAYER " << player << endl;
            vector<string> qstack = {};
            string garbage;
            int v1 = rand() % 25;            //NOT WORKING
            for (int i = 0; i < v1; i++) {for(int j = 0; j < 5; j++) garbage = readline(myfile);}
            for (int i = 0; i < 5; i++) qstack.push_back(readline(myfile)); //Reads our question
            string answer = qstack.at(1);
            string bruh = qstack.at(0);
            replace_all(bruh, "\\n", "\n");
            cout << bruh;
            qstack.erase(qstack.begin()); //Removes the wuestion prompt
            shuffle(qstack.begin(), qstack.end(), rng); //Shuffles answers
            for (int i = 0; i < qstack.size(); i++) cout << char(65+i) << ") " << qstack.at(i) << endl; //Question output
            cout << "Answer: ";
            string uans = readline(cin); //read in user answer
			auto ptime = steady_clock::now() - old;
			int btime = duration_cast<seconds>(ptime).count();
			if (abs(btime) > seconds2) {
				cout << "Took too long!" << endl;
				return 0;
			}
            if (uans == "a" or uans == "A") uans = qstack.at(0);
            if (uans == "b" or uans == "B") uans = qstack.at(1); //Jank but it works
            if (uans == "c" or uans == "C") uans = qstack.at(2);
            if (uans == "d" or uans == "D") uans = qstack.at(3); 
			if (uans == answer) {
				cout << "Correct!" << endl;
				return abs(btime); //CHANGE THIS TO USE CHRONO
			}else {
                cout << "Wrong!" << endl;
                return 0;
            }
        }

int main(int argc, char* argv[])
{
	try
	{
		/*if (argc != 3)
		{
			cerr << "Usage: daytime_client <host> <port>" << endl;
			return EXIT_FAILURE;
		}
		*/
		tcp::iostream s("localhost", "8972"); //[1] == host, [2] == port
		if (!s) //Connection failed
		{
			cout << "Unable to connect: " << s.error().message() << endl;
			return EXIT_FAILURE;
		}
		ifstream myfile("questions.txt");
		//string line;
		//getline(s, line);           //Testing lines commented out.
		//cout << line << endl;
		auto rng = default_random_engine {};
		cout <<"Welcome to Volleyshipardy! You are player 1 so you will start first.\n" << "You will have 5 second for each question. Game begins in: ";
		for (int i = 1; i < 6 ; i++) {
		cout << i << " "; }
		cout << endl;
		int x = 5;
		while(true) {
			x = jeopardy(1, x);
			if (x == 0) {
				cout << endl << "Player 2 Wins!" << endl;
				break;
			} x = jeopardy(2, x);
			if (x == 0) {
                cout << endl << "Player 1 Wins!" << endl;
                break;
		}
	}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
