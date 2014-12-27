#ifndef BOULE_H
#define BOULE_H

#include "BoiteAOutil.h"

class boule
{
public:
	boule(float r, vertex c);
	void afficherGL() const;
	vertex getIntersection(myVecteur2D* u, double R)const; // R est le rayon de la boule lanc�e
	~boule();

private:
	float rayon;
	vertex centre;
};


#endif // BOULE_H