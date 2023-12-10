/******************************************************************************
Author: Markus Perez
Program 6: Connect 4 with backtracking
TA: Tues 2-2:50
Date: Dec 1 2023
Enviroment: ZyBooks
This program plays the game "Connect 4" with two users taking turns making moves until
there is a winner, draw, or a user chooses to quit. Additionally, the progam allows for
backtracking and printing out all previous gamestates
*******************************************************************************/
#include <iostream>
#include <string>
using namespace std;

class connect4{ //handles board actions
    public:
        void displayBoard();
        bool isFinished();
        void checkWinStatus();
        void userMove(string player);
        void alternateTurn();
        string getTurn();
        void quit();
    private:
        string Board[7][7] = {{"0", "1", "2", "3", "4", "5", "6"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"},{"-", "-", "-", "-", "-", "-", "-"}}; //Initializes empty board
        bool winStatus = false;
        bool forceQuit = false;
        string turn = "X";
};

class connect4node{ //creates connect 4 nodes for the linked list
    public:
        connect4node(connect4 c4);
        connect4 getBoard();
        connect4node* getNext();
        void setNext(connect4node* next);
    private:
        connect4 game;
        connect4node* next;
};

class connect4linkedlist{ //creates connect 4 linked lists
    public:
        connect4linkedlist();
        void add(connect4 game);
        void remove();
        void print();
        connect4 getLast();
    private:
        connect4node* head;
        void print(connect4node* node);
};

connect4linkedlist::connect4linkedlist(){ //creates a nullptr head as the beginning of an empty list
    head = nullptr;
}

connect4 connect4linkedlist::getLast(){ //returns the board from the previous move
    connect4node* current = head;
    connect4 temp = current -> getBoard();
    if(head -> getNext() != nullptr) //Removes current board if board isn't empty
        remove();
    return temp;
}

void connect4linkedlist::add(connect4 game){ //adds game state to linked list
    connect4node* newNode = new connect4node(game);
    newNode -> setNext(this -> head);
    head = newNode;
}

void connect4linkedlist::remove(){ //removes game state from linked list
    connect4node* c4 = head;
    head = head -> getNext();
    delete c4;
}

void connect4linkedlist::print(){//checks if list is empty before printing
    if(head != nullptr){
        print(head);
    }
}

void connect4linkedlist::print(connect4node* node){//recursively prints game history in order
    if(node != nullptr){
        print(node -> getNext());
        node -> getBoard().displayBoard();
    }
}

connect4node::connect4node(connect4 c4){//constructor for node given a game
    this->game = c4;
    this->next = nullptr; 
}

connect4 connect4node::getBoard(){//returns the connect4 object from node
    return game;
}

connect4node* connect4node::getNext(){//returns pointer to next object
    return next;
}

void connect4node::setNext(connect4node* next){//sets the next object
    this->next = next; 
}

string connect4::getTurn(){//returns the player whose turn it is
    return turn;
}

void connect4::alternateTurn(){//switches to next player's turn
    if(turn == "X")
        turn = "O";
    else
        turn ="X";
}

void connect4::displayBoard(){ //displays the board
    cout << endl;
    for(int k = 0; k < 6; k++)
        cout << Board[0][k] << " ";
    cout << Board[0][6];
    for(int i = 1; i < 7; i++){
        cout << "\n\t";
        for(int j = 0; j < 7; j++)
            cout << Board[i][j] << " ";
    }
}

bool connect4::isFinished(){ //checks if the game is finished (someone won, there is a draw, or someone quit)
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

void connect4::checkWinStatus(){ //checks all possible win conditions, all 4 different in a row combinations, updates win status if needed
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

void connect4::userMove(string move){ //executes a user move
    bool moveMade = false;

    if(stoi(move) < 0 || stoi(move) > 6){ //Checks the vailidity of the inputted column
        cout << "Please enter a valid column ";
        cin >> move;
        userMove(move);
        return;
    }

    for(int i = 6; i > 0; i--){ //Executes a move if possible
        if(Board[i][stoi(move)] == "-"){
            Board[i][stoi(move)] = getTurn();
            moveMade = true;
            break;
        }
    }
    if(moveMade == false){ //If a move was not possible, calls the function again for a new move
        cout << "\ncolumn chosen is already full";
        userMove(move);
    }
}

void connect4::quit(){//sets quit status to true, which will end game
    forceQuit = true;
}

int main() 
{
    cout << "This is the Game Connect 4. \nEach player should place an X or an O in the space \nby entering the column you want to place the piece. \nThe piece will fall until it reaches the bottom or \nthe current pieces in the board. When X or O gets 4 in \na row (either horizontally, vertically, or diagonally, \nthen that person wins. The user can enter Q (or q) to \nend the game early. \nLet's get started!!! ";

    connect4 userGame; //creates a connect 4 game
    connect4linkedlist userList; //creates a linked list

    while(userGame.isFinished() == false){ //continues the game until the function declares it is finished
        userGame.displayBoard(); //displays the board
        
        string move;
        cout << "\nIt is " << userGame.getTurn() << "'s turn.\nEnter a column to place your piece.\t";
        cin >> move; //receives user move

        if(move == "Q" || move == "q") //checks if user wants to quit
            userGame.quit();
        else if(move == "P" || move == "p"){//checks if user wants to print
            userList.print();
        }
        else if(move == "U" || move == "u"){//checks if user wants to undo
            userGame = userList.getLast();
        }
        else{ //adds current game state to list, executes a move, and moves to next player's turn
            userList.add(userGame);
            userGame.userMove(move);
            userGame.alternateTurn();
        }
    }
    return 0;
}