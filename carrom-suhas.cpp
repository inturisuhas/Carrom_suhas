#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "stdio.h"
using namespace std;

#define PI 3.141592653589
#define DEG2radiu(deg) (deg * PI / 180)
class COIN{
	public:

		void set_circle(float x, float  y, float r)
		{
			center_x = x;
			center_y = y;
			radiu = r;
		}
		float center_x;
		float center_y;
		float radiu;
		double velocity_x;
		double velocity_y;
		float mass;
};
COIN carrom[10];
char scbuf[100];
float lift_x = 2.0f;
float lift_y = 0.0f;
float striker_velx,striker_vely;
int i,j;
int flag=0;
int flags[10];
float pointer,speed;
float place1_x,place1_y,place2_y,place2_x;
int zero;
int rep=0;
//Below declaration used for stacking the coins
float pos_x = 3.8f;
float pos_y = -1.2f;
//Score
void renderBitmapString(
float x,
float y,
float z,
void *font,
char *string) {

char *c;
glRasterPos3f(x, y,z);
for (c=string; *c != '\0'; c++) {
glutBitmapCharacter(font, *c);
}
}
int score = 100;
// Function Declarations
void scoreup(int value);
void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float radiu);
void drawCircle(float radiu);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleKeypress3(unsigned char key, int x, int y);
void handleKeypress4(unsigned char key, int x, int y);
//void handleMouseclick(int button, int state, int x, int y);
//below declarations have been commented to understand the code
// Global Variables

float ball_velx1 = 0.0f;
float ball_vely1 = 0.0f;
float ball_radiu1 = 0.15f;
float box_len_in = 4.99f;
float box_len_out = 5.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;



float ball_velx2 = 0.00f;
float ball_vely2 = 0.00f;
float ball_radiu2 = 0.084f;
void setup() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
//Assuming that the radiuius of circle in which the coins are kept initially is 0.5f
// 0-striker 1-red 2,3,4,5 - carrom 6,7,8,9 - black
void declaration(){
	//striker position and velocity
	carrom[0].center_x = 0.02f;
	carrom[0].center_y = -1.9f;
	carrom[0].velocity_x = ball_velx1;
	carrom[0].velocity_y = ball_vely1;
	//striker radiuius
	carrom[0].radiu = ball_radiu1;
	//striker mass
	carrom[0].mass = 5;
	//balls position and velocity
	carrom[1].center_x = 0.1f;carrom[1].center_y = 0.1f;
	carrom[2].center_x = 0.6f;carrom[2].center_y = 0.1f;
	carrom[3].center_x = 0.1f;carrom[3].center_y = 0.6f;
	carrom[4].center_x = -0.4f;carrom[4].center_y = 0.1f;
	carrom[5].center_x = 0.1f;carrom[5].center_y = -0.4f;
	carrom[6].center_x = 0.453f;carrom[6].center_y = 0.453f;
	carrom[7].center_x = -0.27f;carrom[7].center_y = 0.45f;
	carrom[8].center_x = -0.27f;carrom[8].center_y = -0.27f;
	carrom[9].center_x = 0.45f;carrom[9].center_y = -0.27f;
	carrom[1].velocity_x = carrom[2].velocity_x = carrom[3].velocity_x = carrom[4].velocity_x = carrom[5].velocity_x = carrom[6].velocity_x = carrom[7].velocity_x = carrom[8].velocity_x = carrom[9].velocity_x = ball_velx2;
	carrom[1].velocity_y = carrom[2].velocity_y = carrom[3].velocity_y = carrom[4].velocity_y = carrom[5].velocity_y = carrom[6].velocity_y = carrom[7].velocity_y  = carrom[8].velocity_y = carrom[9].velocity_y = ball_vely2;
	//coins radius
	carrom[1].radiu = carrom[2].radiu = carrom[3].radiu = carrom[4].radiu = carrom[5].radiu = carrom[6].radiu  = carrom[7].radiu = carrom[8].radiu  = carrom[9].radiu = ball_radiu2;
	//Mass declaration for all the coins
	carrom[1].mass = carrom[2].mass = carrom[3].mass = carrom[4].mass = carrom[5].mass = carrom[6].mass = carrom[7].mass =  carrom[8].mass = carrom[9].mass = 1;
}


