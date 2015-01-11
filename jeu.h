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
cadre* getCadre() const;
void addBoule(boule* b);
int AimBoule(myVecteur2D* v , float r) const; // retourne l'indice de la boule percutée s'il y en a une , -1 sinon

};



#endif // JEU_H
