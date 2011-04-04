#include <cstdlib>

#include "GameController.h"
GameController game;
/* GLUT callback Handlers */



void resize(int width, int height)
{
	const float ar = (float) width / (float) height;
	// Set up the 3D projection
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 60, ar, 1, 700);
	// Move the camera back a bit to see the scene
	glTranslatef( 0, 0, -20 );
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity() ;
}

static void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw the field
	glColor3d(0,0.7,0);
	glPushMatrix();
	glTranslated(0,-2,0);
	glScaled(100,0.01,100);
	glutSolidCube(1);
	glPopMatrix();

	//Draw the goal post
	glColor3d(0.1,0.1,0.1);
	glPushMatrix();
	glTranslated(0,0,-20);
	glScaled(10,30,0.1);
	glutSolidCube(1);
	glPopMatrix();

	game.update(); 

	glutSwapBuffers();

}


static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27 :
		case 'q':
			exit(0);
			break;
	}
	game.handle_key( key, x, y );
	glutPostRedisplay();
}

static void idle(void)
{
	glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(10,10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// Set up the 3D projection
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 60, 640/480, 1, 700);
	// Move the camera back a bit to see the scene
	glTranslatef( 0, 0, -20 );
	glMatrixMode(GL_MODELVIEW);

	glutCreateWindow("Ultimate Football");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glClearColor(1,1,1,1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glutMainLoop();

	return EXIT_SUCCESS;
}
