#include "BoiteAOutil.h"



/*
DEFINTION DE myVecteur2D
*/

myVecteur2D::myVecteur2D(){}

myVecteur2D::myVecteur2D(float x, float y) {
	xdir = x;
	ydir = y;
	normalise();
}
myVecteur2D::myVecteur2D(float x, float y, vertex point) :  origin(point){
	xdir = x;
	ydir = y;
	normalise();
}
/*
myVecteur2D::myVecteur2D(myVecteur2D* v1, myVecteur2D* v2){ // cr�er un rebond : premier vecteur sur le deuxi�me

	vertex originrebond;
	originrebond.x = 0;
	originrebond.y = 0;

	int sens;

	sens = intersectionDroites(v1, v2, originrebond);

	if (sens > 0)
	{
	v1->normalise();
	v2->normalise();
	std::cout << "V1 : " << v1->getNorme() << "  v2 : " << v2->getNorme() << " v1x : " << v1->getxdir() << " v1y : " << v1->getydir() << " v2x : " << v2->getxdir() << " v2y : " << v2->getydir() << std::endl;

	//std::cout << "ps : " << produitscalaire(v1, v2) << std::endl;
		float alpha = acos(abs(produitscalaire(v1, v2))); // TODO : prendre en compte la valeur n�gative ou poistive de l'angle
		
		
		
		//if (produitscalaire(v1, v2) < 0)
			alpha = -alpha;
		std::cout << "alpha : " << alpha << " deg " << alpha * 360 / (2 * 3.14f) << std::endl;

		vertex dirOrtho; //d�fini le vecteur orthogonal au vecteur v2
		dirOrtho.x =  v2->getydir();
		dirOrtho.y = - v2->getxdir();
		this -> origin = originrebond;
		this -> xdir = cos(alpha)*v2->getxdir() + sin(alpha)*dirOrtho.x;
		this -> ydir = sin(alpha)*dirOrtho.y + sin(alpha) * v2->getydir();
		
		//xdir = dirOrtho.x;
		//ydir = dirOrtho.y;
		std::cout << "vec : " << getNorme() << std::endl;
		this -> normalise();
		std::cout << "vec : " << getNorme() << std::endl;
	}
	else
	{

	}
	

}
*/

myVecteur2D::myVecteur2D(myVecteur2D* v1, myVecteur2D* v2){ // cr�er un rebond : premier vecteur sur le deuxi�me

	vertex originrebond;
	originrebond.x = 0;
	originrebond.y = 0;

	int sens;

	sens = intersectionDroites(v1, v2, originrebond);


	if (sens > 0)
	{
		v1->normalise();
		v2->normalise();
		//std::cout << "V1 : " << v1->getNorme() << "  v2 : " << v2->getNorme() << " v1x : " << v1->getxdir() << " v1y : " << v1->getydir() << " v2x : " << v2->getxdir() << " v2y : " << v2->getydir() << std::endl;
		
		vertex dirOrtho;
		dirOrtho.x =  v2->getydir();
		dirOrtho.y = - v2->getxdir();

		float psv12 = produitscalaire(v1,v2); //produit scalaire de v1 sur v2
		float psv12ortho = v1->getxdir() * dirOrtho.x + v1->getydir() * dirOrtho.y;

		

		xdir = psv12*v2->getxdir() - psv12ortho * dirOrtho.x;
		ydir = psv12*v2->getydir() - psv12ortho * dirOrtho.y;
		origin = originrebond;

		//std::cout << "psv12 : " << psv12 << "  ortho " << psv12ortho << "xdir : " << xdir << "direct " << psv12*v2->getxdir() + psv12ortho * dirOrtho.x<< std::endl;

		normalise();
		
	}
	else
	{

	}


}

