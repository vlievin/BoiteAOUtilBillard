#ifndef BOITEAOUTIL_H
#define BOITEAOUTIL_H

#include <iostream>
#include <Windows.h>

// Fichiers d'en-t�tes pour OpenGL et GLUT
#ifdef __APPLE__
#include <OPENGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <vector>

typedef struct {
	float x;
	float y;

} vertex;


class myVecteur2D { //il faut g�rer le cas du vecteur nul

private:
	float xdir;
	float ydir;
	vertex origin;
public:
	myVecteur2D(float x, float y);
	myVecteur2D(float x, float y, vertex point);
	myVecteur2D(myVecteur2D* v1, myVecteur2D* v2); // cr�e le vecteur "rebond", du premier vecteur sur le deuxi�me
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
	

};


class cadre{
	/*
	1->2
	^  |
	|  v
	4<-3
	*/

private:
	myVecteur2D* bords[4];
public:
	cadre();
	cadre(myVecteur2D* a, myVecteur2D* b, myVecteur2D* c, myVecteur2D* d);
	cadre(vertex a, vertex b, vertex c, vertex d);
	void afficherGL() const;
	myVecteur2D* getBords(int i) const;
	vertex getcoins(int i) const;
	void setBords(int i, myVecteur2D* vector);
	int getBordVise(myVecteur2D* vec) const; // retourne l'indice du bord point� 
	

};


float produitVectoriel(myVecteur2D* v1, myVecteur2D* v2); //produit mixte

int intersectionDroites( myVecteur2D* v1,  myVecteur2D* v2, vertex& sol); //1 si l'intersction existe est est dans le sens du premier vecteur, 0 si elle n'existe pas, 1 si l'intersection se trouve dans l'autre sens 


float produitscalaire(myVecteur2D *v1, myVecteur2D *v2); // produit scalaire

bool appartientSegment(vertex pointCible, vertex A, vertex B); // on consid�re le segment ouvert (pour �viter qu'un point appartienne � deux segements)-> TODO gestion des coins s�par�mment

float distance(vertex A, vertex B);

#endif //BOITEAOUTIL_H
