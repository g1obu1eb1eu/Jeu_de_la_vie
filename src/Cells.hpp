#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class File{
    private:
        std::string file;
        int row, column;
        std::vector<std::vector<bool>> grille;
    public:
        File(std::string file) : file(file) {}
        int FileInMatrix(){
            std::ifstream fichier(file);
            if(!fichier) {
                std::cerr << "Erreur : impossible d'ouvrir le fichier." << std::endl;
                return 1;
            }

            if (fichier >> row >> column) std::cout << "valeur extraite : " << row <<" & "<< column << "\n" << std::endl;
            else std::cerr << "Impossible de lire les valeurs" <<std::endl;

            for (int i = 0; i<row; i++){
                std::vector<bool> ligne;
                bool val;
                for (int j = 0; j<column; j++){
                    fichier >> val;
                    ligne.push_back(val);
                }
                grille.push_back(ligne);
            }
            fichier.close();
            return 0;
        }

        void PrintMatrix(std::vector<std::vector<bool>>& matrix){
            for (const auto& lign : matrix){
                for (const auto& elem : lign){
                    std::cout << elem << " ";
                }
                std::cout << std::endl;
            }
        }
        std::vector<std::vector<bool>> GetList(){
            FileInMatrix();
            PrintMatrix(grille);
            return grille;
        }
};

class Cells {
    private:
        File Myfile;
        std::vector<std::vector<bool>> MyList;
    public:
        Cells (File& file) : Myfile(file), MyList(Myfile.GetList()) {}

        void NextCell(){
            auto TempList = MyList;
            for (int i = 0; i < TempList.size(); i++){
                for (int j = 0; j < TempList[i].size(); j++){
                    bool val = TempList[i][j];
                    int SurrCells = CheckSurounding(i, j);

                    if(val && (SurrCells < 2 || SurrCells > 3)){
                        TempList[i][j] = false;
                    }

                    if((!val) && SurrCells == 3){
                        TempList[i][j] = true;
                    }
                }
            }

            MyList = TempList;
            std::cout<<std::endl;
            Myfile.PrintMatrix(MyList);
        }
        int CheckSurounding(int& lign, int& col){
            int compt = 0, myCol = 0, myLign = 0;
            for (int i = -1; i <= 1; i++){
                for (int j = -1; j<=1; j++){
                    if (i == 0 && j == 0) continue;
                    
                    myLign = lign + i;
                    myCol = col + j;

                    if ((myLign >= 0) && (myLign < MyList.size()) && (myCol >= 0) && (myCol < MyList[0].size())) {
                        compt+=MyList[myLign][myCol];
                    }
                }
            }
            return compt;
        }
};
