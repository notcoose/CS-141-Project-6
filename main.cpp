/******************************************************************************
Author: Markus Perez
Program 5: Connect 4
TA: Tues 2-2:50
Date: Nov 17, 2023
Enviroment: ZyBooks
This program plays the game "Connect 4" with two users taking turns making moves until
there is a winner, draw, or a user chooses to quit.
*******************************************************************************/
#include <iostream>
#include <string>
using namespace std;

class connect4{ //The connect4 class handles all actions
    public:
        void displayBoard();
        bool isFinished();
        void checkWinStatus();
        void userMove(string player);
    private:
        string Board[7][7] = {{"0", "1", "2", "3", "4", "5", "6"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"}}; //Creates the board as a 7x7 array
        bool winStatus = false;
        bool forceQuit = false;
};

void connect4::displayBoard(){ //Displays the board in the console
    cout << endl;
    for(int k = 0; k < 7; k++)
        cout << Board[0][k] << " ";
    for(int i = 1; i < 7; i++){
        cout << "\n        ";
        for(int j = 0; j < 7; j++)
            cout << Board[i][j] << " ";
    }
}

bool connect4::isFinished(){ //Checks to see if the game is finished (someone won, there is a draw, or someone quit)
    bool boardFull = true;

    for(int i = 0; i < 7; i++){ //Determines if the board is not full
        for(int j = 0; j < 7; j++){
            if(Board[i][j] == "-")
                boardFull = false;
        }
    }

    if(boardFull == true){ //If the board is full, declares a draw and returns true
        cout << "Board is Full, It's a Draw!!!";
        return true;
    }
    else if(forceQuit == true){ //If the user wanted to quit, declares an end to the game and returns true
        cout << "Ending Game";
        return true;
    }
    else //Calls the function to check the win status
        checkWinStatus();
    
    return winStatus; //Returns the win status if the board is not full and the user did not want to quit
}

void connect4::checkWinStatus(){ //Checks all possible win conditions, all 4 different in a row combinations, updates win status if needed
    for(int i = 1; i < 7; i++){ //Checks for horizontal win
        for(int j = 0; j < 4; j++){
            if((Board[i][j] != "-") && (Board[i][j] == Board[i][j + 1]) && (Board[i][j + 1] == Board[i][j + 2]) && (Board[i][j + 2] == Board[i][j + 3])){
                winStatus = true;
                cout << "Game is Over, Player " << Board[i][j] << " got 4 in a row!!!!";
            }
        }
    }

    for(int i = 1; i < 4; i++){ //Checks for vertical win
        for(int j = 0; j < 7; j++){
            if((Board[i][j] != "-") && (Board[i][j] == Board[i + 1][j]) && (Board[i + 1][j] == Board[i + 2][j]) && (Board[i + 2][j] == Board[i + 3][j])){
                winStatus = true;
                cout << "Game is Over, Player " << Board[i][j] << " got 4 in a row!!!!";
            }
        }
    }

    for(int i = 6; i > 3; i--){ //Checks for upward diagonal win
        for(int j = 0; j < 4; j++){
            if((Board[i][j] != "-") && (Board[i][j] == Board[i - 1][j + 1]) && (Board[i - 1][j + 1] == Board[i - 2][j + 2]) && (Board[i - 2][j + 2] == Board[i - 3][j + 3])){
                winStatus = true;
                cout << "Game is Over, Player " << Board[i][j] << " got 4 in a row!!!!";
            }
        }
    }

    for(int i = 1; i < 4; i++){ //Checks for downward diagonal win
        for(int j = 0; j < 4; j++){
            if((Board[i][j] != "-") && (Board[i][j] == Board[i + 1][j + 1]) && (Board[i + 1][j + 1] == Board[i + 2][j + 2]) && (Board[i + 2][j + 2] == Board[i + 3][j + 3])){
                winStatus = true;
                cout << "Game is Over, Player " << Board[i][j] << " got 4 in a row!!!!";
            }
        }
    }
}

void connect4::userMove(string player){ //Prompts and executes a user move
    string move;
    bool moveMade = false;
    cout << "\nIt is " << player << "'s turn.\nEnter a column to place your piece. ";
    cin >> move;

    if(move == "Q" || move == "q") //Checks to see if a user wants to quit
        forceQuit = true;
    else{
        if(stoi(move) < 0 || stoi(move) > 6){ //Checks the vailidity of the inputted column
                cout << "Please enter a valid column";
                userMove(player);
        }
        for(int i = 6; i > 0; i--){ //Executes a move if possible
            if(Board[i][stoi(move)] == "-"){
                Board[i][stoi(move)] = player;
                moveMade = true;
                break;
            }
        }
        if(moveMade == false){ //If a move was not possible, calls the function again for a new move
            cout << "\ncolumn chosen is already full";
            userMove(player);
        }
    }    
}

int main() 
{
    cout << "This is the Game Connect 4. \n\nEach player should place an X or an O in the space \nby entering the column you want to place the piece. \nThe piece will fall until it reaches the bottom or \nthe current pieces in the board. When X or O gets 4 in \na row (either horizontally, vertically, or diagonally, \nthen that person wins. The user can enter Q (or q) to \nend the game early. \n\nLet's get started!!!\n ";

    connect4 userGame; //Creates the userGame object of connect4 class
    int roundCount = 1;

    while(userGame.isFinished() == false){   //Continues the game until the function declares it is finished
        userGame.displayBoard(); //Displays the board
        switch(roundCount % 2){ //Switches the player every round
            case 1:
                userGame.userMove("X");
                roundCount++;
                break;
            case 0:
                userGame.userMove("O");
                roundCount++;
                break;
        }
    }
    return 0;
}

