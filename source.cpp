

#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#define MAX_CHAR       128

typedef struct { GLfloat x, y; } point;
point p0 = { 0, -1 };
const GLfloat PI = 3.141592653f;


//mouse interactions star
int stateSTAR = 0;
int starPosX = 0;
int starPosY = 0;
//mouse interactions cap
int capX = 0;
int capY = 0;
int capstate = 0;


//balloon
int time_interval = 15;
int BalloonFlag = 0;
GLfloat step1 = 0.0;
GLfloat step2 = 3;
GLfloat wordx = 300;
GLfloat balloony = 0;


//paper flight
float t = 0.0;
float n = 0.0;


//open envelope
float coverl = 0.0;
float coverr = 0.0;
int stageletter = 0;


//light board
int light = 0;
int lit = 0;



int flag = 0;

//bubble and envelope
int stage = 0;
int z0 = 0;
int a0 = 0;
int m0 = 0;
int time_intervalBG = 50;

//rotation and transform envelope
float w0 = 0;
int time_intervalBGO =1;


//viewing(zoom in/out)
GLint stepy = 0;
GLint stepx = 0;
int stageView = 0;

bool increasing = true;

//bubble rotation
GLfloat rotateStep = 4; 
GLfloat rotation = 0; 
GLfloat downStep = 0;  
GLfloat BubbleRotate = 0;

//random falling stars
GLfloat starX, starY, Rs, rs = 0;
int starNum = 0;
typedef GLfloat star2[100];
star2 randomX = {};
star2 randomY = {};
star2 randomR = {};
star2 randomr = {};



void TimerBalloon(int value) {
	balloony += step1;
	if (balloony >=1000)
	{
		step1 = 0;
		balloony = 1025;
	}

	glutTimerFunc(time_interval, TimerBalloon, 1);
}
int time_interval1 = 1000;
void OnTimerLight(int value) {
	light++;
	if (light % 2 == 0) {
		lit = 0;
	}
	else {
		lit = 1;
	}
	glutTimerFunc(time_interval1, OnTimerLight, 1);
}
int flight = 0;
int time_interval2 = 10;
void OnTimerFlight(int value) {
	if (flight > -600) {
		flight-=1;
		glutTimerFunc(time_interval2, OnTimerFlight, 1);
	}
	else if (flight == -600) {
		flight = 300;
		glutTimerFunc(time_interval2, OnTimerFlight, 1);
	}
	/*flight -= 10;
	glutTimerFunc(time_interval1, OnTimerFlight, 1);*/
}
void ChatTimer(int value)
{
	p0.x -= step2;
	if (p0.x >=600)
		p0.x = 0;
	else if (p0.x <= -100)
		p0.x =599;
	//when_in_mainloop();
	glutTimerFunc(time_interval, ChatTimer, 1);
}
void OnTimerOuterLetter(int value) {
	if (stage == 2 && w0 < 90) { 
		w0 += 0.1;
	}

	if (w0 <= 90) {
		glutTimerFunc(time_intervalBGO, OnTimerOuterLetter, 1);
	}
	else {
		stage = 1;
		glutTimerFunc(time_intervalBGO, OnTimerOuterLetter, 1);
	}
}

// keyboard interactions//////////////////////////////////////////
void keyboard_input(unsigned char key, int x, int y) {
	//quit
	if (key == 'q' || key == 'Q')
		exit(0);
	//fly to the right
	else if (key == 'd' || key == 'D')
		t += 10;
	//fly to the left and fallen
	else if (key == 'a' || key == 'A') {
		t -= 10;
		n -= 3;
	}
	//fly upwards
	else if (key == 'w' || key == 'W')
		n += 10;
	//fly downwards
	else if (key == 's' || key == 'S')
		n -= 10;
	//right bubble
	else if (key == 'r' || key == 'R')
		flag = 1;
	//left bubble
	else if (key == 'l' || key == 'L')
		flag = 2;
	//middle bubble
	else if (key == 'm' || key == 'M')
		flag = 0;
	//open the letter
	else if (key == 'o' || key == 'O') {
		if (stage==1) {
			stageletter = 1;
		}
	}	
	//pick up the envelope
	else if (key == 'z' || key == 'Z') {
		stage = 2;
	}
	//release the balloon
	else if (key == 'f' || key == 'F') {
		if (stageletter == 1) {
			BalloonFlag = 1;
			step1 = 2.0;
		}	
	}
	//decrease the speed of bullet chat
	else if (key == 'u' || key == 'U') 
	{
		step2 -= 1;
	}
	//increase the speed of bullet chat
	else if (key == 'j' || key == 'J') 
	{
		step2 += 1;
	}
	//zoom in
	else if (key == 'n' || key == 'N') 
	{
		if (stepy <= 100) {
			stepy += 3;
		}
		
	}
	//zoom out
	else if (key == 'b' || key == 'B') 
	{
		if (stepy >= 0) {
			stepy -= 5;
	}	
	}
	//zoom in
	else if (key == 'v' || key == 'V') 
	{
		if (stepx <= 100) {
			stepx += 3;
		}
		
	}
	//zoom out
	else if (key == 'c' || key == 'C') 
	{
		if (stepx >= 0) {
			stepx -= 5;
		}
	}
		
}
//////////////////////////////////////////////////////////////////

//mouse interactions/////////////////////////////
void mouse_input(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		stateSTAR = 1;
		starPosX =  x ;
		starPosY =  -y ; 	

	}
	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) {
		capstate = 1;
		capX = x;
		capY = -y;
	}
}
void drawDoctoralCapSHOW() {
	// Draw the diamond shape (black)
	if (capstate == 1) {
		glColor3ub(0, 0, 0);  // Set color to black
		glBegin(GL_POLYGON);
		glVertex2d(capX + 50, capY + 60);
		glVertex2d(capX - 30, capY + 40);
		glVertex2d(capX + 50, capY + 20);
		glVertex2d(capX + 130, capY + 40);
		glEnd();

		// Draw the trapezoidal lower part (black)
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(capX + 20, capY + 35);
		glVertex2d(capX + 20, capY + 40);
		glVertex2d(capX + 80, capY + 40);
		glVertex2d(capX + 80, capY + 35);
		glEnd();

		glColor3ub(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2d(capX + 20, capY + 35);
		glVertex2d(capX + 80, capY + 35);
		glVertex2d(capX + 90, capY + 0);
		glVertex2d(capX + 10, capY + 0);
		glEnd();

		// Draw the trapezoidal lower part (black)
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(capX + 100, capY + 6);
		glVertex2d(capX + 100, capY + 40);
		glVertex2d(capX + 102, capY + 40);
		glVertex2d(capX + 102, capY + 6);
		glEnd();

		// Draw the trapezoidal lower part (black)
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(capX + 98, capY + 6);
		glVertex2d(capX + 101, capY + 25);
		glVertex2d(capX + 102, capY + 25);
		glVertex2d(capX + 106, capY + 8);
		glEnd();
	}
	
}
void starM() {
	if (stateSTAR == 1) {
		int windowHeight = 850;  
		int starHeight = 70;     

		glColor3f(1, 1, 0);
		glBegin(GL_TRIANGLES);
		glVertex2f(starPosX, windowHeight + starPosY);
		glVertex2f(starPosX + starHeight, windowHeight + starPosY);
		glVertex2f(starPosX + starHeight / 2, windowHeight + starPosY - 45);
		glEnd();

		glColor3f(1, 1, 0);
		glBegin(GL_TRIANGLES);
		glVertex2f(starPosX, windowHeight+ starPosY - 30);
		glVertex2f(starPosX + starHeight, windowHeight +starPosY - 30);
		glVertex2f(starPosX + starHeight / 2, windowHeight + starPosY + 15);
		glEnd();
	}
}
/////////////////////////////////////////////////

void DrawCircleBG(int r) {

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(250 + r * cos(theta), 250 + r * sin(theta));
	}

	glEnd();
}


