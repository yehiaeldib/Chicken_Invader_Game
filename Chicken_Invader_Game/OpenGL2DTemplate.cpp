#include<iostream>
using namespace std;


#include <glut.h>
#include<queue>


queue<int> xBullet;
queue<int> yBullet;

int playerColor = 0;

bool PowerUp = false;

int playerHealth = 3;

int enemyHealth = 500;

int keyX = -80;
int keyY = 0;

int enemyBulletX = 0;
int enemyBulletY = 0;
int powerCount = 5;

int enemyX = 0;

bool f = true;
int powerX = (rand() % (500 - 20)) + 20;
int powerY = (rand() % (150 - 30)) + 30;




void time(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{


	if (PowerUp == true) {
		powerCount--;
	}

	if (powerCount == 0) {
		PowerUp = false;
		playerColor = 0;
	}



	glutPostRedisplay();
	glutTimerFunc(1000, time, 0);
}






void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

void actM(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)//if the left button has been clicked it shoot a bullet
	{
		int x = 260 + keyX;
		int y = 160 + keyY;
		xBullet.push(x);
		yBullet.push(y);

	}

	glutPostRedisplay();
}


void Anim(int value) {

	if (enemyX == 200)
		f = false;
	if (enemyX == -200)
		f = true;
	if (f)
		enemyX += 1;
	else
		enemyX -= 1;



	int len = xBullet.size();
	for (int i = 0; i < len; i++) {
		int y = yBullet.front();
		int x = xBullet.front();
		if (((x >= 240 + enemyX && x <= 260 + enemyX) && (y >= 220 && y <= 240)) || ((x >= 230 + enemyX && x <= 270 + enemyX) && (y >= 180 && y <= 220)) || ((x >= 220 + enemyX && x <= 280 + enemyX) && (y >= 200 && y <= 205)) || ((x == 240) && (y >= 165 && y <= 182)) || ((x == 260) && (y >= 165 && y <= 182))) {
			enemyHealth -= 10;
			xBullet.pop();
			yBullet.pop();
		}
		else if (y > 245) {

			xBullet.pop();
			yBullet.pop();

		}
		else {

			y += 5;
			xBullet.pop();
			xBullet.push(x);
			yBullet.pop();
			yBullet.push(y);

		}
	}

	glutPostRedisplay();

	glutTimerFunc(10, Anim, 0);
}



