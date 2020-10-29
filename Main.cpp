#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string input;
    cout<<"Enter name: ";
    getline(cin, input);
    cout<<"Welcome, " + input + "."<<endl;

    do{
        cout<<"do you choose X's or O's?";
        getline(cin,input);

        if(input != "X" || input != "O"){
            cout<<"Please choose a valid input ([X]/[O])."<<endl;
        }
    }while(input != "X" && input != "O");

    // display the game board..
}