void FallingStarTimer(int value)
{
	downStep += 2;
	glutTimerFunc(time_intervalBG, FallingStarTimer, 5);
}
void BGBubbleTimer(int value) {
	m0++;
	if (increasing) {
		if (z0 < 20) {
			z0+=1;
		}
		else {
			increasing = false;
		}
	}
	else {
		if (z0 > 0) {
			z0-=1;
		}
		else {
			increasing = true;
		}
	}
	if (increasing) {
		if (a0 < 20) {
			a0 += 1;
		}
		else {
			increasing = false;
		}
	}
	else {
		if (a0 > 0) {
			a0 -= 1;
		}
		else {
			increasing = true;
		}
	}
	glutTimerFunc(time_intervalBG, BGBubbleTimer, 1);
}
void RotateBubbleTimer(int value)
{
	BubbleRotate += 0.9;
	glutTimerFunc(time_interval, RotateBubbleTimer, 6);
}

//Envelope/////////////////////////////
void DrawCoverRight() {
	
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2d(0, 0);
	glVertex2d(600,0);
	glVertex2d(600, 850);
	glVertex2d(0, 850);
	glEnd();
}
void OnTimerCoverRight(int value) {
	if (stageletter > 0) {
		coverl -= 1;
		glutTimerFunc(time_interval, OnTimerCoverRight, 1);
	}else
	{
		glutTimerFunc(time_interval, OnTimerCoverRight, 1);
	}
	
	
	
}
void DrawCoverLeft() {

	glBegin(GL_POLYGON);
	glColor3ub(105, 15, 128);
	glVertex2d(0, 0);
	glVertex2d(200, 0);
	glVertex2d(200, 850);
	glVertex2d(0, 850);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(105, 15, 128);
	glVertex2d(200, 0);
	glVertex2d(200, 850);
	glVertex2d(200, 850);
	glVertex2d(300, 425);
	glEnd();
}
void OnTimerCoverLeft(int value) {
	if (stageletter > 0) {
		coverr += 3;
		glutTimerFunc(time_interval, OnTimerCoverLeft, 1);
	}
	else{
		glutTimerFunc(time_interval, OnTimerCoverLeft, 1);
	}	
}
///////////////////////////////////////


//paper flight
void DrawTriangles()
{
	
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_TRIANGLES);
	glVertex2f(490, 620);
	glVertex2f(540, 630);
	glVertex2f(540, 610);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(490, 620);
	glVertex2f(545, 625);
	glVertex2f(560, 605);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(490, 620);
	glVertex2f(540, 630);
	glVertex2f(530, 640);
	glEnd();

}



//Typing words//////////////////////////////////
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
	
}
///////////////////////////////////////////////////

//card background
void drawBackground() {
	
	glBegin(GL_POLYGON);
	
	glVertex2d(0, 0);
	glVertex2d(600, 0);
	glVertex2d(600, 850);
	glVertex2d(0, 850);
	glEnd();
}

//12 colors for bubbles and rings
void setcolor(GLint x0, GLint y0, GLint x, GLint y, int type)
{
	switch (type)
	{
	case 1: glColor3f(252.0 / 255, 193.0 / 255, 88.0 / 255);
		break;
	case 2: glColor3f(255.0 / 255, 243.0 / 255, 127.0 / 255);
		break;
	case 3: glColor3f(44.0 / 255, 228.0 / 255, 214.0 / 255);
		break;
	
	case 4: glColor3f(0.0 / 255, 94.0 / 255, 255.0 / 255);
		break;

	case 5: glColor3f(144.0 / 255, 238.0 / 255, 144.0 / 255);
		break;
	case 6: glColor3f(144.0 / 255, 238.0 / 255, 144.0 / 255);
		break;
	default:
		break;
	}
	glVertex2f((x0 + x), (y0 + y));
	glVertex2f((x0 + y), (y0 + x));
	glVertex2f((x0 + y), (y0 - x));
	glVertex2f((x0 + x), (y0 - y));
	switch (type)
	{
	case 1: glColor3f(252.0 / 255, 193.0 / 255, 88.0 / 255);
		break;
	case 2: glColor3f(234.0 / 255, 139.0 / 255, 89.0 / 255);
		break;
	case 3: glColor3f(44.0 / 255, 228.0 / 255, 214.0 / 255);
		break;	
	case 4: glColor3f(44.0 / 255, 228.0 / 255, 214.0 / 255);
		break;
	case 5: glColor3f(144.0 / 255, 238.0 / 255, 144.0 / 255);
		break;
	case 6: glColor3f(34.0 / 255, 139.0 / 255, 34.0 / 255);
		break;
	default:
		break;
	}
	glVertex2f((x0 - x), (y0 - y));
	glVertex2f((x0 - y), (y0 - x));
	glVertex2f((x0 - y), (y0 + x));
	glVertex2f((x0 - x), (y0 + y));
}
//self rotation bubbles
void SpinningBubbles(GLint x0, GLint y0, GLint r0, int type)
{	
	glPushMatrix(); 
	glTranslatef(x0, y0, 0);
	glRotatef(BubbleRotate, 0, 0, 1);
	glTranslatef(-x0, -y0, 0);
	GLint x = 0; 
	GLint y = r0; 
	GLint d = 1 - r0;     
	glBegin(GL_POLYGON);
	setcolor(x0, y0, x, y, type);
	while (x < y)
	{
		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		setcolor(x0, y0, x, y, type);
		glShadeModel(GL_SMOOTH);
	}
	glEnd();
	glPopMatrix();
}



