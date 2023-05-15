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
#include <gtest/gtest.h>
//#include <stdio.h>
//#include "graphics.h" //graphics.h does not work
//#include <dos.h> //dos.h does not work

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
void printBoard(const vector<int> &vec);

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

void printBoard(const vector<int> &gameboard){
	cout << "  ";
	for(int i = 0; i < 10 ; i++) cout << GREEN << i << " ";
	for(int i = 0; i < gameboard.size(); i++){// BARE BONES UI CODE, JUST PRINTS A GRID (1/0 == NOTHING, 2 == HIT, -1 == MISS)
		
        if (i % int(sqrt(gameboard.size())) == 0){
			char bob = 65 + (i / 10); 
			cout << endl << GREEN << bob << " ";
			}
        if (gameboard.at(i) == 0 or gameboard.at(i) == 1) cout <<WHITE << "- ";
        else if (gameboard.at(i) == 2) cout << GREEN <<"X ";
        else if (gameboard.at(i) == -1) cout << RED << "O ";
		else if (gameboard.at(i) == 3) cout << YELLOW <<"* ";
        else cout << "Error";
    }
	cout << endl;
}

enum ShotCaller {
	MISSED_ALREADY = -1,
	OOB = -2,
	HIT = 2,
	MISS = -3
};

int tileShoot(int tile, const vector<int> &gameboard) {
	if (tile < 0 or tile >= gameboard.size() or gameboard.at(tile) == -1 or gameboard.at(tile) == 2) return -2;
	else if (gameboard.at(tile) == 1) {
		//cout << GREEN << "HIT!" << endl;
		return 2;
	}
	else if (gameboard.at(tile) == 0) {
		//cout << RED << "Miss!" << endl;
		return -1;
	}
	else return -3;
}

//Error codes: -2: "tile is not on board or has already been fired at", 2: hit (target is a ship), -1: miss (target is empty), -3: "should never trigger"

vector<int> tester(100, 0);
vector<int> tester2(100, 1);
vector<int> tester3(100, 2);
TEST(TileShoot, GoodTests){
	EXPECT_EQ(tileShoot(50, tester), -1);
	EXPECT_EQ(tileShoot(50, tester2), 2);
	EXPECT_EQ(tileShoot(5, tester), -1);
	EXPECT_EQ(tileShoot(5, tester2), 2);
}

TEST(TileShoot, BadTests){
	EXPECT_EQ(tileShoot(10000, tester), -2);
	EXPECT_EQ(tileShoot(10000, tester2), -2);
	EXPECT_EQ(tileShoot(50, tester3), -2);
	EXPECT_EQ(tileShoot(0, tester3), -2);
}

TEST(TileShoot, EdgeTests){
	EXPECT_EQ(tileShoot(100, tester), -2);
	EXPECT_EQ(tileShoot(99, tester), -1);
	EXPECT_EQ(tileShoot(0, tester), -1);
	EXPECT_EQ(tileShoot(0, tester2), 2);
	EXPECT_EQ(tileShoot(99, tester2), 2);
	EXPECT_EQ(tileShoot(-1, tester), -2);
	EXPECT_EQ(tileShoot(-1, tester2), -2);

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
	if (tileShoot(tile, gameboard)  == -2) cout << RED << "TRY AGAIN!" << endl; // if we already tried there, try again
	else break;
	}
		gameboard.at(tile) = tileShoot(tile, gameboard);
		if (gameboard.at(tile) == 2) cout << GREEN << "HIT!" << endl;
		else if (gameboard.at(tile) == -1) cout << RED << "Miss!" << endl;
	}
	printBoard(gameboard);
	return gameboard;		
}

void printVolleyshipardy() {
    /*// auto detection
    int gdriver = DETECT,gmode,i;

    // initialize graphics mode
    initgraph(&gdriver,&gmode,"C:\\volleyshipardy");

    for (i=3; i<7; i++)
    {
        // setcolor of cursor
        setcolor(i);

        // set text style as
        // settextstyle(font, orientation, size)
        settextstyle(i,0,i);

        // print text at coordinate x,y;
        outtextxy(100,20*i,"Volleyshipardy");

        delay(500);
    }
    delay(2000);
	*/
	string vol = R"(
	eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
	eeeeeeeeeeee(eee(eeeeeeeeeeeeeeeeeeeee)eeeeeeeeeeeeeeeeeeeeeeee(eeeeeeeeeee
	e(eee(eeeeee)\ee)\eee(eee(eeeeeeeee(e/(e(eeeeeeeeeeeee)ee(eeeee)\e)ee(eeeee
	e)\ee)\e(ee((_)((_)e))\ee)\e)ee(eee)\()))\ee`ee)eee(e/(ee)(eee(()/(ee)\e)ee
	((_)((_))\ee_eee_ee/((_)(()/(ee)\e((_)\((_)e/(/(eee)(_))(()\eee((_))(()/(ee
	\e\e/e/((_)|e|e|e|(_))eee)(_))((_)|e|(_)(_)((_)_\e((_)_ee((_)ee_|e|ee)(_))e
	e\eVe//e_e\|e|e|e|/e-_)e|e||e|(_-<|e'e\e|e||e'_e\)/e_`e||e'_|/e_`e|e|e||e|e
	ee\_/e\___/|_|e|_|\___|ee\_,e|/__/|_||_||_||e.__/e\__,_||_|ee\__,_|ee\_,e|e
	eeeeeeeeeeeeeeeeeeeeeeeee|__/eeeeeeeeeeeeee|_|eeeeeeeeeeeeeeeeeeeeeee|__/ee
	)";
	for(int x = 0; x < vol.size(); x++) {
		if (vol.at(x) == 'e') cout << ' ';
		else if (vol.at(x) == '(' or vol.at(x) == ')') cout << RED << vol.at(x);
		else if (vol.at(x) == '/' or vol.at(x) == '\\') cout << YELLOW << vol.at(x);
		else cout << WHITE << vol.at(x);
}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
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
		//string spaces = "                                                                                ";
		printVolleyshipardy(); //failed
        cout << CYAN << "\nPlease select an option: \n\n";
    	cout << GREEN << "play       - will start a game of volleyshipardy " << RED << "immediately!\n";
    	cout << GREEN <<"test       - will run the test suite you've created.\n";
    	string st;
    	getline(cin ,st);
    	if (st == "test") return RUN_ALL_TESTS();
		else cout << YELLOW << "Starting now!\n";
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
                cout << CYAN <<"Player 1 has sunk all of player 2's ships! Player 1 WINS!" << endl;
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
