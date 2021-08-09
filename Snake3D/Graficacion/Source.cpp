#include<GL/freeglut.h>
#include <stdlib.h>
#include<iostream>
#include <string.h>
#include <Windows.h>
#include <windows.h>
#include<time.h>
#include<list>
#include<vector>
#define FPS 10


struct snake {
	int x;
	int y;

};
int initial_time = time(NULL), final_time, frame_count = 0;
int velx = 0, vely = 0;
bool generarComida = true;
int cx = 1, cy = 1;
int puntaje = 0;
std::vector<snake> vBody;
snake mySnake;

void theFood(int x, int z) {
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(x, 0, z);
	glutSolidSphere(0.4, 100, 100);
	glPopMatrix();
}
void theCube(int x, int z) {
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(x, 0, z);
	glutSolidCube(0.4);
	glPopMatrix();
}

void comida() {

	//std::cout << "generando comida";
	srand(time(NULL));
	if (cx == mySnake.x && cy == mySnake.y) {
		generarComida = true;
		puntaje++;
		vBody.push_back(mySnake);
	}
	if (generarComida) {
		cx = rand()%19;
		cy = rand()%19;
	}
	theFood(cx, cy);
	generarComida = false;

}


void drawGrid() {
	int i;
	for (i = 0; i < 40; i++) {
		glPushMatrix();
		if (i < 20)
			glTranslatef(0, 0, i);
		if (i >= 20) {
			glTranslatef(i - 20, 0, 0);
			glRotatef(-90, 0, 1, 0);
		}
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glLineWidth(1);
		glVertex3f(0, -0.1, 0);
		glVertex3f(19, -0.1, 0);
		glEnd();
		glPopMatrix();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-13, 0, -45);
	glRotatef(40, 1, 1, 0);
	drawGrid();
	comida();
	std::rotate(vBody.begin(), vBody.begin() + 1, vBody.end());

	mySnake.x = mySnake.x + velx;
	mySnake.y = mySnake.y + vely;
	vBody[0] = mySnake;

	for (int i = 1; i < vBody.size(); i++) {
		if (mySnake.x == vBody[i].x && mySnake.y == vBody[i].y) {
			glutLeaveMainLoop();
		}
	}
	if (mySnake.x == 19 || mySnake.x < 0 || mySnake.y == 19 || mySnake.y < 0) {
		glutLeaveMainLoop();
	}
	
	
	for (int i = 0; i < vBody.size(); i++) {

		theCube(vBody[i].x, vBody[i].y);
	}

	glutSwapBuffers();

	frame_count++;
	final_time = time(NULL);
	if (final_time - initial_time > 0) {
		std::cout << "Fps: " << frame_count / (final_time - initial_time) << std::endl;
		frame_count = 0;
		initial_time = final_time;
	}

}



void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0f, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.1, 0.1, 1);
	mySnake = { 0,0 };
	vBody.push_back(mySnake);
}
void update(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, update, 0);
}
void teclado(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 'w':
		vely = -1;
		velx = 0;
		break;
	case 'a':
		vely = 0;
		velx = -1;
		break;
	case 's':
		vely = 1;
		velx = 0;
		break;
	case 'd':
		vely = 0;
		velx = 1;
		break;
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	//glutInitWindowPosition(200, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Graficacion");

	glutDisplayFunc(display);
	glutTimerFunc(1000 / FPS, update, 0);
	glutKeyboardFunc(teclado);
	init();
	glutMainLoop();
	return 0;
}