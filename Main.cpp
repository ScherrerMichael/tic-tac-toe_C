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
    char player_one_icon;

    string player_two_name;
    int player_two_score;
    char player_two_icon;
};

void print_spaces(int num_spaces = 100);
void print_welcome();
void prompt_create_game(player_data * & data);
void print_board(const char array[][columns]);
void clear_board(char array[][columns]);
bool make_turn(bool player, player_data *&data, char array[][columns]);
bool check_win(const char array[][columns], player_data *& data, int row, int col, char symbol, bool player);
bool is_full(const char array[][columns]);
void make_winner(bool player, player_data *& data);
bool play_again(player_data *& data);

int main()
{
    player_data *data = new player_data;
    bool current_turn = false;

    char array[rows][columns] ={
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '},
    };

    print_welcome();
    prompt_create_game(data);

    //main loop
    do{
        clear_board(array);
        //game loop
        print_board(array);
        cout<<endl;
        do{
            current_turn = !current_turn;
        }while(make_turn(current_turn, data, array));

    }while(play_again(data));
}

void print_welcome(){
 cout << R"(_____  _  ____     _____  ____  ____     _____  ____  _____
/__ __\/ \/   _\   /__ __\/  _ \/   _\   /__ __\/  _ \/  __/
  / \  | ||  / _____ / \  | / \||  / _____ / \  | / \||  \  
  | |  | ||  \_\____\| |  | |-|||  \_\____\| |  | \_/||  /_ 
  \_/  \_/\____/     \_/  \_/ \|\____/     \_/  \____/\____\)" <<"\n";
}

void prompt_create_game(player_data * & data){

    int num_players;
    string input;

    cout<<"Welcome! \n";

    // set up player names

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

        // set up player icons

        cout<<"Player 1 icon: ";
        cin >> data -> player_one_icon;

        cout<<"Player 2 icon: ";
        cin >> data -> player_two_icon;
    }
    else{
        cout<<"Player name: ";
        getline(cin, data -> player_one_name);

        data -> player_two_name = "CPU";

        // set up player icons

        cout<<"Player 1 icon: ";
        cin >> data -> player_one_icon;

        if(data -> player_one_icon == 'X')
        data -> player_two_icon = 'O';
        else
        data -> player_two_icon = 'X';
    }

    data -> player_one_score = 0;
    data -> player_two_score = 0;
}

void print_board(const char array[][columns])
{
    print_spaces();
    cout<< "   1     2     3\n\n";
    cout<<"   "<< array[0][0]; cout<< "  |  "; cout<< array[0][1]; cout<<"  |  "; cout<< array[0][2] <<endl;
    cout<<"1  "<< '_'; cout<< "     "; cout<< '_'; cout<<"     "; cout<< '_' <<endl;
    cout<<endl;
    cout<<"   "<< array[1][0]; cout<< "  |  "; cout<< array[1][1]; cout<<"  |  "; cout<< array[1][2] <<endl;
    cout<<"2  "<< '_'; cout<< "     "; cout<< '_'; cout<<"     "; cout<< '_' <<endl;
    cout <<endl;
    cout<<"   "<< array[2][0]; cout<< "  |  "; cout<< array[2][1]; cout<<"  |  "; cout<< array[2][2] <<endl;
    cout<<"3  "<<endl;
}

bool make_turn(bool player, player_data *&data, char array[][columns])
{
    int row;
    int col;

    if(player)
    cout<<"Player: " << data -> player_one_name<< "'s turn:" <<endl;
    else
    cout<<"Player: " << data -> player_two_name<< "'s turn:" <<endl;

    do{
        cout<<"enter row, column: "; cin >> row; cin >> col;
        if((row < 1 || row > 3) || (col < 1 || col > 3))
        {
            cout << "please enter a valid row/column" <<endl <<endl;
        }
    }while((row < 1 || row > 3) || (col < 1 || col > 3));

    if(player == 1){
        array[row - 1][col - 1] = data -> player_one_icon;
        return check_win(array, data, row-1, col-1, data -> player_one_icon, player);
    }
    else{
        array[row - 1][col - 1] = data -> player_two_icon;
        return check_win(array, data, row-1, col-1, data -> player_two_icon, player);
    }

}

bool check_win(const char array[][columns], player_data *& data, int row, int col, char symbol, bool player)
{

    print_board(array);

    cout<<endl;

    //verify: 

        // diagonals
        if( row == col){
            if((array[0][0] == symbol) && (array[1][1] == symbol) && (array[2][2] == symbol)){

                make_winner(player, data);
                return false;
            }
        }

        // first row
        if(row == 0){
            if(array[0][0] == symbol && array[0][1] == symbol && array[0][2] == symbol){

                make_winner(player, data);
                return false;
            }
        }
        // second row
        if(row == 1){
            if(array[1][0] == symbol && array[1][1] == symbol && array[1][2] == symbol){

                make_winner(player, data);
                return false;
            }
        }
        // third row
        if(row == 2){
            if(array[2][0] == symbol && array[2][2] == symbol && array[2][2] == symbol){

                make_winner(player, data);
                return false;
            }
        }
        // first column
        if(col == 0){
            if(array[0][0] == symbol && array[1][0] == symbol && array[2][0] == symbol){

                make_winner(player, data);
                return false;
            }
        }
        // second column
        if(col == 1){
            if(array[0][1] == symbol && array[1][1] == symbol && array[2][1] == symbol){

                make_winner(player, data);
                return false;
            }
        }
        // third column
        if(col == 2){
            if(array[0][2] == symbol && array[1][2] == symbol && array[2][2] == symbol){

                make_winner(player, data);
                return false;
            }
        }

        //cats game (no winner)
        if(is_full(array))
        {
            cout<<"Cats game (no winner)";
            return false;
        }

        return true;
        
}
bool is_full(const char array[][columns])
{
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < columns; ++j){

            if(array[i][j] == ' '){
                return false;
            }
        }
    }

    return true;
}

void make_winner(bool player, player_data *& data)
{
    if(player == 1){
        data -> player_one_score += 1;
        cout<<"Player: " <<data->player_one_name <<" wins!"<<endl;
    }
    else{
        data -> player_two_score += 1;
        cout<<"Player: " <<data->player_two_name <<" wins!"<<endl;
    }
}

void print_spaces(int num_spaces){

    for(int i = 0; i < num_spaces; ++i){
        cout<<endl;
    }
}

bool play_again(player_data *& data){
    char input;

    cout<<data->player_one_name<<": " <<data->player_one_score<<"  "<<data->player_two_name<<": "<<data->player_two_score<<endl;

    cout<<"Continue(y/n)?: ";
    cin >> input;
    cin.ignore(100,'\n');

    if(input == 'y')
        return true;
    else
        return false;
}

void clear_board(char array[][columns]){

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < columns; ++j){

            array[i][j] = ' ';

        }
    }
}