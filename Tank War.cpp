#include <glut.h>
#include <math.h>
#include <windows.h>
#include <iostream>

int pX1 = 200;
int pX2 = 600;
bool done = false;

int bird = 290;
int bird2 = 295;

int birdTrans = 0;

bool gameOver = false;

int bom1 = 0;
int bom2 = 0;
bool damage2 = false;
bool damage1 = false;

int cl = 0;
bool collision = false;

int sX = 0;
int sY = 0;

int trY = 50;
int tr2Y = 50;
int defT = 0;
bool switchPlayer = true;

int p0[2];
int p1[2];
int p2[2];
int p3[2];

int* p;
int* v;
bool fire = false;
float t;

int end1X = -1;
int end1Y = -1;

int end2X = -1;
int end2Y = -1;

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

		float x = r * cosf(theta);
		float y = r * sinf(theta);

		glVertex2f(x + cx, y + cy);

	}
	glEnd();
};

void powerKey(unsigned char k, int x, int y)
{
	if (k == 'a' && trY <= 140 && switchPlayer == true && gameOver == false) {
		tr2Y = 50;
		trY += 20;
	}
	else if (k == 'l' && tr2Y <= 140 && switchPlayer == false && gameOver == false) {
		trY = 50;
		tr2Y += 20;
	}

	glutPostRedisplay();
}


void power(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && switchPlayer == true && gameOver == false)
	{
		trY = 50;
		fire = true;
		t = 0;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && switchPlayer == false && gameOver == false)
	{
		tr2Y = 50;
		fire = true;
		t = 0;
	}

	
	glutPostRedisplay();
}

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3) * p0[0] + 3 * t * pow((1 - t), 2) * p1[0] + 3 * pow(t, 2) * (1 - t) * p2[0] + pow(t, 3) * p3[0];
	res[1] = pow((1 - t), 3) * p0[1] + 3 * t * pow((1 - t), 2) * p1[1] + 3 * pow(t, 2) * (1 - t) * p2[1] + pow(t, 3) * p3[1];
	return res;
}

void timeDefender(int val)
{
	if (defT < 800) {
		defT += 1;
	}
	if (defT == 800) {
		defT = 0;
	}

	glutPostRedisplay();	
	glutTimerFunc(10, timeDefender, 0);		
}

