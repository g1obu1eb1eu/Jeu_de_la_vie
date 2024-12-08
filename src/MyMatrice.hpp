#ifndef MYMATRICE_HPP
#define MYMATRICE_HPP

#include "Matrice.hpp"
#include <limits>

class MyMatrice : public Matrice {
private:
    int rows;
    int cols;

public:
    MyMatrice() : rows(0), cols(0) {}
    ~MyMatrice() = default;

    bool createMatrix() override {
        std::cout << "Entrez le nombre de lignes : ";
        std::cin >> rows;
        std::cout << "Entrez le nombre de colonnes : ";
        std::cin >> cols;

        grid.assign(rows, std::vector<int>(cols, 0)); // Redimensionne la matrice

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                while (true) {
                    std::cout << "Entrez la valeur pour la cellule [" << i << "][" << j << "] (0 ou 1) : ";
                    std::cin >> grid[i][j];
                    if (grid[i][j] == 0 || grid[i][j] == 1) {
                        break;
                    }
                    std::cout << "Valeur invalide, veuillez entrer 0 ou 1.\n";
                }
            }
        }
        std::cout << "Matrice creee avec succes.\n";
        return true;
    }

    void printGrid() const override {
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    Matrice* clone() const override {
        MyMatrice* copy = new MyMatrice();
        copy->grid = this->grid; 
        return copy;
    }

};

#endif // MYMATRICE_HPP
