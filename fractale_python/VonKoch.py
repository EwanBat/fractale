##Import de librairies
from matplotlib import pyplot as plt
import numpy as np
# matplotlib qt

##
plt.close('all')
N = 1 #Nombre de récurrences
e1,e2 = np.array([0,0]),np.array([10,0]) #Premiers points
Départ = [e1,e2] #Liste de départ

def Affichage_doublet(L):
    plt.figure('Fractale de Von Koch')
    plt.axis('equal')
    X,Y = [],[]
    for v in L:
        x,y = v[0],v[1]
        X.append(x)
        Y.append(y)
    plt.plot(X,Y)
    plt.savefig("Fractale_de_Von_Koch.svg")
    if N <= 10:
        plt.show()

def Angle(Vect): #Vect un array de dim 2
    x,y = Vect
    if x != 0:
        if x > 0:
            Theta = np.arctan(y/x)
        elif x < 0:
            Theta = np.arctan(y/x) + np.pi
    else:
        print('Erreur division par 0')
        return
    return Theta

def Sommet(e1,e2):
    a = e2-e1
    Theta = Angle(a)
    r = np.sqrt(3/4) * np.linalg.norm(a/3)
    Psi = Theta + np.pi/2
    d = np.array([r*np.cos(Psi),r*np.sin(Psi)]) + e1 + a/2
    b,c = e1 + a/3,e1 + a*2/3
    return b,d,c

def Von_Koch(L): #Construit la fractale de Von Koch par récursivité
    k = 0
    def aux(L,k):
        if k >= N:
            return L
        else:
            k += 1
            N_L = aux(L,k)
            LL = [L[0]]
            for i in range(1,len(N_L)): #Construit un nouveau sommet entre 2 points
                s1,s2,s3 = Sommet(N_L[i-1],N_L[i])
                LL.append(s1)
                LL.append(s2)
                LL.append(s3)
                LL.append(N_L[i])
            return LL
    LL = aux(L,k)
    return LL

Liste_VonKoch = Von_Koch(Départ)
Affichage_doublet(Liste_VonKoch)