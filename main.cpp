//
//  main.cpp
//  ANREC_OGL_FirstEx
//
//  Created by Jean-Marie Normand on 24/09/2014.
//  Copyright (c) 2014 Centrale Innovation. All rights reserved.
//

#include <time.h>
#include "BoiteAOutil.h"
#include "trajectoire.h"
#include "boule.h"

using namespace std;




/*

TODO

*/



// Création des sommets du contour
vertex contour[4] =
{
	{ 0.90f,1.1f },
	{ 1.15f, -1.2f },
	{ -1.0f, -1.3f },
	{ -1.4f, 1.2f },

};

// Création des faces du cube



// Quelques variables globales (c'est pas bien)
GLfloat pointSize = 1.0f;

// Rotations autour de X et Y


// Taille de la fenêtre
int windowW = 740;
int windowH = 780;
float focale = 65.0f;
//float near = 0.1f;
//float far = 100.0f;

// Déclarations des fonctions de rappel (callbacks)
GLvoid affichage();
//GLvoid clavier(unsigned char touche, int x, int y);
//GLvoid souris(int bouton, int etat, int x, int y);
GLvoid deplacementSouris(int x, int y);
GLvoid redimensionner(int w, int h);
GLvoid time();

float t = 0.2;
float offset = 0.1;


// Definition de la fonction d'affichage
GLvoid affichage(){
	
	system("cls");
	//création d'un vecteur test
	//cout << "1" << endl;
	myVecteur2D* v1;
	// t varie avec la touche 8 enfoncée
	v1 = new myVecteur2D(5*cos(t), 5*sin(t));
	//cout << "2 : "<<v1->getNorme() << endl;
	v1->normalise();
	//cout << "3 : " << v1->getNorme() << endl;
	vertex v1or = { 0.0f, 0.0f };
	v1->setorigin(v1or);
	
	cadre* cadreJeu;
	cadreJeu = new cadre(contour[0], contour[1], contour[2], contour[3]);

	
	

	// Effacement du frame buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	// Animation du cube!
	glLoadIdentity();
	//glRotatef(-angleY, 1.0f, 0.0f, 0.0f);
	//glRotatef(-angleX, 0.0f, 1.0f, 0.0f);

	
	//on bouge la camera
	glTranslatef(0.0, 0.0, -3.0);
		
	glColor3f(1.0f, 1.0f, 1.0f);
	cadreJeu->afficherGL();


	// rebonds etc
		
	
		
		//tracé des vecteurs
		v1->afficherGL(0.2f);
		//vr->afficherGL();
		
		int idbord = 0;
		cadreJeu->afficherVecteursGL();
		cadreJeu->afficherGL();

				//REBONDS

		//trajectoire* t1;
		//t1 = new trajectoire(v1, cadreJeu, 3);
		//t1->afficherGL();
				
				
		//boules

		vertex vb = { 0.4f, 0.4f };
		boule* b1;
		b1 = new boule(0.2f, vb);
		glLineWidth(1.0f);
		b1->afficherGL();
		
		
		

		
	glFlush();
	glutSwapBuffers();

	delete cadreJeu;
	delete v1;
	delete b1;
	
	

}

// Definition de la fonction gerant les interruptions clavier

GLvoid clavier(unsigned char touche, int x, int y) {

	// Suivant les touches pressees, nous aurons un comportement different de l'application
	// ESCAPE ou 'q' : fermera l'application
	// 'p' : affichage du carre plein
	// 'f' : affichage du carre en fil de fer
	// 's' : affichage des sommets du carre

	switch (touche) {
	case 'p': // carre plein
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'f': // fil de fer
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 's': // sommets du carre
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;

		// Gestion du tampon de profondeur
	case 'd':
		glEnable(GL_DEPTH_TEST);
		glutPostRedisplay();
		break;
	case 'D':
		glDisable(GL_DEPTH_TEST);
		glutPostRedisplay();
		break;

	case '+':
		// Augmenter la taille des sommets affiches
		pointSize += 1.0f;
		glPointSize(pointSize);
		break;
	case '-':
		// Augmenter la taille des sommets affiches
		pointSize -= 1.0f;
		if (pointSize <= 0.0f)
			pointSize = 1.0f;
		glPointSize(pointSize);
		break;
	case '8':
		t += offset;
		break;



	case 'q': // quitter
	case 27:
		exit(0);
		break;
	}

	// Demande a GLUT de reafficher la scene
	glutPostRedisplay();
}

