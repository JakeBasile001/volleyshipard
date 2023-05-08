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
using boost::replace_all;
using namespace std;
using boost::asio::ip::tcp;

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
		//sleep(1); //not working
		cout << i << " "; }
		cout << endl;
		int inx = 1; //Question number
		while (true) {
			cout << "Question " << inx << ":\n";
			//map<char, string> qstack;
			vector<string> qstack = {};
			//string garbage;
			//int v1 = rand() % 25;            NOT WORKING
			//for (int i = 0; i < v1; i++) {for(int j = 0; j < 5; j++) garbage = readline(myfile);}
			for (int i = 0; i < 5; i++) qstack.push_back(readline(myfile)); //Reads our question
			string answer = qstack.at(1); 
			string bruh = qstack.at(0);
			//bruh.replace(bruh.begin(), bruh.end(), "\\", '\n'); 
			replace_all(bruh, "\\n", "\n");
			cout << bruh;
			qstack.erase(qstack.begin()); //Removes the wuestion prompt
			shuffle(qstack.begin(), qstack.end(), rng); //Shuffles answers
			for (int i = 0; i < qstack.size(); i++) cout << char(65+i) << ") " << qstack.at(i) << endl; //Question output
			cout << "Answer: ";
			string uans = readline(cin); //read in user answer
			if (uans == "a" or uans == "A") uans = qstack.at(0); 
			if (uans == "b" or uans == "B") uans = qstack.at(1); //Jank but it works
			if (uans == "c" or uans == "C") uans = qstack.at(2);
			if (uans == "d" or uans == "D") uans = qstack.at(3);
			if (uans == answer) cout << "Correct!" << endl;
			else { 
				cout << "Wrong!" << endl;
				break; 
			} inx++;
		}


	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
