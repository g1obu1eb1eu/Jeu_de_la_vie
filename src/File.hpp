#ifndef FILE_HPP
#define FILE_HPP

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

#endif
