/*------------------------------------------------------------------------------
Title: Tic Tac Bro
Programmer: Justin Rucinski
Purpose: Create a ascii tic tac toe game with two difficulties
				for computer controlled AI.

------------------------------------------------------------------------------*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <math.h>
#include <time.h>

using namespace std;

void clear_board();
void draw_board();
void user_turn();
void comp_turn();
int computer_can_win();
int computer_can_block();
int computer_neither();
bool checkVal(int);
bool checkWin(string);

string spaces[9] = { " ", " ", " ", " ", " ", " ", " ", " ", " "};
//queue<int> boardOpen;
bool easy = false;
bool hard = false;
bool userWin = false;
bool compWin = false;
bool catsGame = false;

int main() {

	int difficulty;
	string computer_difficulty;
	bool bad = false;
	char again = 'n';

	cout << "Welcome to Tic Tac Bro!" << endl;

	do {
		clear_board();
		//Loop if user enters invalid input
		do {
			cout << "Which difficulty would you like to play?" << endl;
			cout << "(1)Easy" << endl;
			cout << "(2)Hard" << endl;
			cout << "Difficulty: ";
			cin  >> difficulty;

			//Check if user enters an integer
			bad = cin.fail();
			if(bad) {
				cout <<  endl << "Please enter a digit.";
			}
			cin.clear();
			cin.ignore(10, '\n');

			//Check if user enter 1 or 2
			if(difficulty != 1 && difficulty != 2) {
				cout << endl << "Please enter (1) for Easy and (2) for Hard" << endl << endl;
				bad = true;
			} else if (difficulty == 1) {
				easy = true;
			} else if (difficulty == 2) {
				hard = true;
			}
		} while(bad);

		while(!catsGame) {
			draw_board();
			user_turn();
			if(checkWin("user")) {
				cout << "You win!" << endl;
				break;
			}
			if (checkWin("cat")) {
				cout << "Cats game!" << endl;
				break;
			}
			comp_turn();
			if (checkWin("comp")) {
				cout << "You lose!" << endl;
				break;
			}
			if (checkWin("cat")) {
				cout << "Cats game!" << endl;
				break;
			}
		}

		cout << "Final Board" << endl;
		cout << "-----------" << endl;
		draw_board();

		cout << endl;
		cout << "Play again (y/n)?: ";
		cin >> again;

	} while (again == 'y');

	return 0;
}

/*------------------------------------------------------------------------------
Function: 	clear_board

Use:				Clear board and set variables back

Arguments:	none

Returns:		void
//----------------------------------------------------------------------------*/
void clear_board() {
	for(int i = 0; i < 9; i++) {
		spaces[i] = " ";
	}
	easy = false;
	hard = false;
	userWin = false;
	compWin = false;
	catsGame = false;
}

/*------------------------------------------------------------------------------
Function: 	draw_board

Use:				Draw the tic tac toe board

Arguments:	none

Returns:		void
//----------------------------------------------------------------------------*/
void draw_board() {
	cout << "    0     1     2" << endl;
	cout << "0   " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  " << endl;
	cout << "  -----|-----|-----" << endl;
	cout << "1   " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  " << endl;
	cout << "  -----|-----|-----" << endl;
	cout << "2   " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  " << endl;
}

/*------------------------------------------------------------------------------
Function: 	user_move

Use:				Ask the user which (col, row) they want to place their letter
						place the letter if it's a valid spot

Arguments:	none

Returns:		void
//----------------------------------------------------------------------------*/
void user_turn() {
	int col, row, index;
	bool invalidMove = true;

	cout << "YOUR MOVE!" << endl;

	while (invalidMove) {
		cout << "Please enter the column number: ";
		cin >> col;

		cout << "Please enter the row number: ";
		cin >> row;

		if (col == 0 && row == 0) {
			index = 0;
		} else if (col == 0 && row == 1) {
			index = 3;
		} else if (col == 0 && row == 2) {
			index = 6;
		} else if (col == 1 && row == 0) {
			index = 1;
		} else if (col == 1 && row == 1) {
			index = 4;
		} else if (col == 1 && row == 2) {
			index = 7;
		} else if (col == 2 && row == 0) {
			index = 2;
		} else if (col == 2 && row == 1) {
			index = 5;
		} else if (col == 2 && row == 2) {
			index = 8;
		}

		//Make sure the space is empty and place their letter
		if (spaces[index] == " ") {
			spaces[index] =  "X";
			invalidMove = false;
		} else {
			cout << "Invalid Move! Try again!" << endl;
		}
	}
}

