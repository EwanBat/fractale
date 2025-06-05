#pragma once

#include <cmath>  // pour std::atan2
#include <fstream>
#include <complex>
#include <iomanip>

#include "Fractale.hpp"
#include "Eigen/Dense"

class Newton : public Fractale {
public:
    int ordre;
    int iterations_; // Nombre de points par axe

    Newton(int iterations) : iterations_(iterations) { }
    
    void generate() override {
        image.resize(3, iterations_ * iterations_);
        double step_x = (xmax - xmin) / iterations_;
        double step_y = (ymax - ymin) / iterations_;

        for (int i = 0; i < iterations_; ++i) {
            for (int j = 0; j < iterations_; ++j) {
                double x = xmin + i * step_x;
                double y = ymin + j * step_y;

                std::complex<double> z(x, y);
                int count = 0;

                while (count < 100 && std::abs(f(z.real(), z.imag())) > 1e-6) {
                    z = newton_step(z.real(), z.imag());
                    count++;
                }

                Eigen::Vector3d color = color_map(z);
                image(0, i * iterations_ + j) = static_cast<unsigned char>(color[0] * 255);
                image(1, i * iterations_ + j) = static_cast<unsigned char>(color[1] * 255);
                image(2, i * iterations_ + j) = static_cast<unsigned char>(color[2] * 255);
            }
        }
    }
    
    void exportData() const override {
        std::ofstream file(filename);

        if (!file) {
            std::cerr << "Erreur : impossible d’ouvrir le fichier " << filename << std::endl;
            return;
        }

        // En-tête
        file << "# x,y,r,g,b\n";
        file << std::fixed << std::setprecision(6); // Précision de sortie
        for (int i = 0; i < image.cols(); ++i) {
            double x = xmin + (i % iterations_) * (xmax - xmin) / iterations_;
            double y = ymin + (double(i) / iterations_) * (ymax - ymin) / iterations_;
            file << x << "," << y << ","
                 << static_cast<int>(image(0, i)) << ","
                 << static_cast<int>(image(1, i)) << ","
                 << static_cast<int>(image(2, i)) << "\n";
        }

        file.close();

        std::cout << "Données exportées vers " << filename << std::endl;
    }
    
private:
    double xmin = -2.0, xmax = 2.0;
    double ymin = -2.0, ymax = 2.0;
    Eigen::Matrix<unsigned char, 3, Eigen::Dynamic> image;
    
    std::complex<double> f(double x, double y) const {
        // Exemple de fonction complexe : f(z) = z^3 - 1
        std::complex<double> z(x, y);
        return std::pow(z, ordre) - 1.0;
    }

    std::complex<double> df(double x, double y) const {
        // Dérivée de la fonction complexe : f'(z) = 3z^2
        std::complex<double> z(x, y);
        return static_cast<double>(ordre) * std::pow(z, ordre - 1);
    }

    std::complex<double> newton_step(double x, double y) const {
        std::complex<double> z(x, y);
        return z - f(x, y) / df(x, y);
    }

    Eigen::Vector3d color_map(const std::complex<double>& z) const {
        // Exemple de mappage de couleur basé sur l'argument de z
        double angle = std::arg(z);
        double norm = std::abs(z);
        return Eigen::Vector3d(
            0.5 + 0.5 * std::cos(angle + 0.0),
            0.5 + 0.5 * std::cos(angle + 2.0 * M_PI / 3.0),
            0.5 + 0.5 * std::cos(angle + 4.0 * M_PI / 3.0)
        );
    }
};