/*
void myVecteur2D::setRebond(myVecteur2D* v1, myVecteur2D* v2){ // cr�er un rebond : premier vecteur sur le deuxi�me

	vertex originrebond;
	originrebond.x = 0;
	originrebond.y = 0;

	int sens;

	sens = intersectionDroites(v1, v2, originrebond);

	//if (sens > 0)
	//{
	v1->normalise();
	v2->normalise();
	std::cout << "V1 : " << v1->getNorme() << "  v2 : " << v2->getNorme() << std::endl;

	std::cout << "ps : " << produitscalaire(v1, v2) << std::endl;
	float alpha = acos(abs(produitscalaire(v1, v2))); // TODO : prendre en compte la valeur n�gative ou poistive de l'angle


	if (produitVectoriel(v1, v2) < 0)
		alpha = -alpha;
	std::cout << "alpha : " << alpha << std::endl;

	vertex dirOrtho; //d�fini le vecteur orthogonal au vecteur v2
	dirOrtho.x = -v2->getydir();
	dirOrtho.y = v2->getxdir();
	this->origin = originrebond;
	this->xdir = cos(alpha)*v2->getxdir() + sin(alpha)*dirOrtho.x;
	this->ydir = sin(alpha)*dirOrtho.y + sin(alpha) * v2->getydir();

	//xdir = dirOrtho.x;
	//ydir = dirOrtho.y;
	std::cout << "vec : " << getNorme() << std::endl;
	this->normalise();
	std::cout << "vec : " << getNorme() << std::endl;
	/*}
	else
	{

	}
	

}
*/
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
	if (getNorme()==0)
	{
		std::cout << "vecteur nul" << std::endl;
	}
	else 
	{ 
		float norm = sqrt(abs(xdir*xdir + ydir*ydir));
		xdir = xdir / norm;
		ydir = ydir / norm;
		std::cout << "vecteur non nul : "<< getNorme() << std::endl;
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
	bords.push_back(a);
	bords.push_back(b);
	bords.push_back(c);
	bords.push_back(d);
	
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
	bords.push_back(va);
	bords.push_back(vb);
	bords.push_back(vc);
	bords.push_back(vd);
}

myVecteur2D* cadre::getBords(int i) const{
	return bords[i];
}

vertex cadre::getcoins(int i) const{
	return bords[i]->getorigin();
}

void cadre::afficherVecteursGL()const{
	
	//for (std::vector<myVecteur2D*>::iterator it = bords.begin(); it != bords->end(); ++it){
		//(*it)->afficherGL();
	//}

	for (int i = 0; i < bords.size(); i++)
	{
		bords[i]->afficherGL(0.3f);
	}

	/*glBegin(GL_LINES);
	for (int i = 0; i<3; i++){
		glVertex2f(getcoins(i).x, getcoins(i).y);
		glVertex2f(getcoins(i+1).x, getcoins(i + 1).y);
	}
	glVertex2f(getcoins(3).x, getcoins(3).y);
	glVertex2f(getcoins(0).x, getcoins(0).y);
	glEnd();*/
	//debug 
	//std::cout << "affichage du cadre" << std::endl;
}