/*------------------------------------------------------------------------------
Function: 	comp_turn

Use:				Ask the user which (col, row) they want to place their letter
						place the letter if it's a valid spot

Arguments:	none

Returns:		void
//----------------------------------------------------------------------------*/
void comp_turn() {
	int index;
	//Easy Difficulty
	if(easy) {
		do {
			index = floor(rand() % 9);
		} while(spaces[index] != " ");
		spaces[index] = "O";
	}

	//Hard Difficulty
	if(hard) {
		bool found = false;

		//If middle spot is open, take it
		if(spaces[4] == " ") {
			index = 4;
			found = true;
		}
		else {
			index = computer_can_win();
		}
		if(!checkVal(index)) {
			index = computer_can_block();
		}
		if(!checkVal(index)) {
			index = computer_neither();
  	}

		spaces[index] = "O";

	}
}

/*------------------------------------------------------------------------------
Function: 	computer_can_win

Use:				Check if the computer can win;
						return winning index

Arguments:	none

Returns:		index of best move or null
//----------------------------------------------------------------------------*/
int computer_can_win() {
	int index;

	//Check for win in top row
	if(spaces[0] == "O" && spaces[1] == "O" && spaces[2] == " ") {
		index = 2;
	}	else if(spaces[0] == "O" && spaces[2] == "O" && spaces[1] == " ") {
		index = 1;
	} else if(spaces[1] == "O" && spaces[2] == "O" && spaces[0] == " ") {
		index = 0;
	}
	//Left col win
	else if(spaces[0] == "O" && spaces[3] == "O" && spaces[6] == " ") {
		index = 6;
	} else if(spaces[0] == "O" && spaces[6] == "O" && spaces[3] == " ") {
		index = 3;
	} else if(spaces[3] == "O" && spaces[6] == "O" && spaces[0] == " ") {
		index = 0;
	}
	//Left to right diag win
	else if(spaces[0] == "O" && spaces[4] == "O" && spaces[8] == " ") {
		index = 8;
	} else if(spaces[0] == "O" && spaces[8] == "O" && spaces[4] == " ") {
		index = 4;
	} else if(spaces[4] == "O" && spaces[8] == "O" && spaces[0] == " ") {
		index = 0;
	}
	//Middle col win
	else if(spaces[1] == "O" && spaces[4] == "O" && spaces[7] == " ") {
		index = 7;
	} else if(spaces[1] == "O" && spaces[7] == "O" && spaces[4] == " ") {
		index = 4;
	} else if(spaces[4] == "O" && spaces[7] == "O" && spaces[1] == " ") {
		index = 1;
	}
	//Check for right column win
	else if(spaces[2] == "O" && spaces[5] == "O" && spaces[8] == " ") {
		index = 8;
	}	else if(spaces[2] == "O" && spaces[8] == "O" && spaces[5] == " ") {
		index = 5;
	} else if(spaces[5] == "O" && spaces[8] == "O" && spaces[2] == " ") {
		index = 2;
	}
	//Right to left diag win
	else if(spaces[2] == "O" && spaces[4] == "O" && spaces[6] == " ") {
		index = 6;
	} else if(spaces[2] == "O" && spaces[6] == "O" && spaces[4] == " ") {
		index = 4;
	} else if(spaces[4] == "O" && spaces[6] == "O" && spaces[2] == " ") {
		index = 2;
	}
	//Check for middle row win
	else if(spaces[3] == "O" && spaces[4] == "O" && spaces[5] == " ") {
		index = 5;
	} else if(spaces[3] == "O" && spaces[5] == "O" && spaces[4] == " ") {
		index = 4;
	} else if(spaces[4] == "O" && spaces[5] == "O" && spaces[3] == " ") {
		index = 3;
	}
	//Check for bottom row
	else if(spaces[6] == "O" && spaces[7] == "O" && spaces[8] == " ") {
		index = 8;
	} else if(spaces[6] == "O" && spaces[8] == "O" && spaces[7] == " ") {
		index = 7;
	} else if(spaces[7] == "O" && spaces[8] == "O" && spaces[6] == " ") {
		index = 6;
	}

	return index;
}

