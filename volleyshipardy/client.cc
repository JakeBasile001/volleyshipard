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
		srand(time(NULL));
        //string line;
        //getline(s, line);           //Testing lines commented out.
        //cout << line << endl;
        auto rng = default_random_engine {};
			auto old = steady_clock::now();
            cout << "PLAYER " << player << endl;
            vector<string> qstack = {};
            string garbage;
            int v1 = rand() % 91;            //91 questions (maybe 92?)
            for (int i = 0; i < v1; i++) {for(int j = 0; j < 5; j++) garbage = readline(myfile);}
            for (int i = 0; i < 5; i++) qstack.push_back(readline(myfile)); //Reads our question
            string answer = qstack.at(1);
            string bruh = qstack.at(0);
            replace_all(bruh, "\\n", "\n");
            cout << bruh << endl;
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
vector<int> battleBoard(int SIZE) { //Creates random board
	vector<int> gameboard1; 
	bool flag = true;
	for(int i = 0; i < SIZE*SIZE; i++) {
			int gorp = rand() % 100;
			if (flag){
			gameboard1.push_back(1);
			flag = false;
			}else if (gorp % 50 == 0){
                for (int j = 0; j < 5; j++) gameboard1.push_back(1); //2% chance of a battleship of length 5
                i += 4;
            } else if (gorp % 20 == 0) {
                for (int j = 0; j < 3; j++) gameboard1.push_back(1); //5% chance of creating a battleship of lenth 3
                i += 2;
            }
            else gameboard1.push_back(0);
        }
	return gameboard1;
}

void printBoard(vector<int> board){
	
	
}

vector<int> battleship(int player, vector<int> gameboard) {
	string answer;
	int SIZE = 10;
	cout << "Player " << player << " may take their shot (A-J Row, 0-9 column)" << endl;
	//
	//
	//
	//		UI code go here // print out the grid and make it pretty // grid is of 0's and 1's
	//      1's are ships
	//
	//
	//
	int tile = 0;
	for(int i = 0; i < 3; i++) {
	while (true) {
	for(int i = 0; i < SIZE*SIZE; i++){
		if (i % (SIZE) == 0) cout << endl;
		if (gameboard.at(i) == 0 or gameboard.at(i) == 1) cout << "-";
		else if (gameboard.at(i) == 2) cout << "X";
		else if (gameboard.at(i) == -1) cout << "O";
		else cout << "Error";
	}
	cout << "\nTile-To-Shoot: ";
	cin >> answer;
	cout << endl; 
	if (answer.size() != 2) {
		cout << "TRY AGAIN!" << endl;
		continue;
	}
	tile = int(toupper(answer.at(0))) - 65 + int(answer.at(1)) - 48;
	//cout << answer.at(0) << toupper(answer.at(0)) << int('2');
	if (tile < 0 or tile > SIZE*SIZE or gameboard.at(tile) == -1 or gameboard.at(tile) == 2) cout << "TRY AGAIN!" << endl;
	else break;
	}
	if (gameboard.at(tile) == 1) {
		cout << "HIT!" << endl;
		gameboard.at(tile) = 2;
	}
	else {
		cout << "Miss!" << endl;
		gameboard.at(tile) = -1;
	}
	}
	return gameboard;		
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
		int timeset = 20;
		int x = timeset; //Amount of seconds the players start with
		const int SIZE = 10;
		vector<int> gameboard1 = battleBoard(SIZE);
		vector<int> gameboard2 = battleBoard(SIZE);  //battleship boards
		//vector<int> zeroVec(gameboard1.size(), 0);
		bool wflag = true;
		while(true) {
			x = jeopardy(1, x);
			if (x == 0) {
				wflag = true;
				cout << endl << "Player 2 Scores!" << endl;
				gameboard1 = battleship(2, gameboard1);
				x = timeset;
				if(find(gameboard1.begin(), gameboard1.end(), 1) != gameboard1.end()) wflag = false; 
				if (wflag) {
				cout << "Player 2 has sunk all of player 1's ships! Player 2 WINS!" << endl;
				break;
				}
			} x = jeopardy(2, x);
			if (x == 0) {
				wflag = true;
                cout << endl << "Player 1 Scores!" << endl;
                gameboard2 = battleship(1, gameboard2);
				x = timeset;
				if(find(gameboard2.begin(), gameboard2.end(), 1) != gameboard2.end()) wflag = false;
                if (wflag) {
                cout << "Player 2 has sunk all of player 1's ships! Player 2 WINS!" << endl;
				break;
				}
		}
	}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
