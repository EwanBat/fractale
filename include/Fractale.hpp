#pragma once

#include <iostream>

// Fractale.hpp
class Fractale {
public:
    std::string filename;
    virtual ~Fractale() = default;
    
    // Méthode pour générer les données de la fractale
    virtual void generate() = 0;
    
    // Méthode pour exporter les données (par exemple une liste de segments ou de points)
    virtual void exportData() const = 0;
};
