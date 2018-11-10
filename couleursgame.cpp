#include <conio.h>   // Pour getch()
#include <iomanip>   // Pour setprecision()
#include <iostream>  // Pour cout
#include <string>    // Pour cout
#include <time.h>    // Pour clock_t
#include <windows.h> // Pour couleurs

using namespace std; // std::cout, std::cin

const static string ENTETE = "\033c=== couleurgames.cpp ===\n";

const static int NBPARTIES = 15;
const static int CODECOULEURS[6] = {9, 10, 11, 12, 13, 14};
const static string NOMSCOULEURS[6] = {"bleu", "vert", "cyan", "rouge", "violet", "jaune"};

const static int NBMEDAILLES = 4;
const static int LIMITE[NBMEDAILLES] = {25, 20, 15, 12};
const static string MEDAILLES[NBMEDAILLES] = {"bronze", "argent", "or", "platine"};
const static string ENCOURAGEMENTS[NBMEDAILLES]
    = {"Ceci est un bon temps.\n", "Ceci est un tres bon temps!\n", "Bravo, c'est un super temps!\n", "Magnifique!\n"};

int main() {

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    srand(time(0));

    cout
        << fixed << showpoint << setprecision(2) << ENTETE
        << "Vous repondre par v(rai) ou f(aux) en fonction de la couleur du mot est de la meme couleur que le mot ecrit.\n"
        << "Vous allez devoir repondre correctement " << NBPARTIES << " fois le plus rapidement possible\n"
        << "[ENTER] pour commencer...\n";

    cout << sizeof(LIMITE);
    cin.get(); // Attendre une entrée

    clock_t begin_time = clock();
    bool failed = false;

    // Début jeu
    for (int i = 0; i < NBPARTIES; i++) {

        // Génération des incides
        int randindmot = rand() % 6; // generer un indice mot
        int randincol;               // generer un indice couleur
        for (int i = 0; i < 4; i++) {
            randincol = rand() % 6;
            if (randincol == randindmot) {
                break;
            }
        }

        // Afficher le mot en couleur
        cout << ENTETE;
        cout << "[" << i + 1 << "/" << NBPARTIES << "] -> ";
        SetConsoleTextAttribute(hConsole, CODECOULEURS[randindmot]);
        cout << NOMSCOULEURS[randincol];
        SetConsoleTextAttribute(hConsole, 7);
        cout << "?\n";

        // Verification réponse
        char charLu;
        cin >> charLu;
        if ((randindmot == randincol) == (charLu == 'v')) {
            // si vrai
        } else {
            // si piège
            failed = true;
            break;
        }
    }
    // Fin jeu

    // Calcul de la difference de temps
    // https://stackoverflow.com/questions/728068/how-to-calculate-a-time-difference-in-c
    double seconds = float(clock() - begin_time) / CLOCKS_PER_SEC;

    // Affichage du message de fin
    if (!failed) {
        cout << "Fini en " << seconds << " secondes\n";
        for (int i = NBMEDAILLES-1; i > 0; i--) {
            if (seconds < LIMITE[i]) {
                cout << ENCOURAGEMENTS[i];
                cout << "Vous avez recu une medaille en " << MEDAILLES[i] << "\n";
                break;
            }
        }

    } else {
        cout << " Vous avez perdu... \n";
    }

    cout << "====== fin du jeu ======\n";
}
