#include <vector>
#include <iostream>
#include <cmath>
#include "colors.h"


//You can do this if you want.. 
using std::vector, std::cout, std::endl, std::cin, std::string;


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