def newton(F , f , x0 , epsilon):
    N=100
    U=x0
    if abs(f(U)) <= 10**-6:
        return "division par 0 C'EST UN SOS JE SUIS PERDU",None
    V= U - F(U)/f(U)
    compteur=0
    while abs(V-U) >= epsilon:
        U=V
        if abs(f(U)) <= 10**-6:
            return "division par 0 C'EST UN SOS JE SUIS PERDU",None
        V=U - F(U)/f(U)
        compteur += 1
        if compteur == N:
            return "erreur",None
    return V,compteur

from math import sqrt
from pylab import *
import cmath as cm

def Arc_En_Ciel_Newton(N,N_max):
    X=Echelle(N,0,N_max,0,1530)
    L=[]
    if X<0:
        L=[0,0,0]
    elif X <= 45:
        L=[0,150,150]
    elif 45<=X and X<= 61:
        L=[176,223,229]
    elif 61<=X and X<=76:
        L=[14,77,146]
    elif 76 <= X and X<=91:
        L=[0,49,82]
    elif 91<=X and X <= 107:
        L=[29,41,81]
    elif 107<= X and X <= 153:
        L=[17,30,108]
    elif X>=153:
        L=[0,0,0]
    L[0] =round(L[0]/255,2)
    L[1] =round(L[1]/255,2)
    L[2] =round(L[2]/255,2)
    return L

def Echelle(u,u_min,u_max,v_min,v_max):
    a=(v_max-v_min)/(u_max-u_min)
    b=v_max-a*u_max
    return a*u+b

def Ploting(X,Y,Color):
    plot(X,Y,",",color=Color)
    return
## III-Fractale de Newton

def fcomplexe3(z):
    return z**3 - 1
def fcomplexe_prime3(z):
    return 3*z**2

"""pas bon test car pc comprends un chiffre = 0 alors que non"""

#racine 3ème de l'unité exp(2jpik/n) pour 0<=k<n
r1=complex(1,0)
r2=complex(-0.5,sqrt(3)/2)
r3=complex(-0.5,-sqrt(3)/2)
BorneX=[-1.5,1.5]
BorneY=[-1.5,1.5]

def affichage_newton_3eme(LimX,LimY,a,b,c,F,f,epsilon):
    figure(2)
    title("Fractale de Newton")
    GreenX=[]
    BlueX=[]
    RedX=[]
    GreenY=[]
    BlueY=[]
    RedY=[]
    BlackX=[]
    BlackY=[]
    k=BorneY[0]
    j=BorneX[0]
    compteurj=0
    compteurk=0
    while k <= BorneY[1]:
        while j <= BorneX[1]:
            Z=newton(F,f,complex(round(j,2),round(k,2)),epsilon)
            if Z[1] == None:
                BlackX.append(j)
                BlackY.append(k)
            elif abs(a-Z[0]) <= epsilon:
                GreenX.append(j)
                GreenY.append(k)
            elif abs(b-Z[0]) <= epsilon:
                BlueX.append(j)
                BlueY.append(k)
            elif abs(c-Z[0]) <= epsilon:
                RedX.append(j)
                RedY.append(k)
            elif abs(c-Z[0]) == abs(b-Z[0]) and abs(c-Z[0]) == abs(a-Z[0]):
                BlackX.append(j)
                BlackY.append(k)
            j = round(j+1e-4,6)
        k = round(k+1e-4,6)
        #print("k=",k)
        j=BorneX[0]
    xlim(LimX)
    ylim(LimY)
    plot(GreenX,GreenY,",",color = [0,1,0])
    plot(BlueX,BlueY,",",color = [0,0,1])
    plot(RedX,RedY,",",color = [1,0,0])
    plot(BlackX,BlackY,",",color = "black")
    return show()

affichage_newton_3eme(BorneX,BorneY,r1,r2,r3,fcomplexe3,fcomplexe_prime3,10**-1)

## racine 4ème de l'unité fractale
BorneX=[-1.5,1.5]
BorneY=[-1.5,1.5]

def fcomplexe4(z):
    return z**4 - 1
def fcomplexe_prime4(z):
    return 4*z**3

r14,r24,r34,r44 =complex(1,0),complex(0,1),complex(-1,0),complex(0,-1)

def affichage_newton_4eme(LimX,LimY,a,b,c,d,F,f,epsilon):
    title("Fractale de Newton")
    GreenX=[]
    BlueX=[]
    RedX=[]
    GreenY=[]
    BlueY=[]
    RedY=[]
    BlackX=[]
    BlackY=[]
    YellowX=[]
    YellowY=[]
    k=LimX[0]
    j=LimX[0]
    while k <= LimX[-1]:
        while j <= LimX[-1]:
            Z=newton(F,f,complex(round(j,2),round(k,2)),epsilon)
            if Z[1] == None:
                BlackX.append(j)
                BlackY.append(k)
            elif abs(a-Z[0]) <= epsilon:
                GreenX.append(j)
                GreenY.append(k)
            elif abs(b-Z[0]) <= epsilon:
                BlueX.append(j)
                BlueY.append(k)
            elif abs(c-Z[0]) <= epsilon:
                RedX.append(j)
                RedY.append(k)
            elif abs(d-Z[0]) <= epsilon:
                YellowX.append(j)
                YellowY.append(k)
            elif abs(c-Z[0]) == abs(b-Z[0]) and abs(c-Z[0]) == abs(a-Z[0]):
                BlackX.append(j)
                BlackY.append(k)
            j += 0.004
        k += 0.004
        j=-1.5
    xlim(LimX)
    ylim(LimY)
    plot(GreenX,GreenY,",",color = "green")
    plot(BlueX,BlueY,",",color = "blue")
    plot(RedX,RedY,",",color = "red")
    plot(BlackX,BlackY,",",color = "black")
    plot(YellowX,YellowY,",",color = "yellow")
    return show()