float striker_x,x19;
float striker_y,y19;
void motion(int x, int y)
{
	striker_x = x * 1.0;
	striker_y = y * 1.0;
	striker_x = ((2.0 / float(1300)) * striker_x) - 1.0;
	striker_y = ((2.0 / float(715)) * striker_y) - 1.0;
	striker_y = -striker_y;
	//printf("=====%f\n",striker_y );
	//printf("%f\n",striker_x );
	if(striker_x < 0.13 && striker_x > -0.57)
	{
		carrom[0].set_circle(striker_x, -0.524f, 0.025f);
		glPushMatrix();
		glColor3f(0.0,1.0,0.0);
		carrom[0].center_x = striker_x;
		carrom[0].center_y = -0.524f;
		carrom[0].center_y = carrom[0].center_y;
		carrom[0].center_x = carrom[0].center_x;
		//printf("%f %f\n",carrom[0].center_x,carrom[0].center_y);
		glEnd();
		glPopMatrix();
		glutSwapBuffers();
	}
	else if(striker_x < -0.57)
		carrom[0].center_x = -0.57;
	else if(striker_x > 0.13)
		carrom[0].center_x = 0.135;

		//glutPostRedisplay();
}


void replay()
{
	//puts("dec\n");
	carrom[0].center_x = 0.02f;
	carrom[0].center_y = -1.9f;
	carrom[1].center_x = 0.1f;carrom[1].center_y = 0.1f;
	carrom[2].center_x = 0.6f;carrom[2].center_y = 0.1f;
	carrom[3].center_x = 0.1f;carrom[3].center_y = 0.6f;
	carrom[4].center_x = -0.4f;carrom[4].center_y = 0.1f;
	carrom[5].center_x = 0.1f;carrom[5].center_y = -0.4f;
	carrom[6].center_x = 0.453f;carrom[6].center_y = 0.453f;
	carrom[7].center_x = -0.27f;carrom[7].center_y = 0.45f;
	carrom[8].center_x = -0.27f;carrom[8].center_y = -0.27f;
	carrom[9].center_x = 0.45f;carrom[9].center_y = -0.27f;
	pointer = -0.9;
	for(i=1;i<10;i++)
	{
		carrom[i].radiu = 0.084f;
		carrom[i].velocity_x = 0.0;
		carrom[i].velocity_y = 0.0;
		carrom[i].mass = 1.0;
		flags[i]=0;
	}
	carrom[0].radiu = 0.15;
	carrom[0].mass = 5.0;
	flags[0]=0;
	place1_y = 0.8;
	place1_x = 0.8;
	place2_x = 0.8;
	place2_y = 0.8;
	zero = 0;
}
int main(int argc, char **argv) {

	declaration();
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w * 2 / 3;
	int windowHeight = h * 2 / 3;
	setup();
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("Carrom game - SUHAS");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	//glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	//glutTimerFunc(100, update, 0);
	glutTimerFunc(1000,scoreup,0);
	glutMainLoop();
	return 0;
}

