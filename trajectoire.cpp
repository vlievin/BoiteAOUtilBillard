#include "trajectoire.h"

using namespace std;


trajectoire::trajectoire(){}

trajectoire::trajectoire(myVecteur2D* v1, cadre* cadreJeu, int nbRebonds){

	vector<vertex> result ;
	result.clear();
	myVecteur2D* tmp;
	tmp = v1; //oui ?
	result.push_back(v1->getorigin());
	cout << "--------------- direction du vecteur v1( x|y) : " << v1->getxdir() << " | " << v1->getydir() << endl << endl;


	for (int k = 0; k < nbRebonds; k++)
	{
		myVecteur2D* vr;
		vertex inter;

		int bord = cadreJeu->getBordVise(tmp);
		if (bord >= 0)
		{
			//debug 
			
			intersectionDroites(tmp, cadreJeu->getBords(bord), inter);
			glColor3f(1.0f, 0.0f, 0.0f);
			cadreJeu->getBords(bord)->afficherGL(2.0f);
			vr = new myVecteur2D(tmp, cadreJeu->getBords(bord));
			cout << "in : trajectoire : numéro de bord : " << bord << " | incrément : " << k <<
				endl << " -------------- intersection  (x|y) : " << inter.x << " | " << inter.y << endl <<
				endl << "--------------- direction du vecteur rebond ( x|y) : " << vr->getxdir() << " | " << vr->getydir() << endl << endl;
			tmp = vr;
			result.push_back(vr->getorigin());
		}
		else
		{
			cout << "in : trajectoire : numéro de bord : " << bord << " | incrément :  " << k << endl;
		}

	} //endfor nbRebonds

	//FIN

	SuiteIntersections = result;

}

void trajectoire::afficherGL() const{

	for(int i = 0; i < (SuiteIntersections.size()-1); i++)
	{
		glPointSize(8);
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(SuiteIntersections[i].x, SuiteIntersections[i].y);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(SuiteIntersections[i].x, SuiteIntersections[i].y);
		glVertex2f(SuiteIntersections[i+1].x, SuiteIntersections[i+1].y);
		glEnd();
	}
	glPointSize(8);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(SuiteIntersections[SuiteIntersections.size() - 1].x, SuiteIntersections[SuiteIntersections.size() - 1].y);
	glEnd();
}

std::vector<vertex> trajectoire::getTrajectoire() const{
	return SuiteIntersections;
}