//animation
GLvoid time(){
	
}


// Fonction de rappel de la souris
/*
GLvoid souris(int bouton, int etat, int x, int y){
	// Test pour voir si le bouton gauche de la souris est appuyé
	if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
		boutonClick = true;
		oldX = x;
		oldY = y;
	}

	// si on relache le bouton gauche
	if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
		boutonClick = false;
	}
}
*/
/*
GLvoid deplacementSouris(int x, int y) {
	// si le bouton gauche est appuye et qu'on se deplace
	// alors on doit modifier les angles de rotations du cube
	// en fonction de la derniere position de la souris 
	// et de sa position actuelle
	if (boutonClick) {
		angleX += (x - oldX);
		angleY += (y - oldY);
		// Appeler le re-affichage de la scene OpenGL
		glutPostRedisplay();
	}

	// Mise a jour des anciennes positions de la souris en X et Y
	oldX = x;
	oldY = y;
}
*/
//c'est ici pour la 2D
// Callback de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {
	// Garde les valeurs
	windowW = w;
	windowH = h;
	// eviter une division par 0
	if (windowH == 0)
		windowH = 1;

	float ratio = (float)windowW / (float)windowH;
	std::cout << "Ratio : " << ratio << std::endl;

	// Projection
	glMatrixMode(GL_PROJECTION);

	// Resetting matrix
	glLoadIdentity();

	// Viewport
	glViewport(0, 0, windowW, windowH);

	// Mise en place de la perspective
	gluPerspective(focale, ratio, 0.1, 100);


	// Placement de la caméra
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

	// Retourne a la pile modelview
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char *argv[])
{  
	// Initialisation de GLUT
	glutInit(&argc, argv);
	// Choix du mode d'affichage (ici RVB)
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	// Position initiale de la fenetre GLUT
	glutInitWindowPosition(200, 200);
	// Taille initiale de la fenetre GLUT
	glutInitWindowSize(windowW, windowH);
	// Creation de la fenetre GLUT
	glutCreateWindow("Cube3D");

	// Définition de la couleur d'effacement du framebuffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Initialement on desactive le Z-buffer
	glDisable(GL_DEPTH_TEST);

	// Définition des fonctions de callbacks
	glutDisplayFunc(affichage);
	glutKeyboardFunc(clavier);
	
	// Nouveaux callbacks
	//glutMouseFunc(souris);
	//glutMotionFunc(deplacementSouris);
	glutReshapeFunc(redimensionner);

	// Lancement de la boucle infinie GLUT
	glutMainLoop();

	return 0;
}



/*
sauvegarde
*/

/*
cout << "nb bords" << cadreJeu->getBords().size() << endl;
for (int j = 0; j < cadreJeu->getBords().size(); j++){
int l = j+1;
if (l > 3)
{
l = 0;
}
vertex* inter;
inter = new vertex;
int dir = intersectionDroites(v1, cadreJeu->getBords(j), *inter);

if (dir > 0 && appartientSegment(*inter, cadreJeu->getBords(j)->getorigin(), cadreJeu->getBords(l)->getorigin()))
{
glPointSize(10);
glBegin(GL_POINTS);
glColor3f(1.0f, 0.0f, 0.0f);
glVertex2f(inter->x, inter->y);
glEnd();
//retenir le bord sur lequel le rayon rebondi
idbord = j;
myVecteur2D* vr;
vr = new myVecteur2D(v1, cadreJeu->getBords(j)); std::cout << " main inter  x : " << inter->x << "  y : " << inter->y << std::endl;
cout << "main vr : " << " x : " << vr->getxdir() << " y : " << vr->getydir() << " origin : " << vr->getorigin().x << " | " << vr->getorigin().y << endl;

vr->afficherGL(0.2f);

*/