################################# Imports #################################
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

################################# Affichage Koch ##########################
def afficher_von_koch(filename):
    data = np.loadtxt(filename, skiprows=1, delimiter=",")
    plt.figure("Fractale de Von Koch")
    plt.plot(data[:,0], data[:,1])
    plt.axis("equal")
    plt.title("Fractale de Von Koch")
    plt.show()

################################# Affichage Newton ########################
def afficher_newton(filename):
    data = np.loadtxt(filename, skiprows=1, delimiter=",")
    plt.figure("Fractale de Newton")
    plt.scatter(data[:,0], data[:,1], c=data[:,2], cmap='plasma', s=1)
    plt.axis("equal")
    plt.title("Fractale de Newton")
    plt.colorbar(label='Nombre d’itérations')
    plt.show()

################################# Affichage Dragon ###########################
def afficher_dragon(filename):
    data = np.loadtxt(filename, skiprows=1, delimiter=",")
    plt.figure("Fractale du dragon de Heighway")
    plt.plot(data[:,0], data[:,1])
    plt.axis("equal")
    plt.title("Fractale du dragon de Heighway")
    plt.show()

################################# Main dispatcher #########################
def main():
    if len(sys.argv) != 3:
        print("Usage : python3 display.py <fractale> <fichier>")
        sys.exit(1)

    fractale = sys.argv[1].lower()
    filename = sys.argv[2]

    if not os.path.exists(filename):
        print(f"Erreur : fichier {filename} introuvable.")
        sys.exit(1)

    if fractale == "koch":
        afficher_von_koch(filename)
    elif fractale == "newton":
        afficher_newton(filename)
    elif fractale == "dragon":
        afficher_dragon(filename)
    else:
        print(f"Erreur : fractale inconnue '{fractale}'")
        sys.exit(1)

if __name__ == "__main__":
    main()
