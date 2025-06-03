#include <iostream>
#include <memory>
#include <string>
#include <cstdlib> // pour system()


#include "../include/Fractale.hpp"
#include "../include/VonKoch.hpp"
#include "../include/Dragon.hpp"


// Fonction de sélection
std::unique_ptr<Fractale> choisirFractale() {
    std::cout << "=== Sélection de fractale ===\n";
    std::cout << "1. Von Koch\n";
    std::cout << "2. Dragon de Heighway\n";
    std::cout << "Votre choix : ";

    int choix;
    std::cin >> choix;

    switch (choix) {
        case 1: {
            int iterations;
            std::cout << "Nombre d’itérations pour Von Koch : ";
            std::cin >> iterations;

            auto fractale = std::make_unique<VonKoch>(iterations);
            
            Eigen::Vector2d first(0.,0.), last(10.,0.);
            fractale->first = first; fractale->last = last;
            
            std::string filename = "../data/von_koch_data.txt", nom = "koch";
            fractale->filename = filename; fractale->nom = nom;

            return fractale;
        }

        
        case 2: {
            int iterations;
            std::cout << "Nombre d’itérations pour le dragon de Heighway : ";
            std::cin >> iterations;

            auto fractale = std::make_unique<Dragon>(iterations);

            Eigen::Vector2d origin(0,0), direction(1,0); double Angle(M_PI/2);
            fractale->origin = origin; fractale->direction = direction; fractale->Angle = Angle;

            std::string filename = "../data/dragon_data.txt", nom = "dragon";
            fractale->filename = filename; fractale->nom = nom;

            return fractale;
        }
        

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
    std::string cmd = "python3 ../display.py " + fractale->nom + " " + fractale->filename;
    int result = std::system(cmd.c_str());
    if (result != 0) {
        std::cerr << "Erreur lors de l'affichage Python.\n";
    }

    return 0;
}