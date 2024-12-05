#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "MyMatrice.hpp"
#include "File.hpp"

class Terminal {
private:
    int choice;
    Matrice* matrice; 

    void displayMenu() {
        std::cout << "\nMenu :\n";
        std::cout << "1. Creer une matrice dynamiquement\n";
        std::cout << "2. Charger une matrice depuis un fichier\n";
        std::cout << "3. Afficher la matrice\n";
        std::cout << "4. Quitter\n";
        std::cout << "Votre choix : ";
    }

    bool getUserChoice() {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erreur : veuillez entrer un nombre valide.\n";
            return false;
        }
        return true;
    }

    void processChoice() { // choix de neuille
        switch (choice) {
            case 1:
                matrice = new MyMatrice();
                matrice->createMatrix();
                break;
            case 2: {
                std::string filename;
                std::cout << "Entrez le nom du fichier (ex: mon_fichier.txt) : ";
                std::cin >> filename;
                matrice = new File(filename);
                matrice->createMatrix();
                break;
            }
            case 3:
                if (matrice) {
                    matrice->printGrid();
                } else {
                    std::cout << "Aucune matrice disponible. Veuillez en creer une ou en charger une depuis un fichier.\n";
                }
                break;
            case 4:
                std::cout << "Au revoir !\n";
                break;
            default:
                std::cout << "Choix invalide.\n";
        }
    }

public:
    Terminal() : choice(0), matrice(nullptr) {}
    ~Terminal() {
        delete matrice; // Nettoyage mémoire
    }

    void runMenu() {
        do {
            displayMenu();
            if (!getUserChoice()) {
                continue;
            }
            processChoice();
        } while (choice != 4);
    }
};

#endif // TERMINAL_HPP
