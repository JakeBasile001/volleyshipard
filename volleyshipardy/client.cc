#include "headers/read.h"
#include "headers/colors.h"
#include "headers/jeopardy.h"
#include "headers/testcases.h"

using namespace std;
using boost::asio::ip::tcp;


// Make more Gtest cases, since the ship can exit outside of bounds..
// Object oreneded programing can go along way in this
// - Alex ~

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
