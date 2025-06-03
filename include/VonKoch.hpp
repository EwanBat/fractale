#pragma once

#include <vector>
#include <cmath>  // pour std::atan2
#include <fstream>
#include <iomanip>

#include "Fractale.hpp"
#include "Eigen/Dense"

class VonKoch : public Fractale {
public:
    Eigen::Vector2d first, last;
    int iterations_;

    VonKoch(int iterations) : iterations_(iterations) { }
    
    void generate() override {
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
            std::cout << i << std::endl;
            Eigen::Vector2d point = list_point[i];
            file << point[0] << "," << point[1] << "\n";
        }

        file.close();
        std::cout << "Données exportées vers : " << filename << std::endl;
        }
    
private:
    std::vector<Eigen::Vector2d> list_point;
};
