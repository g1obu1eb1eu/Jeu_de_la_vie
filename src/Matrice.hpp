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
    virtual void createMatrix() = 0; 
    virtual void printGrid() const = 0; 
};

#endif 