/*---------------------Fenêtre SFML---------------------*/
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Cells.hpp"
#include "Terminal.hpp"

class Window{
    private:
        File Myfile;
        int cellSize=10, gridWidth, gridHeight;
        std::vector<std::vector<int>> grid;
        
    public:
        // Window(const std::string& filename): Myfile(filename), grid(Myfile.GetList()){}

        void renderGrid(sf::RenderWindow &window) {
            int x, y;
            gridHeight = grid.size();
            gridWidth = grid[0].size();

            sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
            window.clear();
            for (x = 0; x < gridHeight; x++) {
                for (y = 0; y < gridWidth; y++) {
                    if (grid[x][y]) {
                        cell.setPosition(x * cellSize, y * cellSize);
                        // if (grid[y][x] == 1) {  
                        //     cell.setFillColor(sf::Color::Green);  
                        // } else {
                        //     cell.setFillColor(sf::Color::Black);  
                        // }
                        window.draw(cell);
                    }
                }
            }
            window.display();
        }

        void run() {
            std::string MyTxt = "../../src/grille.txt";
            bool runCode = false;

            gridHeight = grid.size();
            gridWidth = grid[0].size();

            File file(MyTxt);
            Cells myCells(file);

            sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) window.close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) runCode = true;
                    if (runCode) {
                        
                        myCells.NextCell();
                        
                    }
                    
                }

                renderGrid(window);
                sf::sleep(sf::milliseconds(100)); // Adjust or replace with clock for frame control
            }
        }

};


int main() {
    Terminal terminal; 
    terminal.runMenu(); 
 
    // std::string MyTxt = "../../src/grille.txt";

    // // /*---------------------Fenêtre SFML---------------------*/

    // // Window instance
    // Window gameWindow(MyTxt); 
    // gameWindow.run();

    return 0;
}
