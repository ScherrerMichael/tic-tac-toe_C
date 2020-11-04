#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int rows = 3;
const int columns = 3;

struct player_data
{
    bool multiplayer;

    string player_one_name;
    int player_one_score;
    char player_one_symbol;

    string player_two_name;
    int player_two_score;
    char player_two_symbol;
};


void print_welcome();
void prompt_create_game(player_data *data);
void print_board(const char array[][columns]);
void make_turn(bool player, char symbol, char array[][columns]);
bool check_win(const char array[][columns]);

int main()
{
    string input;
    player_data *data = new player_data;

    char array[rows][columns] ={
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '},
    };

    print_welcome();
    prompt_create_game(data);

    do{
        cout<<"do you choose X's or O's?";
        getline(cin,input);

        if(input != "X" && input != "O"){
            cout<<"Please choose a valid input ([X] or [O]).\n"<<endl;
        }
    }while(input != "X" && input != "O");

    // display the game board

    make_turn(true,'X', array);
    print_board(array);
}

void print_welcome(){
 cout << R"(_____  _  ____     _____  ____  ____     _____  ____  _____
/__ __\/ \/   _\   /__ __\/  _ \/   _\   /__ __\/  _ \/  __/
  / \  | ||  / _____ / \  | / \||  / _____ / \  | / \||  \  
  | |  | ||  \_\____\| |  | |-|||  \_\____\| |  | \_/||  /_ 
  \_/  \_/\____/     \_/  \_/ \|\____/     \_/  \____/\____\)" <<"\n";
}

void prompt_create_game(player_data *data){

    int num_players;
    string input;

    cout<<"Welcome! \n";

    do{
    cout<<"How many players (1/2)?: ";
    cin >> num_players;
    cin.ignore(100,'\n');
    cout<<"\n";

    if((num_players != 1) && (num_players != 2)){
        cout <<"\nPlease enter a valid number (1 or 2)";
    }

    }while((num_players != 1) && (num_players != 2));

    if(num_players == 2)
    {
        cout<<"player 1 name: ";
        getline(cin, data -> player_one_name);
        cout<<"\n";

        cout<<"player 2 name: ";
        getline(cin, data -> player_two_name);
        cout<<"\n";
    }
    else{
        cout<<"Player name: ";
        getline(cin, data -> player_one_name);

        data -> player_two_name = "CPU";
    }

    cout<<"\nEnter name: ";
    getline(cin, input);
    cout<<"Welcome, " + input + "."<<endl;

}

void print_board(const char array[][columns])
{
    cout<< array[0][0]; cout<< "  |  "; cout<< array[0][1]; cout<<"  |  "; cout<< array[0][2] <<endl;
    cout<< '_'; cout<< "     "; cout<< '_'; cout<<"     "; cout<< '_' <<endl;
    cout <<endl;
    cout<< array[1][0]; cout<< "  |  "; cout<< array[1][1]; cout<<"  |  "; cout<< array[1][2] <<endl;
    cout<< '_'; cout<< "     "; cout<< '_'; cout<<"     "; cout<< '_' <<endl;
    cout <<endl;
    cout<< array[2][0]; cout<< "  |  "; cout<< array[2][1]; cout<<"  |  "; cout<< array[2][2] <<endl;
}

void make_turn(bool player, char symbol, char array[][columns])
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