void timeCloud(int val)
{
	if (cl < 800) {
		cl += 1;
	}
	if (cl == 800) {
		cl = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(200, timeCloud, 0);
}

void timeBirds(int val)
{
	if (birdTrans < 800) {
		birdTrans += 1;
	}
	if (birdTrans == 800) {
		birdTrans = 0;
	}
	if (bird == 290) {
		bird = 275;
	}
	else if (bird == 275) {
		bird = 290;
	}
	if (bird2 == 295) {
		bird2 = 280;
	}
	else if (bird2 == 280) {
		bird2 = 295;
	};

	glutPostRedisplay();
	glutTimerFunc(50, timeBirds, 0);
}

void boom(int val)
{

	if (damage2 == true) {
		bom2 -= 20;
		damage2 = false;
	}
	else if (damage1 == true) {
		bom1 -= 20;
		damage1 = false;
	}
	glutTimerFunc(500, boom, 0);

	glutPostRedisplay();
}

void projectile(){

	if (switchPlayer == true && trY == 70) {
		p0[0] = 150;
		p0[1] = 40;

		p1[0] = 300;
		p1[1] = 300;

		p2[0] = 400;
		p2[1] = 200;

		p3[0] = 500;
		p3[1] = 0;
	}
	if (switchPlayer == true && trY == 90) {

		p0[0] = 150;
		p0[1] = 40;

		p1[0] = 300;
		p1[1] = 300;

		p2[0] = 500;
		p2[1] = 300;

		p3[0] = 600;
		p3[1] = 0;
		
	}
	if (switchPlayer == true && trY == 110) {
		p0[0] = 150;
		p0[1] = 40;

		p1[0] = 300;
		p1[1] = 300;

		p2[0] = 500;
		p2[1] = 300;

		p3[0] = 700;
		p3[1] = 0;
	}
	if (switchPlayer == true && trY == 130) {
		p0[0] = 150;
		p0[1] = 40;

		p1[0] = 300;
		p1[1] = 300;

		p2[0] = 500;
		p2[1] = 300;

		p3[0] = 800;
		p3[1] = 0;
		
	}
	if (switchPlayer == true && trY == 150) {

		p0[0] = 150;
		p0[1] = 40;

		p1[0] = 300;
		p1[1] = 300;

		p2[0] = 500;
		p2[1] = 300;

		p3[0] = 900;
		p3[1] = 0;

	}
	

///////////////////////////// Second player 

	if (switchPlayer == false && tr2Y == 70) {
		p0[0] = 645;
		p0[1] = 40;

		p1[0] = 540;
		p1[1] = 300;

		p2[0] = 400;
		p2[1] = 200;

		p3[0] = 300;
		p3[1] = 0;
	}
	if (switchPlayer == false && tr2Y == 90) {

		p0[0] = 645;
		p0[1] = 40;

		p1[0] = 540;
		p1[1] = 300;

		p2[0] = 300;
		p2[1] = 300;

		p3[0] = 200;
		p3[1] = 0;

	}
	if (switchPlayer == false && tr2Y == 110) {


		p0[0] = 645;
		p0[1] = 40;

		p1[0] = 540;
		p1[1] = 300;

		p2[0] = 300;
		p2[1] = 300;

		p3[0] = 100;
		p3[1] = 0;
	}
	if (switchPlayer == false && tr2Y == 130) {
		p0[0] = 645;
		p0[1] = 40;

		p1[0] = 540;
		p1[1] = 300;

		p2[0] = 300;
		p2[1] = 300;

		p3[0] = 0;
		p3[1] = 0;

	}
	if (switchPlayer == false && tr2Y == 150) {

		p0[0] = 645;
		p0[1] = 40;

		p1[0] = 540;
		p1[1] = 300;

		p2[0] = 300;
		p2[1] = 300;

		p3[0] = -100;
		p3[1] = 0;

	}
	

	glutPostRedisplay();

}

void adjust() {
	if (fire == false && gameOver == false) {
		glPointSize(2);
		glColor3f(0, 0, 0);
		glBegin(GL_POINTS);
		for (float f = 0; f < 10; f += 0.01)
		{
			p = bezier(f, p0, p1, p2, p3);
			glVertex3f(p[0], p[1], 0);
		}
		glEnd();
}
}

void displayText(float x, float y, int r, int g, int b, const char* string) {
	int j = strlen(string);

	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void shoot() {
	if (fire == true && gameOver == false) {
		done = false;
		collision = false;
		v = bezier(t, p0, p1, p2, p3);
		sX = v[0];
		sY = v[1];
		t += 0.0003;
		
	if (sY <= 0 && switchPlayer == false) {
		fire = false;
		switchPlayer = true;
		done = true;
	}
	else if (sY <= 0 && switchPlayer == true && done == false) {
		fire = false;
		switchPlayer = false;
		done = true;
	}
	}

	if (sX >= 600 && sX <= 717 && sY <= 55 && switchPlayer == true && done == false) {
		fire = false;
		switchPlayer = false;
		pX2 += 70;
		collision = true;
		bom2 += 20;
		damage2 = true;
		done = true;
	}
	else if (sX >= 80 && sX <= 190 && sY <= 55 && switchPlayer == false && done == false) {
		fire = false;
		switchPlayer = true;
		pX1 -= 70;
		bom1 += 20;
		collision = true;
		damage1 = true;
		done = true;
	}
	else if (sX == 400 && sY <= 200 && switchPlayer == true && done == false) {
		fire = false;
		switchPlayer = false;
		collision = true;
		done = true;
	}
	else if (sX == 410 && sY <= 200 && switchPlayer == false && done == false) {
		fire = false;
		switchPlayer = true;
		collision = true;
		done = true;
	}
	else if (sX >= (0 + defT) && sX <= (115 + defT) && sY >= 220 && sY <= 235 && done == false) {
		fire = false;
		collision = true;
		if (switchPlayer == true) {
			switchPlayer = false;
		}
		else if (switchPlayer == false) {
			switchPlayer = true;
		}
		done = true;
	}
	if (pX2 == 740) {
		gameOver = true;
		end1X = 330;
		end1Y = 250;
	}
	else if (pX1 == 60) {
		gameOver = true;
		end2X = 330;
		end2Y = 250;
	}
	

	glutPostRedisplay();
}


void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	//First player 
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(60, 350, 0.0f);
	glVertex3f(60, 360, 0.0f);
	glVertex3f(200, 360, 0.0f);
	glVertex3f(200, 350, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(60, 350, 0.0f);
	glVertex3f(60, 360, 0.0f);
	glVertex3f(pX1, 360, 0.0f);
	glVertex3f(pX1, 350, 0.0f);
	glEnd();


	// The 1st tank player
	glPushMatrix();
	glTranslated(0, bom1, 0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(85, 15, 0.0f);
	glVertex3f(80, 18, 0.0f);
	glVertex3f(78, 20, 0.0f);
	glVertex3f(80, 23, 0.0f);
	glVertex3f(200, 23, 0.0f);
	glVertex3f(195, 18, 0.0f);
	glVertex3f(190, 17, 0.0f);
	glVertex3f(185, 16, 0.0f);
	glVertex3f(180, 15, 0.0f);


	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.2f);
	glVertex3f(80, 23, 0.0f);
	glVertex3f(80, 40, 0.0f);
	glVertex3f(190, 40, 0.0f);
	glVertex3f(190, 23, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.4f, 0.2f);
	glVertex3f(90, 40, 0.0f);
	glVertex3f(90, 55, 0.0f);
	glVertex3f(150, 55, 0.0f);
	glVertex3f(150, 40, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.3f, 0.1f);
	glVertex3f(150, 55, 0.0f);
	glVertex3f(190, 65, 0.0f);
	glVertex3f(193, 58, 0.0f);
	glVertex3f(150, 48, 0.0f);
	glEnd();

	glColor3f(0.3f, 0.3f, 0.3f);
	DrawCircle(90, 19, 4, 50);
	DrawCircle(100, 19, 4, 50);
	DrawCircle(110, 19, 4, 50);
	DrawCircle(120, 19, 4, 50);
	DrawCircle(130, 19, 4, 50);
	DrawCircle(140, 19, 4, 50);
	DrawCircle(150, 19, 4, 50);
	DrawCircle(160, 19, 4, 50);
	DrawCircle(170, 19, 4, 50);
	DrawCircle(180, 19, 4, 50);
	glPopMatrix();
	

	//Power
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0, 50, 0.0f);
	glVertex3f(0, 150, 0.0f);
	glVertex3f(10, 150, 0.0f);
	glVertex3f(10, 50, 0.0f);
	glEnd();

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 50, 0.0f);
	glVertex3f(0, trY, 0.0f);
	glVertex3f(10, trY, 0.0f);
	glVertex3f(10, 50, 0.0f);
	glEnd();
	glPopMatrix();

	//////////////////////////////

	//Projectile Shape
	
	adjust();
	projectile();

	
	// BULLET _______

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	if (collision == false){
		DrawCircle(sX, sY, 5, 50);
		glBegin(GL_LINES);
		glVertex3f(sX-9, sY+0.5, 0.0f);
		glVertex3f(sX+9, sY + 0.5, 0.0f);
		glEnd();
	}
	glPopMatrix();


	///////////////////////////////////////


	//Second player 

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0, 0);
	glVertex3f(740, 350, 0.0f);
	glVertex3f(740, 360, 0.0f);
	glVertex3f(600, 360, 0.0f);
	glVertex3f(600, 350, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0, 0);
	glVertex3f(740, 350, 0.0f);
	glVertex3f(740, 360, 0.0f);
	glVertex3f(pX2, 360, 0.0f);
	glVertex3f(pX2, 350, 0.0f);
	glEnd();


	// The 2nd tank player
	glPushMatrix();
	glTranslated(0, bom2, 0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(710, 15, 0.0f);
	glVertex3f(715, 18, 0.0f);
	glVertex3f(717, 20, 0.0f);
	glVertex3f(715, 23, 0.0f);
	glVertex3f(600, 23, 0.0f);
	glVertex3f(605, 18, 0.0f);
	glVertex3f(610, 17, 0.0f);
	glVertex3f(615, 16, 0.0f);
	glVertex3f(620, 15, 0.0f);

	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.4f, 0.3f);
	glVertex3f(715, 23, 0.0f);
	glVertex3f(715, 40, 0.0f);
	glVertex3f(610, 40, 0.0f);
	glVertex3f(610, 23, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.3f, 0.4f);
	glVertex3f(705, 40, 0.0f);
	glVertex3f(705, 55, 0.0f);
	glVertex3f(645, 55, 0.0f);
	glVertex3f(645, 40, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.2f, 0.2f);
	glVertex3f(645, 55, 0.0f);
	glVertex3f(605, 65, 0.0f);
	glVertex3f(602, 58, 0.0f);
	glVertex3f(645, 48, 0.0f);
	glEnd();

	glColor3f(0.3f, 0.3f, 0.3f);
	DrawCircle(710, 19, 4, 50);
	DrawCircle(700, 19, 4, 50);
	DrawCircle(690, 19, 4, 50);
	DrawCircle(680, 19, 4, 50);
	DrawCircle(670, 19, 4, 50);
	DrawCircle(660, 19, 4, 50);
	DrawCircle(650, 19, 4, 50);
	DrawCircle(640, 19, 4, 50);
	DrawCircle(630, 19, 4, 50);
	DrawCircle(620, 19, 4, 50);
	glPopMatrix();
	

	//Power 
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(800, 50, 0.0f);
	glVertex3f(800, 150, 0.0f);
	glVertex3f(790, 150, 0.0f);
	glVertex3f(790, 50, 0.0f);
	glEnd();

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(790, 50, 0.0f);
	glVertex3f(790, tr2Y, 0.0f);
	glVertex3f(800, tr2Y, 0.0f);
	glVertex3f(800, 50, 0.0f);
	glEnd();
	glPopMatrix();

	

	/////////////////////////////

	//WALL
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.7f);
	glVertex3f(410, 0, 0.0f);
	glVertex3f(410, 200, 0.0f);
	glVertex3f(400, 200, 0.0f);
	glVertex3f(400,0, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.3f);
	glVertex3f(390, 0, 0.0f);
	glVertex3f(390, 200, 0.0f);
	glVertex3f(400, 200, 0.0f);
	glVertex3f(400, 0, 0.0f);

	glEnd();

	//Defender plane

	glPushMatrix();
	glTranslated(defT, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(10, 220, 0.0f);
	glVertex3f(0, 235, 0.0f);
	glVertex3f(100, 235, 0.0f);
	glVertex3f(115, 220, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(110, 230, 0.0f);
	glVertex3f(100, 235, 0.0f);
	glVertex3f(90, 230, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 235, 0.0f);
	glVertex3f(0, 250, 0.0f);
	glVertex3f(5, 250, 0.0f);
	glVertex3f(15, 235, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(50, 225, 0.0f);
	glVertex3f(50, 230, 0.0f);
	glVertex3f(55, 230, 0.0f);
	glVertex3f(55, 225, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(40, 225, 0.0f);
	glVertex3f(40, 230, 0.0f);
	glVertex3f(45, 230, 0.0f);
	glVertex3f(45, 225, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(30, 225, 0.0f);
	glVertex3f(30, 230, 0.0f);
	glVertex3f(35, 230, 0.0f);
	glVertex3f(35, 225, 0.0f);
	glEnd();
	glPopMatrix();

	//Ground  :::::
	glBegin(GL_QUADS);  // Ground
	glColor3f(0.1f, 0.6f, 0.2f);
	glVertex3f(0, 0, 0.0f);
	glVertex3f(0, 15, 0.0f);
	glVertex3f(800, 15, 0.0f);
	glVertex3f(800, 0, 0.0f);
	glEnd();

	glBegin(GL_QUADS);    //Tree
	glColor3f(0.6f, 0.4f, 0.2f);
	glVertex3f(300, 15, 0.0f);
	glVertex3f(300, 55, 0.0f);
	glVertex3f(310, 55, 0.0f);
	glVertex3f(310, 15, 0.0f);
	glEnd();

	glColor3f(0.2f, 0.7f, 0.2f);
	DrawCircle(290,50,10,50);

	glColor3f(0.2f, 0.7f, 0.2f);
	DrawCircle(300, 50, 10, 50);
	
	glColor3f(0.2f, 0.7f, 0.2f);
	DrawCircle(310, 50, 10, 50);

	glColor3f(0.2f, 0.7f, 0.2f);
	DrawCircle(320, 50, 10, 50);

	glColor3f(0.2f, 0.7f, 0.2f);
	DrawCircle(310, 58, 10, 50);

	glColor3f(0.2f, 0.7f, 0.2f);
	DrawCircle(300, 58, 10, 50);


	glBegin(GL_QUADS);  // Flag
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(500, 15, 0.0f);
	glVertex3f(500, 130, 0.0f);
	glVertex3f(503, 130, 0.0f);
	glVertex3f(503, 15, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(470, 110, 0.0f);
	glVertex3f(470, 115, 0.0f);
	glVertex3f(500, 115, 0.0f);
	glVertex3f(500, 110, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(470, 115, 0.0f);
	glVertex3f(470, 120, 0.0f);
	glVertex3f(500, 120, 0.0f);
	glVertex3f(500, 115, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(483, 115, 0.0f);
	glVertex3f(483, 120, 0.0f);
	glVertex3f(487, 120, 0.0f);
	glVertex3f(487, 115, 0.0f);
	glEnd();




	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(470, 120, 0.0f);
	glVertex3f(470, 125, 0.0f);
	glVertex3f(500, 125, 0.0f);
	glVertex3f(500, 120, 0.0f);
	glEnd();

	





	// SKYYY ::
	glColor3f(1.0f, 1.0f, 0.0f); //Sun
	DrawCircle(700, 285, 40, 50);

	glPushMatrix();  //Cloud
	glTranslated(cl, 0, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCircle(0, 275, 20, 50);

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCircle(20, 275, 20, 50);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCircle(30, 275, 20, 50);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCircle(50, 275, 20, 50);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCircle(35, 285, 20, 50);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawCircle(20, 285, 20, 50);

	glPopMatrix();


	glPushMatrix();   // Birdsss
	glTranslated(birdTrans, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f( 30, 280, 0.0f);
	glVertex3f( 20, 283, 0.0f);
	glVertex3f( 35, 283, 0.0f);
	glVertex3f( 45, 280, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f( 30, 282, 0.0f);
	glVertex3f( 20, bird, 0.0f);
	glVertex3f( 40, 282, 0.0f);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f( 60, 285, 0.0f);
	glVertex3f( 50, 288, 0.0f);
	glVertex3f( 65, 288, 0.0f);
	glVertex3f( 75, 285, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f( 60, 287, 0.0f);
	glVertex3f( 50, bird2, 0.0f);
	glVertex3f( 70, 287, 0.0f);
	glEnd();
	glPopMatrix();


	// Ending the game ::
	displayText(end1X, end1Y, 1, 0, 0, "Game over player 1 wins !");
	displayText(end2X, end2Y, 1, 0, 0, "Game over player 2 wins !");



	glFlush();
}


void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(800, 400);
	glutInitWindowPosition(150, 150);


	glutCreateWindow("TH - Game");
	glutDisplayFunc(Display);
	glutMouseFunc(power);
	glutKeyboardFunc(powerKey);
	glutTimerFunc(0,timeDefender,0);	
	glutTimerFunc(0, timeCloud, 0);
	//glutTimerFunc(0, shoot, 0);
	glutTimerFunc(0, boom, 0);
	glutIdleFunc(shoot);
	glutTimerFunc(0, timeBirds, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.2,0.7,0.9, 0.0f);
	gluOrtho2D(0.0, 800, 0.0, 400);


	glutMainLoop();
}
