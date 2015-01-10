#ifndef BOULE_H
#define BOULE_H

#include "BoiteAOutil.h"

class boule
{
public:
	boule(float r, vertex c);
	void afficherGL() const;
	bool getIntersection(myVecteur2D* u, double R, vertex &sol)const; // R est le rayon de la boule lancée
	~boule();

private:
	float rayon;
	vertex centre;
};


#endif // BOULE_H
