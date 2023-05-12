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
int jeopardy(int player, int &seconds2) {  //Jeopardy function! this performs one wuestion of jeop
 		ifstream myfile("questions.txt");  // open file
		srand(time(NULL)); //seeding time for rng
        auto rng = default_random_engine {}; // rng engine (ignore)
			auto old = steady_clock::now(); //TIME POINT 1
            cout << "PLAYER " << player << endl; 
            vector<string> qstack = {}; // holds our question and answer pool
            string garbage; //wuite literally garbage
            int v1 = rand() % 91;            //91 questions (maybe 92?)
            for (int i = 0; i < v1; i++) {for(int j = 0; j < 5; j++) garbage = readline(myfile);} //eats up a random amount of questions (decided above)
            for (int i = 0; i < 5; i++) qstack.push_back(readline(myfile)); //Reads our actual question
            string answer = qstack.at(1);
            string bruh = qstack.at(0);
            replace_all(bruh, "\\n", "\n"); // formating 
            cout << bruh << endl;
            qstack.erase(qstack.begin()); //Removes the wuestion prompt
            shuffle(qstack.begin(), qstack.end(), rng); //Shuffles answers
            for (int i = 0; i < qstack.size(); i++) cout << char(65+i) << ") " << qstack.at(i) << endl; //Question output
            cout << "Answer: ";
            string uans = readline(cin); //read in user answer
			auto ptime = steady_clock::now() - old; // 	TIME POINT 2
			int btime = duration_cast<seconds>(ptime).count(); // TIMEPOINT 2 - TIMEPOINT 1 = USED TIME
			if (abs(btime) > seconds2) {
				cout << "Took too long!" << endl;
				return 0; //RETURN 0 SECONDS LEFT, TRIGGERING A LOSS
			}
            if (uans == "a" or uans == "A") uans = qstack.at(0);
            if (uans == "b" or uans == "B") uans = qstack.at(1); //Jank but it works
            if (uans == "c" or uans == "C") uans = qstack.at(2);
            if (uans == "d" or uans == "D") uans = qstack.at(3); 
			if (uans == answer) {
				cout << "Correct!" << endl;
				return abs(btime); //RETURN HOWEVER MANY SECONDS LEFT, NOT TRIGGERING A LOSS
			}else {
                cout << "Wrong!" << endl;
                return 0; // 0 SEC = LOSS
            }
        }
vector<int> battleBoard(int SIZE) { //Creates random board (1d vector)
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


vector<int> battleship(int player, vector<int> gameboard) {
	string answer;
	int SIZE = 10;
	cout << "Player " << player << " may take their shot (A-J Row, 0-9 column)" << endl;
	
	// UI CODE BELOW vvvvvvvvvvvvv
	//
	int tile = 0;
	for(int i = 0; i < 3; i++) {
	while (true) {
	for(int i = 0; i < SIZE*SIZE; i++){               // BARE BONES UI CODE, JUST PRINTS A GRID (1/0 == NOTHING, 2 == HIT, -1 == MISS)
		if (i % (SIZE) == 0) cout << endl;
		if (gameboard.at(i) == 0 or gameboard.at(i) == 1) cout << "-";
		else if (gameboard.at(i) == 2) cout << "X";
		else if (gameboard.at(i) == -1) cout << "O";
		else cout << "Error";
	}
	//
	// UI CODE ABOVE ^^^^^^^^^^^^

	cout << "\nTile-To-Shoot: ";
	cin >> answer;
	cout << endl; 
	if (answer.size() != 2) {
		cout << "TRY AGAIN!" << endl;
		continue;
	}
	tile = int(toupper(answer.at(0))) - 65 + int(answer.at(1)) - 48; //stupid ascii math
	if (tile < 0 or tile > SIZE*SIZE or gameboard.at(tile) == -1 or gameboard.at(tile) == 2) cout << "TRY AGAIN!" << endl; // if we already tried there, try again
	else break;
	}
	if (gameboard.at(tile) == 1) {
		cout << "HIT!" << endl;
		gameboard.at(tile) = 2; // Hit
	}
	else {
		cout << "Miss!" << endl;
		gameboard.at(tile) = -1; // miss
	}
	}
	return gameboard;		
}

int main(int argc, char* argv[])
{
	try
	{
		tcp::iostream s("localhost", "8972"); //[1] == host, [2] == port
		if (!s) //Connection failed
		{
			cout << "Unable to connect: " << s.error().message() << endl;
			return EXIT_FAILURE;
		}
		ifstream myfile("questions.txt");
		auto rng = default_random_engine {};
		cout <<"Welcome to Volleyshipardy! You are player 1 so you will start first.\n" << "You will have 5 second for each question. Game begins in: ";
		int timeset = 20;
		int x = timeset; //Amount of seconds the players start with
		const int SIZE = 10;
		vector<int> gameboard1 = battleBoard(SIZE);
		vector<int> gameboard2 = battleBoard(SIZE);  //battleship boards
		while(true) {  //Infinite loop until a win
			x = jeopardy(1, x); 							//player 1 jeop question
			if (x == 0) { 									//If they lost, continue for player 2's battleship
				cout << endl << "Player 2 Scores!" << endl; 
				gameboard1 = battleship(2, gameboard1); 	//plays battleship (See above function)
				x = timeset; 								//resets jeop timer
				if (find(gameboard1.begin(), gameboard1.end(), 1) == gameboard1.end()) { //searches for any ships, ends game if none found
				cout << "Player 2 has sunk all of player 1's ships! Player 2 WINS!" << endl;
				break;
				}
			} x = jeopardy(2, x); //repeat of above code but for opposite player
			if (x == 0) {
                cout << endl << "Player 1 Scores!" << endl;
                gameboard2 = battleship(1, gameboard2);
				x = timeset;
                if (find(gameboard2.begin(), gameboard2.end(), 1) == gameboard2.end()) {
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
