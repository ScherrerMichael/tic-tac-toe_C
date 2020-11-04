[1mdiff --git a/Main.cpp b/Main.cpp[m
[1mindex e7136bd..1beac89 100644[m
[1m--- a/Main.cpp[m
[1m+++ b/Main.cpp[m
[36m@@ -1,6 +1,7 @@[m
 #include <iostream>[m
 #include <vector>[m
 #include <string>[m
[32m+[m[32m#include <stdlib.h>[m
 [m
 using namespace std;[m
 [m
[36m@@ -9,7 +10,7 @@[m [mconst int columns = 3;[m
 [m
 struct player_data[m
 {[m
[31m-    bool multiplayer;[m
[32m+[m[32m    bool is_multiplayer;[m
 [m
     string player_one_name;[m
     int player_one_score;[m
[36m@@ -25,7 +26,8 @@[m [mvoid print_welcome();[m
 void prompt_create_game(player_data * & data);[m
 void print_board(const char array[][columns]);[m
 void clear_board(char array[][columns]);[m
[31m-bool make_turn(bool player, player_data *&data, char array[][columns]);[m
[32m+[m[32mbool make_turn(bool multiplayer, bool player, player_data *&data, char array[][columns]);[m
[32m+[m[32mbool make_cpu_turn(char array[][columns], player_data *& data, int difficulty);[m
 bool check_win(const char array[][columns], player_data *& data, int row, int col, char symbol, bool player);[m
 bool is_full(const char array[][columns]);[m
 void make_winner(bool player, player_data *& data);[m
[36m@@ -53,7 +55,7 @@[m [mint main()[m
         cout<<endl;[m
         do{[m
             current_turn = !current_turn;[m
[31m-        }while(make_turn(current_turn, data, array));[m
[32m+[m[32m        }while(make_turn(data -> is_multiplayer, current_turn, data, array));[m
 [m
     }while(play_again(data));[m
 }[m
[36m@@ -104,6 +106,8 @@[m [mvoid prompt_create_game(player_data * & data){[m
 [m
         cout<<"Player 2 icon: ";[m
         cin >> data -> player_two_icon;[m
[32m+[m
[32m+[m[32m        data -> is_multiplayer = true;[m
     }[m
     else{[m
         cout<<"Player name: ";[m
[36m@@ -120,6 +124,8 @@[m [mvoid prompt_create_game(player_data * & data){[m
         data -> player_two_icon = 'O';[m
         else[m
         data -> player_two_icon = 'X';[m
[32m+[m
[32m+[m[32m        data -> is_multiplayer = false;[m
     }[m
 [m
     data -> player_one_score = 0;[m
[36m@@ -140,7 +146,7 @@[m [mvoid print_board(const char array[][columns])[m
     cout<<"3  "<<endl;[m
 }[m
 [m
[31m-bool make_turn(bool player, player_data *&data, char array[][columns])[m
[32m+[m[32mbool make_turn(bool multiplayer, bool player, player_data *&data, char array[][columns])[m
 {[m
     int row;[m
     int col;[m
[36m@@ -150,22 +156,26 @@[m [mbool make_turn(bool player, player_data *&data, char array[][columns])[m
     else[m
     cout<<"Player: " << data -> player_two_name<< "'s turn:" <<endl;[m
 [m
[31m-    do{[m
[31m-        cout<<"enter row, column: "; cin >> row; cin >> col;[m
[31m-        if((row < 1 || row > 3) || (col < 1 || col > 3))[m
[31m-        {[m
[31m-            cout << "please enter a valid row/column" <<endl <<endl;[m
[31m-        }[m
[31m-    }while((row < 1 || row > 3) || (col < 1 || col > 3));[m
[32m+[m[32m    if(multiplayer || player){[m
[32m+[m[32m        do{[m
[32m+[m[32m            cout<<"enter row, column: "; cin >> row; cin >> col;[m
[32m+[m[32m            if((row < 1 || row > 3) || (col < 1 || col > 3))[m
[32m+[m[32m            {[m
[32m+[m[32m                cout << "please enter a valid row/column" <<endl <<endl;[m
[32m+[m[32m            }[m
[32m+[m[32m        }while((row < 1 || row > 3) || (col < 1 || col > 3));[m
[32m+[m[32m    }[m
 [m
     if(player == 1){[m
         array[row - 1][col - 1] = data -> player_one_icon;[m
         return check_win(array, data, row-1, col-1, data -> player_one_icon, player);[m
     }[m
[31m-    else{[m
[32m+[m[32m    else if(multiplayer){ // turn other than player 1[m
         array[row - 1][col - 1] = data -> player_two_icon;[m
         return check_win(array, data, row-1, col-1, data -> player_two_icon, player);[m
     }[m
[32m+[m[32m    else[m
[32m+[m[32m        return make_cpu_turn(array, data, 1);[m
 [m
 }[m
 [m
[36m@@ -303,4 +313,22 @@[m [mvoid clear_board(char array[][columns]){[m
 [m
         }[m
     }[m
[32m+[m[32m}[m
[32m+[m[32mbool make_cpu_turn(char array[][columns], player_data *& data, int difficulty){[m
[32m+[m[32m    //difficulty:[m[41m [m
[32m+[m[32m    // 1 - random (easy)[m
[32m+[m[32m    // 2 - my ai (??)[m
[32m+[m[32m    // 3 - algorithm (hard)[m
[32m+[m
[32m+[m[32m    int r_row = (rand() % 3 + 1) -1;[m
[32m+[m[32m    int r_col = (rand() % 3 + 1) -1;[m
[32m+[m
[32m+[m[32m    if(array[r_row][r_col] == ' '){[m
[32m+[m[32m        array[r_row][r_col] = data -> player_two_icon;[m
[32m+[m[32m    }[m
[32m+[m[32m    else[m
[32m+[m[32m        return make_cpu_turn(array, data, difficulty);[m
[32m+[m
[32m+[m[32m    return check_win(array, data, r_row, r_col, data -> player_two_icon, false);[m
[32m+[m
 }[m
\ No newline at end of file[m
[1mdiff --git a/Main.exe b/Main.exe[m
[1mindex edd6878..9653a97 100644[m
Binary files a/Main.exe and b/Main.exe differ
