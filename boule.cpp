

#include"boule.h"
#include <math.h>

using namespace std;

boule::boule(float r, vertex c) : centre(c), rayon(r)
{
}

boule::~boule()
{
}
void boule::afficherGL()const{
	//debug
	cout << "boule : " << " centre xy : " << centre.x << " | " << centre.y << " rayon : " << rayon << endl << endl;

	float angle;
	float angle2;
	int nb_faces = 32;

	glPointSize(5);

	glColor3f(0.3f, 0.1f, 0.3f);
	glBegin(GL_POINTS);
	
	glVertex2f(centre.x, centre.y);
		
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < nb_faces; i++)
	{
		angle = 2 * M_PI*i / nb_faces;
		angle2 = 2 * M_PI*(i+1) / nb_faces;
		//glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(centre.x + cos(angle)*rayon, centre.y + sin(angle)*rayon);
		//glVertex2f(centre.x + cos(angle2)*rayon, centre.y + sin(angle2)*rayon);
		//cout << "angle cercle : " << i << endl << endl;
	}
	glEnd();
	
}

vertex boule::getIntersection(myVecteur2D* u, double R)const{
	
	vertex M;
	double r = R + rayon;

	if (u->isNul())
		cout << " in boule.getIntersection() : vecteur nul" << endl << endl;
	else
	{
		if (u->getxdir() == 0 && u->getydir() == 0)
		{
			double l = u->getxdir() / u->getydir();
			double K = r*r - centre.x*centre.x - centre.y*centre.y;
			double b = u->getorigin().x - l * u->getorigin().y;
			double da = b*b + l*l + 1;
			double db = 2 * (l * b - (l * centre.x + centre.y));
			double dc = -2 * (b* centre.x + K);


		}
		else if (u->getxdir() == 0)
		{

		}
		else if (u->getydir() == 0)
		{

		}
		else
			cout << " in boule.getIntersection() : aucun test valide" << endl << endl;
	}
	
}