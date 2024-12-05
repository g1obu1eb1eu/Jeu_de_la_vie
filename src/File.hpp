#ifndef FILE_HPP
#define FILE_HPP

#include "Matrice.hpp"
#include <fstream>
#include <string>

class File : public Matrice {
private:
    std::string filename;

public:
    File(const std::string& file) : filename(file) {}
    ~File() = default;

    void createMatrix() override {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << ".\n";
            return;
        }

        int rows, cols;
        file >> rows >> cols;

        grid.assign(rows, std::vector<int>(cols, 0)); // Redimensionne la matrice

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!(file >> grid[i][j]) || (grid[i][j] != 0 && grid[i][j] != 1)) {
                    std::cerr << "Erreur : fichier corrompu ou valeurs invalides (attendu uniquement 0 ou 1).\n";
                    return;
                }
            }
        }
        file.close();
        std::cout << "Matrice chargée depuis le fichier avec succès.\n";
    }

    void printGrid() const override {
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    void setGrid(const std::vector<std::vector<int>>& newGrid) {
        grid = newGrid;
    }

    std::vector<std::vector<int>> GetList() {
        return grid;
    }
};

#endif 