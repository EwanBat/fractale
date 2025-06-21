#pragma once

#include <fstream>
#include <complex>
#include <iomanip>

#include "Fractale.hpp"
#include "Eigen/Dense"

/**
 * @brief Classe représentant la fractale de Newton basée sur les racines complexes.
 *
 * Principe : La fractale de Newton est générée en appliquant la méthode de Newton-Raphson
 * à chaque point du plan complexe pour trouver les racines d'une fonction polynomiale.
 * Chaque pixel du plan est colorié selon la racine vers laquelle il converge et la rapidité de convergence.
 *
 * Fonctions principales :
 *  - generate() : génère l'image de la fractale en appliquant l'algorithme de Newton sur chaque point.
 *  - exportData() : exporte les données RVB de l'image générée dans un fichier texte.
 */
class Newton : public Fractale {
public:
    int ordre;         ///< Ordre du polynôme (ex : 3 pour z^3 - 1)
    int iterations_;   ///< Nombre de points par axe (résolution de l'image)

    /**
     * @brief Constructeur
     * @param iterations Nombre de points par axe (résolution)
     */
    Newton(int iterations) : iterations_(iterations) { }
    
    /**
     * @brief Génère l'image de la fractale de Newton.
     *
     * Pour chaque point du plan complexe, applique la méthode de Newton-Raphson
     * et colorie le pixel selon la racine atteinte et la vitesse de convergence.
     */
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
                
                if (count == 100) {
                    // Si on n'a pas convergé, on colorie en noir
                    image(0, i * iterations_ + j) = 0;
                    image(1, i * iterations_ + j) = 0;
                    image(2, i * iterations_ + j) = 0;
                    continue;
                }
                Eigen::Vector3d color = color_map(z);
                image(0, i * iterations_ + j) = static_cast<unsigned char>(color[0] * 255);
                image(1, i * iterations_ + j) = static_cast<unsigned char>(color[1] * 255);
                image(2, i * iterations_ + j) = static_cast<unsigned char>(color[2] * 255);
            }
        }
    }
    
    /**
     * @brief Exporte les données de l'image générée dans un fichier texte.
     *
     * Le fichier contient pour chaque pixel ses coordonnées (x, y) et ses valeurs RVB.
     */
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

    /**
     * @brief Fonction polynomiale complexe à étudier (ex : z^3 - 1).
     */
    std::complex<double> f(double x, double y) const {
        std::complex<double> z(x, y);
        return std::pow(z, ordre) - 1.0;
    }

    /**
     * @brief Dérivée de la fonction complexe (ex : 3z^2 pour z^3 - 1).
     */
    std::complex<double> df(double x, double y) const {
        std::complex<double> z(x, y);
        return static_cast<double>(ordre) * std::pow(z, ordre - 1);
    }

    /**
     * @brief Effectue une itération de la méthode de Newton-Raphson.
     */
    std::complex<double> newton_step(double x, double y) const {
        std::complex<double> z(x, y);
        return z - f(x, y) / df(x, y);
    }

    /**
     * @brief Associe une couleur à un point selon la racine atteinte (argument de z).
     */
    Eigen::Vector3d color_map(const std::complex<double>& z) const {
        double angle = std::arg(z);
        double norm = std::abs(z);

        if (ordre == 3) {
            // Racines du polynôme z^3 - 1 : 1, exp(2iπ/3), exp(4iπ/3)
            // On associe une couleur à chaque racine
            const double eps = 1e-2;
            std::complex<double> racines[3] = {
                std::polar(1.0, 0.0),
                std::polar(1.0, 2.0 * M_PI / 3.0),
                std::polar(1.0, 4.0 * M_PI / 3.0)
            };
            Eigen::Vector3d couleurs[3] = {
                Eigen::Vector3d(91./255, 206./255, 250./255), // Rouge
                Eigen::Vector3d(245./255, 169./255, 184./255), // Vert
                Eigen::Vector3d(1, 1, 1)  // Bleu
            };
            int idx = 0;
            double min_dist = std::abs(z - racines[0]);
            for (int i = 1; i < 3; ++i) {
                double dist = std::abs(z - racines[i]);
                if (dist < min_dist) {
                    min_dist = dist;
                    idx = i;
                }
            }
            // Optionnel : moduler la luminosité selon la norme (pour l'effet)
            double lum = std::min(1.0, 1.0 / (1.0 + 0.3 * std::abs(norm - 1.0)));
            return couleurs[idx] * lum;
        }

        // Cas général : dégradé selon l'argument
        return Eigen::Vector3d(
            0.5 + 0.5 * std::cos(angle + 0.0),
            0.5 + 0.5 * std::cos(angle + 2.0 * M_PI / 3.0),
            0.5 + 0.5 * std::cos(angle + 4.0 * M_PI / 3.0)
        );
    }
};