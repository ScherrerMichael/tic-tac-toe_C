#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print_board(const char array[][3]);
void make_turn(bool player, char symbol, char array[][3]);

int main()
{
    string input;

    char array[3][3] ={
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '},
    };

    cout<<"Enter name: ";
    getline(cin, input);
    cout<<"Welcome, " + input + "."<<endl;

    do{
        cout<<"do you choose X's or O's?";
        getline(cin,input);

        if(input != "X" && input != "O"){
            cout<<"Please choose a valid input ([X]/[O])."<<endl;
        }
    }while(input != "X" && input != "O");

    // display the game board

    make_turn(1,'X', array);
    print_board(array);
}

void print_board(const char array[][3])
{
    cout<< array[0][0]; cout<< "  |  "; cout<< array[0][1]; cout<<"  |  "; cout<< array[0][2] <<endl;
    cout<< '_'; cout<< "     "; cout<< '_'; cout<<"     "; cout<< '_' <<endl;
    cout <<endl;
    cout<< array[1][0]; cout<< "  |  "; cout<< array[1][1]; cout<<"  |  "; cout<< array[1][2] <<endl;
    cout<< '_'; cout<< "     "; cout<< '_'; cout<<"     "; cout<< '_' <<endl;
    cout <<endl;
    cout<< array[2][0]; cout<< "  |  "; cout<< array[2][1]; cout<<"  |  "; cout<< array[2][2] <<endl;
}

void make_turn(bool player, char symbol, char array[][3])
{
    int row;
    int col;

    cout<<"player" << player << "'s turn:" <<endl;
    do{
        cout<<"enter row number: "; cin >> row;
        cout<<"enter colum number: "; cin >> col;
        if((row < 1 || row > 3) || (col < 1 || col > 3))
        {
            cout << "please enter a valid row/column" <<endl <<endl;
        }
    }while((row < 1 || row > 3) || (col < 1 || col > 3));

    array[row - 1][col - 1] = symbol;
}