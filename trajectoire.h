#ifndef TRAJECTOIRE_H
#define TRAJECTOIRE_H


#include "BoiteAOutil.h"
#include "jeu.h"


class trajectoire{

private:
		std::vector<vertex> SuiteIntersections;
		int nbRebonds;

public:
	trajectoire();
	trajectoire(myVecteur2D* v1, cadre* cadreJeu, int nbRebonds);
	trajectoire(myVecteur2D* v1, jeu* j,float r , int nbRebonds);
	std::vector<vertex> getTrajectoire() const;
	void afficherGL() const;
	~trajectoire();
};


#endif // TRAJECTOIRE_H
