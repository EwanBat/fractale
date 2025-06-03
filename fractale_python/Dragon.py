from matplotlib import pyplot as plt
import numpy as np
plt.close('all')
# %matplotlib qt

N = 10 #Nombre de récurrence de la fractale
Theta = np.pi/2 #Angle de rotation à chaque récurrence
Origine = np.array([0,0]) #Point de départ
L_Points = [Origine,Origine + np.array([0,1])]
Mat_Rota = np.round(np.array([[np.cos(Theta),-np.sin(Theta)],[np.sin(Theta),np.cos(Theta)]]),6)

def Affichage_doublet(L):
    plt.figure('Fractale du dragon')
    X,Y = [],[]
    for (x,y) in L:
        X.append(x)
        Y.append(y)
    plt.plot(X,Y)
    plt.savefig("Fractale_du_Dragon.svg")
    if N <= 25:
        plt.show()

def Rotation(z):
    return Mat_Rota @ z

def Translation(z,z0,z1):
    return z-(z0-z1)

def Dragon(L,N):
    def aux(L,N):
        if N == 0:
            return L 
        else:
            z_fixe = L[-1]
            #L_New = []
            #for z in L[:-1]:
            #    z_p = Translation(z,z_fixe,Origine)
            #    z_p = Mat_Rota @ z_p
            #    z_p = Translation(z_p,Origine,z_fixe)
            #    L_New.append(z_p)
            L_New = Translation(np.array(L[:-1]),z_fixe,Origine)
            L_New = np.array([Rotation(z) for z in L_New])
            L_New = Translation(L_New,Origine,z_fixe)
            L += list(L_New)[::-1]
            L = aux(L,N-1)
        return L
    L = aux(L,N)
    return L

Dragon(L_Points,N)
Affichage_doublet(L_Points)