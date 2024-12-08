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

    bool createMatrix() override {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << ".\n";
            return false;
        }

        int rows, cols;
        file >> rows >> cols;

        grid.assign(rows, std::vector<int>(cols, 0)); // Redimensionne la matrice

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!(file >> grid[i][j]) || (grid[i][j] != 0 && grid[i][j] != 1)) {
                    std::cerr << "Erreur : fichier corrompu ou valeurs invalides (attendu uniquement 0 ou 1).\n";
                    return false;
                }
            }
        }
        file.close();
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

    void setGrid(const std::vector<std::vector<int>>& newGrid) {
        grid = newGrid;
    }

    Matrice* clone() const override {
        File* copy = new File(filename);
        copy->setGrid(grid);
        return copy;
    }

    void rewriteFile(const std::vector<std::vector<int>>& myGrid, std::string& filename){
        //Ouveture en mode écriture -> écrase les données
        std::ofstream file(filename, std::ios::out | std::ios::trunc);
        if (!file) {
            std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << ".\n";
            return;
        }

        int rows = myGrid.size();
        int cols = myGrid[0].size();
        file << rows << " " << cols << "\n";

        for (const auto& row : myGrid) {
            for (const auto& cell : row) {
                file << cell << " ";
            }
            file << "\n";
        }

        file.close();
    }


};

#endif 