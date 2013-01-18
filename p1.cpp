#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define RABBIT_CENTER_Y 1.0
#define HEAD_LENGTH 0.7
#define HEAD_WIDTH 0.7
#define HEAD_DEPTH 0.7
#define SNOUT_LENGTH 0.15
#define SNOUT_WIDTH 0.40
#define SNOUT_DEPTH 0.5
#define EYE_WIDTH 0.1
#define EYE_HEIGHT 0.15
#define NOSE_WIDTH 0.15
#define NOSE_DEPTH 0.2
#define EAR_LENGTH 0.8
#define EAR_WIDTH 0.4
#define EAR_DEPTH 0.15
#define NECK_LENGTH 0.7
#define NECK_WIDTH 0.6
#define NECK_DEPTH 0.5
#define M_BODY_LENGTH 1.0
#define M_BODY_WIDTH 0.8
#define M_BODY_DEPTH 0.8
#define U_BODY_LENGTH 0.7
#define U_BODY_WIDTH 0.8
#define U_BODY_DEPTH 0.8
#define L_BODY_LENGTH 0.7
#define L_BODY_WIDTH 0.6
#define L_BODY_DEPTH 0.8
#define TAIL_WIDTH 0.4
#define U_LEG_LENGTH 0.85
#define U_LEG_WIDTH 0.55
#define U_LEG_DEPTH 0.3
#define L_LEG_LENGTH 0.7
#define L_LEG_WIDTH 0.25
#define L_LEG_DEPTH 0.25
#define LEG_PAW_LENGTH 0.65
#define LEG_PAW_WIDTH 0.2
#define LEG_PAW_DEPTH 0.3
#define U_ARM_LENGTH 0.6
#define U_ARM_WIDTH 0.3
#define U_ARM_DEPTH 0.25
#define L_ARM_LENGTH 0.7
#define L_ARM_WIDTH 0.25
#define L_ARM_DEPTH 0.25
#define ARM_PAW_LENGTH 0.35
#define ARM_PAW_WIDTH 0.2
#define ARM_PAW_DEPTH 0.25

double neckAngle = 30;

int dumpPPM(int frameNum);

void drawRabbit();
void drawArm(GLfloat,GLfloat,GLfloat);
void drawLeg(GLfloat,GLfloat,GLfloat);
void drawBox(GLfloat,GLfloat,GLfloat);
void drawCube();
void drawAxis();
void drawFloor();

unsigned char camera = 'r';

int iCount = 0;       // used for numbering the PPM image files
int Width = 400;      // window width (pixels)
int Height = 400;     // window height (pixels)
bool Dump=false;      // flag set to true when dumping animation frames

void keyboardCallback(unsigned char c, int x, int y) {
	switch (c) {
	case 'q':
		exit (0);
		break;
	case 'p':
		camera = 'p';
		break;
	case 'f':
		camera = 'f';
		break;
	case 'b':
		camera = 'b';
		break;
	case 'a':
		camera = 'a';
		break;
	case 'u':
		camera = 'u';
		break;
	case 'r':
		camera = 'r';
		break;
	case 'h':
		neckAngle = 0;
		break;
	case 'i':
		dumpPPM(iCount);
		iCount++;
		break;
	case 'd':               // dump animation PPM frames
		iCount = 0;         // image file count
		Dump = !Dump;
		break;
	}

	glutPostRedisplay();
}

void reshapeCallback(int w, int h)
{
	Width = w;
	Height = h;
	glViewport(0, 0, w, h);
}

void displayCallback()
{
	// clear the color buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// set up camera
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45, 1.0, 0.1, 200.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( 0.0, 0.0, -10.0 );
	switch (camera) {
	case 'p':
		glRotatef( 180, 0.0, 1.0, 0.0 );
		break;
	case 'f':
		glRotatef( -90, 0.0, 1.0, 0.0 );
		break;
	case 'b':
		glRotatef( 90, 0.0, 1.0, 0.0 );
		break;
	case 'a':
		glRotatef( 90, 1.0, 0.0, 0.0 );
		break;
	case 'u':
		glRotatef( -90, 1.0, 0.0, 0.0 );
		break;
	case 'r':
		break;
	}

	// drawAxis();

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// Draw your rabbit here
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	drawRabbit();



	// draw after the opaque objects, since it is translucent
	drawFloor();

	// draw the buffer to the screen
	glutSwapBuffers();

	if (Dump) {               // save images to file
		dumpPPM(iCount);
		iCount++;
	}

	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
		printf("ERROR: %s\n", gluErrorString(error));
}


