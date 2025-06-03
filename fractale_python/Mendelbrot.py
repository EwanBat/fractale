
# TP2 - Récursivité

# Import des librairies

import numpy as np
import matplotlib.pyplot as plt
plt.close('all')

# Fonction d'affichage d'une image

def f_affiche(image):
    plt.figure()
    plt.ion()
    plt.imshow(image)
    plt.axis('off')
    plt.show()
    plt.pause(0.00001)

# Données

X_Min = -2.35
X_Max = 0.85
Y_Min = -1.2
Y_Max = 1.2
Nb_Colonnes = 500 # Valeur à modifier

# Création d'une image vierge

Nb_Lignes = int(((Y_Max - Y_Min) / (X_Max - X_Min)) * Nb_Colonnes)
Image_Liste = []
Image = np.zeros((Nb_Lignes,Nb_Colonnes,3),dtype=np.uint8)

# Programme du TP à compléter



# Affichage et sauvegarde du résultat

f_affiche(Image)
plt.imsave("Resultat.bmp",Image)
''' Si bug format bmp, essayer avec .png ou sans extension '''

##
from math import sqrt
from math import tan
from pylab import *
def Suite_Mandelbrot(n,c):
    Z0=0
    Z1=Z0**2 + c
    M=0
    for k in range(n):
        Z0 = Z1
        if sqrt(real(Z0)**2 + imag(Z0)**2) < 3:
            Z1 =Z0**2 + c
            M += 1
        else:
            Z1=3
    return [Z1,M]

def Echelle(u,u_min,u_max,v_min,v_max):
    a=(v_max-v_min)/(u_max-u_min)
    b=v_max-a*u_max
    return a*u+b

def Coordonnees_Pixel(l_pix,c_pix):
    A=Echelle(l_pix,Nb_Lignes-1,0,-1.2,1.2)
    B=Echelle(c_pix,0,Nb_Colonnes-1,-2.35,0.85)
    return B,A

def Couleur_Pixel(l_pix,c_pix):
    X,Y=Coordonnees_Pixel(l_pix,c_pix)
    L=Suite_Mandelbrot(50,complex(X,Y))
    S=L[0]
    if S==3:
        Image[l_pix,c_pix]=Arc_En_Ciel(L[1],50)
    else:
        if 10<=L[1] and L[1]<20:
            Image[l_pix,c_pix]=[10,120,120]
        elif 20<=L[1] and L[1]<30:
            Image[l_pix,c_pix]=[120,10,120]
        elif 30<=L[1] and L[1]<40:
            Image[l_pix,c_pix]=[120,120,10]
    return Image[l_pix,c_pix]

def Fractale_Mandelbrot():
    for l_pix in range(Nb_Lignes):
        for c_pix in range(Nb_Colonnes):
            Couleur_Pixel(l_pix,c_pix)
            Etat=(l_pix+1)*Nb_Colonnes + c_pix + 1
            Pct=Etat*100/(Nb_Colonnes*Nb_Lignes)
            Pct=round(Pct,1)
            print(Pct,"%")
    f_affiche(Image)

def Arc_En_Ciel(N,N_max):
    X=Echelle(N,0,N_max,0,1530)
    L=[]
    if X<0:
        L=[255,0,0]
    elif X <= 255:
        L=[255,X,0]
    elif 255<=X and X<= 510:
        L=[510-X,255,0]
    elif 510<=X and X<=765:
        L=[0,255,X-510]
    elif 765 <= X and X<=1020:
        L=[0,1020-X,255]
    elif 1020<=X and X <= 1275:
        L=[X-1020,0,255]
    elif 1275<= X and X <= 1530:
        L=[255,0,1530-X]
    elif X>=1530:
        L[255,0,0]
    return L

Fractale_Mandelbrot()





