// Function to draw objects on the screen
void drawScene() {

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw outer Box
	glTranslatef(0.0f, 0.0f, -7.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawBox(box_len_out);
	//Draw inner box
	glTranslatef(0.0f,0.0f,-1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f,0.79f,0.6f);
	drawBox(box_len_in);
	/*   //Draw per rectangle
	     glTranslatef(0.5f,1.8f,-2.0f);
	     glColor3f(0.0f,0.0f,0.0f);
	//drawBox_small(box_len_in_1_up);
	glBegin(GL_LINES);
	glVertex2f(2.1f,0.8f);
	glVertex2f(2.1f,0.6f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(2.1f,0.6f);
	glVertex2f(-3.1f,0.6f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-3.1f,0.6f);
	glVertex2f(-3.1f,0.8f);
	glEnd();	
	glBegin(GL_LINES);
	glVertex2f(-3.1f,0.8f);
	glVertex2f(2.1f,0.8f);
	glEnd();
	glEnd();*/
	//Left and right rectangles
	for(int i=1;i<3;i++)
	{
		glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex2f(pow(-1,i)*2.0f,pow(-1,i)*1.7f);
		glVertex2f(pow(-1,i)*1.8f,pow(-1,i)*1.7f);
		glVertex2f(pow(-1,i)*1.8f,pow(-1,i)*1.7f);
		glVertex2f(pow(-1,i)*1.8f,pow(-1,i+1)*1.7f);
		glVertex2f(pow(-1,i)*1.8f,pow(-1,i+1)*1.7f);
		glVertex2f(pow(-1,i)*2.0f,pow(-1,i+1)*1.7f);
		glVertex2f(pow(-1,i)*2.0f,pow(-1,i+1)*1.7f);
		glVertex2f(pow(-1,i)*2.0f,pow(-1,i)*1.7f);
		glEnd();
		glPopMatrix();
		for(int j=1;j<3;j++)
		{
			glPushMatrix();
			switch(j)
			{
				case 1:
					glTranslatef(pow(-1,i)*1.9f,pow(-1,i)*1.68f, 0.0f);
					break;
				case 2:
					glTranslatef(pow(-1,i)*1.9f,pow(-1,i+1)*1.68f, 0.0f);
					break;
			}
			glColor3f(1.0f,0.0f,0.0f);
			drawBall(0.12f);
			glPopMatrix();
		}

	}
	// Upper and Lower Rectangle Bars
	for(int i=1;i<3;i++)
	{
		glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex2f(pow(-1,i)*1.7f,pow(-1,i+1)*2.0f);
		glVertex2f(pow(-1,i)*1.7f,pow(-1,i+1)*1.8f);
		glVertex2f(pow(-1,i)*1.7f,pow(-1,i+1)*1.8f);
		glVertex2f(pow(-1,i+1)*1.7f,pow(-1,i+1)*1.8f);
		glVertex2f(pow(-1,i+1)*1.7f,pow(-1,i+1)*1.8f);
		glVertex2f(pow(-1,i+1)*1.7f,pow(-1,i+1)*2.0f);
		glVertex2f(pow(-1,i+1)*1.7f,pow(-1,i+1)*2.0f);
		glVertex2f(pow(-1,i)*1.7f,pow(-1,i+1)*2.0f);
		glEnd();
		glPopMatrix();


		// Red Circle for upper and lower rectangles
		for(int j=1;j<3;j++)
		{
			glPushMatrix();
			switch(j)
			{
				case 1:
					glTranslatef(pow(-1,i)*1.67f,pow(-1,i+1)*1.9f, 0.0f);
					break;
				case 2:
					glTranslatef(pow(-1,i+1)*1.67f,pow(-1,i+1)*1.9f, 0.0f);
					break;
			}
			glColor3f(1.0f,0.0f,0.0f);
			drawBall(0.12f);
			glPopMatrix();
		}


	}



	//Holes start
	glPushMatrix();
	glTranslatef(2.3f,2.3f, 0.0f);
	glColor3f(0.095f, .158f, 0.160f);
	drawBall(0.199f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.3f,-2.3f, 0.0f);
	glColor3f(0.095f, .158f, 0.160f);
	drawBall(0.199f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.3f,2.3f, 0.0f);
	glColor3f(0.095f, .158f, 0.160f);
	drawBall(0.199f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.3f,-2.3f, 0.0f);

	glColor3f(0.095f, .158f, 0.160f);
	drawBall(0.199f);
	glPopMatrix();

	//Holes done
	//Middle circle
	glPushMatrix();
	glTranslatef(0.1f,0.1f, 0.1f);
	glColor3f(1.0f,1.0f,0.0f);
	drawBall(0.8f);
	glColor3f(1.0f,0.79f,0.6f);
	drawBall(0.6f);

	glPopMatrix();

	glEnd();
	//Middle circle drawn
	// Draw striker
	glPushMatrix();
	glTranslatef(carrom[0].center_x, carrom[0].center_y, 0.0f);

	glColor3f(0.57f, 0.439f, 0.85f);
	drawBall(carrom[0].radiu);
	glPopMatrix();
	//Draw red coin
	glPushMatrix();
	glTranslatef(carrom[1].center_x,carrom[1].center_y, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawBall(ball_radiu2);

	glPopMatrix();
	//Pointer
	glPushMatrix();
	glTranslatef(lift_x,lift_y, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawBall(0.05f);

	glPopMatrix();
	//Draw coins
	for(int k=1;k<9;k++)
	{
		glPushMatrix();
		glTranslatef(carrom[k+1].center_x,carrom[k+1].center_y, 0.0f);
		if (k<5){	
			glColor3f(0.823f, 0.411f, 0.117f);}
		else
		{
			glColor3f(0.0f,0.0f,0.0f);
		}
		drawBall(ball_radiu2);

		glPopMatrix();
	}
	//Coins drawn



	/*    // Draw Triangle
	      glPushMatrix();
	      glTranslatef(tri_x, tri_y, 0.0f);
	      glRotatef(theta, 0.0f, 0.0f, 1.0f);
	      glScalef(0.5f, 0.5f, 0.5f);
	      drawTriangle();
	      glPopMatrix();*/
	// speedometer
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0,1.0,0.0);
	glVertex2f(3.2,-1.3);
	glVertex2f(3.4,-1.3);
	glVertex2f(3.4,pointer);
	glVertex2f(3.2,pointer);
	glColor3f(1.0,0.0,0.1);
	glVertex2f(3.2,1.3);
	glVertex2f(3.4,1.3);
	glVertex2f(3.4,pointer);
	glVertex2f(3.2,pointer);
	glEnd();
	//glBegin(GL_LINES);
	glColor3f(0.4,0.3,0.1);
	glVertex2f(0.6,pointer);
	glVertex2f(0.3,pointer);
	//glEnd();
	glPopMatrix();
	/*//Stack for carrom coins
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.25f,.264f,.65f);
	glVertex2f(3.8,1.0);
	glVertex2f(5.5,1.0);
	glVertex2f(5.5,1.3);
	glVertex2f(3.8,1.3);
	glEnd();
	glPopMatrix();	
	//Stack for red coin
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.15f,.464f,.9f);
	glVertex2f(4.2,0.5);
	glVertex2f(4.8,0.5);
	glVertex2f(4.8,0.2);
	glVertex2f(4.2,0.2);
	glEnd();
	glPopMatrix();	
	//Stack for black coins

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.35f,.764f,.55f);
	glVertex2f(3.8,-0.9);
	glVertex2f(5.5,-0.9);
	glVertex2f(5.5,-1.2);
	glVertex2f(3.8,-1.2);
	glEnd();
	glPopMatrix();*/
sprintf(scbuf,"%d",score);
//printf("asd");
renderBitmapString(3.5,2.56,0.0f,GLUT_BITMAP_HELVETICA_18,scbuf);	
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
float theta;
float slope;
float count = 1.0;
float final_velocity_x,final_velocity_y,f_velocity_y,f_velocity_x;
void update(int value) {

	// Handle ball collisions with box
	if(carrom[0].center_x + carrom[0].radiu > box_len_in/2)
		carrom[0].velocity_x = -fabs(carrom[0].velocity_x);
	else if(carrom[0].center_x - carrom[0].radiu < -box_len_in/2)
		carrom[0].velocity_x = fabs(carrom[0].velocity_x);
	else if(carrom[0].center_y + carrom[0].radiu > box_len_in/2)
		carrom[0].velocity_y = -fabs(carrom[0].velocity_y);
	else if(carrom[0].center_y - carrom[0].radiu < -box_len_in/2)
		carrom[0].velocity_y = fabs(carrom[0].velocity_y);
	//Update striker position after collision with wall
	carrom[0].center_x  += carrom[0].velocity_x;
	carrom[0].center_y  += carrom[0].velocity_y;
	//CHECK THE BELOW FOR LOOPS VALIDITY
	for(int i = 1;i<10;i++)
	{	
		if(carrom[i].center_x + carrom[i].radiu > box_len_in/2)
		carrom[i].velocity_x = -fabs(carrom[i].velocity_x);
	else if(carrom[i].center_x - carrom[i].radiu < -box_len_in/2)
		carrom[i].velocity_x = fabs(carrom[i].velocity_x);
	else if(carrom[i].center_y + carrom[i].radiu > box_len_in/2)
		carrom[i].velocity_y = -fabs(carrom[i].velocity_y);
	else if(carrom[i].center_y - carrom[i].radiu < -box_len_in/2)
		carrom[i].velocity_y = fabs(carrom[i].velocity_y);

		// Update position of ball

		carrom[i].center_x  += carrom[i].velocity_x;
		carrom[i].center_y += carrom[i].velocity_y;
	}
	//Ball to ball collisions
	for(int i=0;i<10;i++)
	{

		for(int j=i+1;j<10;j++)
		{
			float dom = carrom[i].center_x - carrom[j].center_x;
			float dom2 = carrom[i].center_y - carrom[j].center_y;
			float total_dist = sqrt(dom*dom + dom2*dom2);
			//printf("%f",total_dist);

			if(total_dist <= carrom[i].radiu + carrom[j].radiu)
			{
				float collision[2];
				collision[0]=dom;
				collision[1]=dom2;
				float distance = sqrt((dom*dom) + (dom2*dom2)) ;
				//printf("h\n");
				float unor[2];   unor[0]=collision[0]/distance;  unor[1] = collision[1]/distance;
				float u1[2]; u1[0]=carrom[i].velocity_x; u1[1]=carrom[i].velocity_y;
				float u2[2]; u2[0]=carrom[j].velocity_x; u2[1]=carrom[j].velocity_y;
				float utang[2]; utang[0]=-1*unor[1]; utang[1]=unor[0];
				float u1n = unor[0] * u1[0] + unor[1] * u1[1];
				float u1t = utang[0] * u1[0] + utang[1] * u1[1];
				float u2n = unor[0] * u2[0] + unor[1] * u2[1];
				float u2t = utang[0] * u2[0] + utang[1] * u2[1];    
				float v1n = (u1n * (carrom[i].mass - carrom[j].mass)+ (2 * carrom[j].mass * u2n))/(carrom[i].mass + carrom[j].mass);
				float v2n = (u2n * (carrom[j].mass - carrom[i].mass)+ (2 * carrom[i].mass * u1n))/(carrom[i].mass + carrom[j].mass);
				float v1nf[2]; v1nf[0] = v1n * unor[0]; v1nf[1] = v1n * unor[1];
				float v1tf[2]; v1tf[0] = u1t * utang[0]; v1tf[1] = u1t * utang[1];
				float v2nf[2]; v2nf[0] = v2n * unor[0]; v2nf[1] = v2n * unor[1];
				float v2tf[2]; v2tf[0] = u2t * utang[0]; v2tf[1] = u2t * utang[1];
				float v1[2]; v1[0] = v1nf[0] + v1tf[0];  v1[1] = v1nf[1] + v1tf[1];
				float v2[2]; v2[0] = v2nf[0] + v2tf[0];  v2[1] = v2nf[1] + v2tf[1];
				carrom[i].velocity_x = v1[0];
				carrom[i].velocity_y = v1[1];
				carrom[j].velocity_x = v2[0];
				carrom[j].velocity_y = v2[1];
				carrom[i].velocity_x *= 0.97;
				carrom[i].velocity_y *= 0.97;
				carrom[j].velocity_x *= 0.97;
				carrom[j].velocity_y *= 0.97;
				carrom[i].center_x += carrom[i].velocity_x;
				carrom[i].center_y += carrom[i].velocity_y;
				carrom[j].center_x += carrom[j].velocity_x;
				carrom[j].center_y += carrom[j].velocity_y;
				//printf("ggggg \n");

			}
		}
		carrom[i].velocity_x *= 0.97;
		carrom[i].velocity_y *= 0.97;
		carrom[i].center_x += carrom[i].velocity_x;
		carrom[i].center_y += carrom[i].velocity_y;


	}
	//printf("%f",carrom[0].velocity_x);
	//printf("%f \n",carrom[0].velocity_y);

	//Pocket coin interaction
	for(int i = 1 ; i<10;i++){
		float p1 = carrom[i].center_x - 2.3;float p2 = carrom[i].center_y - 2.3;
		float p3 = carrom[i].center_x + 2.3;float p4 = carrom[i].center_y - 2.3;
		float p5 = carrom[i].center_x + 2.3;float p6 = carrom[i].center_y + 2.3;
		float p7 = carrom[i].center_x - 2.3;float p8 = carrom[i].center_y + 2.3;
		float pocket_distance1 = sqrt((p1 * p1 )+ (p2 * p2));
		float pocket_distance2 = sqrt((p3 * p3 )+ (p4 * p4));
		float pocket_distance3 = sqrt((p5 * p5 )+ (p6 * p6));
		float pocket_distance4 = sqrt((p7 * p7 )+ (p8 * p8));//printf("%d",i);
		if (pocket_distance1<= 0.2f ||pocket_distance2<= 0.2f ||pocket_distance3<= 0.2f ||pocket_distance4<= 0.2f )
		{//printf("%d",i);
			if (i == 1)
			{			
			score += 50;
			carrom[i].center_x = pos_x;carrom[i].center_y = pos_y;
			carrom[i].velocity_x = 0;carrom[i].velocity_y = 0;
			pos_y = pos_y + 0.2;rep++;
			}
			else if (i>1 && i<6)
			{//printf("carrom");
			score += 10;
			carrom[i].center_x = pos_x;carrom[i].center_y = pos_y;
			carrom[i].velocity_x = 0;carrom[i].velocity_y = 0;
			pos_y = pos_y + 0.2;rep++;
			}
			else if (i>5 && i<10)
			{
//printf("blavk");
			score = score -5;
			carrom[i].center_x = pos_x;carrom[i].center_y = pos_y;
			carrom[i].velocity_x = 0;carrom[i].velocity_y = 0;
			pos_y = pos_y + 0.2;
			}
		  
		}

}
if(rep % 5 ==0)
{replay();}
if(value == 0)
{
	//printf("adfsdf");
	carrom[0].center_x = 0.02f;
	carrom[0].center_y = -1.9f;
}
if (value > 0){

	glutTimerFunc(20, update, value-1);
	}}

void drawBox(float len) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f(-len / 2, -len / 2);
	glVertex2f(len / 2, -len / 2);
	glVertex2f(len / 2, len / 2);
	glVertex2f(-len / 2, len / 2);





	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void scoreup(int value)
{
score=score-1;
glutTimerFunc(1000,scoreup,0);
}
void drawCircle(float radiu){
	glBegin(GL_POINTS);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(radiu * cos(DEG2radiu(i)), radiu * sin(DEG2radiu(i)));
	}
	glEnd();
}
void drawBall(float radiu) {

	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(radiu * cos(DEG2radiu(i)), radiu * sin(DEG2radiu(i)));
	}
	glEnd();
}



void drawTriangle() {

	glBegin(GL_TRIANGLES);
	glColor3f(5.0f, 0.0f, 1.0f);
	glVertex3f(6.0f, 3.0f, 3.0f);
	glColor3f(5.0f, 1.0f, 0.0f);
	glVertex3f(6.0f, 3.0f, 3.0f);
	glColor3f(5.0f, 5.0f, 0.0f);
	glVertex3f(6.0f, 3.0f, 3.0f);
	glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);     // escape key is pressed
	}
	if (key == 32)   //Press Space for shot
	{
		slope = (lift_y - carrom[0].center_y) / (lift_x - carrom[0].center_x);
		theta = atan(slope);
		if(theta<0)
			theta+=PI;
		//if(pointer <= 0.5)
		//{
		speed = pointer + 1.1;
		//} 
		//else
		//speed = pointer; 
		striker_velx = speed * 0.1;
		count = 1.0;
		for(i=1;i<10;i++)
		{
			carrom[i].velocity_x = 0.0;
			carrom[i].velocity_y = 0.0;
		}
		carrom[0].velocity_x = striker_velx * cos(theta);
		carrom[0].velocity_y = striker_velx * sin(theta);
		//printf("%f %f\n",carrom[0].velocity_x,carrom[0].velocity_y);
		glutTimerFunc(20, update, 100);
		//   printf("%f %f\n",carrom[0].velocity_x,carrom[0].velocity_y);
	}
	if(key == 'r')
	{
		replay();
		score = 100;
	}
	if(key == 13)
	{
		lift_x = 2.0f;
		lift_y = 0.0f;
		flag=11;
	}

	if(key == 97 && lift_x >=-2.5 && lift_x<=2.5 && lift_y>=-2.5 && lift_y<=2.5)
		lift_x -= 0.1f;
	if(key == 115 && lift_x >=-2.5 && lift_x<=2.5 && lift_y>=-2.5 && lift_y<=2.5)
		lift_y -= 0.1f;
	if(key == 100 && lift_x >=-2.5 && lift_x<=2.5 && lift_y>=-2.5 && lift_y<=2.5)
		lift_x += 0.1f;
	if(key == 119 && lift_x >=-2.5 && lift_x<=2.5 && lift_y>=-2.5 && lift_y<=2.5)
		lift_y += 0.1f;
	if(lift_y < -2.5f)
		lift_y = -2.5f;
	else if(lift_y > 2.5f)
		lift_y = 2.5f;
	else if(lift_x < -2.5f)
		lift_x = -2.5f;
	else if(lift_x > 2.5f)
		lift_x = 2.5f;
	//printf("%f %f\n",lift_x,lift_y);
	return;
}

