#pragma once

#include <vector>
#include <fstream>
#include <iomanip>

#include "Fractale.hpp"
#include "Eigen/Dense"

/**
 * @brief Classe représentant la fractale du Dragon de Heighway.
 *
 * Principe : Le Dragon de Heighway est une fractale générée par un procédé itératif de repliement
 * d'un segment selon un angle donné. À chaque itération, la courbe se complexifie en ajoutant de nouveaux
 * points calculés par rotation autour du dernier point généré.
 *
 * Fonctions principales :
 *  - generate() : génère les points de la fractale du Dragon selon le nombre d'itérations choisi.
 *  - exportData() : exporte les points générés dans un fichier texte.
 */
class Dragon : public Fractale {
public:
    Eigen::Vector2d origin, direction; ///< Origine et direction initiale du segment
    double Angle;                      ///< Angle de rotation à chaque itération (en radians)
    int iterations_;                   ///< Nombre d'itérations

    /**
     * @brief Constructeur
     * @param iterations Nombre d'itérations pour la génération de la fractale
     */
    Dragon(int iterations) : iterations_(iterations) { }
    
    /**
     * @brief Génère les points de la fractale du Dragon.
     *
     * Le segment initial est défini par origin et direction. À chaque itération,
     * de nouveaux points sont ajoutés par rotation autour du dernier point généré.
     */
    void generate() override {
        list_point.clear();

        Eigen::Rotation2D<double> rotation(Angle);
        Eigen::Matrix2d rotationMatrix = rotation.toRotationMatrix();

        list_point.push_back(origin);
        list_point.push_back(origin + direction);

        for (int i = 0; i < iterations_; i++) {
            int Npoint = list_point.size();
            std::vector<Eigen::Vector2d> new_points;
            new_points.reserve(Npoint - 1);

            Eigen::Vector2d fixe = list_point[Npoint - 1];
            for (int j = Npoint - 2; j >= 0; j--) {
                Eigen::Vector2d point = list_point[j];
                point = point - fixe + origin;
                point = rotationMatrix * point;
                point = point - origin + fixe;
                new_points.push_back(point);
            }

            list_point.insert(list_point.end(), new_points.begin(), new_points.end());
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

        // En-tête
        file << "# x1,y1\n";
        file << std::fixed << std::setprecision(6); // Précision de sortie

        for (int i = 0; i < list_point.size(); i++) {
            Eigen::Vector2d point = list_point[i];
            file << point[0] << "," << point[1] << "\n";
        }

        file.close();
        std::cout << "Données exportées vers : " << filename << std::endl;
    }
    
    
    void dimensions() const override {
        std::cout << "De la manière dont elle est générée, la dimension de Minkowski-Bouligand du Dragon de Heighway n'est pas définie" << std::endl;
    }
    
private:
    /// Liste des points générés pour la fractale du Dragon
    std::vector<Eigen::Vector2d> list_point;
};