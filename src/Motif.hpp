#ifndef MOTIF_HPP
#define MOTIF_HPP

#include <vector>
#include <string>

class Motif {
private:
    std::vector<std::vector<int>> pattern;

public:
    Motif(const std::vector<std::vector<int>>& pat) : pattern(pat) {}

    //Modifie la grille en ajoutant les différents motifs 
    void applyToGrid(std::vector<std::vector<int>>& grid, int startRow, int startCol) {
        for (int i = 0; i < pattern.size(); i++) {
            for (int j = 0; j < pattern[i].size(); j++) {
                int newRow = startRow + i;
                int newCol = startCol + j;

                if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size()) {
                    grid[newRow][newCol] = pattern[i][j];
                }
            }
        }
    }

    //Définis les motifs prédéfinis
    static std::vector<Motif> predefinedMotifs() {
        return {
            Motif({{1, 1}, {1, 1}}), // Bloc
            Motif({{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}), // Croix
            Motif({{0, 1, 0}, {0, 0, 1}, {1, 1, 1}})  // Planeur
        };
    }
};

#endif // MOTIF_HPP