void handleKeypress2(int key, int x, int y) {

	if(key == GLUT_KEY_UP && pointer <= 1.5)
	{
		pointer += 0.07; 
	}
	if(key == GLUT_KEY_DOWN && pointer >= -1.5)
	{
		pointer -= 0.07;
	}
	if (key == GLUT_KEY_LEFT && carrom[0].center_x >=-1.8f && carrom[0].center_x <= 1.8f)
		carrom[0].center_x -= 0.01;
	else if (key == GLUT_KEY_RIGHT && carrom[0].center_x >= -1.8f && carrom[0].center_x <= 1.8f)
		carrom[0].center_x += 0.01;
	else if (carrom[0].center_x < -1.8)
		carrom[0].center_x = -1.8;
	else if (carrom[0].center_x > 1.8)
		carrom[0].center_x = 1.8;

}
float marker_x;
float marker_y;
void motion(int , int);
/*void handleMouseclick(int button, int state, int x, int y) {

  switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN)
            {   
                glColor3f(0.0,1.0,0.0);
                marker_x = ((2.0 / float(1300)) * x*1.0) - 1.0;
                marker_y = ((2.0 / float(715)) * y*1.0) - 1.0;
                printf("%f\n",marker_x);
                printf("%f\n",marker_y);
                glVertex2f(marker_x,marker_y);
                
            }
            break;
    }
  }*/
