#ifndef WINDOW_HPP
#define WINDOW_HPP

/*---------------------Fenêtre SFML---------------------*/
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Matrice.hpp"
#include "Cells.hpp"
#include "Motif.hpp"

class Window {
private:
    Matrice* matrice, *prevMatrice, *prevPrevMatrice;
    Cells* cells;
    int cellSize = 15, gridWidth, gridHeight, iterationCount=0;
    bool isToroidal, runCode=false; 

    sf::CircleShape toroidalIndicator; 
    sf::Font font; 
    sf::Text iterationText;     
    sf::RectangleShape iterationBackground;
    
    //Change l'indicateur torique
    void updateToroidalIndicator() {
        // Change la couleur du cercle en fonction du mode torique
        if (isToroidal) {
            toroidalIndicator.setFillColor(sf::Color::Red); // Mode torique activé
        } else {
            toroidalIndicator.setFillColor(sf::Color::Green); // Mode torique désactivé
        }
    }

    //Mets à jour l'affichage des itérations
    void updateIterationText() {
        iterationText.setString("Iterations: " + std::to_string(iterationCount));
        sf::FloatRect textBounds = iterationText.getLocalBounds();
        iterationBackground.setSize(sf::Vector2f(textBounds.width + 10, textBounds.height + 10));
        iterationBackground.setPosition(iterationText.getPosition().x - 5, iterationText.getPosition().y - 2);
    }

public:
    // Constructeur
    Window(Matrice* matrice) : matrice(matrice), isToroidal(false) {
        File* fileMatrix = dynamic_cast<File*>(matrice);
        if (fileMatrix) {
            cells = new Cells(*fileMatrix);
        } else {
            cells = nullptr;
        }

        auto grid = matrice->GetList();
        gridHeight = grid.size();
        gridWidth = grid[0].size();

        // Initialisation du cercle indicateur  
        toroidalIndicator.setRadius(10); // Rayon du cercle
        toroidalIndicator.setFillColor(sf::Color::Green); // Mode par défaut : désactivé (vert)
        toroidalIndicator.setPosition(2, 2); // Position : en haut à gauche

        if (!font.loadFromFile("../../src/arial.ttf")) {
            std::cerr << "Erreur : Impossible de charger la police arial.ttf.\n";
        }

        iterationText.setFont(font);
        iterationText.setCharacterSize(14);
        iterationText.setFillColor(sf::Color::Green); 
        iterationText.setPosition(gridWidth * cellSize - 100, 5); 
        iterationBackground.setFillColor(sf::Color::Black);
        updateIterationText();
    
    }

    //Lance ou non le mode toroide
    void toggleToroidalMode() {
        isToroidal = !isToroidal;
        updateToroidalIndicator();
        if (cells) {
            cells->setToroidalMode(isToroidal);
        }
    }

    // Méthode pour dessiner la grille
    void renderGrid(sf::RenderWindow& window) {
        auto grid = matrice->GetList(); 
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
        window.clear();

        // Dessin des cellules
        for (int i = 0; i < gridHeight; i++) {
            for (int j = 0; j < gridWidth; j++) {
                if (grid[i][j]) {
                    cell.setPosition(j * cellSize, i * cellSize);
                    cell.setFillColor(sf::Color::Green);
                    window.draw(cell);
                }
            }
        }

        // Dessiner l'indicateur de mode torique (cercle)
        window.draw(toroidalIndicator);

        //Dessiner indicateur d'itérations
        window.draw(iterationBackground);
        window.draw(iterationText);

        window.display();
    }

    // Méthode principale
    void run() {
        if (!matrice) {
            std::cerr << "Erreur : Matrice non initialisee.\n";
            return;
        }

        auto grid = matrice->GetList();
        gridHeight = grid.size();
        gridWidth = grid[0].size();

        sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Space) {
                        runCode = !runCode;
                    } 
                    else if (event.key.code == sf::Keyboard::T) {
                        toggleToroidalMode();
                    }
                    else if (event.key.code == sf::Keyboard::M) {
                        auto motifs = Motif::predefinedMotifs();

                        std::cout << "Liste des motifs disponibles :\n";
                        for (size_t i = 0; i < motifs.size(); ++i) {
                            std::cout << i + 1 << ". Motif " << i + 1 << "\n";
                        }

                        int motifChoice, startRow, startCol;
                        std::cout << "Choisissez un motif : ";
                        std::cin >> motifChoice;

                        std::cout << "Entrez les coordonnees de depart (ligne, colonne) : ";
                        std::cin >> startRow >> startCol;

                        if (motifChoice >= 1 && motifChoice <= motifs.size()) {
                            motifs[motifChoice - 1].applyToGrid(matrice->GetList(), startRow, startCol);
                            matrice->updateGrid(matrice->GetList());
                        }
                    }
                }
            
            }

            if (runCode) {

                if (iterationCount > 1)prevPrevMatrice = prevMatrice->clone();
                if (iterationCount > 0) prevMatrice = matrice->clone();

                cells->NextCell();
                iterationCount++;
                updateIterationText();

                bool end = false;

                if (iterationCount > 1){
                    if (Matrice::Compare(*prevMatrice, *matrice)){
                        end = true;
                    }
                }
                if (iterationCount > 2){
                    if (Matrice::Compare(*prevPrevMatrice, *matrice)){
                        end = true;
                    }
                }

                if(end){
                    // std::cout<<"Mat\n";
                    // matrice->printGrid();
                    // std::cout<<"\n" <<std::endl;
                    // std::cout<<"Mat1\n";
                    // prevMatrice->printGrid();
                    // std::cout<<"\n" <<std::endl;
                    // std::cout<<"Mat2\n";
                    // prevPrevMatrice->printGrid();
                    // std::cout<<"\n" <<std::endl;
                    std::cout << "Plus d'evolution possible. Arret de la simulation.\n";
                    sf::sleep(sf::milliseconds(10));
                    runCode = false; 
                }

                sf::sleep(sf::milliseconds(10));
            }
            renderGrid(window);
            sf::sleep(sf::milliseconds(200)); // Contrôle des frames    
        }
    }
    
};

#endif
