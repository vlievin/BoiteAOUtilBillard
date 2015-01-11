#ifndef BOITEAOUTIL_H
#define BOITEAOUTIL_H

#include <iostream>
//#include <Windows.h>

// Fichiers d'en-têtes pour OpenGL et GLUT
#ifdef __APPLE__
#include <OPENGL/gl.h>
#include <GLUT/glut.h>
#else
//#include <GL/gl.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#endif

#include <cmath>

#include <vector>
#include <algorithm>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif


/// TODO : corriger la fonction intersectionDroiteBoule : la formule est fausse



typedef struct {
	float x;
	float y;

} vertex;

const float  M_ERR = 0.001;

class boule;

class myVecteur2D { //il faut gérer le cas du vecteur nul

private:
	float xdir;
	float ydir;
	vertex origin;
public:
	myVecteur2D();
	myVecteur2D(float x, float y);
	myVecteur2D(float x, float y, vertex point);
	myVecteur2D(myVecteur2D* v1, myVecteur2D* v2); // crée le vecteur "rebond", du premier vecteur sur le deuxième
	myVecteur2D(myVecteur2D* v1 , boule* b , float r); //crée le vecteur direction rebond sur une boule pour une boule lancée de rayon r
	~myVecteur2D();
	void setdir(float x, float y);
	void setorigin(vertex point);
	float getxdir() const;
	float getydir() const;
	vertex getorigin() const;
	void normalise();
	void afficherGL() const;
	void afficherGL(float alpha) const;
	float getNorme()const;
	bool isEgal(myVecteur2D* v) const;
	bool isNul()const;
	//void setRebond(myVecteur2D* v1, myVecteur2D* v2);


};


class cadre{
	/*
	1->2
	^  |
	|  v
	4<-3
	*/

private:
	std::vector<myVecteur2D*> bords;
public:
	cadre();
	//cadre(myVecteur2D* a, myVecteur2D* b, myVecteur2D* c, myVecteur2D* d);
	cadre(vertex a, vertex b, vertex c, vertex d);
	void afficherGL() const;
	void afficherVecteursGL() const;
	myVecteur2D* getBords(int i) const;
	std::vector<myVecteur2D*> getBords()const;
	vertex getcoins(int i) const;
	void setBords(int i, myVecteur2D* vector);
	int getBordVise(myVecteur2D* vec) const; // retourne l'indice du bord pointé
	std::vector<myVecteur2D*> rebonds(myVecteur2D* v,int nb)const;

};


float produitVectoriel(myVecteur2D* v1, myVecteur2D* v2); //produit mixte

int intersectionDroites( myVecteur2D* v1,  myVecteur2D* v2, vertex& sol); //1 si l'intersction existe est est dans le sens du premier vecteur, 0 si elle n'existe pas, 1 si l'intersection se trouve dans l'autre sens

int intersectionDroiteBoule(myVecteur2D* v1 , myVecteur2D* v2, float r , vertex& sol); // même fonction que ci dessus en prenant en compte le rayon de la boule

float produitscalaire(myVecteur2D *v1, myVecteur2D *v2); // produit scalaire

bool appartientSegment(vertex pointCible, vertex A, vertex B); // on considère le segment ouvert (pour éviter qu'un point appartienne à deux segements)-> TODO gestion des coins séparémment

float distancePoints(vertex A, vertex B);

void afficherRebondsGL(std::vector<myVecteur2D*> rebonds);


bool egalerr(float x, float y); // donne l'égalité entre deux valeurs en prenant en compte l'imprecision des calculs

vertex operator+(vertex const& a, myVecteur2D* const& b);

void afficherGL(vertex point);

std::vector<double> solvePoly2(double a, double b, double c); // résoud une equation polynomiale de degré 2

#endif //BOITEAOUTIL_H

