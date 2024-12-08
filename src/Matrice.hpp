#ifndef MATRICE_HPP
#define MATRICE_HPP

#include <vector>
#include <iostream>

class Matrice {
protected:
    std::vector<std::vector<int>> grid; 

public:
    virtual ~Matrice() = default;

    // Méthodes virtuelles pures
    virtual bool createMatrix() = 0; 
    virtual void printGrid() const = 0;
    virtual Matrice* clone() const = 0;


    //Méthodes virtuelle
    virtual std::vector<std::vector<int>>& GetList(){return grid;};

    //Méthode concrète & statique
    void updateGrid(const std::vector<std::vector<int>>& newGrid) {this->grid = newGrid;}
    static bool Compare(const Matrice& mat1, const Matrice& mat2) {

        const auto& grid1 = mat1.grid;
        const auto& grid2 = mat2.grid;

        if (grid1.empty() || grid2.empty()) {
            std::cerr << "Erreur : une des grilles est vide.\n" << std::endl;
            return false;
        }

        if (grid1.size() != grid2.size()) {
            std::cerr << "Les tailles des grilles ne correspondent pas.\n" << std::endl;
            return false;
        }

        for (int i = 0; i < grid1.size(); i++) {
            for (int j = 0; j < grid1[i].size(); j++) {
                if (grid1[i][j] != grid2[i][j]) {
                    return false;
                }
            }
        }
        return true;
    } 
};

#endif