#ifndef CELLS_HPP
#define CELLS_HPP

#include <algorithm>
#include "File.hpp"
#include "Observer.hpp"

class Cells {
private:
    File& Myfile;
    std::vector<std::vector<int>> MyList;
    bool isToroidal; // Nouveau drapeau pour le mode torique
    std::vector<Observer*> observers;

public:
    Cells(File& file) : Myfile(file) {
        Myfile.createMatrix();
        MyList = Myfile.GetList();
    }

    void setToroidalMode(bool enable) {
        isToroidal = enable;
    }

    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }


    void notifyObservers() {
        for (auto obs : observers) {
            obs->update(MyList); 
        }
    }

    void NextCell() {
        auto TempList = MyList;
        for (int i = 0; i < TempList.size(); i++) {
            for (int j = 0; j < TempList[i].size(); j++) {
                int val = TempList[i][j];
                int SurrCells = CheckSurounding(i, j);

                if (val && (SurrCells < 2 || SurrCells > 3)) {
                    TempList[i][j] = 0;
                }

                if ((!val) && SurrCells == 3) {
                    TempList[i][j] = 1;
                }
            }
        }

        MyList = TempList;
        Myfile.setGrid(MyList);
        notifyObservers();
    }

    // en gros la, le drapeau est initialiser de base sur false et elle va se comporter normalment tant que le drapeau n'est pas activé
    int CheckSurounding(int lign, int col) {
        int compt = 0;
        int rows = MyList.size();
        int cols = MyList[0].size();
        //la on verifie si elle est torique ou non soir s'il y'a le drapeau ou non 
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                // cas 1 : NON TORIQUE donc elle fonctionne normalement 
                if (i == 0 && j == 0) continue;

                int newRow = lign + i;
                int newCol = col + j;

                //cas 2 : TORIQUE donc on applique avec les voisins en -1
                if (isToroidal) {
                    // Calcul des indices toriques
                    newRow = (newRow + rows) % rows;
                    newCol = (newCol + cols) % cols;
                }

                // Vérification standard hors mode torique
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                    compt += MyList[newRow][newCol];
                }
            }
        }
        return compt;
    }
};

#endif // CELLS_HPP
