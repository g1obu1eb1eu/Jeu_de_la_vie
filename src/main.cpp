/*---------------------Fenêtre SFML---------------------*/
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Cells.hpp"

class Window{
    private:
        File Myfile;
        float cellSize=0.5, gridWidth, gridHeight;
        std::vector<std::vector<bool>> grid;
        
    public:
        Window(const std::string& filename): Myfile(filename), grid(Myfile.GetList()) {}

        void renderGrid(sf::RenderWindow &window) {
            int x, y;
            gridHeight = grid.size();
            gridWidth = grid[0].size();

            window.clear();

            sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
            for (x = 0; x < gridHeight; x++) {
                for (y = 0; y < gridWidth; y++) {
                    if (grid[x][y]) {
                        cell.setPosition(x * cellSize, y * cellSize);
                        window.draw(cell);
                    }
                }
            }
            window.display();
        }

        void run() {
            gridHeight = grid.size();
            gridWidth = grid[0].size();

            sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                renderGrid(window);
                sf::sleep(sf::milliseconds(100)); // Adjust or replace with clock for frame control
            }
        }

};


int main() {
    std::string MyTxt = "../../src/grille.txt";
    File file(MyTxt);
    Cells myCells(file);
    for (int i =0; i < 3; i++) myCells.NextCell();;

    // /*---------------------Fenêtre SFML---------------------*/

    // Window instance
    Window gameWindow(MyTxt); 
    gameWindow.run();

    return 0;
}
