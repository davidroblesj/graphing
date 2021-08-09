#include<GL/freeglut.h>
#include <stdlib.h>
#include<iostream>
#include <string.h>
#include <Windows.h>
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
std::vector<snake> vBody;
snake mySnake;


void comida() {

	//std::cout << "generando comida";
	srand(time(NULL));
	if (cx == mySnake.x && cy == mySnake.y) {
		generarComida = true;
		vBody.push_back(mySnake);
	}
	if (generarComida) {
		cx = rand() % 9 - 9;
		cy = rand() % 9 - 9;

	}


	glBegin(GL_POINTS);
	glColor3f(1.0, 0, 0);
	glVertex2f(cx, cy);

	glEnd();

	generarComida = false;

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glPointSize(20.0);
	comida();

	std::rotate(vBody.begin(), vBody.begin() + 1, vBody.end());

	mySnake.x = mySnake.x + velx;
	mySnake.y = mySnake.y + vely;
	vBody[0] = mySnake;
	for (int i = 1; i < vBody.size(); i++) {

		if (mySnake.x == vBody[i].x && mySnake.y == vBody[i].y)
			glutLeaveMainLoop();



	}
	if (mySnake.x == -10)
		mySnake.x = 10;
	else if (mySnake.x == 10)
		mySnake.x = -10;
	if (mySnake.y == 10)
		mySnake.y = -10;
	else if (mySnake.y == -10)
		mySnake.y = 10;




	for (int i = 0; i < vBody.size(); i++) {
		glBegin(GL_POINTS);
		glColor3f(0, 1.0, 0);
		glVertex2f(vBody[i].x, vBody[i].y);
		glEnd();

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

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);

}
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
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
		vely = 1;
		velx = 0;
		break;
	case 'a':
		vely = 0;
		velx = -1;
		break;
	case 's':
		vely = -1;
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Graficacion");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / FPS, update, 0);
	glutKeyboardFunc(teclado);

	glutMainLoop();
}