/*------------------------------------------------------------------------------
Function: 	computer_can_block

Use:				If computer can't win;
						check if the computer can block the user from winning,
						return the block index

Arguments:	none

Returns:		index of best move or null
//----------------------------------------------------------------------------*/
int computer_can_block() {
	int index;

	//Top Row
	if(spaces[0] == "X" && spaces[1] == "X" && spaces[2] == " ") {
		index = 2;
	}	else if(spaces[0] == "X" && spaces[2] == "X" && spaces[1] == " ") {
		index = 1;
	} else if(spaces[1] == "X" && spaces[2] == "X" && spaces[0] == " ") {
		index = 0;
	}
	//Left Col
	else if(spaces[0] == "X" && spaces[3] == "X" && spaces[6] == " ") {
		index = 6;
	} else if(spaces[0] == "X" && spaces[6] == "X" && spaces[3] == " ") {
		index = 3;
	} else if(spaces[3] == "X" && spaces[6] == "X" && spaces[0] == " ") {
		index = 0;
	}
	//Left to Right Diagonal
	else if(spaces[0] == "X" && spaces[4] == "X" && spaces[8] == " ") {
		index = 8;
	} else if(spaces[0] == "X" && spaces[8] == "X" && spaces[4] == " ") {
		index = 4;
	} else if(spaces[4] == "X" && spaces[8] == "X" && spaces[0] == " ") {
		index = 0;
	}
	//Check for block in middle column
	else if(spaces[1] == "X" && spaces[4] == "X" && spaces[7] == " ") {
		index = 7;
	} else if(spaces[1] == "X" && spaces[7] == "X" && spaces[4] == " ") {
		index = 4;
	} else if(spaces[4] == "X" && spaces[7] == "X" && spaces[1] == " ") {
		index = 1;
	}
	//Check for right col block
	else if(spaces[2] == "X" && spaces[5] == "X" && spaces[8] == " ") {
		index = 8;
	}	else if(spaces[2] == "X" && spaces[8] == "X" && spaces[5] == " ") {
		index = 5;
	} else if(spaces[5] == "X" && spaces[8] == "X" && spaces[2] == " ") {
		index = 2;
	}
	//Right to left diag block
	else if(spaces[2] == "X" && spaces[4] == "X" && spaces[6] == " ") {
		index = 6;
	} else if(spaces[2] == "X" && spaces[6] == "X" && spaces[4] == " ") {
		index = 4;
	} else if(spaces[4] == "X" && spaces[6] == "X" && spaces[2] == " ") {
		index = 2;
	}
	//Check for block in middle row
	else if(spaces[3] == "X" && spaces[4] == "X" && spaces[5] == " ") {
		index = 5;
	} else if(spaces[3] == "X" && spaces[5] == "X" && spaces[4] == " ") {
		index = 4;
	} else if(spaces[4] == "X" && spaces[5] == "X" && spaces[3] == " ") {
		index = 3;
	}
	//Check for block in bottom row
	else if(spaces[6] == "X" && spaces[7] == "X" && spaces[8] == " ") {
		index = 8;
	} else if(spaces[6] == "X" && spaces[8] == "X" && spaces[7] == " ") {
		index = 7;
	} else if(spaces[7] == "X" && spaces[8] == "X" && spaces[6] == " ") {
		index = 6;
	}

	return index;
}