//3bubbles////////////////////////
void circlestarM() {
	//rings
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(300, 280, 202, 1);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles( 300,280, 200, 1);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(300, 280, 198, 1);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(300, 280, 196, 1);
	glEnd();
	//bubble
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(300, 280, 0);
	glRotatef(BubbleRotate, 0, 0, 1);
	glTranslatef(-300, -280, 0);
	SpinningBubbles(  300 + 45, 475,15, 2);
	glEnd();
}
void circlestarL() {
	//rings
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(150, 160, 202, 3);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(150, 160, 200, 3);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(150, 160, 198, 3);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(150, 160, 196, 3);
	glEnd();
	//bubble
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(150, 160, 0);
	glRotatef(BubbleRotate, 0, 0, 1);
	glTranslatef(-150, -160, 0);
	SpinningBubbles(150 + 45, 355, 15, 4);
	glEnd();
}
void circlestarR() {
	//rings
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(450, 330, 202, 5);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(450, 330, 200, 5);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(450, 330, 198, 5);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SpinningBubbles(450, 330, 196, 5);
	glEnd();
	//bubble
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(450, 330, 0);
	glRotatef(BubbleRotate, 0, 0, 1);
	glTranslatef(-450, -340, 0);
	SpinningBubbles(450 + 45, 535, 15, 6);
	glEnd();
}
//3circle//////////////////////////
void circleR() {
	glColor3ub(158, 0, 158);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(250 + 200 * cos(theta), 250 + 200 * sin(theta));
	}
	
	glEnd();
}
void circleL() {
	glColor3ub(105, 15, 158);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(-50 + 200 * cos(theta), 80 + 200 * sin(theta));
	}
	glEnd();

}
void circleM() {
	glColor3ub(105, 15, 128);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(100 + 200 * cos(theta), 200 + 200 * sin(theta));
	}
	glEnd();

}
//3campus/////////////////////////
void drawTaicang() {
	//buildings
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(130, 220);
	glVertex2d(110, 320);
	glVertex2d(200, 320);
	glVertex2d(180, 220);
	glEnd();
	glColor3ub(105, 15, 158);
	glBegin(GL_POLYGON);
	glVertex2d(142, 240);
	glVertex2d(137, 320);
	glVertex2d(173, 320);
	glVertex2d(168, 240);
	glEnd();

	glColor3ub(255, 99, 71);
	glPushMatrix();  
	glTranslatef(155, 160, 0);  
	glRotatef(40, 0, 0, 1);  
	glTranslatef(-155, -160, 0);  
	glBegin(GL_POLYGON);
	glVertex2d(130, 220);
	glVertex2d(110, 320);
	glVertex2d(200, 320);
	glVertex2d(180, 220);
	glEnd();
	glColor3ub(105, 15, 158);
	glBegin(GL_POLYGON);
	glVertex2d(142, 240);
	glVertex2d(137, 320);
	glVertex2d(173, 320);
	glVertex2d(168, 240);
	glEnd();

	glColor3ub(255, 215, 0);
	glPushMatrix(); 
	glTranslatef(155, 160, 0);  
	glRotatef(70, 0, 0, 1);  
	glTranslatef(-155, -160, 0); 
	glBegin(GL_POLYGON);
	glVertex2d(130, 220);
	glVertex2d(110, 320);
	glVertex2d(200, 308);
	glVertex2d(180, 220);
	glEnd();
	glColor3ub(105, 15, 158);
	glBegin(GL_POLYGON);
	glVertex2d(142, 240);
	glVertex2d(137, 320);
	glVertex2d(173, 320);
	glVertex2d(168, 240);
	glEnd();

	glColor3ub(127, 255, 0);
	glPushMatrix();  
	glTranslatef(155, 160, 0);  
	glRotatef(40, 0, 0, 1);  
	glTranslatef(-155, -160, 0);  
	glBegin(GL_POLYGON);
	glVertex2d(130, 220);
	glVertex2d(110, 320);
	glVertex2d(200, 320);
	glVertex2d(180, 220);
	glEnd();
	glColor3ub(105, 15, 158);
	glBegin(GL_POLYGON);
	glVertex2d(142, 240);
	glVertex2d(137, 320);
	glVertex2d(173, 320);
	glVertex2d(168, 240);
	glEnd();

	glColor3ub(0, 255, 255);
	glPushMatrix();  
	glTranslatef(155, 160, 0);  
	glRotatef(40, 0, 0, 1);  
	glTranslatef(-155, -160, 0);  
	glBegin(GL_POLYGON);
	glVertex2d(130, 220);
	glVertex2d(110, 320);
	glVertex2d(200, 308);
	glVertex2d(180, 220);
	glEnd();
	glColor3ub(105, 15, 158);
	glBegin(GL_POLYGON);
	glVertex2d(142, 240);
	glVertex2d(137, 320);
	glVertex2d(173, 320);
	glVertex2d(168, 240);
	glEnd();

	glColor3ub(30, 144, 255);
	glPushMatrix();  
	glTranslatef(155, 160, 0);  
	glRotatef(70, 0, 0, 1); 
	glTranslatef(-155, -160, 0);  
	glBegin(GL_POLYGON);
	glVertex2d(130, 220);
	glVertex2d(110, 320);
	glVertex2d(200, 320);
	glVertex2d(180, 220);
	glEnd();
	glColor3ub(105, 15, 158);
	glBegin(GL_POLYGON);
	glVertex2d(142, 240);
	glVertex2d(137, 320);
	glVertex2d(173, 320);
	glVertex2d(168, 240);
	glEnd();

	glColor3ub(128, 0, 128);
	glPushMatrix();  
	glTranslatef(155, 160, 0); 
	glRotatef(40, 0, 0, 1);  
	glTranslatef(-155, -160, 0); 
	glBegin(GL_POLYGON);
	glVertex2d(130, 220);
	glVertex2d(110, 320);
	glVertex2d(200, 320);
	glVertex2d(180, 220);
	glEnd();
	glColor3ub(105, 15, 158);
	glBegin(GL_POLYGON);
	glVertex2d(142, 240);
	glVertex2d(137, 320);
	glVertex2d(173, 320);
	glVertex2d(168, 240);
	glEnd();
	//circle //outer //grey
	glColor3ub(220, 220, 220);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 360; i += 5)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(155 + 120 * cos(theta), 160 + 120 * sin(theta));
		glVertex2f(155 + 100 * cos(theta), 160 + 100 * sin(theta));
	}
	glEnd();

	//circle //inner //dark grey
	glColor3ub(180, 180, 180);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 360; i += 5)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(155 + 105 * cos(theta), 160 + 105 * sin(theta));
		glVertex2f(155 + 100 * cos(theta), 160 + 100 * sin(theta));
	}
	glEnd();
	
}
void drawSouthCampus() {
	glTranslated(195, 75, 0);
	//street// outer// grey//circle
	glColor3ub(185, 185, 175);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(250 + 85 * cos(theta), 250 + 85 * sin(theta));
	}
	glEnd();

	
	//grass//pentagon//green
	glColor3ub(70, 160, 58);
	glBegin(GL_POLYGON);
	//center
	double centerX = 250;
	double centerY = 250;
	// radius
	double radius = 80;
	// five vertex
	for (int i = 0; i < 5; i++) {
		double angle = 72 * i; 
		double x = centerX + radius * cos(angle * 3.1415926f / 180);
		double y = centerY + radius * sin(angle * 3.1415926f / 180);
		glVertex2d(x, y);
	}
	glEnd();

	
	//pond//pentagon//blue
	glColor3ub(150, 160, 190);
	glBegin(GL_POLYGON);
	double centerA = 250;
	double centerS = 250;
	double ra = 60;
	for (int i = 0; i < 5; i++) {
		double angle = 72 * i;  
		double a = centerA + ra * cos(angle * 3.1415926f / 180);
		double s = centerS + ra * sin(angle * 3.1415926f / 180);
		glVertex2d(a, s);
	}
	glEnd();


	//street//inner//grey 
	glColor3ub(185, 185, 175);
	glBegin(GL_POLYGON);
	glVertex2d(240, 220);
	glVertex2d(220, 250);
	glVertex2d(240, 280);
	glVertex2d(270, 270);
	glVertex2d(280, 240);
	glEnd();


	//street//diverge//grey 
	glColor3ub(185, 185, 175);
	glBegin(GL_POLYGON);
	glVertex2d(200, 180);
	glVertex2d(235, 230);
	glVertex2d(245, 230);	
	glVertex2d(220, 170);
	glEnd();
	glColor3ub(185, 185, 175);
	glBegin(GL_POLYGON);
	glVertex2d(170, 230);
	glVertex2d(170, 250);
	glVertex2d(230, 252);
	glVertex2d(230, 245);
	glEnd();
	glColor3ub(185, 185, 175);
	glBegin(GL_POLYGON);
	glVertex2d(240, 280);
	glVertex2d(230, 320);
	glVertex2d(245, 320);
	glVertex2d(248, 275);
	glEnd();
	glColor3ub(185, 185, 175);
	glBegin(GL_POLYGON);
	glVertex2d(265, 265);
	glVertex2d(258, 275);
	glVertex2d(320, 300);
	glVertex2d(320, 280);
	glEnd();
	glColor3ub(185, 185, 175);
	glBegin(GL_POLYGON);
	glVertex2d(265, 245);
	glVertex2d(265, 255);
	glVertex2d(320, 220);
	glVertex2d(320, 200);
	glEnd();


	//buildings//orange
	glColor3ub(250, 132, 43);
	glBegin(GL_POLYGON);
	glVertex2d(150, 150);
	glVertex2d(150, 200);
	glVertex2d(250, 150);
	glVertex2d(220, 100);
	glEnd();

	glColor3ub(250, 132, 43);
	glBegin(GL_POLYGON);
	glVertex2d(320, 180);
	glVertex2d(350, 230);
	glVertex2d(400, 210);
	glVertex2d(370, 160);
	glEnd();

	glColor3ub(250, 132, 43);
	glBegin(GL_POLYGON);
	glVertex2d(100, 230);
	glVertex2d(120, 280);
	glVertex2d(150, 260);
	glVertex2d(155, 210);
	glEnd();

	glColor3ub(250, 132, 43);
	glBegin(GL_POLYGON);	
	glVertex2d(170, 320);
	glVertex2d(170, 360);
	glVertex2d(220, 400);
	glVertex2d(225, 360);
	glEnd();
	glColor3ub(250, 132, 43);
	glBegin(GL_POLYGON);
	glVertex2d(225, 360);
	glVertex2d(220, 400);
	glVertex2d(310, 390);
	glVertex2d(290, 350);
	glEnd();
	glColor3ub(250, 132, 43);
	glBegin(GL_POLYGON);
	glVertex2d(350, 300);
	glVertex2d(290, 350);
	glVertex2d(310, 390);
	glVertex2d(390, 310);
	glEnd();
	glColor3ub(250, 132, 43);
	glBegin(GL_POLYGON);
	glVertex2d(350, 250);
	glVertex2d(350, 300);
	glVertex2d(390, 310);
	glVertex2d(390, 260);
	glEnd();


	//tree//green //circle
	glColor3ub(0, 100, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(300 + 10 * cos(theta), 200 + 10 * sin(theta));
	}
	glEnd();
	glColor3ub(0, 128, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(310 + 10 * cos(theta), 210 + 8 * sin(theta));
	}
	glEnd();
	glColor3ub(0, 100, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = i * 3.1415926f / 180.0f;
		glVertex2f(300 + 10 * cos(theta), 200 + 10 * sin(theta));
	}
	glEnd();
}
void drawCB() {


	//right side// dark blue
	glColor3ub(120, 130, 180);
	glBegin(GL_POLYGON);
	glVertex2d(300, 230);
	glVertex2d(300, 400);
	glVertex2d(400, 350);
	glVertex2d(400, 230);
	glEnd();

	//right side// dark grey
	glColor3ub(90, 90, 90);
	glBegin(GL_POLYGON);
	glVertex2d(300, 330);
	glVertex2d(300, 410);
	glVertex2d(355, 380);
	glVertex2d(355, 320);
	glEnd();
	glColor3ub(90, 90, 90);
	glBegin(GL_POLYGON);
	glVertex2d(375, 280);
	glVertex2d(365, 378);
	glVertex2d(405, 350);
	glVertex2d(405, 290);
	glEnd();
	glColor3ub(90, 90, 90);
	glBegin(GL_POLYGON);
	glVertex2d(300, 230);
	glVertex2d(300, 300);
	glVertex2d(405, 250);
	glVertex2d(405, 230);
	glEnd();
	
	//left side//light blue 
	glColor3ub(150, 160, 190);
	glBegin(GL_POLYGON);
	glVertex2d(200, 230);
	glVertex2d(200, 350);
	glVertex2d(300, 400);
	glVertex2d(300, 230);
	glEnd();
	//left side//light grey 
	//up side
	glColor3ub(130, 130, 130);
	glBegin(GL_POLYGON);
	glVertex2d(275, 310);
	glVertex2d(245, 380);
	glVertex2d(300, 410);
	glVertex2d(300, 330);
	glEnd();
	glColor3ub(130, 130, 130);
	glBegin(GL_POLYGON);
	glVertex2d(240, 310);
	glVertex2d(240, 350);
	glVertex2d(245, 380);
	glVertex2d(275, 310);
	glEnd();
	glColor3ub(130, 130, 130);
	glBegin(GL_POLYGON);
	glVertex2d(195, 300);
	glVertex2d(195, 350);
	glVertex2d(235, 375);
	glVertex2d(235, 310);
	glEnd();
	glColor3ub(130, 130, 130);
	glBegin(GL_POLYGON);
	glVertex2d(195, 290);
	glVertex2d(195, 350);
	glVertex2d(235, 375);
	glVertex2d(235, 310);
	glEnd();
	glColor3ub(130, 130, 130);
	glBegin(GL_POLYGON);
	glVertex2d(195, 290);
	glVertex2d(195, 340);
	glVertex2d(235, 355);
	glVertex2d(275, 310);
	glEnd();
	//down side
	glColor3ub(130, 130, 130);
	glBegin(GL_POLYGON);
	glVertex2d(245, 230);
	glVertex2d(245, 290);
	glVertex2d(300, 300);
	glVertex2d(300, 230);
	glEnd();
	glColor3ub(130, 130, 130);
	glBegin(GL_POLYGON);
	glVertex2d(225, 230);
	glVertex2d(225, 270);
	glVertex2d(245, 290);
	glVertex2d(245, 230);
	glEnd();
	glColor3ub(130, 130, 130);
	glBegin(GL_POLYGON);
	glVertex2d(195, 230);
	glVertex2d(195, 265);
	glVertex2d(225, 270);
	glVertex2d(225, 230);
	glEnd();
	

	//bottom//blue
	glColor3ub(30, 93, 127);
	glBegin(GL_POLYGON);
	glVertex2d(120, 220);
	glVertex2d(120, 230);
	glVertex2d(480, 230);
	glVertex2d(480, 220);
	glEnd();

	//platform//red 
	glColor3ub(190, 77, 48);
	glBegin(GL_POLYGON);
	glVertex2d(220, 210);
	glVertex2d(220, 220);
	glVertex2d(320, 220);
	glVertex2d(320, 210);
	glEnd();

	//step //red
	glColor3ub(190, 77, 48);
	glBegin(GL_POLYGON);
	glVertex2d(350, 150);
	glVertex2d(300, 220);
	glVertex2d(400, 220);
	glVertex2d(450, 160);
	glEnd();

	//lawn//green 
	glColor3ub(100, 160, 48);
	glBegin(GL_POLYGON);
	glVertex2d(360, 157);
	glVertex2d(320, 213);
	glVertex2d(400, 213);
	glVertex2d(440, 165);
	glEnd();

	//tree//dark green//trunk//brown 
	glColor3ub(60, 100, 48);
	glBegin(GL_POLYGON);
	glVertex2d(390, 280);
	glVertex2d(410, 300);
	glVertex2d(410, 300);
	glVertex2d(430, 280);
	glEnd();
	glColor3ub(60, 100, 48);
	glBegin(GL_POLYGON);
	glVertex2d(380, 248);
	glVertex2d(410, 288);
	glVertex2d(410, 288);
	glVertex2d(440, 248);
	glEnd();
	glColor3ub(160, 100, 48);
	glBegin(GL_POLYGON);
	glVertex2d(405, 230);
	glVertex2d(405, 248);
	glVertex2d(415, 248);
	glVertex2d(415, 230);
	glEnd();

}
////////////////////////////////////