#affichage_newton_4eme(BorneX,BorneY,r14,r24,r34,r44,fcomplexe4,fcomplexe_prime4,10**-2)
## Racine 7ème de l'unité
BorneX=[-1.5,1.5]
BorneY=[-1.5,1.5]

def Racine(n):
    CoorComplexe=[cm.rect(1,(2*k*cm.pi/n)) for k in range(n)]
    return CoorComplexe

def fcomplexe7(z):
    return z**7 - 1
def fcomplexe_prime7(z):
    return 7*z**6
Liste=Racine(7)
r17,r27,r37,r47,r57,r67,r77 = Liste[0],Liste[1],Liste[2],Liste[3],Liste[4],Liste[5],Liste[6]

def affichage_newton_7eme(LimX,LimY,a,b,c,d,e,g,h,F,f,epsilon):
    title("Fractale de Newton")
    GreenX=[]
    BlueX=[]
    RedX=[]
    GreenY=[]
    BlueY=[]
    RedY=[]
    BlackX=[]
    BlackY=[]
    YellowX=[]
    YellowY=[]
    PinkX=[]
    PinkY=[]
    PurpleX=[]
    PurpleY=[]
    OrangeX=[]
    OrangeY=[]
    k=LimX[0]
    j=LimX[0]
    while k <= LimX[-1]:
        while j <= LimX[-1]:
            Z=newton(F,f,complex(round(j,2),round(k,2)),epsilon)
            if Z[1] == None:
                BlackX.append(j)
                BlackY.append(k)
            elif abs(a-Z[0]) <= epsilon:
                GreenX.append(j)
                GreenY.append(k)
            elif abs(b-Z[0]) <= epsilon:
                BlueX.append(j)
                BlueY.append(k)
            elif abs(c-Z[0]) <= epsilon:
                RedX.append(j)
                RedY.append(k)
            elif abs(d-Z[0]) <= epsilon:
                YellowX.append(j)
                YellowY.append(k)
            elif abs(e-Z[0]) <= epsilon:
                PinkX.append(j)
                PinkY.append(k)
            elif abs(g-Z[0]) <= epsilon:
                PurpleX.append(j)
                PurpleY.append(k)
            elif abs(h-Z[0]) <= epsilon:
                OrangeX.append(j)
                OrangeY.append(k)
            elif abs(c-Z[0]) == abs(b-Z[0]) and abs(c-Z[0]) == abs(a-Z[0]):
                BlackX.append(j)
                BlackY.append(k)
            j = round(j+0.004,4)
        k = round(k+0.004,4)
        j=-1.5
    xlim(LimX)
    ylim(LimY)
    plot(GreenX,GreenY,",",color = "green")
    plot(BlueX,BlueY,",",color = "blue")
    plot(RedX,RedY,",",color = "red")
    plot(BlackX,BlackY,",",color = "black")
    plot(YellowX,YellowY,",",color = "yellow")
    plot(PinkX,PinkY,",",color = "pink")
    plot(PurpleX,PurpleY,",",color = "purple")
    plot(OrangeX,OrangeY,",",color = "orange")
    return show()

#affichage_newton_7eme(BorneX,BorneY,r17,r27,r37,r47,r57,r67,r77,fcomplexe7,fcomplexe_prime7,10**-2)

## Racine 3ème psychiadelique
BorneX=[-1.5,1.5]
BorneY=[-1.5,1.5]

def fcomplexe3(z):
    return z**3 - 1
def fcomplexe_prime3(z):
    return 3*z**2

"""pas bon test car pc comprends un chiffre = 0 alors que non"""

#racine 3ème de l'unité exp(2jpik/n) pour 0<=k<n
r1=complex(1,0)
r2=complex(-0.5,sqrt(3)/2)
r3=complex(-0.5,-sqrt(3)/2)

def affichage_newton_3eme_psy(LimX,LimY,a,b,c,F,f,epsilon):
    clf()
    title("Fractale de Newton")
    BlackX=[]
    BlackY=[]
    k=BorneY[0]
    j=BorneX[0]
    while k < BorneY[1]:
        while j < BorneX[1]:
            Z=newton(F,f,complex(round(j,2),round(k,2)),epsilon)
            if Z[1] == None:
                BlackX.append(j)
                BlackY.append(k)
            else:
                Couleur=(Arc_En_Ciel_Newton(Z[1],100))
                plot(j,k,",",color=Couleur)
            j = round(j+0.001,4)
        k = round(k+0.001,4)
        print("k=",k)
        j=BorneX[0]
    plot(BlackX,BlackY,c='b')
    xlim(LimX)
    ylim(LimY)
    return show()

#affichage_newton_3eme_psy(BorneX,BorneY,r1,r2,r3,fcomplexe3,fcomplexe_prime3,10**-2)

##

3,4,5,6,7,10,14,15

print(Echelle(3,0,100,0,1530))
print(Echelle(4,0,100,0,1530))
print(Echelle(5,0,100,0,1530))
print(Echelle(6,0,100,0,1530))
print(Echelle(7,0,100,0,1530))
print(Echelle(10,0,100,0,1530))























