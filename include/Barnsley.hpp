#pragma once

#include <fstream>
#include <iomanip>
#include <random>
#include <vector>

#include "Fractale.hpp"
#include "Eigen/Dense"

/**
 * @brief Classe représentant la fougère de Barnsley (attracteur de Barnsley).
 *
 * Principe : L'attracteur de Barnsley est une fractale obtenue en appliquant de façon répétée,
 * à un point du plan, une transformation affine choisie aléatoirement parmi un ensemble de 4,
 * chacune étant associée à une probabilité. À chaque itération, le point est transformé et ajouté
 * à la liste des points, ce qui fait émerger la célèbre forme de fougère.
 *
 * Fonctions principales :
 *  - generate() : génère les points de la fractale en appliquant les transformations affines aléatoires.
 *  - exportData() : exporte les points générés dans un fichier texte.
 */
class Barnsley : public Fractale {
public:
    int iterations_; // Nombre de points à générer

    /**
     * @brief Constructeur
     * @param iterations Nombre de points à générer
     */
    Barnsley(int iterations) : iterations_(iterations) { }
    
    /**
     * @brief Génère les points de la fractale de Barnsley.
     *
     * Le point de départ est (0,0). À chaque itération, une transformation affine
     * (matrice + translation) est tirée aléatoirement selon les probabilités définies,
     * puis appliquée au dernier point généré.
     */
    void generate() override {
        double x0 = 0.0, y0 = 0.0; // Point de départ
        list_point.clear();
        list_point.reserve(iterations_);
        list_point.push_back(Eigen::Vector2d(x0, y0));

        Eigen::Matrix2d A;
        Eigen::Vector2d point;

        for (int i = 0; i < iterations_; i++) {
            auto [A, b] = randomBarnsleyTransform();
            point = A * list_point.back() + b;
            list_point.push_back(point);
        }
    }
    
    /**
     * @brief Exporte les points générés dans un fichier texte.
     *
     * Le fichier contient les coordonnées x et y de chaque point généré.
     */
    void exportData() const override {
        std::ofstream file(filename);

        if (!file) {
            std::cerr << "Erreur : impossible d’ouvrir le fichier " << filename << std::endl;
            return;
        }
        double x,y;
        // En-tête
        file << "# x,y\n";
        file << std::fixed << std::setprecision(6); // Précision de sortie
        for (int i = 0; i < iterations_; ++i) {
            x = list_point[i].x();
            y = list_point[i].y();
            file << x << "," << y << "\n";
        }

        file.close();

        std::cout << "Données exportées vers " << filename << std::endl;
    }
    
private:
    // Liste des points générés
    std::vector<Eigen::Vector2d> list_point;

    // Vecteurs de translation associés à chaque transformation affine
    std::vector<Eigen::Vector2d> translations = {
        Eigen::Vector2d(0.0, 0.0),
        Eigen::Vector2d(0.0, 1.6),
        Eigen::Vector2d(0.0, 1.6),
        Eigen::Vector2d(0.0, 0.44)
    };

    // Matrices 2x2 des transformations affines de la fougère de Barnsley
    std::vector<Eigen::Matrix2d> matrices = {
        (Eigen::Matrix2d() << 0.0, 0.0, 0.0, 0.16).finished(),
        (Eigen::Matrix2d() << 0.85, 0.04, -0.04, 0.85).finished(),
        (Eigen::Matrix2d() << 0.2, -0.26, 0.23, 0.22).finished(),
        (Eigen::Matrix2d() << -0.15, 0.28, 0.26, 0.24).finished()
    };

    // Probabilités associées à chaque transformation
    std::vector<double> probabilities = {0.01, 0.85, 0.07, 0.07};

    /**
     * @brief Tire aléatoirement une transformation affine selon les probabilités.
     * @return Un couple (matrice, translation) à appliquer au point courant.
     */
    std::pair<Eigen::Matrix2d, Eigen::Vector2d> randomBarnsleyTransform() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::discrete_distribution<> distrib(probabilities.begin(), probabilities.end());
        int idx = distrib(gen);
        return {matrices[idx], translations[idx]};
    }

};