//light board
void bg() {
	
	glColor3ub(85, 15, 128);
	glBegin(GL_POLYGON);
	glVertex2d(155, 640);
	glVertex2d(164, 730);
	glVertex2d(253, 740);
	glVertex2d(267, 630);
	glEnd();

	glColor3ub(85, 15, 128);
	glBegin(GL_POLYGON);
	glVertex2d(355, 628);
	glVertex2d(364, 730);
	glVertex2d(453, 740);
	glVertex2d(467, 622);
	glEnd();


	glColor3ub(105, 15, 128);
	glBegin(GL_POLYGON);
	glVertex2d(55, 630);
	glVertex2d(64, 700);
	glVertex2d(153, 750);
	glVertex2d(167, 630);
	glEnd();


	glColor3ub(105, 15, 128);
	glBegin(GL_POLYGON);
	glVertex2d(255, 620);
	glVertex2d(264, 724);
	glVertex2d(353, 746);
	glVertex2d(367, 627);
	glEnd();

	glColor3ub(105, 15, 128);
	glBegin(GL_POLYGON);
	glVertex2d(430, 630);
	glVertex2d(440, 750);
	glVertex2d(520, 750);
	glVertex2d(550, 630);
	glEnd();

}


void drawBalloon(void) {

	if (BalloonFlag == 0)
	{
		glColor3f(1, 1, 1);
		selectFont(24, ANSI_CHARSET, "Helvetica");
		glRasterPos2f(150, 100);
		drawString("Press 'f' or 'F' to show balloons");
	}
	else if (BalloonFlag == 1)
	{


		glColor3f(1, 1, 1);
		selectFont(24, ANSI_CHARSET, "Helvetica");
		glRasterPos2f(80, 100);
		drawString("Press 'w/W','a/A','s/S','d/D' to control the paper flight");




		int n = 3000;
		float a = 50.0f;
		float b = 55.0f;

		// Balloon 1
		glColor3ub(169, 60, 196);
		glBegin(GL_TRIANGLE_FAN);

		for (int i = 1; i <= n; i++) {
			glVertex2f(a * cos(2 * PI / i * n) + 100, b * sin(2 * PI / i * n) + 100 + balloony + step1);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (float i = 0; i < 500; i = i + 5.0) {
			float x = 5.0 * sin(i * (2 * PI / 360.0));
			float y = 0.3 * (float)i;
			glColor3ub(255, 255, 255);
			glVertex2f(x + 95, y + balloony + step1 - 106);
		}
		glEnd();

		// Balloon 2
		glColor3ub(85, 50, 137);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 1; i <= n; i++) {
			glVertex2f(a * cos(2 * PI / i * n) + 280, b * sin(2 * PI / i * n) + 30 + balloony + step1);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (float i = 0; i < 500; i = i + 5.0) {
			float x = 5.0 * sin(i * (2 * PI / 360.0));
			float y = 0.3 * (float)i;
			glColor3ub(255, 255, 255);
			glVertex2f(x + 275, y + balloony + step1 - 174);
		}
		glEnd();

		// Balloon 3
		glColor3ub(116, 68, 187);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 1; i <= n; i++) {
			glVertex2f(a * cos(2 * PI / i * n) + 400, b * sin(2 * PI / i * n) + 50 + balloony + step1);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (float i = 0; i < 300; i = i + 5.0) {
			float x = 10.0 * sin(i * (2 * PI / 360.0));
			float y = 0.5 * (float)i;
			glColor3ub(255, 255, 255);
			glVertex2f(x + 405, y + balloony + step1 - 154);
		}
		glEnd();


		// Balloon 4
		glColor3ub(160, 28, 127);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 1; i <= n; i++) {
			glVertex2f(a * cos(2 * PI / i * n) + 320, b * sin(2 * PI / i * n) + 204 + balloony + step1);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (float i = 0; i < 300; i = i + 5.0) {
			float x = 10.0 * sin(i * (2 * PI / 360.0));
			float y = 0.5 * (float)i;
			glColor3ub(255, 255, 255);
			glVertex2f(x + 325, y + balloony + step1 );
		}
		glEnd();

		// Balloon 5
		glColor3ub(196, 88, 147);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 1; i <= n; i++) {
			glVertex2f(a * cos(2 * PI / i * n) + 550, b * sin(2 * PI / i * n) + 100 + balloony + step1);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (float i = 0; i < 300; i = i + 5.0) {
			float x = 10.0 * sin(i * (2 * PI / 360.0));
			float y = 0.5 * (float)i;
			glColor3ub(255, 255, 255);
			glVertex2f(x + 555, y + balloony + step1 - 104);
		}
		glEnd();

		// Balloon 6
		glColor3ub(146, 68, 127);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 1; i <= n; i++) {
			glVertex2f(a * cos(2 * PI / i * n) + 160, b * sin(2 * PI / i * n) + 120 + balloony + step1);
		}
		glEnd();
		glBegin(GL_POINTS);
		for (float i = 0; i < 300; i = i + 5.0) {
			float x = 10.0 * sin(i * (2 * PI / 360.0));
			float y = 0.5 * (float)i;
			glColor3ub(255, 255, 255);
			glVertex2f(x + 165, y + balloony + step1 - 84);
		}
		glEnd();



	}
	glLoadIdentity();
	glFlush();
}
void drawStarBack(float cx, float cy, float R, float r, float o)
{
	float x0, y0, x1, y1;
	float o0 = o;
	float o1 = o + 0.2 * 3.14;

	for (int i = 0; i < 10; i++)
	{
		x0 = cx + R * cos(o0);
		y0 = cy + R * sin(o0);
		x1 = cx + r * cos(o1);
		y1 = cy + r * sin(o1);
		if (i % 2 == 0) glColor3f(1, 1, 0);
		else
		{
			glColor3f(248.0 / 255, 250.0 / 255, 237.0 / 255);
		}
		glBegin(GL_POLYGON);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glVertex2f(cx, cy);
		glEnd();
		if (i % 2 == 0) o0 = o0 + 0.4 * 3.14;
		else o1 = o1 + 0.4 * 3.14;
	}
}
void drawRandomStar() {
	GLfloat starA = 0, starB = 0, starC = 0, starD = 0; 

	
	if (starNum < 50) {
		
		for (starNum = 0; starNum < 50; starNum++) {

			starA = rand() % 550 + 20;
			starB = rand() % 750 + 20;
			starC = rand() % 5 + 10;
			starD = starC / 3;

			randomX[starNum] = { starA };
			randomY[starNum] = { starB };
			randomR[starNum] = { starC };
			randomr[starNum] = { starD };
		}
	}
	else {
		
		for (int i = 0; i < starNum; i++) {
			glPushMatrix();
			drawStarBack(randomX[i], randomY[i] - downStep, randomR[i], randomr[i], rotation);
			if (randomY[i] - downStep <= 0) randomY[i] = 800 + downStep;

			glPopMatrix();
		}
	}



}
void drawWords() {
	//X
	glTranslated(100, 560, 0);
	if (lit == 1) {
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(100, 100);
		glVertex2d(70, 150);
		glVertex2d(80, 150);
		glVertex2d(110, 100);
		glEnd();
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(70, 100);
		glVertex2d(100, 150);
		glVertex2d(110, 150);
		glVertex2d(80, 100);
		glEnd();
		//J
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(135, 140);
		glVertex2d(135, 150);
		glVertex2d(165, 150);
		glVertex2d(165, 140);
		glEnd();
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(145, 100);
		glVertex2d(145, 150);
		glVertex2d(155, 150);
		glVertex2d(155, 100);
		glEnd();
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(138, 100);
		glVertex2d(138, 110);
		glVertex2d(155, 110);
		glVertex2d(155, 100);
		glEnd();
		//T
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(185, 140);
		glVertex2d(185, 150);
		glVertex2d(215, 150);
		glVertex2d(215, 140);
		glEnd();
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(195, 100);
		glVertex2d(195, 150);
		glVertex2d(205, 150);
		glVertex2d(205, 100);
		glEnd();
		//L
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(230, 100);
		glVertex2d(230, 110);
		glVertex2d(260, 110);
		glVertex2d(260, 100);
		glEnd();
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(230, 100);
		glVertex2d(230, 150);
		glVertex2d(240, 150);
		glVertex2d(240, 100);
		glEnd();
		//U
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(280, 100);
		glVertex2d(280, 110);
		glVertex2d(310, 110);
		glVertex2d(310, 100);
		glEnd();
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(280, 100);
		glVertex2d(280, 150);
		glVertex2d(290, 150);
		glVertex2d(290, 100);
		glEnd();
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		glVertex2d(300, 100);
		glVertex2d(300, 150);
		glVertex2d(310, 150);
		glVertex2d(310, 100);
		glEnd();


		//bulbs
		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(30 + 10 * cos(t), 160 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(-20 + 10 * cos(t), 130 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(-30 + 10 * cos(t), 85 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(390 + 10 * cos(t), 85 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(410 + 10 * cos(t), 165 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(255, 255, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(355 + 10 * cos(t), 175 + 10 * sin(t));
		}
		glEnd();

		

	}
	else {
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(100, 100);
		glVertex2d(70, 150);
		glVertex2d(80, 150);
		glVertex2d(110, 100);
		glEnd();
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(70, 100);
		glVertex2d(100, 150);
		glVertex2d(110, 150);
		glVertex2d(80, 100);
		glEnd();
		//J
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(135, 140);
		glVertex2d(135, 150);
		glVertex2d(165, 150);
		glVertex2d(165, 140);
		glEnd();
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(145, 100);
		glVertex2d(145, 150);
		glVertex2d(155, 150);
		glVertex2d(155, 100);
		glEnd();
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(138, 100);
		glVertex2d(138, 110);
		glVertex2d(155, 110);
		glVertex2d(155, 100);
		glEnd();
		//T
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(185, 140);
		glVertex2d(185, 150);
		glVertex2d(215, 150);
		glVertex2d(215, 140);
		glEnd();
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(195, 100);
		glVertex2d(195, 150);
		glVertex2d(205, 150);
		glVertex2d(205, 100);
		glEnd();
		//L
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(230, 100);
		glVertex2d(230, 110);
		glVertex2d(260, 110);
		glVertex2d(260, 100);
		glEnd();
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(230, 100);
		glVertex2d(230, 150);
		glVertex2d(240, 150);
		glVertex2d(240, 100);
		glEnd();
		//U
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(280, 100);
		glVertex2d(280, 110);
		glVertex2d(310, 110);
		glVertex2d(310, 100);
		glEnd();
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(280, 100);
		glVertex2d(280, 150);
		glVertex2d(290, 150);
		glVertex2d(290, 100);
		glEnd();
		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		glVertex2d(300, 100);
		glVertex2d(300, 150);
		glVertex2d(310, 150);
		glVertex2d(310, 100);
		glEnd();

		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(30 + 10 * cos(t), 160 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(-20 + 10 * cos(t), 130 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(-30 + 10 * cos(t), 85 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(390 + 10 * cos(t), 85 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(410 + 10 * cos(t), 165 + 10 * sin(t));
		}
		glEnd();

		glColor3ub(100, 100, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float t = i * 3.1415926f / 180.0f;
			glVertex2f(355 + 10 * cos(t), 175 + 10 * sin(t));
		}
		glEnd();

	}
    



}

void printBitmapString(void* font, const char* s) {
	if (s && strlen(s)) {
		while (*s) {
			glutBitmapCharacter(font, *s);
			s++;
		}
	}
}
int TextOut(float x, float y, const char* cstr) {
	glRasterPos2f(x, y);
	printBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, cstr);
	return 1;
}

void whenInMainloop() {
	glutPostRedisplay();
}
void drawBackgroundOuter() {
	glBegin(GL_POLYGON);
	glColor3ub(75, 0, 130);
	glVertex2d(0, 0);
	glColor3ub(109, 0, 139);
	glVertex2d(600, 0);
	glColor3ub(139, 0, 139);
	glVertex2d(600, 850);
	glColor3ub(109, 0, 139);
	glVertex2d(0, 850);
	glEnd();
}





void idleDisplay() {
	if (stageView == 0) {
		glViewport(0-0.8*stepx, 0 - 0.2 * stepx + 0.2 * stepy, 600 + 0.72 * stepx + 0.72 * stepy, 850 + 1.02 * stepx + 1.02 * stepy);
		glutPostRedisplay();
	}
}
void myDisplay(void) {
	//Initializing the Canvas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 850);
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Draw Blending Outer Background
	glPushMatrix();
	drawBackgroundOuter();
	glPopMatrix();
	glFlush();
	//Draw Bubble1
	glPushMatrix();
	glTranslatef(180,-120, 0);
	glColor3ub(221, 160, 221);
	DrawCircleBG(120+a0);
	glPopMatrix();
	glFlush();
	//Draw Bubble2
	glPushMatrix();
	glTranslatef(0, 500, 0);
	glColor3ub(147, 112, 219);
	DrawCircleBG(80 + a0);
	glPopMatrix();
	glFlush();
	//Draw Bubble3
	glPushMatrix();
	glTranslatef(230, 400, 0);
	glColor3ub(138, 43, 226);
	DrawCircleBG(150 + a0);
	glPopMatrix();
	glFlush();
	//Draw Bubble4
	glPushMatrix();
	glTranslatef(-150, 280, 0);
	glColor3ub(221, 190, 221);
	DrawCircleBG(60 + a0);
	glPopMatrix();
	glFlush();
	//Draw Bubble5
	glPushMatrix();
	glTranslatef(-120, 40, 0);
	glColor3ub(151, 20, 151);
	DrawCircleBG(90 + a0);
	glPopMatrix();
	glFlush();
	//Draw Random Falling Stars
	glPushMatrix();
	drawRandomStar();
	glPopMatrix();
	glFlush();


	// Bullet Chat
	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(p0.x + 120, p0.y + 800);
	drawString("2024!!!");

	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(p0.x + 80, p0.y + 700);
	drawString("Congratulations!");

	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(p0.x + 60, p0.y + 600);
	drawString("I completed my studies!");

	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(p0.x + 0, p0.y + 650);
	drawString("I graduated");

	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(p0.x -100, p0.y + 750);
	drawString("XJTLU");

	glColor3f(1.0, 1.0, 1.0);
	selectFont(24, ANSI_CHARSET, "Helvetica");
	glRasterPos2f(p0.x + 180, p0.y + 730);
	drawString("Come join us for the graduation ceremony");

	

	

	//Outer Envelope
	if (stage == 0) {

		//Translate the envelope up and down
		glTranslatef(100,530, 0);
		glTranslatef(0,z0, 0);
		glScalef(0.5, 0.5, 0);
		glRotatef(-90, 0, 0, 1);
		
		//Envelope right part
		glPushMatrix();
		glTranslatef(coverr, 0, 0);
		DrawCoverRight();
		glPopMatrix();
		glFlush();
		//Envelope left part
		glPushMatrix();
		glTranslatef(coverl, 0, 0);
		DrawCoverLeft();
		glPopMatrix();
		glFlush();

		glColor3f(1, 1, 1);
		TextOut(800, 50, "press 'z' or 'Z'to get the Invitation Letter");

		glColor3f(1, 1, 1);
		TextOut(750, -50, "press 'j' or 'J' to increase the speed of bullet chat");

		glColor3f(1, 1, 1);
		TextOut(700, -60, "press 'u' or 'U' to decrease the speed of bullet chat");

		glColor3f(1, 1, 1);
		TextOut(1000, 800, "2144981");

		

	}
	//Rotation the Envelope
	else if (stage == 2) {
		//Rotation the Envelope
		glTranslatef(100, 530, 0);
		glScalef(0.5, 0.5, 0);
		glRotatef(-90, 0, 0, 1);
		glRotatef(w0, 0, 0, 1);
		glTranslatef(w0, -w0*6, 0);
		
		//Envelop right and left parts
		glPushMatrix();
		glTranslatef(coverr, 0, 0);
		DrawCoverRight();
		glPopMatrix();
		glFlush();
		glPushMatrix();
		glTranslatef(coverl, 0, 0);
		DrawCoverLeft();
		glPopMatrix();
		glFlush();

	}
	
	else if (stage == 1) {
		// Draw Blending Background
		glScalef(1, 1, 0);
		glPushMatrix();
		glColor3ub(220, 155, 218);
		drawBackground();
		glPopMatrix();
		glFlush();

		//// Draw Doctoral Cap
		//glPushMatrix();
		//glTranslated(50, 200, 0);
		//drawDoctoralCap();
		//glPopMatrix();

		//Paper airplane1
		glPushMatrix();
		glTranslatef(-400, 50, 0);
		glTranslatef(flight*0.6, flight*0.8, 0); 
		DrawTriangles();
		glPopMatrix();
		glFlush();
		//Paper airplane2
		glPushMatrix();
		glTranslatef(-10, 200, 0);
		glTranslatef(flight * 1.2, flight * 0.2, 0); 
		DrawTriangles();
		glPopMatrix();
		glFlush();
		//Paper airplane3
		glPushMatrix();
		glTranslatef(-150, 100, 0);
		glTranslatef(flight, flight, 0); 
		DrawTriangles();
		glPopMatrix();
		glFlush();
		//Paper airplane4
		glPushMatrix();
		glTranslatef(100,20, 0);
		glTranslatef(flight, flight*0.7, 0); 
		DrawTriangles();
		glPopMatrix();
		glFlush();
		////Paper airplane5
		glPushMatrix();
		glTranslatef(150,40, 0);
		glTranslatef(flight*1.6, flight * 0.2, 0); 
		DrawTriangles();
		glPopMatrix();
		glFlush();
		////Paper airplane6
		glPushMatrix();
		glTranslatef(150, 40, 0);
		glTranslatef(flight*1.5, flight * 0.1, 0); 
		DrawTriangles();
		glPopMatrix();
		glFlush();

		//draw background cubes for light bulb
		glPushMatrix();
		bg();
		glPopMatrix();

		//middle bubble
		if (flag == 0) {
			// Draw circleL
			glPushMatrix();
			glTranslated(200, 80, 0);
			circleL();
			glPopMatrix();
			//draw Taicang
			glPushMatrix();
			glTranslated(0, 0, 0);
			drawTaicang();
			glPopMatrix();
			// Draw circleR
			glPushMatrix();
			glTranslated(200, 80, 0);
			circleR();
			glPopMatrix();
			//draw South Campus
			glPushMatrix();
			glTranslated(0, 0, 0);
			drawSouthCampus();
			glPopMatrix();
			// Draw circleM
			glPushMatrix();
			glTranslated(200, 80, 0);
			circleM();
			glPopMatrix();
			// Draw CB 
			glPushMatrix();
			glTranslated(0, 0, 0);
			drawCB();
			glPopMatrix();
			//star
			glPushMatrix();
			circlestarM();
			glPopMatrix();
			//cue words
			glColor3f(1, 1, 0);
			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(150, 450);
			drawString("North campus-Central Building");

			glColor3f(1, 1, 1);
			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(120, 80);
			drawString("Press 'l/L','r/R' to change bubbles");

			
		}
		//right bubble
		else if (flag == 1) {
			// Draw circleL
			glPushMatrix();
			/*glTranslated(500, 250, 0);*/
			glTranslated(200, 80, 0);
			circleL();
			glPopMatrix();
			glEnd();
			//draw Taicang
			glPushMatrix();
			/*glTranslated(400, 200, 0);*/
			drawTaicang();
			glPopMatrix();
			
			// Draw circleM
			glPushMatrix();
			/*glTranslated(50, -40, 0);*/
			glTranslated(200, 80, 0);
			circleM();
			glPopMatrix();
			// Draw CB 
			glPushMatrix();
			glTranslated(0, 0, 0);
			drawCB();
			glPopMatrix();

			// Draw circleR
			glPushMatrix();
			/*glTranslated(50, 30, 0);*/
			glTranslated(200, 80, 0);
			circleR();
			glPopMatrix();
			//SouthCampus
			glPushMatrix();
			/*glTranslated(50, 30, 0);*/
			drawSouthCampus();
			glPopMatrix();
			
			//star
			glPushMatrix();
			/*glTranslated(150, 50, 0);*/
			circlestarR();
			glPopMatrix();
			//cue words
			glColor3f(1, 1, 0);
			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(380, 500);
			drawString("South campus");

			glColor3f(1, 1, 1);
			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(0, 80);
			drawString("Press 'v/V' to zoom in, 'c/C' to zoom out on the South campus");

			glColor3f(1, 1, 1);
			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(120, 60);
			drawString("Press 'l/L','m/M' to change bubbles");

		}
		//left bubble
		else {
			
			// Draw circleR
			glPushMatrix();
			glTranslated(200, 80, 0);
			circleR();
			glPopMatrix();
			//South Campus
			glPushMatrix();
			glTranslated(0, 0, 0);
			drawSouthCampus();
			glPopMatrix();
			// Draw circleM
			glPushMatrix();
			glTranslated(200, 80, 0);
			circleM();
			glPopMatrix();
			// Draw CB 
			glPushMatrix();
			glTranslated(0, 0, 0);
			drawCB();
			glPopMatrix();
			// Draw circleL
			glPushMatrix();
			glTranslated(200, 80, 0);
			circleL();
			glPopMatrix();
			//draw Taicang
			glPushMatrix();
			glTranslated(0, 0, 0);
			drawTaicang();
			glPopMatrix();
			//star
			glPushMatrix();
			circlestarL();
			glPopMatrix();
			//cue words
			glColor3f(1, 1, 0);
			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(70, 320);
			drawString("TaiCang campus");

			glColor3f(1, 1, 1);
			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(0, 80);
			drawString("Press 'n/N' to zoom in, 'b/B' to zoom out on the TaiCang campus");

			glColor3f(1, 1, 1);
			selectFont(24, ANSI_CHARSET, "Helvetica");
			glRasterPos2f(120, 60);
			drawString("Press 'm/M','r/R' to change bubbles");
		}


		//light board words
		glPushMatrix();
		glTranslated(0, 0, 0);
		drawWords();
		glPopMatrix();

		//words
		glColor3f(0, 0, 0);
		TextOut(130, 575, "2024 XJTLU Graduation Ceremony");

		//words
		glColor3f(0, 0, 0);
		TextOut(220, 555, "Invitation Card");



		//Paper airplane
		glPushMatrix();
		glTranslatef(t, n, 0); 
		DrawTriangles();
		glPopMatrix();
		glFlush();


		// Draw Balloons
		glPushMatrix();
		drawBalloon();
		glPopMatrix();

	/*	glPushMatrix();
		glTranslated(0, 0 , 0);
		starM();
		glPopMatrix();
		

		glPushMatrix();
		glTranslated(0, 800 , 0);
		drawDoctoralCapSHOW();
		glPopMatrix();*/


		//Envelope
		glPushMatrix();
		glTranslatef(coverr, 0, 0);
		DrawCoverRight();
		glPopMatrix();
		glFlush();

		glPushMatrix();
		glTranslatef(coverl, 0, 0);
		DrawCoverLeft();
		glPopMatrix();
		glFlush();

		//mouse star
		glPushMatrix();
		glTranslated(0, 0 + coverl, 0);
		starM();
		glPopMatrix();
		//mouse cap
		glPushMatrix();
		glTranslated(0, 800 + coverl, 0);
		drawDoctoralCapSHOW();
		glPopMatrix();


		//cue words
		glColor3f(0, 0, 0);
		TextOut(150, 30+coverl, "press 'o' or 'O' to open the envelope");

		glColor3f(0, 0, 0);
		TextOut(80, 70 + coverl, "Click the right mouse button to show Doctoral Cap");

		glColor3f(0, 0, 0);
		TextOut(100, 50 + coverl, "Click the left mouse button to show Star");	
	}
	glutSwapBuffers();
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 850);
	glutCreateWindow("2024 XJTLU Graduation Ceremony Invitation Letter");
	

	//Timer
	glutTimerFunc(time_interval, TimerBalloon, 1);
	glutTimerFunc(time_interval, ChatTimer, 1);
	glutTimerFunc(time_interval, OnTimerCoverRight, 1);
	glutTimerFunc(time_intervalBG, BGBubbleTimer, 1);
	glutTimerFunc(time_interval, OnTimerCoverLeft, 1);
	glutTimerFunc(time_intervalBG, FallingStarTimer, 5);
	glutTimerFunc(time_intervalBGO, OnTimerOuterLetter, 1);
	glutTimerFunc(time_interval1, OnTimerLight, 1);
	glutTimerFunc(time_interval2, OnTimerFlight, 1);
	glutTimerFunc(time_interval, RotateBubbleTimer, 6);
	

	glutDisplayFunc(&myDisplay);
	glutIdleFunc(whenInMainloop);


	//interactions
	glutMouseFunc(mouse_input);
	glutKeyboardFunc(keyboard_input); 

	glutIdleFunc(idleDisplay);
	glutMainLoop();

}