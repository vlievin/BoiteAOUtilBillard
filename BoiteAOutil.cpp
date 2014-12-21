#include "BoiteAOutil.h"



/*
DEFINTION DE myVecteur2D
*/

myVecteur2D::myVecteur2D(float x, float y) : xdir(x), ydir(y){
	normalise();
}
myVecteur2D::myVecteur2D(float x, float y, vertex point) : xdir(x), ydir(y), origin(point){
	normalise();
}

myVecteur2D::myVecteur2D(myVecteur2D* v1, myVecteur2D* v2){ // créer un rebond : premier vecteur sur le deuxième

	vertex originrebond;
	originrebond.x = 0;
	originrebond.y = 0;

	int sens;

	sens = intersectionDroites(v1, v2, originrebond);

	//if (sens > 0)
	//{
		
	std::cout << "ps : " << produitscalaire(v1, v2) << std::endl;
		float alpha = acos(abs(produitscalaire(v1, v2))); // TODO : prendre en compte la valeur négative ou poistive de l'angle

		
		if (produitVectoriel(v1, v2) < 0)
			alpha = -alpha;
		std::cout << "alpha : " << alpha << std::endl;

		vertex dirOrtho; //défini le vecteur orthogonal au vecteur v2
		dirOrtho.x = - v2->getydir();
		dirOrtho.y =  v2->getxdir();
		origin = originrebond;
		xdir = cos(alpha)*v2->getxdir() + sin(alpha)*dirOrtho.x;
		ydir = sin(alpha)*dirOrtho.y + sin(alpha) * v2->getydir();

		//xdir = dirOrtho.x;
		//ydir = dirOrtho.y;

		normalise();
	/*}
	else
	{

	}
	*/

}

myVecteur2D::~myVecteur2D() {

}

void myVecteur2D::setdir(float x, float y){
	xdir = x;
	ydir = y;
	normalise();
}

void myVecteur2D::setorigin(vertex point){
	origin = point;
}

float myVecteur2D::getxdir() const{
	return xdir;
}

float myVecteur2D::getydir() const{
	return ydir;
}

vertex myVecteur2D::getorigin() const {
	return origin;
}

void myVecteur2D::normalise(){
	if (xdir != 0.0f &&ydir != 0.0f)
	{
		float norm = sqrt(xdir*xdir + ydir*ydir);
		xdir = xdir / norm;
		ydir = ydir / norm;
	}
}

void myVecteur2D::afficherGL() const{
	glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(origin.x, origin.y);
		glVertex2f(origin.x + xdir, origin.y + ydir);
	glEnd();
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(origin.x + xdir, origin.y + ydir);
	glEnd();
}

void myVecteur2D::afficherGL(float alpha) const{
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(origin.x, origin.y);
	glVertex2f(origin.x + alpha*xdir, origin.y + alpha* ydir);
	glEnd();
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(origin.x + alpha* xdir, origin.y + alpha* ydir);
	glEnd();
}

float myVecteur2D::getNorme()const{
	return sqrt(xdir*xdir + ydir*ydir);
}

/*
DEFINITION DE cadre
*/

cadre::cadre(){}

cadre::cadre(myVecteur2D* a, myVecteur2D* b, myVecteur2D* c, myVecteur2D* d)   {
	bords[0] = a;
	bords[1] = b;
	bords[2] = c;
	bords[3] = d;
}

cadre::cadre(vertex a, vertex b, vertex c, vertex d)   {
	myVecteur2D* va;
	va = new myVecteur2D(b.x - a.x, b.y - a.y, a);
	myVecteur2D* vb;
	vb = new myVecteur2D(c.x - b.x, c.y - b.y, b);
	myVecteur2D* vc;
	vc = new myVecteur2D(d.x - c.x, d.y - c.y, c);
	myVecteur2D* vd;
	vd = new myVecteur2D(a.x - d.x, a.y - d.y, d);
	bords[0] = va;
	bords[1] = vb;
	bords[2] = vc;
	bords[3] = vd;
}

myVecteur2D* cadre::getBords(int i) const{
	return bords[i];
}

vertex cadre::getcoins(int i) const{
	return bords[i]->getorigin();
}

void cadre::afficherGL()const{
	glBegin(GL_LINES);
	for (int i = 0; i<3; i++){
		glVertex2f(getcoins(i).x, getcoins(i).y);
		glVertex2f(getcoins(i+1).x, getcoins(i + 1).y);
	}
	glVertex2f(getcoins(3).x, getcoins(3).y);
	glVertex2f(getcoins(0).x, getcoins(0).y);
	glEnd();
	//debug 
	//std::cout << "affichage du cadre" << std::endl;
}

void cadre::setBords(int i, myVecteur2D* vector){ // TODO : refermeture du cadre
	bords[i] = vector;
}

