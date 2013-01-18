#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include "rabbit.h"

int dumpPPM(int frameNum);

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

void drawEar(GLfloat earAngle) {
	glPushMatrix();
	glRotatef(earAngle,1,0,0);
	glTranslatef(0,EAR_WIDTH/2,0);
	drawBox(EAR_LENGTH,EAR_WIDTH,EAR_DEPTH);
	glPopMatrix();
}

void drawArm(GLfloat uArmAngle, GLfloat lArmAngle, GLfloat pawAngle) {
	glPushMatrix();

	// upper arm
	glRotatef(UBODY_UARM_ANGLE+uArmAngle,0,0,1);
	glTranslatef(U_ARM_LENGTH/2,-U_ARM_WIDTH/2,0);
	drawBox(U_ARM_LENGTH,U_ARM_WIDTH,U_ARM_DEPTH);
	glPushMatrix();

	// lower arm
	glTranslatef(U_ARM_LENGTH/2-L_ARM_WIDTH/2,0,0);
	glRotatef(UARM_LARM_ANGLE+lArmAngle,0,0,1);
	glTranslatef(L_ARM_LENGTH/2,0,0);
	drawBox(L_ARM_LENGTH,L_ARM_WIDTH,L_ARM_DEPTH);
	glPushMatrix();

	// paw
	glTranslatef(L_ARM_LENGTH/2-ARM_PAW_WIDTH/2,0,0);
	glRotatef(LARM_PAW_ANGLE+pawAngle,0,0,1);
	glTranslatef(ARM_PAW_LENGTH/2,0,0);
	drawBox(ARM_PAW_LENGTH,ARM_PAW_WIDTH,ARM_PAW_DEPTH);
	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

void drawLeg(GLfloat uLegAngle, GLfloat lLegAngle, GLfloat pawAngle) {
	glPushMatrix();

	// upper leg
	glRotatef(MBODY_ULEG_ANGLE+uLegAngle,0,0,1);
	glTranslatef(U_LEG_LENGTH/2,0,0);
	drawBox(U_LEG_LENGTH,U_LEG_WIDTH,U_LEG_DEPTH);
	glPushMatrix();

	// lower leg
	glTranslatef(U_LEG_LENGTH/2,-U_LEG_WIDTH/2+L_LEG_WIDTH/2,0);
	glRotatef(ULEG_LLEG_ANGLE+lLegAngle,0,0,1);
	glTranslatef(L_LEG_LENGTH/2,0,0);
	drawBox(L_LEG_LENGTH,L_LEG_WIDTH,L_LEG_DEPTH);
	glPushMatrix();

	// leg paw
	glTranslatef(L_LEG_LENGTH/2,0,0);
	glRotatef(LLEG_PAW_ANGLE+pawAngle,0,0,1);
	glTranslatef(LEG_PAW_LENGTH/2,0,0);
	drawBox(LEG_PAW_LENGTH,LEG_PAW_WIDTH,LEG_PAW_DEPTH);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawRabbit() {
	glColor3f(1,1,1);

	// mid body
	glPushMatrix();
	glTranslatef(0,rabbitY,0);
	glRotatef(GROUND_MBODY_ANGLE+mBodyAngle,0,0,1);
	drawBox(M_BODY_LENGTH, M_BODY_WIDTH, M_BODY_DEPTH);
	glPushMatrix();

	// lower body
	glTranslatef(-M_BODY_LENGTH/2,M_BODY_WIDTH/2,0);
	glRotatef(MBODY_LBODY_ANGLE+lBodyAngle,0,0,1);
	glTranslatef(-L_BODY_LENGTH/2,-L_BODY_WIDTH/2,0);
	drawBox(L_BODY_LENGTH, L_BODY_WIDTH, L_BODY_DEPTH);
	glPushMatrix();

	// tail
	glTranslated(-L_BODY_LENGTH/2,L_BODY_WIDTH/2,0);
	glRotatef(LBODY_TAIL_ANGLE,0,0,1);
	drawBox(TAIL_WIDTH,TAIL_WIDTH,TAIL_WIDTH);
	glPopMatrix();

	// right leg
	glPushMatrix();
	glTranslatef(-L_BODY_LENGTH/2,L_BODY_WIDTH/2-U_ARM_WIDTH/2,L_BODY_DEPTH/2+U_LEG_DEPTH/2);
	drawLeg(uRLegAngle,lRLegAngle,rLegPawAngle);
	glPopMatrix();

	// left leg
	glPushMatrix();
	glTranslatef(-L_BODY_LENGTH/2,L_BODY_WIDTH/2-U_ARM_WIDTH/2,-L_BODY_DEPTH/2-U_LEG_DEPTH/2);
	drawLeg(uLLegAngle,lLLegAngle,lLegPawAngle);
	glPopMatrix();

	// upper torso
	glPopMatrix();
	glTranslatef(M_BODY_LENGTH/2,M_BODY_WIDTH/2,0);
	glRotatef(MBODY_UBODY_ANGLE+uBodyAngle,0,0,1);
	glTranslatef(U_BODY_LENGTH/2,-U_BODY_WIDTH/2,0);
	drawBox(U_BODY_LENGTH, U_BODY_WIDTH, U_BODY_DEPTH);
	glPushMatrix();

	// right arm
	glTranslatef(U_BODY_LENGTH/2,-U_BODY_WIDTH/2,U_BODY_DEPTH/2);
	drawArm(uRArmAngle,lRArmAngle,rArmPaw);
	glPopMatrix();
	glPushMatrix();

	// right arm
	glTranslatef(U_BODY_LENGTH/2,-U_BODY_WIDTH/2,-U_BODY_DEPTH/2);
	drawArm(uLArmAngle,lLArmAngle,lArmPaw);
	glPopMatrix();

	// neck
	glTranslatef(U_BODY_LENGTH/2-NECK_WIDTH/2,U_BODY_WIDTH/2-NECK_WIDTH/2,0);
	glRotatef(HEAD_NECK_ANGLE+neckAngle,0,0,1);
	glTranslatef(NECK_LENGTH/2,0,0);
	drawBox(NECK_LENGTH,NECK_WIDTH,NECK_DEPTH);
	glPushMatrix();

	// head
	glTranslatef(NECK_LENGTH/2,NECK_WIDTH/2,0);
	glRotatef(UBODY_HEAD_ANGLE+headAngle,0,0,1);
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

	// right ear
	glColor3f(1,1,1);
	glPushMatrix();
	glTranslatef(0,HEAD_WIDTH/2,HEAD_DEPTH/2);
	glRotatef(HEAD_EAR_X_ANGLE,1,0,0);
	drawEar(rEarAngle);
	glPopMatrix();

	// left ear
	glPushMatrix();
	glTranslatef(0,HEAD_WIDTH/2,-HEAD_DEPTH/2);
	glRotatef(-HEAD_EAR_X_ANGLE,1,0,0);
	drawEar(lEarAngle);
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

