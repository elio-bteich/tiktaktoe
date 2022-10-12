#include <iostream>
#include <cstdlib>
using namespace std;

struct Player
{
    string name;
    char symbol;
};

void display_grid(char **tab, size_t length)
{
    cout << "      ";
    for (int i = 0; i < length; i++)
    {
        cout << "  C" << i + 1 << "    ";
    }
    cout << endl;

    // pour chaque ligne de la grille
    for (int i = 0; i < length; i++)
    {
        cout << "      ";
        // la ligne numero 1 de chaque ligne de la grille
        for (int j = 0; j < length; j++)
        {
            if (j < length - 1)
            {
                cout << "       |";
            }
            else
            {
                cout << "       " << endl;
            }
        }
        // la ligne numero 2 de chaque ligne de la grille
        cout << "  L" << i + 1 << "  ";
        for (int j = 0; j < length; j++)
        {
            if (j < length - 1)
            {
                cout << "   " << (tab[i][j] != 0 ? tab[i][j] : ' ') << "   |";
            }
            else
            {
                cout << "   " << (tab[i][length - 1] != 0 ? tab[i][length - 1] : ' ') << "   " << endl;
            }
        }

        // la ligne numero 3 de chaque ligne de la grille
        cout << "      ";
        if (i < length - 1) // si ligne de la grille n'est pas la dernière
        {
            for (int j = 0; j < length; j++)
            {
                if (j < length - 1)
                {
                    cout << "_______|";
                }
                else
                {
                    cout << "_______" << endl;
                }
            }
        }
        else // si ligne de la grille est la dernière
        {
            for (int j = 0; j < length; j++)
            {
                if (j < length - 1)
                {
                    cout << "       |";
                }
                else
                {
                    cout << "       " << endl;
                }
            }
        }
    }
}

bool is_tile_empty(char **tab, size_t row, size_t col)
{

    return tab[row - 1][col - 1] == 0 ? true : false;
}

void put_symbol_on_grid(char **tab, char symbol, size_t row, size_t col)
{

    tab[row - 1][col - 1] = symbol;
}

void play_turn(Player player, char **tab, size_t n)
{

    display_grid(tab, n);
    cout << "Tour de " << player.name << "!" << endl
         << endl;

    size_t row, col;

    cout << "Saisissez la ligne: ";
    cin >> row;
    while (row <= 0 || row > n)
    {
        cout << "La ligne n'est pas dans l'intervalle!" << endl
             << "Re-saisissez la ligne: ";
        cin >> row;
    }

    cout << "Saisissez la colonne: ";
    cin >> col;
    while (col <= 0 || col > n)
    {
        cout << "La colonne n'est pas dans l'intervalle!" << endl
             << "Re-saisissez la colonne: ";
        cin >> col;
    }

    system("clear");
    if (is_tile_empty(tab, row, col))
    {
        put_symbol_on_grid(tab, player.symbol, row, col);
    }
    else
    {
        cout << "La case saisie n'est pas vide, essayez une autre..." << endl << endl;
        play_turn(player, tab, n);
    }
}

bool are_equals(char *symbols_arr, size_t n)
{

    for (size_t i = 1; i < n; i++)
    {
        if (symbols_arr[0] != symbols_arr[i])
        {
            return false;
        }
    }
    return true;
}

bool is_winner(char symbol, char **tab, size_t n)
{

    char *symbols_arr = new char[n];

    // lignes
    for (size_t row = 0; row < n; row++)
    {
        if (symbol == tab[row][0]) // verifie si le symbole est égale au moins au premier symbole de la ligne
        { 
            for (size_t col = 0; col < n; col++)
            {
                symbols_arr[col] = tab[row][col];
            }
            if (are_equals(symbols_arr, n))
            {
                return true;
            };
        }
    }

    // colonnes
    for (size_t col = 0; col < n; col++)
    {
        if (symbol == tab[0][col]) // verifie si le symbole est égale au moins au premier symbole de la colonne
        { 
            for (size_t row = 0; row < n; row++)
            {
                symbols_arr[row] = tab[row][col];
            }
            if (are_equals(symbols_arr, n))
            {
                return true;
            };
        }
    }

    // diagonale haut-gauche bas-droite
    if (symbol == tab[0][0]) // verifie si le symbole est égale au moins au premier symbole de la diagonale
    { 
        for (size_t i = 0; i < n; i++)
        {
            symbols_arr[i] = tab[i][i];
        }
        if (are_equals(symbols_arr, n))
        {
            return true;
        }
    }

    // diagonale bas-gauche haut-droite
    if (symbol == tab[n - 1][0]) // verifie si le symbole est égale au moins au premier symbole de la diagonale
    { 
        for (size_t i = 0; i < n; i++)
        {
            symbols_arr[i] = tab[n - 1 - i][i];
        }
        if (are_equals(symbols_arr, n))
        {
            return true;
        }
    }

    return false;
}

void init_players(Player players_arr[2])
{
    for (int i = 0; i < 2; i++)
    {
        cout << "Saisissez le nom du joueur" << i + 1 << " : ";
        cin >> players_arr[i].name;
        cout << "Saisissez le symbole du joueur" << i + 1 << " : ";
        cin >> players_arr[i].symbol;
        system("clear");
    }
}

void next_turn(int &turn)
{
    turn = (turn + 1) % 2; // turn oscille entre 0 et 1
}

int main()
{
    Player player1, player2;
    Player players_arr[2] = {player1, player2};

    srand(time(0));
    int turn = rand() % 2; // choisit le premier tour alleatoirement

    system("clear");
    init_players(players_arr);

    int n;
    cout << "Saisissez la taille de la grille: ";
    cin >> n;
    while (n < 3)
    {
        system("clear");
        cout << "La taille est invalide! Veuillez saisir une taille plus grande ou égale à 3" << endl;
        cout << "Saisir de nouveau la taille de la grille: ";
        cin >> n;
    }

    system("clear");

    // initialisation de la grille
    char **tab = new char *[n];
    for (int i = 0; i < n; i++)
    {
        tab[i] = new char[n];
    }

    while (!is_winner(players_arr[turn].symbol, tab, n))
    {
        next_turn(turn);
        play_turn(players_arr[turn], tab, n);
    }

    display_grid(tab, n);
    cout << players_arr[turn].name << " a gagné le jeu!" << endl;

    // desallocation de chaque ligne de la grille
    for (int i = 0; i < n; i++){
        delete [] tab[i];
    }
    
    // desallocation de la grille
    delete [] tab;
}
