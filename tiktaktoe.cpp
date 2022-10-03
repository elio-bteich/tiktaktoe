#include <iostream>
#include <cstdlib>
using namespace std;

struct Player {
    string name;
    char symbol;
};

void display_grid(char** tab, size_t length) {
    cout <<  "      ";
    for (int i=0; i < length; i++) {
        cout << "  C" << i+1 << "    "; 
    }
    cout << endl;

    // pour chaque ligne de la grille
    for (int i=0; i<length; i++) {
        cout << "      ";
        // la ligne numero 1 de chaque ligne de la grille
        for (int j=0; j<length; j++) {
            if (j < length -1 ){
                cout << "       |";
            }
            else {
                cout << "       " << endl;
            }
        }
        // la ligne numero 2 de chaque ligne de la grille
        cout << "  R" << i+1 << "  ";
        for (int j=0; j<length; j++) {
            if (j < length - 1) {
                cout << "   " << (tab[i][j] != 0 ? tab[i][j] : ' ') <<"   |";
            }
            else {
                cout << "   " << (tab[i][length-1] != 0 ? tab[i][length-1] : ' ') <<"   " << endl; 
            }
        }
        
        // la ligne numero 3 de chaque ligne de la grille
        cout << "      ";
        if (i<length-1) {
            for (int j=0; j < length; j++) {
                if (j < length-1) {
                    cout << "_______|";
                }
                else {
                    cout << "_______" << endl;
                }
            }
        }else {
            for (int j=0; j< length; j++) {
                if (j < length-1) {
                    cout << "       |";
                }
                else {
                    cout << "       " << endl;
                }
            }
        }
    }
}

bool is_tile_empty(char** tab, size_t row, size_t col) {

    return tab[row-1][col-1] == 0 ? true : false;

}

void put_symbol_on_grid(char** tab, char symbol, size_t row, size_t col) {

    tab[row-1][col-1] = symbol;

}

void play_turn(Player player, char** tab, size_t n) {

    display_grid(tab, n);
    cout << player.name << "'s turn!" << endl << endl;

    size_t row, col;

    cout << "Enter row: ";
    cin >> row;
    while (row <= 0 || row > n) {
        cout << "Row is not in range!" << endl << "Re-enter row: ";
        cin >> row;
    }
    

    
    cout << "Enter col: ";
    cin >> col;
    while (col <= 0 || col > n) {
        cout << "Column is not in range!" << endl << "Re-enter col: ";
        cin >> col;
    }
    
    system ("clear");
    if (is_tile_empty(tab, row, col)) {
        put_symbol_on_grid(tab, player.symbol, row, col);
    }
    else {
        cout << "tile is not empty try a different one..." << endl;
        play_turn(player, tab, n);
    }
}

bool are_equals(char* symbols_arr, size_t n) {

    for (size_t i = 1; i < n; i++) {
        if (symbols_arr[0] != symbols_arr[i]) {
            return false;
        }
    }
    return true;
}

bool is_winner(char symbol, char** tab, size_t n) {

    char* symbols_arr = new char[n];

    // lignes
    for (size_t row = 0; row < n; row++) {
        if (symbol == tab[row][0]) { // check if the symbol is equal at least to the first symbol of the row
            for (size_t col = 0; col < n; col++) {
                symbols_arr[col] = tab[row][col];
            }
            if (are_equals(symbols_arr, n)) {
                return true;
            };
        }
    }

    // colonnes
    for (size_t col = 0; col < n; col++) {
        if (symbol == tab[0][col]) { // check if the symbol is equal at least to the first symbol of the column
            for (size_t row = 0; row < n; row++) {
                symbols_arr[row] = tab[row][col];
            }
            if (are_equals(symbols_arr, n)) {
                return true;
            };
        }
    }

    // diagonale haut-gauche bas-droite
    if (symbol == tab[0][0]) {
        for (size_t i = 0; i < n; i++) {
            symbols_arr[i] = tab[i][i];
        }
        if (are_equals(symbols_arr, n)) {
            return true;
        }
    }

    // diagonale bas-gauche haut-droite
    if (symbol == tab[n-1][0]) {
        for (size_t i = 0; i < n; i++) {
            symbols_arr[i] = tab[n-1-i][i];
        }
        if (are_equals(symbols_arr, n)) {
            return true;
        }
    }

    return false;
}

void init_players(Player players_arr[2]) {
    for (int i =0; i < 2; i++) {
        cout << "Enter player" << i+1 << "'s name: ";
        cin >> players_arr[i].name;
        cout << "Enter player" << i+1 << "'s symbol: ";
        cin >> players_arr[i].symbol;
        system("clear");
    }
}


int main() {
    Player player1, player2;
    Player players_arr[2] = {player1, player2};
    srand(time(0));
    int turn = rand()%2;

    system("clear");
    init_players(players_arr);

    int n;
    cout << "Saisir la taille de la grille: ";
    cin >> n;
    system ("clear");

    // initialisation de la grille
    char** tab = new char*[n];
    for (int i=0; i< n; i++) {
        tab[i] = new char[n];
    }
    
    while(!is_winner(players_arr[turn].symbol, tab, n)) {
        turn = (turn + 1)%2; 
        play_turn(players_arr[turn], tab, n);        
    }
    
    display_grid(tab, n);
    cout << players_arr[turn].name << " won the game!" << endl;
}