void cadre::afficherGL() const{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	for (int i = 0; i<3; i++){
		glVertex2f(getcoins(i).x, getcoins(i).y);
		glVertex2f(getcoins(i + 1).x, getcoins(i + 1).y);
	}
	glVertex2f(getcoins(3).x, getcoins(3).y);
	glVertex2f(getcoins(0).x, getcoins(0).y);
	glEnd();
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
	int bord = -1; // cas o� il n'y a pas de solution (ce qui ne devrait pas arriver)
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

std::vector<myVecteur2D*> cadre::rebonds(myVecteur2D* v ,int nb)const{
	std::vector<myVecteur2D*> result;
	myVecteur2D* tmp;
	tmp = v;
	for (int i = 0; i < nb; i++)
	{

		for (int j = 0; j < bords.size(); j++){
			int l = j + 1;
			if (l > 3)
			{
				l = 0;
			}
			vertex* inter;
			inter = new vertex;
			int dir = intersectionDroites(tmp, getBords(j), *inter);
			if (dir > 0 && appartientSegment(*inter, getBords(j)->getorigin(), getBords(l)->getorigin()))
			{
				myVecteur2D* vr;
				vr = new myVecteur2D(tmp, getBords(j));
				vr->setorigin(*inter);
				result.push_back(vr);
				tmp = vr;
				std::cout << "vr : " << " x : " << vr->getxdir() << " y : " << vr->getydir() << " origin : " << vr->getorigin().x << " | " << vr->getorigin().y << std::endl;
			}
			
		}
	}
	return result;
}


/*
DEFINTION DES FONCTIONS BOITE A OUTIL
*/


int intersectionDroites( myVecteur2D* v1, myVecteur2D* v2, vertex& sol) {
	

	if (produitVectoriel(v1, v2) == 0) // on exclut le cas o� il n'y a pas de solution : vecteur colin�aires (inclus le vecteur nul)
		return 0;
	else
	{
		/*
		On pose l'�galit� :
		|	Ax+t1*v1x = Bx+t2*v2x = xsol
		|	Ay+t1*v1y = By+t2*v2y = ysol
		*/


		float t1 = 0;
		float t2 = 0;

		if (v1->getxdir() != 0 && v2->getxdir() != 0 && v1->getydir() != 0 && v2->getydir()) {

			float k = v2->getxdir() / v2->getydir();

			t1 = (1 / (v1->getxdir() - k * v1->getydir())) * (v2->getorigin().x - v1->getorigin().x + k * (v1->getorigin().y - v2->getorigin().y)); //le diviseur est diff�rent de z�ro car les droites sont non colin�raires
			t2 = 1 / (v2->getxdir())*(v1->getorigin().x + t1* v1->getxdir() - v2->getorigin().x);

			//debug 
			//std::cout << "cas 1" << std::endl;
			
		}

		else if (v1->getxdir() == 0) //v2x !0 car ils seraient colin�aires (test OK)
		{
			t2 = 1 / v2->getxdir() * (v1->getorigin().x + t1 * v1->getxdir() - v2->getorigin().x);
			t1 = 1 / v1->getydir() * (v2->getorigin().y - v1->getorigin().y + t2* v2->getydir());
			//debug 
			//std::cout << "cas 2" << std::endl;
			//std::cout << v2->getydir() << std::endl;
		}
		else if (v1->getydir() == 0) // par symm�trie (r�aliser des tests)
		{
			t2 = 1 / v2->getydir() * (v1->getorigin().y + t1* v1->getydir() - v2->getorigin().y);
			t1 = 1 / v1->getxdir() * (v2->getorigin().x - v1->getorigin().x + t2*v2->getxdir());
			//debug 
			//std::cout << "cas 3" << std::endl;
			
		}
		else if (v2->getydir() == 0) // par symm�trie (r�aliser des tests)
		{
			t1 = 1 / v1->getydir() * (v1->getorigin().y + t2* v2->getxdir() - v2->getorigin().y);
			t2 = 1 / v2->getxdir() * (v2->getorigin().x - v1->getorigin().x + t1*v2->getxdir());
			//debug 
			//std::cout << "cas 4" << std::endl;
		}
		else if (v2->getxdir() == 0) // par symm�trie (r�aliser des tests)
		{
			t1 = 1 / v1->getxdir() * (v1->getorigin().x + t2* v2->getydir() - v2->getorigin().x);
			t2 = 1 / v2->getydir() * (v2->getorigin().y - v1->getorigin().y + t1*v2->getydir());
			//debug 
			//std::cout << "cas 5" << std::endl;
		}


	// r�sultats
		sol.x = v1->getorigin().x + t1 * v1->getxdir();
		sol.y = v1->getorigin().y + t1 * v1->getydir();

	if (t1 >= 0)
		return 1;
	else
		return -1;
	}
}


float produitscalaire(myVecteur2D* v1, myVecteur2D* v2){

	float result = ( ( ( v1->getxdir() )*( v2->getxdir() ) +  (v1->getydir() ) * (v2->getydir() ) ) );

	//debug
	//std::cout << " ps : " << result << std::endl;
	return result;


}

float produitVectoriel(myVecteur2D *v1, myVecteur2D* v2){
	return v1->getxdir()*v2->getydir() - v1->getydir()*v2->getxdir();
}

float distance(vertex A, vertex B){
	return sqrt((B.x - A.x)*(B.x - A.x) + (B.y - A.y)*(B.y - A.y));
}


bool appartientSegment(vertex pointCible, vertex A, vertex B){

	if (A.x !=B.x && A.y != B.y)
	{
		float t1 = (pointCible.x - +B.x) * (1 / (A.x - B.x));
		//std::cout << "t1 x :" << t1 << std::endl;

		float t2 = (pointCible.y - B.y) * (1 / (A.y - B.y)) ;
		//std::cout << "t2 y :" << t2 << std::endl;

		if ((t2 < 1 && t2>0) )//&& egalerr( t1 , t2))
		{
			return true;
		}
		else return false;
	}

	else if (A.x == B.x)
	{

		float t2 = (pointCible.y - B.y) * (1 / (A.y - B.y));
		//std::cout << "t2 y :" << t2 << std::endl;

		if (t2 < 1 && t2>0 )// && egalerr(pointCible.x , A.x)  )
			return true;
		else
			return false;

	}

	else if (A.y == B.y)
	{
		float t1 = (pointCible.x - B.x) * (1 / (A.x - B.x));
		//std::cout << "t1 x :" << t1 << std::endl;
		

		if (t1 < 1 && t1>0 ) //&& egalerr(pointCible.y , A.y) )
			return true;
		else
			return false;

	}
}

bool egalerr(float x, float y){
	if (x < (y + M_ERR) && x > (y - M_ERR)){
		return true;
	}
	else return false;
}

void afficherRebondsGL(std::vector<myVecteur2D*> rebonds){
	for (int i = 0; i < rebonds.size(); i++)
	{
		int l = i + 1;
		if (l >= rebonds.size())
			l = 0;
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex2f( rebonds.at(i)->getorigin().x, rebonds.at(i)->getorigin().y);
		std::cout << "it : " << i << std::endl;
		glEnd();
	}
}