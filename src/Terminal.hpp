    #ifndef TERMINAL_HPP
    #define TERMINAL_HPP

    #include "MyMatrice.hpp"
    #include "Cells.hpp"
    #include "Window.hpp"
    #include "Motif.hpp"
    #include "Observer.hpp"

    class TerminalObserver : public Observer {
    public:
        void update(const std::vector<std::vector<int>>& grid) override {
            std::cout << "\nNouvel etat de la matrice :\n";
            for (const auto& row : grid) {
                for (int cell : row) {
                    std::cout << (cell ? "0" : " ") << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "-------------------------\n";
        }
    };

    class Terminal {
    private:
        int choice;
        std::string filename;
        Matrice* matrice,* initialMatrice, *prevMatrice, *prevPrevMatrice; 
        bool isToroidal, fin=false;
        static TerminalObserver terminalObserver;

        void displayMenu() {
            std::cout << "\nMenu :\n";
            std::cout << "1. Creer une matrice dynamiquement\n";
            std::cout << "2. Charger une matrice depuis un fichier\n";
            std::cout << "3. Afficher la matrice\n";
            std::cout << "4. Placer un motif sur la matrice\n";
            std::cout << "5. Passer la matrice a l'etape suivante\n";
            std::cout << "6. Enregistrer changements effectues\n";
            std::cout << "7. Passer en mode graphique\n";
            std::cout << "8. Activer/Desactiver le mode torique\n";
            std::cout << "9. Quitter\n";
            std::cout << "Votre choix : ";
        }

        bool getUserChoice() {
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Erreur : veuillez entrer un nombre valide.\n";
                return false;
            }
            return true;
        }
        //Méthode pour activer/désactiver le mode torique 
        void toggleToroidalMode() {
            isToroidal = !isToroidal;
            std::cout << "Mode torique " << (isToroidal ? "active" : "desactive") << ".\n";
        }

        void endGame(){
            std::string rep;
            do{
                std::cout <<"Voulez-vous arreter competement la simulation (y/n) ? ";
                std::cin >> rep;
                if (rep == "y"){
                    choice=8;
                }
                else if (rep == "n"){
                    fin = !fin;
                    std::cout << "Simulation reprise. Il faut cependant que vous vous recreez une nouvelle matrice !\n" << std::endl;
                }
                else{
                    std::cout<<"Repondez uniquement par 'y' ou 'n'\n"<<std::endl;
                }

            }while (rep !="y" && rep !="n");                            
        }

        void processChoice() { 
            switch (choice) {
                case 1:
                    matrice = new MyMatrice();
                    // initialMatrice = newMyMatrice ();
                    matrice->createMatrix();
                    // initialMatrice = matrice->clone();
                    break;

                case 2: 
                    std::cout << "Entrez le nom du fichier (ex: mon_fichier.txt) : ";
                    std::cin >> filename;
                    matrice = new File(filename);
                    initialMatrice = new File(filename);
                    if(matrice->createMatrix())std::cout << "Matrice chargee depuis le fichier avec succes.\n";
                    initialMatrice = matrice->clone();                    
                    break;
                
                case 3:
                    if (matrice) {
                        matrice->printGrid();
                    } else {
                        std::cerr << "Aucune matrice disponible. Veuillez en creer une ou en charger une depuis un fichier.\n";
                    }
                    break;
                case 4:
                    if (matrice) {
                        auto grid = matrice->GetList();
                        auto motifs = Motif::predefinedMotifs();

                        std::cout << "Liste des motifs disponibles :\n";
                        for (size_t i = 0; i < motifs.size(); ++i) {
                            std::cout << i + 1 << ". Motif " << i + 1 << "\n"; 
                        }

                        int motifChoice;
                        std::cout << "Choisissez un motif : ";
                        std::cin >> motifChoice;

                        if (motifChoice < 1 || motifChoice > motifs.size()) {
                            std::cerr << "Choix invalide.\n";
                            break;
                        }

                        int startRow, startCol;
                        std::cout << "Entrez les coordonnees de depart (ligne, colonne) : ";
                        std::cin >> startRow >> startCol;

                        motifs[motifChoice - 1].applyToGrid(grid, startRow, startCol);
                        matrice->updateGrid(grid);

                        std::cout << "Motif place avec succes.\n";
                    } else {
                        std::cerr << "Aucune matrice disponible. Veuillez en creer une ou en charger une depuis un fichier.\n";
                    }
                    break;

                case 5:
                    if (matrice) {
                        int itération = 0;
                        std::cout<<"Combien d'iterations souhaitez-vous faire ? ";
                        std::cin >> itération;

                        if (std::cin.fail() || itération <= 0) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cerr << "Erreur : veuillez entrer un nombre entier positif.\n";
                            return;
                        }

                        File* fileMatrix = dynamic_cast<File*>(matrice);
                        if (fileMatrix) {
                            static Cells cells(*fileMatrix);
                            cells.addObserver(&terminalObserver);
                            for (size_t i = 1; i <= itération; i++){
                                if (i > 2) prevPrevMatrice = prevMatrice->clone();
                                prevMatrice = matrice->clone();

                                if (!prevMatrice) {
                                    std::cerr << "Erreur lors de la copie de la matrice.\n";
                                    break;
                                }

                                cells.NextCell();

                                bool end = false;

                                if (Matrice::Compare(*prevMatrice, *matrice)){
                                    end = true;
                                }
                                if (i > 2){
                                     if (Matrice::Compare(*prevPrevMatrice, *matrice)){
                                        end = true;
                                    }
                                }

                                if(end){
                                    std::cout << "Plus de changements possibles. Fin de la simulation.\n"<<std::endl;
                                    fin = true;
                                    break;
                                }

                                // std::cout << "\nIteration numero " << std::to_string(i) << ".\n" << std::endl;
                                // matrice->printGrid();
                            }
                        } else {
                            std::cerr <<"NextCell() ne peut être appliquee qu'à une matrice chargee depuis un fichier.\n";
                        }
                    } else {
                        std::cerr << "Aucune matrice disponible. Veuillez en creer une ou en charger une depuis un fichier.\n";
                    }
                    break;

                case 6:
                    if (filename.empty()) {
                        std::cout << "Entrez le nom du fichier (ex: mon_fichier.txt) : ";
                        std::cin >> filename;
                        initialMatrice = new File(filename);
                        initialMatrice->createMatrix();
                    }

                    if (matrice) {
                        if (!Matrice::Compare(*initialMatrice, *matrice)) {
                            File tempFile(filename); 
                            tempFile.rewriteFile(matrice->GetList(), filename);
                            std::cerr << "Fichier mis a jour avec succes.\n";
                        } 
                        else {
                            std::cerr << "Aucune difference.\n";
                        }
                    } 
                    else {
                        std::cerr << "Aucune matrice disponible.\n";
                    }

                    break;

                case 7:
                    if (filename.empty()) {
                        std::cout << "Entrez le nom du fichier (ex: mon_fichier.txt) : ";
                        std::cin >> filename;
                        initialMatrice = new File(filename);
                        initialMatrice->createMatrix();
                    }
                    
                    if (matrice) {
                        if (!Matrice::Compare(*initialMatrice, *matrice)){
                            
                            std::string rep;
                            do{
                                std::cout << "Voulez vous enregistrer les modifications apportees a votre matrice (y/n) ? ";
                                std::cin >> rep;
                                if (rep == "y"){
                                    File tempFile(filename); 
                                    tempFile.rewriteFile(matrice->GetList(), filename);
                                    std::cerr << "Fichier mis a jour avec succes.\n";
                                }
                                else if (rep == "n"){
                                    std::cout <<"Les modifications n'ont pas ete enregistrees. Utilisation des donnees du fichier de sauvegarde.\n"<<std::endl;
                                }
                                else{
                                    std::cout<<"Repondez uniquement par 'y' ou 'n'\n"<<std::endl;
                                }
                            }while (rep !="y" && rep !="n");
                        }
                        matrice = new File(filename);
                        matrice->createMatrix();
                        File* fileMatrix = dynamic_cast<File*>(matrice);
                        if (fileMatrix) {
                            Window window(fileMatrix);
                            window.run();
                        }
                    }                     
                    break;
                    
                case 8:
                    toggleToroidalMode();
                break;

                case 9:
                    std::cout << "Au revoir !\n";
                    break;

                default:
                    std::cerr << "Choix invalide.\n";
            }
        }

    public:
        Terminal() : choice(0), matrice(nullptr) {}
        ~Terminal() {
            delete matrice; 
            delete initialMatrice;
        }

        void runMenu() {
            do{
            std::cout << "Voulez vous :\n - 1.Passer en mode terminal.\n - 2.Passer en mode graphique.\n";
            std::cin >> choice;
            } while(choice !=1 && choice !=2 );

            if (choice == 1){
                do {
                    if(fin){
                        endGame();
                        continue;
                    };
                    displayMenu();
                    if (!getUserChoice()) {
                        continue;
                    }
                    processChoice();
                } while (choice != 9);
            }
            else{
                choice = 2;
                processChoice();
                choice = 7;
                processChoice();
            }
        }
    };

    TerminalObserver Terminal::terminalObserver;

    #endif 