int cadre::getBordVise(myVecteur2D* vec) const{
	vertex intersection;
	int dir;
	int k;
	//debug
	int nbinter = 0;
	//
	int bord = -1; // cas où il n'y a pas de solution (ce qui ne devrait pas arriver)
	for (k = 0; k < 3; k++)
	{
		dir = intersectionDroites(vec, bords[k], intersection);
		if (dir > 0){
			if (appartientSegment(intersection, bords[k]->getorigin(), bords[k + 1]->getorigin()))
				bord = k;
			nbinter += 1;
		}
	}
		k = 3;
		dir = intersectionDroites(vec, bords[k], intersection);
		if (dir > 0){
			if (appartientSegment(intersection, bords[k]->getorigin(), bords[0]->getorigin()))
				bord = k;
			nbinter += 1;
	}
		//std::cout << "nombre d'intersections : " << nbinter << std::endl;
		return bord;
}




/*
DEFINTION DES FONCTIONS BOITE A OUTIL
*/


int intersectionDroites( myVecteur2D* v1, myVecteur2D* v2, vertex& sol) {
	

	if (produitVectoriel(v1, v2) == 0) // on exclut le cas où il n'y a pas de solution : vecteur colinéaires (inclus le vecteur nul)
		return 0;
	else
	{
		/*
		On pose l'égalité :
		|	Ax+t1*v1x = Bx+t2*v2x = xsol
		|	Ay+t1*v1y = By+t2*v2y = ysol
		*/


		float t1 = 0;
		float t2 = 0;

		if (v1->getxdir() != 0 && v2->getxdir() != 0 && v1->getydir() != 0 && v2->getydir()) {

			float k = v2->getxdir() / v2->getydir();

			t1 = (1 / (v1->getxdir() - k * v1->getydir())) * (v2->getorigin().x - v1->getorigin().x + k * (v1->getorigin().y - v2->getorigin().y)); //le diviseur est différent de zéro car les droites sont non colinéraires
			t2 = 1 / (v2->getxdir())*(v1->getorigin().x + t1* v1->getxdir() - v2->getorigin().x);

			//debug 
			//std::cout << "cas 1" << std::endl;
			
		}

		else if (v1->getxdir() == 0) //v2x !0 car ils seraient colinéaires (test OK)
		{
			t2 = 1 / v2->getxdir() * (v1->getorigin().x + t1 * v1->getxdir() - v2->getorigin().x);
			t1 = 1 / v1->getydir() * (v2->getorigin().y - v1->getorigin().y + t2* v2->getydir());
			//debug 
			//std::cout << "cas 2" << std::endl;
			//std::cout << v2->getydir() << std::endl;
		}
		else if (v1->getydir() == 0) // par symmétrie (réaliser des tests)
		{
			t2 = 1 / v2->getydir() * (v1->getorigin().y + t1* v1->getydir() - v2->getorigin().y);
			t1 = 1 / v1->getxdir() * (v2->getorigin().x - v1->getorigin().x + t2*v2->getxdir());
			//debug 
			//std::cout << "cas 3" << std::endl;
			
		}
		else if (v2->getydir() == 0) // par symmétrie (réaliser des tests)
		{
			t1 = 1 / v1->getydir() * (v1->getorigin().y + t2* v2->getxdir() - v2->getorigin().y);
			t2 = 1 / v2->getxdir() * (v2->getorigin().x - v1->getorigin().x + t1*v2->getxdir());
			//debug 
			//std::cout << "cas 4" << std::endl;
		}
		else if (v2->getxdir() == 0) // par symmétrie (réaliser des tests)
		{
			t1 = 1 / v1->getxdir() * (v1->getorigin().x + t2* v2->getydir() - v2->getorigin().x);
			t2 = 1 / v2->getydir() * (v2->getorigin().y - v1->getorigin().y + t1*v2->getydir());
			//debug 
			//std::cout << "cas 5" << std::endl;
		}


	// résultats
		sol.x = v1->getorigin().x + t1 * v1->getxdir();
		sol.y = v1->getorigin().y + t1 * v1->getydir();

	if (t1 >= 0)
		return 1;
	else
		return -1;
	}
}


float produitscalaire(myVecteur2D *v1, myVecteur2D *v2){

	return (v1->getxdir()*v2->getydir() + v1->getydir()*v2->getydir());


}

float produitVectoriel(myVecteur2D *v1, myVecteur2D* v2){
	return v1->getxdir()*v2->getydir() - v1->getydir()*v2->getxdir();
}

float distance(vertex A, vertex B){
	return sqrt((B.x - A.x)*(B.x - A.x) + (B.y - A.y)*(B.y - A.y));
}

/*
bool appartientSegment(vertex pointCible, vertex A, vertex B){ //NE FONCTIONNE PAS
	float d1 = distance(pointCible, A);
	float d2 = distance(A, B);
	std::cout << "d1 :" << d1 << " d2 : " << d2<< std::endl;
	if (d1 > d2)
		return true;
	else
		return false;
}
*/
bool appartientSegment(vertex pointCible, vertex A, vertex B){
	float t1 = pointCible.x * (1 / (A.x - B.x)) * pointCible.x;
	std::cout << "t1 :" << t1  << std::endl;
	if (t1<1 && t1>0 )
	{
		return true;
	}
	else return false;

}