/*------------------------------------------------------------------------------
Function: 	computer_neither

Use:				If computer can't win or block the user,
						find and return the best spot

Arguments:	none

Returns:		index of best move
//----------------------------------------------------------------------------*/
int computer_neither() {
	int index;

	//If user is in the middle and computer hasn't taken a spot yet
	if(spaces[4] == "X") {
		if(spaces[0] == " ") {
			index = 0;
		} else if(spaces[2] == " ") {
			index = 2;
		} else if(spaces[6] == " ") {
			index = 6;
		} else if(spaces[8] == " ") {
			index = 8;
		}
	}
	else if(spaces[0] == "X" && spaces[4] == "O" && spaces[8] == "X"
					&& (spaces[1] == " " || spaces[3] == " " || spaces[5] == " " || spaces[7] == " ")) {
			if(spaces[1] == " ") {
				index = 1;
			}
			else if(spaces[3] == " ") {
				index = 3;
			} else if(spaces[5] == " ") {
				index = 5;
			} else if(spaces[7] == " ") {
				index = 7;
			}
	}
	else if(spaces[2] == "X" && spaces[4] == "O" && spaces[6] == "X"
					&& (spaces[1] == " " || spaces[3] == " " || spaces[5] == " " || spaces[7] == " ")) {
			if(spaces[1] == " ") {
				index = 1;
			}
			else if(spaces[3] == " ") {
				index = 3;
			} else if(spaces[5] == " ") {
				index = 5;
			} else if(spaces[7] == " ") {
				index = 7;
			}
	}
	else if(spaces[4] == "X" && spaces[0] == "X" && spaces[8] == "O"
					&& spaces[2] == " " || spaces[6] == " ") {
			if(spaces[2] == " ") {
				index = 2;
			} else if(spaces[6] == " ") {
				index = 6;
			}
	}
	else if(spaces[4] == "X" && spaces[8] == "X" && spaces[0] == "O"
					&& spaces[2] == " " || spaces[6] == " ") {
			if(spaces[2] == " ") {
				index = 2;
			} else if(spaces[6] == " ") {
				index = 6;
			}
	}
	else if(spaces[4] == "X" && spaces[2] == "X" && spaces[6] == "O"
					&& spaces[0] == " " || spaces[8] == " ") {
			if(spaces[0] == " ") {
				index = 0;
			} else if(spaces[8] == " ") {
				index = 8;
			}
	}
	else if(spaces[4] == "X" && spaces[6] == "X" && spaces[2] == "O"
					&& spaces[0] == " " || spaces[8] == " ") {
			if(spaces[0] == " ") {
				index = 0;
			} else if(spaces[8] == " ") {
				index = 8;
			}
	}

	else {
		do {
			index = floor(rand() % 9);
		} while(spaces[index] != " ");
		spaces[index] = "O";
	}

	return index;
}

/*------------------------------------------------------------------------------
Function: 	checkVal

Use:				If computer can't win or block the user,
						find and return the best spot

Arguments:	none

Returns:		true if valid index
						false if invalid index
//----------------------------------------------------------------------------*/
bool checkVal(int i) {
	if(i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8) {
		return true;
	}
	else {
		return false;
	}
}

/*------------------------------------------------------------------------------
Function: 	checkWin

Use:				Checks if there has been a winner

Arguments:	String

Returns:		true if winner found
//----------------------------------------------------------------------------*/
bool checkWin(string player) {
		if(player == "user") {
			//Check columns
			for(int i = 0; i < 3; i++) {
				if(spaces[i] == "X" && spaces[i+3] == "X" && spaces [i+6] == "X") {
					userWin = true;
					return true;
				}
			}
			//Check rows
			for(int i = 0; i <= 6; i += 3) {
				if(spaces[i] == "X" && spaces[i+1] == "X" && spaces[i+2] == "X") {
					userWin = true;
					return true;
				}
			}
			//Check left to right diag
			if(spaces[0] == "X" && spaces[4] == "X" && spaces[8] == "X") {
				userWin = true;
				return true;
			}
			//Check right to left diag
			if(spaces[2] == "X" && spaces[4] == "X" && spaces[6] == "X") {
				userWin = true;
				return true;
			}

			//False if none of the above is found
			return false;
		}
		if(player == "comp") {
			//Check columns
			for(int i = 0; i < 3; i++) {
				if(spaces[i] == "O" && spaces[i+3] == "O" && spaces [i+6] == "O") {
					compWin = true;
					return true;
				}
			}
			//Check rows
			for(int i = 0; i <= 6; i += 3) {
				if(spaces[i] == "O" && spaces[i+1] == "O" && spaces[i+2] == "O") {
					compWin = true;
					return true;
				}
			}
			//Check left to right diag
			if(spaces[0] == "O" && spaces[4] == "O" && spaces[8] == "O") {
				compWin = true;
				return true;
			}
			//Check right to left diag
			if(spaces[2] == "O" && spaces[4] == "O" && spaces[6] == "O") {
				compWin = true;
				return true;
			}
			//No win if none of the above is found

			return false;
		}

		if (player == "cat") {

			if (spaces[0] != " " &&
					spaces[1] != " " &&
					spaces[2] != " " &&
					spaces[3] != " " &&
					spaces[4] != " " &&
					spaces[5] != " " &&
					spaces[6] != " " &&
					spaces[7] != " " &&
					spaces[8] != " ") {
						return true;
					}
			return false;
		}
}
