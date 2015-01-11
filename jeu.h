#ifndef JEU_H
#define JEU_H

#include "BoiteAOutil.h"
#include "boule.h"


class jeu{

private:
std::vector<boule*> boules;
cadre* c;

public:
jeu();
jeu(cadre* cad);
jeu(cadre* cad, std::vector<boule*> vb);
~jeu();
std::vector<boule*> getBoules() const;
boule* getBoules(int i) const;
cadre* getCadre() const;
void addBoule(boule* b);
int AimBoule(myVecteur2D* v , float r) const; // retourne l'indice de la boule percutée s'il y en a une , -1 sinon
int AimBouleSauf(myVecteur2D* v , float r, int j) const; // cherche la boule intersectée sauf celle définie par l'indice i, retourne l'indice de la boule percutée s'il y en a une , -1 sinon
void afficherGL() const;

};



#endif // JEU_H
