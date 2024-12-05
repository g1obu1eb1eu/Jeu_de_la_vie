#ifndef CELLS_HPP
#define CELLS_HPP

#include "File.hpp"

class Cells {
private:
    File Myfile;
    std::vector<std::vector<int>> MyList;

public:
    Cells(File& file) : Myfile(file) {
        Myfile.createMatrix();
        MyList = Myfile.GetList();
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
        Myfile.printGrid();
    }

    int CheckSurounding(int lign, int col) {
        int compt = 0, myCol = 0, myLign = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;

                myLign = lign + i;
                myCol = col + j;

                if ((myLign >= 0) && (myLign < MyList.size()) && (myCol >= 0) && (myCol < MyList[0].size())) {
                    compt += MyList[myLign][myCol];
                }
            }
        }
        return compt;
    }
};

#endif // CELLS_HPP
