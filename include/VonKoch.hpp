#pragma once

#include <vector>
#include <cmath>  // pour std::atan2
#include <fstream>
#include <iomanip>

#include "Fractale.hpp"
#include "Eigen/Dense"

/**
 * @brief Classe représentant la courbe de Von Koch (flocon de Koch).
 *
 * Principe : La courbe de Von Koch est une fractale construite par itérations successives.
 * À chaque étape, chaque segment est remplacé par quatre segments formant une "pointe" en triangle équilatéral,
 * ce qui complexifie la courbe à chaque itération et fait émerger la structure fractale.
 *
 * Fonctions principales :
 *  - generate() : génère les points de la courbe de Von Koch selon le nombre d'itérations choisi.
 *  - exportData() : exporte les points générés dans un fichier texte.
 */
class VonKoch : public Fractale {
public:
    Eigen::Vector2d first, last; ///< Extrémités du segment initial
    int iterations_;             ///< Nombre d'itérations

    /**
     * @brief Constructeur
     * @param iterations Nombre d'itérations pour la génération de la fractale
     */
    VonKoch(int iterations) : iterations_(iterations) { }
    
    /**
     * @brief Génère les points de la courbe de Von Koch.
     *
     * Le segment initial est défini par first et last. À chaque itération,
     * chaque segment est transformé en quatre segments selon la règle de Von Koch.
     */
    void generate() override {
        list_point.clear();

        // Initialiser avec un segment de base, par exemple de (0,0) à (1,0)
        list_point.push_back(first); list_point.push_back(last);
        
        // Pour chaque itération, appliquer la transformation sur tous les segments
        for (int i = 0; i < iterations_; ++i) {
            std::vector<Eigen::Vector2d> newlist_point;
            int Npoint = list_point.size();
            for (int j = 0; j < Npoint-1; j++) {
                Eigen::Vector2d start = list_point[j], end = list_point[j+1];
                Eigen::Vector2d diff = end - start;
                double Angle = std::atan2(diff.y(), diff.x()), Norm = std::sqrt(3./4) * diff.norm()/3., 
                        offx = Norm * std::cos(Angle + M_PI/2), offy = Norm * std::sin(Angle + M_PI/2);
                
                Eigen::Vector2d offset(offx, offy);
                Eigen::Vector2d new_before = start + diff/3., 
                                new_middle = start + diff/2. + offset, 
                                new_after = start + diff * 2 / 3.;

                newlist_point.push_back(start);
                newlist_point.push_back(new_before);
                newlist_point.push_back(new_middle);
                newlist_point.push_back(new_after);
            }
            Eigen::Vector2d end = list_point[Npoint-1];
            newlist_point.push_back(end);
            list_point = newlist_point;
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

        for (int i = 0; i < list_point.size();i++) {
            Eigen::Vector2d point = list_point[i];
            file << point[0] << "," << point[1] << "\n";
        }

        file.close();
        std::cout << "Données exportées vers : " << filename << std::endl;
    }
    
    void dimensions() const override {
        // La dimension de Minkowski-Bouligand pour la courbe de Von Koch est log(4)/log(3)
        double nb_segments = list_point.size()-1, taille_segment = (list_point[1] - list_point[0]).norm();
        
        double dimension_iter = std::log(nb_segments) / std::log(1./taille_segment);
        double dimension_th = std::log(4.0) / std::log(3.0);
        
        std::cout << "Dimension de Minkowski-Bouligand pour la fractale de Von Koch : " << dimension_th << std::endl;
        std::cout << "Dimension calculée : " << dimension_iter << std::endl;
        std::cout << "Ratio : " << dimension_iter / dimension_th << std::endl;
    }

private:
    /// Liste des points générés pour la courbe de Von Koch
    std::vector<Eigen::Vector2d> list_point;
};
