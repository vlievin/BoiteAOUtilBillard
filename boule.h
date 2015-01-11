#ifndef BOULE_H
#define BOULE_H

#include "BoiteAOutil.h"

class boule
{
public:
	boule(float r, vertex c);
	void afficherGL() const;
	void afficherGL(float r, float v, float b) const;
	bool getIntersection(myVecteur2D* u, double R, vertex &sol)const; // R est le rayon de la boule lancée, vrai s'il y a intersection
	float getRayon() const;
	vertex getCentre() const;
	~boule();

private:
	float rayon;
	vertex centre;
};


#endif // BOULE_H
