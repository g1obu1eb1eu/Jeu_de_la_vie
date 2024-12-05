/*---------------------Fenêtre SFML---------------------*/
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Cells.hpp"

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));

void initializeGrid() {
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = std::rand() % 2;  
        }
    }
}

void renderGrid(sf::RenderWindow &window) {
    int x, y;
    
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (x = 0; x < gridWidth; ++x) {
        for (y = 0; y < gridHeight; ++y) {
            if (grid[x][y] == 1) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    window.display();
}

int main() {
    /*---------------------Fichier---------------------*/
    // Nom du fichier
    std::string fileName = "../../src/grille.txt";

    // Ouvrir le fichier en mode lecture
    std::ifstream file(fileName);

    // Vérifier si le fichier est ouvert correctement
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << fileName << std::endl;
        return 1; // Retourne une erreur
    }

    std::string line;
    std::cout << "Contenu du fichier :" << std::endl;

    // Lire le fichier ligne par ligne
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    // Fermer le fichier
    file.close();

    /*---------------------Fenêtre SFML---------------------*/

    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");
    
    initializeGrid();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        renderGrid(window);

        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}