void Display() {



	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(1, 1, 1, 0);


	if (enemyHealth > 50 && (playerHealth != 0)) {
		glPushMatrix();
		glColor3f(0, playerColor, 0);
		glTranslated(keyX, keyY, 0);
		//player
		glBegin(GL_QUADS);
		glVertex3d(250, 120, 0);
		glVertex3d(250, 140, 0);
		glVertex3d(270, 140, 0);
		glVertex3d(270, 120, 0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3d(250, 140, 0);
		glVertex3d(270, 140, 0);
		glVertex3d(260, 160, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3d(250, 130, 0);
		glVertex3d(250, 135, 0);
		glVertex3d(240, 135, 0);
		glVertex3d(240, 130, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3d(270, 130, 0);
		glVertex3d(270, 135, 0);
		glVertex3d(280, 135, 0);
		glVertex3d(280, 130, 0);
		glEnd();


		glPopMatrix();

		//enemy
		glPushMatrix();


		glTranslated(enemyX, 0, 0);

		glColor3f(1, 0, 0);

		glBegin(GL_LINES);
		glVertex3d(240, 182, 0);
		glVertex3d(240, 165, 0);
		glBegin(GL_LINES);
		glVertex3d(260, 182, 0);
		glVertex3d(260, 165, 0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3d(270, 200, 0);
		glVertex3d(270, 205, 0);
		glVertex3d(280, 205, 0);
		glVertex3d(280, 200, 0);

		glEnd();

		glBegin(GL_QUADS);
		glVertex3d(230, 200, 0);
		glVertex3d(230, 205, 0);
		glVertex3d(220, 205, 0);
		glVertex3d(220, 200, 0);

		glEnd();

		//body of chicken
		drawCircle(250, 200, 20);
		//head of chicken
		drawCircle(250, 230, 10);


		glBegin(GL_TRIANGLES);
		glVertex3d(260, 233, 0);
		glVertex3d(265, 230, 0);
		glVertex3d(260, 227, 0);
		glEnd();

		//eyes
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(255, 235, 0);
		glVertex3f(245, 235, 0);
		glEnd();
		//nose
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3d(250, 231, 0);
		glVertex3f(250, 226, 0);
		glEnd();


		glPopMatrix();

		//bullets of player
		glPushMatrix();



		for (int i = 0; i < xBullet.size();i++) {
			int x = xBullet.front();
			int y = yBullet.front();
			xBullet.pop();
			yBullet.pop();
			glColor3f(0, 0, 0);
			drawCircle(x, y, 2);
			xBullet.push(x);
			yBullet.push(y);


		}

		glEnd();

		glPopMatrix();

		//bullet of enemy
		glPushMatrix();
		glColor3f(1.0f, 0.9f, 0.3f);


		//check if the player get the power up or not

		int leftPower = 10 + powerX;
		int RightPower = 15 + powerX;
		int bottomPower = 10 + powerY;
		int topPower = 15 + powerY;

		if (((((leftPower >= 240 + keyX) && (leftPower <= 280 + keyX)) || ((RightPower >= 240 + keyX) && (RightPower <= 280 + keyX))) && (((bottomPower >= 130 + keyY) && (bottomPower <= 135 + keyY)) || ((topPower >= 130 + keyY) && (topPower <= 135 + keyY)))) || ((((leftPower >= 250 + keyX) && (leftPower <= 270 + keyX)) || ((RightPower >= 250 + keyX) && (RightPower <= 270 + keyX))) && ((topPower >= 120 + keyY && topPower <= 160 + keyY) || (bottomPower >= 120 + keyY && bottomPower <= 160 + keyY)))) {

			PowerUp = true;
			powerCount = 5;
			playerColor = 1;
			powerX = (rand() % (500 - 20)) + 20;
			powerY = (rand() % (150 - 30)) + 30;

		}






		if (enemyBulletX == 0 && enemyBulletY == 0) {
			drawCircle((250 + enemyX), 165, 5);
			enemyBulletX = 250 + enemyX;
			enemyBulletY = 165;
		}
		else {
			if (enemyBulletY > 0 && (!(((enemyBulletX >= (250 + keyX) && enemyBulletX <= (270 + keyX) && enemyBulletY >= (120 + keyY) && enemyBulletY <= (140 + keyY)) || (enemyBulletX >= (240 + keyX) && (enemyBulletX <= (280 + keyX) && (enemyBulletY >= (130 + keyY) && (enemyBulletY <= (135 + keyY))))) || (enemyBulletX >= (250 + keyX) && enemyBulletX <= (270 + keyX) && enemyBulletY >= (140 + keyY) && enemyBulletY <= (160 + keyY)))
				))) {
				enemyBulletY -= 0.05;
				drawCircle(enemyBulletX, enemyBulletY, 5);
			}
			else if (((enemyBulletX >= (250 + keyX) && enemyBulletX <= (270 + keyX) && enemyBulletY >= (120 + keyY) && enemyBulletY <= (140 + keyY)) || (enemyBulletX >= (240 + keyX) && (enemyBulletX <= (280 + keyX) && (enemyBulletY >= (130 + keyY) && (enemyBulletY <= (135 + keyY))))) || (enemyBulletX >= (250 + keyX) && enemyBulletX <= (270 + keyX) && enemyBulletY >= (140 + keyY) && enemyBulletY <= (160 + keyY)))) {
				enemyBulletX = 0;
				enemyBulletY = 0;

				if (PowerUp == false) {

					playerHealth -= 1;
				}
				/*else {
					PowerUp = false;
					playerColor = 0;
				}*/



			}
			else {
				enemyBulletX = 0;
				enemyBulletY = 0;
			}
		}










		glPopMatrix();

		//health of enemy
		glPushMatrix();

		glColor3f(1, 0, 0);

		glBegin(GL_QUADS);
		glVertex3d(50, 245, 0);
		glVertex3d(50, 250, 0);
		glVertex3d(enemyHealth, 250, 0);
		glVertex3d(enemyHealth, 245, 0);

		glEnd();

		// word enemy's Health
		glColor3f(1, 0, 0);
		glRasterPos2f(0, 245);
		int len, i;
		char* string = "Enemy's Health";
		len = (int)strlen("Enemy's Health");
		for (i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		}

		glColor3f(1, 0, 0);
		glRasterPos2f(0, 5);
		int len2, i2;
		char* string2 = "Player's Health : ";
		len2 = (int)strlen(string2);
		for (i2 = 0; i2 < len2; i2++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string2[i2]);
		}

		glPopMatrix();
		glColor3f(0, 0, 0);
		glPushMatrix();
		for (int j = 1; j <= playerHealth; j++) {
			if (j == 1)
				drawCircle(47, 6, 3);
			else if (j == 2)
				drawCircle(54, 6, 3);
			else
				drawCircle(61, 6, 3);
		}
		glPopMatrix();


		//PowerUp
		glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslated(powerX, powerY, 0);
		glBegin(GL_QUADS);
		glVertex3d(10, 10, 0);
		glVertex3d(10, 15, 0);
		glVertex3d(15, 15, 0);
		glVertex3d(15, 10, 0);

		glEnd();

		glPopMatrix();

	}
	else if (enemyHealth <= 50) {
		glColor3f(0, 1, 0);
		glRasterPos2f(200, 150);
		int len, i;
		char* string = "Congratulations! You Win";
		len = (int)strlen("Congratulations! You Win");
		for (i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		}


	}
	else {
		glColor3f(1, 0, 0);
		glRasterPos2f(200, 150);
		int len, i;
		char* string = "Game's Over! You Lose";
		len = (int)strlen("Game's Over! You Lose");
		for (i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		}
	}



	glFlush();
}


void DisplayEnemy() {

	glPushMatrix();

	glBegin(GL_POLYGON);
	glVertex3d(270, 200, 0);
	glVertex3d(270, 210, 0);
	glVertex3d(290, 210, 0);
	glVertex3d(290, 200, 0);
	glEnd();



	glPopMatrix();

	glFlush();
}





void key(unsigned char k, int x, int y)
{
	if (k == 'd' && keyX < 220)
		keyX += 5;
	if (k == 'a' && keyX > -240)
		keyX -= 5;
	if (k == 'w' && keyY < 5)
		keyY += 5;
	if (k == 's' && keyY > -100)
		keyY -= 5;
	glutPostRedisplay();
}


void spe(int k, int x, int y)
{
	if (k == GLUT_KEY_RIGHT && keyX < 220)
		keyX += 5;
	if (k == GLUT_KEY_LEFT && keyX > -240)
		keyX -= 5;
	if (k == GLUT_KEY_UP && keyY < 5)
		keyY += 5;
	if (k == GLUT_KEY_DOWN && keyY > -100)
		keyY -= 5;

	glutPostRedisplay();
}



void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(500, 250);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("Game");
	glutDisplayFunc(Display);
	glutFullScreen();
	glutMouseFunc(actM);
	glutKeyboardFunc(key);
	glPointSize(5);
	glutSpecialFunc(spe);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutTimerFunc(0, Anim, 0);
	glutTimerFunc(0, time, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 500, 0.0, 250);
	glLineWidth(3.0);

	glutMainLoop();
}



