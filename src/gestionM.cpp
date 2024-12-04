#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>


class File {
private:
    std::string file = "mon_fichier.txt"; // Nom du fichier
    int row, column; // Dimensions de la matrice
    std::vector<std::vector<bool>> grille; // Matrice

public:
    // Méthode pour lire une matrice depuis un fichier
    int FileInMatrix() {
        std::ifstream fichier(file);
        if (!fichier) {
            std::cerr << "Erreur : impossible d'ouvrir le fichier '" << file << "'." << std::endl;
            return 1;
        }

        if (!(fichier >> row >> column)) { // Vérifie que les dimensions sont valides
            std::cerr << "Erreur : impossible de lire les dimensions du fichier." << std::endl;
            return 1;
        }

        std::cout << "Dimensions extraites : " << row << " lignes, " << column << " colonnes." << std::endl;

        grille.clear(); // Réinitialise la grille
        grille.resize(row, std::vector<bool>(column)); // Redimensionne la matrice

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                bool val;
                if (!(fichier >> val)) { // Vérifie que chaque valeur est lisible
                    std::cerr << "Erreur : fichier corrompu ou fin inattendue." << std::endl;
                    return 1;
                }
                if (val != 0 && val != 1) { // Vérifie que chaque valeur est 0 ou 1
                    std::cerr << "Erreur : valeur invalide (" << val << ") détectée dans le fichier." << std::endl;
                    return 1;
                }
                grille[i][j] = val;
            }
        }

        fichier.close();
        return 0;
    }

    // Méthode pour afficher la matrice
    void PrintMatrix() {
        for (const auto& ligne : grille) {
            for (const auto& elem : ligne) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

    // Méthode pour créer une matrice dynamique depuis l'entrée utilisateur
 void CreateMatrix() {
    std::cout << "Entrez le nombre de lignes : ";
    while (!(std::cin >> row) || row <= 0) { // Vérifie que la saisie est un entier positif
        std::cin.clear(); // Réinitialise le flux en cas d'erreur
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Vide le buffer
        std::cout << "Erreur : veuillez entrer un nombre positif pour les lignes : ";
    }

    std::cout << "Entrez le nombre de colonnes : ";
    while (!(std::cin >> column) || column <= 0) { // Vérifie que la saisie est un entier positif
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Erreur : veuillez entrer un nombre positif pour les colonnes : ";
    }

    grille.clear(); // Réinitialise la grille
    grille.resize(row, std::vector<bool>(column, false)); // Redimensionne la matrice

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            bool val;
            while (true) { // Boucle pour valider l'entrée utilisateur
                std::cout << "Entrez la valeur pour la cellule [" << i << "][" << j << "] (0 ou 1) : ";
                std::cin >> val;

                if (std::cin.fail() || (val != 0 && val != 1)) { // Vérifie la validité de la saisie
                    std::cin.clear(); // Réinitialise le flux en cas d'erreur
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Vide le buffer
                    std::cout << "Erreur : veuillez entrer uniquement 0 ou 1.\n";
                } else {
                    grille[i][j] = val; // Affecte la valeur valide
                    break;
                }
            }
        }
    }
    std::cout << "Matrice créée avec succès.\n";
}

    // Getter pour la grille
    std::vector<std::vector<bool>> GetMatrix() {
        return grille;
    }
};

// Programme principal
int main() {
    File file1;
    int choice;

    // Menu interactif
    do {
        std::cout << "\nMenu :\n";
        std::cout << "1. Lire une matrice depuis un fichier\n";
        std::cout << "2. Créer une matrice dynamiquement\n";
        std::cout << "3. Afficher la matrice\n";
        std::cout << "4. Quitter\n";
        std::cout << "Votre choix : ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erreur : veuillez entrer un nombre valide.\n";
            continue;
        }

        switch (choice) {
            case 1:
                if (file1.FileInMatrix() == 0) {
                    std::cout << "Matrice chargée depuis le fichier avec succès.\n";
                }
                break;
            case 2:
                file1.CreateMatrix();
                std::cout << "Matrice créée dynamiquement avec succès.\n";
                break;
            case 3:
                std::cout << "Affichage de la matrice :\n";
                file1.PrintMatrix();
                break;
            case 4:
                std::cout << "Au revoir !\n";
                break;
            default:
                std::cout << "Choix invalide. Veuillez entrer un nombre entre 1 et 4.\n";
        }
    } while (choice != 4);

    return 0;
}
