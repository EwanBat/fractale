#pragma once

#include <vector>
#include <cmath>  // pour std::atan2
#include <fstream>
#include <iomanip>

#include "Fractale.hpp"
#include "Eigen/Dense"

class Dragon : public Fractale {
public:
    Eigen::Vector2d origin, direction;
    double Angle;
    int iterations_;

    Dragon(int iterations) : iterations_(iterations) { }
    
    void generate() override {
        list_point.clear();

        Eigen::Rotation2D<double> rotation(Angle);
        Eigen::Matrix2d rotationMatrix = rotation.toRotationMatrix();

        list_point.push_back(origin); list_point.push_back(origin + direction);

        for (int i = 0; i < iterations_; i++){
            int Npoint = list_point.size();
            std::vector<Eigen::Vector2d> new_points;
            new_points.reserve(Npoint - 1);

            Eigen::Vector2d fixe = list_point[Npoint-1];
            for (int j = Npoint - 2; j >= 0; j--){
                Eigen::Vector2d point = list_point[j];
                point = point - fixe + origin;
                point = rotationMatrix * point;
                point = point - origin + fixe;
                new_points.push_back(point);
            }

            list_point.insert(list_point.end(), new_points.begin(), new_points.end());
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
            Eigen::Vector2d point = list_point[i];
            file << point[0] << "," << point[1] << "\n";
        }

        file.close();
        std::cout << "Données exportées vers : " << filename << std::endl;
        }
    
private:
    std::vector<Eigen::Vector2d> list_point;
};