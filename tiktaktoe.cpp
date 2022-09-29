#include <iostream>
using namespace std;

void display_grid(char** tab, size_t length) {
    // pour chaque ligne de la grille
    for (int i=0; i<length; i++) {
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
        for (int j=0; j<length; j++) {
            if (j < length - 1) {
                cout << "   " << (tab[i][j] != 0 ? tab[i][j] : ' ') <<"   |";
            }
            else {
                cout << "   " << (tab[i][length-1] != 0 ? tab[i][length-1] : ' ') <<"   " << endl; 
            }
        }
        
        // la ligne numero 3 de chaque ligne de la grille
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

bool put_symbol_on_grid(char** tab, char symbol, size_t row, size_t col) {
    tab[row-1][col-1] = symbol;
    return true;
}

int main() {
    int n;
    cout << "Saisir la taille de la grille: ";
    cin >> n;
    system ("clear");
    char** tab = new char*[n];
    for (int i=0; i< n; i++) {
        tab[i] = new char[n];
    }

    display_grid(tab, n);
    char symbol;
    size_t row, col;
    while(true) {
        cout << "Enter your symbol: ";
        cin >> symbol;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter col: ";
        cin >> col;
        system ("clear");
        put_symbol_on_grid(tab, symbol, row, col);
        display_grid(tab, n);
    }
}