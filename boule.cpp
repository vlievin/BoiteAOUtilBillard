

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

bool boule::getIntersection(myVecteur2D* u, double R, vertex& sol)const{ // renvoi un le point de l'intersection entre la boule un un vecteur directeur.
// R représente le rayon de la boule en mouvement (vecteur u)


	double r = R + rayon;

	if (u->isNul())
		{
		cout << " in boule.getIntersection() : vecteur nul" << endl << endl;
		return false;
		}
	else
	{
	cout << " in boule.getIntersection() : 1" << endl << endl;
		if (u->getydir() != 0) //si toutes les composantes sont non-nulles
		{



            //voir brouillon pour le détail des calculs

			double l = u->getxdir() / u->getydir();
            double K = r*r - (centre.x*centre.x + centre.y * centre.y);
            double Q = u->getorigin().x - l * u->getorigin().y;

            double da = (l*l + 1 );
            double db = 2 * ( (Q - centre.x) *l  - centre.y );
            double dc = Q*Q - 2 * Q * centre.x - K;

            cout << " in boule.getIntersection() : paramètres clef :  " << "l : "<<l<<
             " K : "<< K << " Q : " << Q << " da : " <<da << " db : "<<db << " dc : "<< dc  << endl ;

			vector<double> solutions = solvePoly2(da, db, dc);
			int nbsol = solutions.size();

			for (int i = 0 ; i< solutions.size() ; i ++)
			{cout << " in boule.getintersection : result solve poly : " <<solutions[i]<< endl;}

            cout << " in boule.getIntersection() : taille du vecteur solution "<< nbsol << endl ;
			// solutions en fonction du nombre de solutions
			if (nbsol== 0)
			{
                return false;
                //debug
                cout<< "in Boule : getIntersection() : 0 solutions (poly)"<<endl;
			}
            else if (nbsol ==1 )
			{
                return true;
                vertex s;
                //debug
                cout<< "in Boule : getIntersection() : 1 solutions (poly)"<<endl;
                s.y = solutions.at(0);
                s.x = Q + l*solutions.at(0);
                sol = s;
			}
			else if (nbsol == 2)// la bonne solution est le point le plus proche de l'origine du vecteur (faire un schéma)
			{
			//debug
                cout<< "in Boule : getIntersection() : 2 solutions (poly)"<<endl;

                // calcul de la solution 1 et de sa distance par rapport à l'origine de u
                vertex s1;
                s1.y = solutions.at(0);
                s1.x = Q + solutions.at(0);
                float d1 = distancePoints(s1,u->getorigin());

                //solution 2
                vertex s2;
                s2.y = solutions.at(1);
                s2.x = Q+ l*solutions.at(1);
                float d2 = distancePoints(s2,u->getorigin());

                // sélection de la solution
                if (d1 > d2)
                {
                    sol = s2;
                }
                else
                {
                    sol = s1;
                }

                return true;


			}
			else
			{
                return false;
                std::cout<<"in Boule::getIntersection() : la fonction solvePoly2 renvoi plus de 2 solutions"<<std::endl;
            }



		}
		else
		{
            std::cout<<"in Boule::getIntersection() : ydir = 0"<<std::endl;
		}

	}

}
