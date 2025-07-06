#pragma once

#include <vector>
#include <fstream>
#include <iomanip>

#include "Fractale.hpp"
#include "Eigen/Dense"


class Levy : public Fractale {
public:
    Eigen::Vector2d first, last; ///< Origine et direction initiale du segment
    double Angle;                      ///< Angle du triangle de départ (en radians)
    int iterations_;                   ///< Nombre d'itérations

    /**
     * @brief Constructeur
     * @param iterations Nombre d'itérations pour la génération de la fractale
     */
    Levy(int iterations) : iterations_(iterations) { }
    
    
    void generate() override {
        list_point.clear();
        list_point.reserve(std::pow(2.,iterations_)+1); // Réserve de la mémoire pour éviter les reallocations

        for (int i = 0; i < iterations_; i++) {
            int Npoint = list_point.size();
            std::vector<Eigen::Vector2d> new_points;
            new_points.reserve(Npoint * 2); // Réserve de la mémoire pour les nouveaux points

            if (i == 0) {
                // Premier segment
                list_point.push_back(first);
                list_point.push_back(last);
            } else {
                for (int j = 0; j < Npoint - 1; j++) {
                    Eigen::Vector2d point1 = list_point[j];
                    Eigen::Vector2d point2 = list_point[j + 1];
                    
                    // Calcul du point intermédiaire et de l'écart entre les deux points
                    Eigen::Vector2d midPoint = (point1 + point2) / 2.0;
                    double dx = point2[0] - point1[0];
                    double dy = point2[1] - point1[1];
                    
                    // Rotation du point intermédiaire
                    Eigen::Vector2d summit = midPoint + Eigen::Vector2d(-dy, dx) * std::tan(Angle / 2)/2;

                    new_points.push_back(point1);
                    new_points.push_back(summit);
                }
                new_points.push_back(list_point[Npoint - 1]);
                list_point = new_points; // Remplace les anciens points par les nouveaux
            }
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
    
    /**
     * @brief Affiche la dimension de Minkowski-Bouligand de la fractale de Levy.
     *
     * La dimension de cette fractale est connue pour être environ 2.0.
     */
    void dimensions() const override {
        // La dimension de Minkowski-Bouligand pour la courbe de Levy
        double nb_segments = list_point.size()-1, taille_segment = (list_point[1] - list_point[0]).norm();
        double dimension_iter = std::log(nb_segments) / std::log(1./taille_segment);
        
        double dimension_th = std::log(2.0) / std::log(2 * std::cos(Angle/2)); // Dimension théorique de la courbe de Levy
        
        std::cout << "Dimension de Minkowski-Bouligand pour la fractale de Levy : " << dimension_th << std::endl;
        std::cout << "Dimension calculée : " << dimension_iter << std::endl;
        std::cout << "Ratio : " << dimension_iter / dimension_th << std::endl;
    }

private:
    /// Liste des points générés pour la fractale de Levy
    std::vector<Eigen::Vector2d> list_point;
};