#include <iostream>
using namespace std;

struct Player {
    string name;
    char symbol;
};

void display_grid() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j==2 and i != 2) {
                cout << "_____|_____|_____" << endl;
            }else {
                cout << "     |     |     " << endl;
            }
        }
    }
    cout << endl;
}

int main() {
    display_grid();
}