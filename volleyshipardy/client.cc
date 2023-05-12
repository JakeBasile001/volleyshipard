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
#include "/public/colors.h"
using boost::replace_all;
using namespace std;
using boost::asio::ip::tcp;
using  namespace chrono;
int jeopardy(int player, int &seconds2) {  //Jeopardy function! this performs one wuestion of jeop
 		ifstream myfile("questions.txt");  // open file
		srand(time(NULL)); //seeding time for rng
        auto rng = default_random_engine {}; // rng engine (ignore)
			auto old = steady_clock::now(); //TIME POINT 1
            cout << CYAN << "PLAYER " << player << endl; 
            vector<string> qstack = {}; // holds our question and answer pool
            string garbage; //wuite literally garbage
            int v1 = rand() % 91;            //91 questions (maybe 92?)
            for (int i = 0; i < v1; i++) {for(int j = 0; j < 5; j++) garbage = readline(myfile);} //eats up a random amount of questions (decided above)
            for (int i = 0; i < 5; i++) qstack.push_back(readline(myfile)); //Reads our actual question
            string answer = qstack.at(1);
            string bruh = qstack.at(0);
            replace_all(bruh, "\\n", "\n"); // formating 
            cout << YELLOW << bruh << endl;
            qstack.erase(qstack.begin()); //Removes the wuestion prompt
            shuffle(qstack.begin(), qstack.end(), rng); //Shuffles answers
            for (int i = 0; i < qstack.size(); i++) cout << WHITE << char(65+i) << ") " <<  qstack.at(i) << endl; //Question output
            cout << CYAN << "Answer: ";
            string uans = readline(cin); //read in user answer
			auto ptime = steady_clock::now() - old; // 	TIME POINT 2
			int btime = duration_cast<seconds>(ptime).count(); // TIMEPOINT 2 - TIMEPOINT 1 = USED TIME
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
void printBoard(vector<int>);
vector<int> battleBoard(int SIZE) { //Creates random board (1d vector)
	vector<int> gameboard(SIZE*SIZE, 0); 
	//bool flag = true;
	//for(int i = 0; i < SIZE*SIZE; i++) {  
			/*int gorp = rand() % 100;
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
        }*/
	cout <<CYAN << "Setup Phase:" << endl;
	string answer;
	printBoard(gameboard);
	cout << WHITE << "Please enter a square (A-J Row, 0-9 column) to be the first square for the ship" << endl;
	while (true) {
	cout << CYAN <<"Ship: XXX      Tile: ";
	int tile = -1;
	cin >> answer;
	tile = (int(toupper(answer.at(0))) - 65)*10 + int(answer.at(1)) - 48; //stupid ascii math
    if (tile < 0 or tile > SIZE*SIZE or gameboard.at(tile) == 1 or gameboard.at(tile) == 2) cout << RED <<"TRY AGAIN!" << endl; // if we already tried there, try again
	else if (tile == 0) {
		for (int i; i < 3; i++)gameboard.at(tile + i) = 3;
		break;
	}
	else if (tile % SIZE == 0 or (tile + 1) % SIZE == 0) cout << RED <<"TRY AGAIN!" << endl;
    else {
		for (int i; i < 3; i++)gameboard.at(tile + i) = 3;
		break;			
	}
	}
	printBoard(gameboard);
	while (true) {
    cout << CYAN <<"Ship: XXXXX    Tile: ";
    int tile = -1;
    cin >> answer;
    tile = (int(toupper(answer.at(0))) - 65)*10 + int(answer.at(1)) - 48; //stupid ascii math
    if (tile < 0 or tile > SIZE*SIZE or gameboard.at(tile) == 1 or gameboard.at(tile) == 2) cout << RED <<"TRY AGAIN!" << endl; // if we already tried there, try again
    else if (tile == 0) {
        for (int i; i < 5; i++) gameboard.at(tile + i) = 3;
        break;
    }
    else if (tile % SIZE == 0  or (tile + 1) % SIZE == 0 or (tile + 2) % SIZE == 0 or (tile + 3) % SIZE == 0 or (tile + 4) % SIZE == 0) cout << RED <<"TRY AGAIN!" << endl;
    else {
        for (int i; i < 5; i++)gameboard.at(tile + i) = 3;
        break;
    }
	}
	printBoard(gameboard);
	while (true) {
    cout << CYAN <<"Ship: Vetical XXX  Tile: ";
    int tile = -1;
    cin >> answer;
    tile = (int(toupper(answer.at(0))) - 65)*10 + int(answer.at(1)) - 48; //stupid ascii math
    if (tile < 0 or tile > SIZE*SIZE or gameboard.at(tile) == 1 or gameboard.at(tile) == 2) cout << RED <<"TRY AGAIN!" << endl; // if we already tried there, try again
	else if (tile >= 80) cout << RED << "TRY AGAIN!" << endl;
	else {
        for (int i = 0; i < 30; i += 10)gameboard.at(tile + i) = 3;
        break;
    }
    }
	cout << YELLOW << "YOUR FINAL BOARD: " << endl;
	printBoard(gameboard);
	for (int i = 0; i < gameboard.size(); i++) if (gameboard.at(i) == 3) gameboard.at(i) = 1;
	return gameboard;
}

void printBoard(vector<int> gameboard){
for(int i = 0; i < gameboard.size(); i++){               // BARE BONES UI CODE, JUST PRINTS A GRID (1/0 == NOTHING, 2 == HIT, -1 == MISS)
        if (i % int(sqrt(gameboard.size())) == 0) cout << endl;
        if (gameboard.at(i) == 0 or gameboard.at(i) == 1) cout <<WHITE << "-";
        else if (gameboard.at(i) == 2) cout << GREEN <<"X";
        else if (gameboard.at(i) == -1) cout << RED << "O";
		else if (gameboard.at(i) == 3) cout << YELLOW <<"*";
        else cout << "Error";
    }
	cout << endl;
}

vector<int> battleship(int player, vector<int> gameboard) {
	string answer;
	int SIZE = 10;
	cout << CYAN <<"Player " << player << " may take their shot (A-J Row, 0-9 column)" << endl;
	
	// UI CODE BELOW vvvvvvvvvvvvv
	//
	int tile = 0;
	for(int i = 0; i < 3; i++) {
	while (true) {
	printBoard(gameboard);
	//
	// UI CODE ABOVE ^^^^^^^^^^^^

	cout << CYAN <<"\nTile-To-Shoot: ";
	cin >> answer;
	cout << endl; 
	if (answer.size() != 2) {
		cout << RED <<"TRY AGAIN!" << endl;
		continue;
	}
	tile = (int(toupper(answer.at(0))) - 65)*10 + int(answer.at(1)) - 48; //stupid ascii math
	if (tile < 0 or tile > SIZE*SIZE or gameboard.at(tile) == -1 or gameboard.at(tile) == 2) cout <<RED << "TRY AGAIN!" << endl; // if we already tried there, try again
	else break;
	}
	if (gameboard.at(tile) == 1) {
		cout << GREEN << "HIT!" << endl;
		gameboard.at(tile) = 2; // Hit
	}
	else {
		cout << RED << "Miss!" << endl;
		gameboard.at(tile) = -1; // miss
	}
	}
	printBoard(gameboard);
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
		cout << YELLOW << "Welcome to Volleyshipardy! You are player 1 so you will start first.\n";
		int timeset = 20;
		int x = timeset; //Amount of seconds the players start with
		const int SIZE = 10;
		vector<int> gameboard1 = battleBoard(SIZE);
		cout << RED << "Player 2" << endl;
		vector<int> gameboard2 = battleBoard(SIZE);  //battleship boards
		while(true) {  //Infinite loop until a win
			x = jeopardy(1, x); 							//player 1 jeop question
			if (x == 0) { 									//If they lost, continue for player 2's battleship
				cout << endl <<GREEN<< "Player 2 Scores!" << endl; 
				gameboard1 = battleship(2, gameboard1); 	//plays battleship (See above function)
				x = timeset; 								//resets jeop timer
				if (find(gameboard1.begin(), gameboard1.end(), 1) == gameboard1.end()) { //searches for any ships, ends game if none found
				cout << CYAN <<"Player 2 has sunk all of player 1's ships! Player 2 WINS!" << endl;
				break;
				}
			} x = jeopardy(2, x); //repeat of above code but for opposite player
			if (x == 0) {
                cout << endl << GREEN <<"Player 1 Scores!" << endl;
                gameboard2 = battleship(1, gameboard2);
				x = timeset;
                if (find(gameboard2.begin(), gameboard2.end(), 1) == gameboard2.end()) {
                cout << CYAN <<"Player 2 has sunk all of player 1's ships! Player 2 WINS!" << endl;
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
