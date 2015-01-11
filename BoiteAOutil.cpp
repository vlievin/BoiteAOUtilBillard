#include "BoiteAOutil.h"
#include "boule.h"



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
myVecteur2D::myVecteur2D(myVecteur2D* v1, myVecteur2D* v2){ // créer un rebond : premier vecteur sur le deuxième

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
		float alpha = acos(abs(produitscalaire(v1, v2))); // TODO : prendre en compte la valeur négative ou poistive de l'angle



		//if (produitscalaire(v1, v2) < 0)
			alpha = -alpha;
		std::cout << "alpha : " << alpha << " deg " << alpha * 360 / (2 * 3.14f) << std::endl;

		vertex dirOrtho; //défini le vecteur orthogonal au vecteur v2
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

myVecteur2D::myVecteur2D(myVecteur2D* v1, myVecteur2D* v2){ // créer un rebond : premier vecteur sur le deuxième

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
//on ne crée rien
	}


}

myVecteur2D::myVecteur2D(myVecteur2D* v1 , boule* b , float r ){

// voir http://fr.wikipedia.org/wiki/Billard

    vertex inter;
    bool binter = b->getIntersection(v1 , r , inter);
    std::cout << " In BoiteAOutil : constructeur rebondboule : intersection : (" << inter.x << " | " << inter.y << ")   r : "<< r
    <<  "centre de b : " << b->getCentre().x << " | " << b->getCentre().y << std::endl;
    if (binter)
    {

        origin = inter;

        ydir = b->getCentre().x - inter.x;
        xdir = - ( b->getCentre().y - inter.y );
        //utilisation du produit mixte pour déterminer le sens de rebond
        float pmixte = ((inter.x - v1->getorigin().x )* (b->getCentre().y - v1->getorigin().y ))
        - ((inter.y - v1->getorigin().y ) * (b->getCentre().x - v1->getorigin().x ));
        std::cout << " in constructeur rebond boule : pmixte : " << pmixte << std::endl;
        if (pmixte > 0)
        {
        xdir = - xdir;
        ydir = - ydir;
        }


    }
    else
    {
    //on ne crée rien
    }


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
	if (getNorme()==0)
	{
		std::cout << "vecteur nul" << std::endl;
	}
	else
	{
		float norm = sqrt(xdir*xdir + ydir*ydir);
		float a = xdir / norm;
		float b = ydir / norm;
		xdir = a;
		ydir = b;
		//std::cout << "vecteur non nul : "<< getNorme() << std::endl;
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

bool myVecteur2D::isEgal(myVecteur2D* v) const{
	if (xdir == v->getxdir() && ydir == v->getydir())
		return true;
	else return false;
}

bool myVecteur2D::isNul()const{
	if (xdir == 0 && ydir == 0)
		return true;
	else return false;
}

/*
DEFINITION DE cadre
*/

cadre::cadre(){}
/*
cadre::cadre(myVecteur2D* a, myVecteur2D* b, myVecteur2D* c, myVecteur2D* d)   {
	bords.push_back(a);
	bords.push_back(b);
	bords.push_back(c);
	bords.push_back(d);

}
*/
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

std::vector<myVecteur2D*> cadre::getBords()const{
	return bords;
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

void cadre::setBords(int i, myVecteur2D* vector){ // TODO : refermeture automatique du cadre
	bords[i] = vector;
}

int cadre::getBordVise(myVecteur2D* vec) const{
	vertex intersection;
	int dir;
	int k;
	//debug
	int nbinter = 0;
	int l = 0;
	//
	int bord = -1;
	//std::cout << "in : getBordsVise : taille du vecteur bords : " << bords.size() << std::endl;
	for (k = 0; k < bords.size(); ++k)
	{
		l = k+1;
		if (l >= bords.size())
		{
			l = 0;
		}
		dir = intersectionDroites(vec, bords[k], intersection);
		if (dir > 0){
			if (appartientSegment(intersection, bords[k]->getorigin(), bords[l]->getorigin()))
			{
				bord = k;
				nbinter += 1;
				//std::cout << "in : getBordsVise : intersections : k : " << k << std::endl;
			}
		}
	}

		//std::cout << "in : getBordsVise : nombre d'intersections : " << nbinter << std::endl;
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

int intersectionDroiteBoule(myVecteur2D* v1 , myVecteur2D* v2, float r , vertex& sol){ // v2 représente le vecteur directeur d'un bord

int result = intersectionDroites(v1, v2, sol); // on utilise la fonction précédente

float vxortho = - v2->getydir();
float vyortho = v2->getxdir();

if (vxortho !=0 && vyortho != 0 )
{
    float abs = sqrt(vxortho*vxortho + vyortho*vyortho);
    vxortho =  vxortho / abs;
    vyortho =  vyortho / abs;

    //prendre en compte les sens des vecteurs à l'aide du produit scalaire

    float ps2 = v1->getxdir() * vxortho + v1->getydir() * vyortho;
    if(ps2>0 ){
    vxortho = -vxortho;
    vyortho = -vyortho;
    }

    //std::cout << "# in intersectionDroiteBoule : vortho : " << vxortho << " | " << vyortho << " ps2 : " << ps2 <<std::endl;

}
else { std::cout << "in intersectionDroiteBoule : vortho est nul "<<std::endl; }

sol.x += r * vxortho;
sol.y += r * vyortho;

return result;


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

float distancePoints(vertex A, vertex B){
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
	else return false;
	std::cout << " in function appartient au segment : aucune condition n'est validée " << std::endl;
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

vertex operator+(vertex const& a, myVecteur2D* const& b){
	vertex result;
	result.x = a.x + b->getxdir();
	result.y = a.y + b->getydir();
	return result;
}

void afficherGL(vertex point){
	glEnd();
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(point.x, point.y);
	glEnd();

}

std::vector<double> solvePoly2(double a, double b, double c){

	std::vector<double> result;
	result.clear();

	double delta = b*b - 4 * a*c;

	if (a != 0) // si le polynome est de degré 2
	{

		if (delta < 0)
		{
			return result; // retourne un vecteur nul (pas de solutions)
		}
		else if (delta == 0)
		{
			double tmp = -b / ( 2 * a);
			result.push_back(tmp);
			return result;
		}
		else
		{
			double tmp = (-b + sqrt(delta)) / (2 * a);
			result.push_back(tmp);
			tmp = (- b - sqrt(delta)) / (2 * a);
			result.push_back(tmp);

			return result;
		}

	}
	else // a = 0
		if (b == 0)
			return result;
		else
		{
			result.push_back((-c) / b);
			return result ;
		}
}
