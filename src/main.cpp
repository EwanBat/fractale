#include <iostream>
#include <memory>
#include <string>
#include <cstdlib> // pour system()


#include "../include/Fractale.hpp"
#include "../include/VonKoch.hpp"


// Fonction de sélection
std::unique_ptr<Fractale> choisirFractale() {
    std::cout << "=== Sélection de fractale ===\n";
    std::cout << "1. Von Koch\n";
    // std::cout << "2. Newton\n";
    std::cout << "Votre choix : ";

    int choix;
    std::cin >> choix;

    switch (choix) {
        case 1: {
            int iterations;
            std::cout << "Nombre d’itérations pour Von Koch : ";
            std::cin >> iterations;

            // Tu peux aussi demander d'autres paramètres ici si besoin
            // Ex : longueur initiale, orientation, etc.

            auto fractale = std::make_unique<VonKoch>(iterations);
            
            Eigen::Vector2d first(0.,0.), last(10.,0.);
            fractale->first = first; fractale->last = last;
            
            std::string filename = "../data/von_koch_data.txt";
            fractale->filename = filename;
            // Tu peux appeler des méthodes de configuration si définies
            // fractale->setLongueurInitiale(1.0);
            // fractale->setOrigine(Eigen::Vector2d(0, 0));

            return fractale;
        }

        /*
        case 2: {
            int profondeur;
            std::cout << "Profondeur pour Newton : ";
            std::cin >> profondeur;
            auto fractale = std::make_unique<Newton>(profondeur);
            // fractale->setFonction(...); etc.
            return fractale;
        }
        */

        default:
            std::cerr << "Choix invalide.\n";
            return nullptr;
    }
}

int main() {
    auto fractale = choisirFractale();
    if (!fractale) {
        std::cerr << "Aucune fractale générée.\n";
        return 1;
    }

    fractale->generate();

    fractale->exportData();
    std::cout << "Fractale exportée avec succès.\n";

    // Appel du script Python
    std::string cmd = "python3 ../display.py koch " + fractale->filename;
    int result = std::system(cmd.c_str());
    if (result != 0) {
        std::cerr << "Erreur lors de l'affichage Python.\n";
    }

    return 0;
}