//---------------------------------------------------------------


void drawArm(GLfloat uArmAngle, GLfloat lArmAngle, GLfloat pawAngle) {
	glPushMatrix();

	// upper arm
	glRotatef(uArmAngle,0,0,1);
	glTranslatef(U_ARM_LENGTH/2,-U_ARM_WIDTH/2,0);
	drawBox(U_ARM_LENGTH,U_ARM_WIDTH,U_ARM_DEPTH);
	glPushMatrix();

	// lower arm
	glTranslatef(U_ARM_LENGTH/2-L_ARM_WIDTH/2,0,0);
	glRotatef(lArmAngle,0,0,1);
	glTranslatef(L_ARM_LENGTH/2,0,0);
	drawBox(L_ARM_LENGTH,L_ARM_WIDTH,L_ARM_DEPTH);
	glPushMatrix();

	// paw
	glTranslatef(L_ARM_LENGTH/2-ARM_PAW_WIDTH/2,0,0);
	glRotatef(pawAngle,0,0,1);
	glTranslatef(ARM_PAW_LENGTH/2,0,0);
	drawBox(ARM_PAW_LENGTH,ARM_PAW_WIDTH,ARM_PAW_DEPTH);
	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

void drawLeg(GLfloat uLegAngle, GLfloat lLegAngle, GLfloat pawAngle) {
	glPushMatrix();

	// upper leg
	glRotatef(uLegAngle,0,0,1);
	glTranslatef(U_LEG_LENGTH/2,0,0);
	drawBox(U_LEG_LENGTH,U_LEG_WIDTH,U_LEG_DEPTH);
	glPushMatrix();

	// lower leg
	glTranslatef(U_LEG_LENGTH/2,-U_LEG_WIDTH/2+L_LEG_WIDTH/2,0);
	glRotatef(lLegAngle,0,0,1);
	glTranslatef(L_LEG_LENGTH/2,0,0);
	drawBox(L_LEG_LENGTH,L_LEG_WIDTH,L_LEG_DEPTH);
	glPushMatrix();

	// leg paw
	glTranslatef(L_LEG_LENGTH/2,0,0);
	glRotatef(pawAngle,0,0,1);
	glTranslatef(LEG_PAW_LENGTH/2,0,0);
	drawBox(LEG_PAW_LENGTH,LEG_PAW_WIDTH,LEG_PAW_DEPTH);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawRabbit() {
	glColor3f(1,1,1);

	// mid body
	GLfloat mBodyAngle = 25;
	glPushMatrix();
	glTranslatef(0,RABBIT_CENTER_Y,0);
	glRotatef(mBodyAngle,0,0,1);
	drawBox(M_BODY_LENGTH, M_BODY_WIDTH, M_BODY_DEPTH);
	glPushMatrix();

	// lower body
	GLfloat lBodyAngle = 35;
	glTranslatef(-M_BODY_LENGTH/2,M_BODY_WIDTH/2,0);
	glRotatef(lBodyAngle,0,0,1);
	glTranslatef(-L_BODY_LENGTH/2,-L_BODY_WIDTH/2,0);
	drawBox(L_BODY_LENGTH, L_BODY_WIDTH, L_BODY_DEPTH);
	glPushMatrix();

	// tail
	GLfloat tailAngle = 45;
	glTranslated(-L_BODY_LENGTH/2,L_BODY_WIDTH/2,0);
	glRotatef(tailAngle,0,0,1);
	drawBox(TAIL_WIDTH,TAIL_WIDTH,TAIL_WIDTH);
	glPopMatrix();

	// right leg
	glColor4f(1,0,0,0.5);
	glPushMatrix();
	glTranslatef(-L_BODY_LENGTH/2,L_BODY_WIDTH/2-U_ARM_WIDTH/2,L_BODY_DEPTH/2+U_LEG_DEPTH/2);
	drawLeg(-45,-150,135);
	glPopMatrix();

	// left leg
	glPushMatrix();
	glTranslatef(-L_BODY_LENGTH/2,L_BODY_WIDTH/2-U_ARM_WIDTH/2,-L_BODY_DEPTH/2-U_LEG_DEPTH/2);
	drawLeg(-45,-150,135);
	glPopMatrix();

	// upper torso
	glColor3f(1,1,1);
	glPopMatrix();
	GLfloat uBodyAngle = -30;
	glTranslatef(M_BODY_LENGTH/2,M_BODY_WIDTH/2,0);
	glRotatef(uBodyAngle,0,0,1);
	glTranslatef(U_BODY_LENGTH/2,-U_BODY_WIDTH/2,0);
	drawBox(U_BODY_LENGTH, U_BODY_WIDTH, U_BODY_DEPTH);

	// right arm
	glColor4f(1,0,0,0.5);
	glPushMatrix();
	glTranslatef(U_BODY_LENGTH/2,-U_BODY_WIDTH/2,U_BODY_DEPTH/2);
	drawArm(-150,90,65);
	glPopMatrix();

	// right arm
	glColor4f(1,0,0,0.5);
	glPushMatrix();
	glTranslatef(U_BODY_LENGTH/2,-U_BODY_WIDTH/2,-U_BODY_DEPTH/2);
	drawArm(-150,90,65);
	glPopMatrix();

	// neck
	glColor4f(0,0,1,0.5);
	glTranslatef(U_BODY_LENGTH/2-NECK_WIDTH/2,U_BODY_WIDTH/2-NECK_WIDTH/2,0);
	glRotatef(neckAngle,0,0,1);
	glTranslatef(NECK_LENGTH/2,0,0);
	drawBox(NECK_LENGTH,NECK_WIDTH,NECK_DEPTH);
	glPushMatrix();

	// head
	glColor3f(1,1,1);
	glTranslatef(NECK_LENGTH/2,NECK_WIDTH/2,0);
	glRotatef(-45,0,0,1);
	glTranslatef(HEAD_LENGTH/2,-HEAD_WIDTH/2,0);
	drawBox(HEAD_LENGTH,HEAD_WIDTH,HEAD_DEPTH);
	glPushMatrix();

	// snout
	glTranslatef(HEAD_LENGTH/2+SNOUT_LENGTH/2,-HEAD_WIDTH/2+SNOUT_WIDTH/2,0);
	drawBox(SNOUT_LENGTH,SNOUT_WIDTH,SNOUT_DEPTH);

	// nose
	glColor3f(1,0.85,0.85);
	glTranslatef(SNOUT_LENGTH/2,0,0);
	drawBox(NOSE_WIDTH,NOSE_WIDTH,NOSE_DEPTH);
	glPopMatrix();

	// eyes
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(HEAD_LENGTH/2,HEAD_WIDTH/4,HEAD_DEPTH/2-EYE_WIDTH);
	drawBox(EYE_WIDTH,EYE_HEIGHT,EYE_WIDTH);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(HEAD_LENGTH/2,HEAD_WIDTH/4,-HEAD_DEPTH/2+EYE_WIDTH);
	drawBox(EYE_WIDTH,EYE_HEIGHT,EYE_WIDTH);
	glPopMatrix();

	// ears
	glColor3f(1,1,1);
	glPushMatrix();
	glTranslatef(0,HEAD_WIDTH/2,HEAD_DEPTH/2);
	glRotatef(90,0,0,1);
	glRotatef(-15,0,1,0);
	glTranslatef(EAR_LENGTH/2,0,0);
	drawBox(EAR_LENGTH,EAR_WIDTH,EAR_DEPTH);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,HEAD_WIDTH/2,-HEAD_DEPTH/2);
	glRotatef(90,0,0,1);
	glRotatef(15,0,1,0);
	glTranslatef(EAR_LENGTH/2,0,0);
	drawBox(EAR_LENGTH,EAR_WIDTH,EAR_DEPTH);
	glPopMatrix();


	
	glPopMatrix();
	glPopMatrix();

}

void drawBox(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glScalef(x,y,z);
	drawCube();
	glPopMatrix();
}

void drawCube() {
	glutSolidCube(1);
}


// Draw a set of coloured cones representing the current local coord system.
// X -> red, Y -> green, Z -> blue.
void drawAxis() {
	float axisHeight = 0.75; // TODO
	float axisBase = 0.075;
	glColor3f(0, 0, 1);
	glutSolidCone(axisBase, axisHeight, 8, 2);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glColor3f(1, 0, 0);
	glutSolidCone(axisBase, axisHeight, 8, 2);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glColor3f(0, 1, 0);
	glutSolidCone(axisBase, axisHeight, 8, 2);
	glPopMatrix();
}

void drawFloor() {
	// Draw a floor. Since it is transparent, we need to do it AFTER all of
	// the opaque objects.
	for (int x = -5; x < 5; x++) {
		for (int y = -5; y < 5; y++) {
			glColor4f(1, 1, 1, (x + y) % 2 ? 0.75 : 0.5);
			glNormal3f(0, 1, 0);
			glBegin(GL_POLYGON);
			glVertex3f(x    , 0, y    );
			glVertex3f(x + 1, 0, y    );
			glVertex3f(x + 1, 0, y + 1);
			glVertex3f(x    , 0, y + 1);
			glEnd();
		}
	}
	// visible from initial side angle
	glBegin(GL_POLYGON);
	glVertex3f(-5,    0, 0);
	glVertex3f(-5, -.05, 0);
	glVertex3f( 5, -.05, 0);
	glVertex3f( 5,    0, 0);
	glEnd();

	// visible from front angle
	glBegin(GL_POLYGON);
	glVertex3f(0,    0, -5);
	glVertex3f(0, -.05, -5);
	glVertex3f(0, -.05, 5);
	glVertex3f(0,    0, 5);
	glEnd();
}

int dumpPPM(int frameNum)
{
	FILE *fp;
	const int maxVal=255;
	register int y;
	unsigned char *pixels;

	glReadBuffer( GL_FRONT );
	char fname[100];
	sprintf(fname,"./ppm/img%03d.ppm",frameNum);
	fp = fopen(fname,"wb");
	if (!fp) {
		printf("Unable to open file '%s'\n",fname);
		return 1;
	}
	printf("Saving image `%s`\n",fname);
	fprintf(fp, "P6 ");
	fprintf(fp, "%d %d ", Width, Height);
	fprintf(fp, "%d", maxVal);
	putc(13,fp);
	pixels = new unsigned char [3*Width];

	y = 0;
	glReadPixels(0,Height-1,Width,1,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) pixels);

	for ( y = Height-1; y >=0; y-- ) {
		glReadPixels(0,y,Width,1,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) pixels);
		for (int n=0; n<3*Width; n++) {
			putc(pixels[n],fp);
		}
	}
	fclose(fp);
	delete [] pixels;
	return 0;
}

//---------------------------------------------------------------

int main(int argc, char **argv)
{
	// create window and rendering context
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize( Width, Height );
	glutCreateWindow( "Rabbit" );

	// register display callback
	glutDisplayFunc( displayCallback );
	glutKeyboardFunc( keyboardCallback );

	glViewport( 0, 0, Width, Height );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_NORMALIZE );

	// Turn on blending (for floor).
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// lighting stuff
	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuse[] = {0.9, 0.9, 0.9, 1.0};
	GLfloat specular[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat position0[] = {1.0, 1.0, 1.0, 0.0};
	glLightfv( GL_LIGHT0, GL_POSITION, position0 );
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
	GLfloat position1[] = {-1.0, -1.0, -1.0, 0.0};
	glLightfv( GL_LIGHT1, GL_POSITION, position1 );
	glLightfv( GL_LIGHT1, GL_AMBIENT, ambient );
	glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT1, GL_SPECULAR, specular );

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHT1 );
	glEnable( GL_COLOR_MATERIAL );

	// pass control over to GLUT
	glutMainLoop();

	return 0;       // never reached
}

