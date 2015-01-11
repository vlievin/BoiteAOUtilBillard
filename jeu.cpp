#include "jeu.h"

using namespace std;

jeu::jeu(){}

jeu::jeu(cadre* cad) : c(cad) {}

jeu::jeu(cadre* cad, std::vector<boule*> vb): c(cad), boules(vb){}

jeu::~jeu(){}


std::vector<boule*> jeu::getBoules() const {return boules;}

cadre* jeu::getCadre() const {return c;}

boule* jeu::getBoules(int i) const{ return boules[i];}

void jeu::addBoule(boule* b){
    boules.push_back(b);
}

int jeu::AimBoule(myVecteur2D* v , float r) const{ // retourne l'indice de la boule percutée s'il y en a une , -1 sinon

    int i =-1;
    vertex vex;
    float d;
    float tmp = 1000000; //nombre très grand
    int k;
    for( k = 0; k< boules.size() ; k++) // on parcoure le vecteur de boule
    {
        if(boules[k]->getIntersection(v,r, vex)) // s'il y a intersection avec une boule
        {
            d = distancePoints(vex, v->getorigin()); // on calcul la distance avec l'origine du vecteur directeur et cette intersection
            if (d<tmp)
            {
                i = k ; // on garde l'indice de la plus petite distance
                tmp = d;
            }

        }
    }

    return i;

}

int jeu::AimBouleSauf(myVecteur2D* v , float r, int j) const{

  int i =-1;
    vertex vex;
    float d;
    float tmp = 1000000; //nombre très grand
    int k;
    for( k = 0; k< boules.size() ; k++) // on parcourt le vecteur de boule
    {
        if(boules[k]->getIntersection(v,r, vex) && k!=j) // s'il y a intersection avec une boule et que cette boule n'est pas celle à exclure
        {
            d = distancePoints(vex, v->getorigin()); // on calcul la distance avec l'origine du vecteur directeur et cette intersection
            if (d<tmp)
            {
                i = k ; // on garde l'indice de la plus petite distance
                tmp = d;
            }

        }
    }

    return i;

}

