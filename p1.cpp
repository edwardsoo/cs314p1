#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include "rabbit.h"

int dumpPPM(int frameNum);


void drawAxis();
void drawFloor();

unsigned char camera = 'r';
bool animToggle = false;
bool updated = true;
float frames = 500;

int iCount = 0;       // used for numbering the PPM image files
int Width = 400;      // window width (pixels)
int Height = 400;     // window height (pixels)
bool Dump=false;      // flag set to true when dumping animation frames

void idle() {
	// only redraw frame if the scene is updated
	if (updated) {
		glutPostRedisplay();
	}
}

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
	case ' ':
		animToggle = !animToggle;
		if (!animToggle) {
			glutIdleFunc(NULL);
		} else {
			glutIdleFunc(idle);
		}
		break;
	case 'h':
		toggleHead();
		break;
	case 'l':
		toggleLeftArm();
		break;
	case 'm':
		toggleRightArm();
		break;
	case 'n':
		toggleRightLeg();
		break;
	case 'o':
		toggleLeftLeg();
		break;
	case 't':
		toggleRearUp();
		break;
	case 'c':
		toggleCurlUp();
		break;
	case 'e':
		toggleRightEar();
		break;
	case 'w':
		toggleLeftEar();
		break;
	case 'j':
		toggleJump();
		break;
	case 's':
		toggleShutEyes();
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

void toggleHead() {
	if (!(rabbitState & NECK_DOWN)) {
		newVal[NECK] = NECK_DOWN_NECK_ANGLE;
		newVal[HEAD] = NECK_DOWN_HEAD_ANGLE;
		rabbitState |= NECK_DOWN;
	} else {
		newVal[NECK] = 0;
		newVal[HEAD] = 0;
		rabbitState &= ~NECK_DOWN;
	}
	oldVal[NECK] = currVal[NECK];
	oldVal[HEAD] = currVal[HEAD];
}

void toggleRightEar() {
	if (!(rabbitState & R_EAR_DOWN)) {
		newVal[R_EAR] = EAR_DOWN_R_EAR_ANGLE;
		rabbitState |= R_EAR_DOWN;
	} else {
		newVal[R_EAR] = 0;
		rabbitState &= ~R_EAR_DOWN;
	}
	oldVal[R_EAR] = currVal[R_EAR];
}

void toggleLeftEar() {
	if (!(rabbitState & L_EAR_DOWN)) {
		newVal[L_EAR] = -EAR_DOWN_R_EAR_ANGLE;
		rabbitState |= L_EAR_DOWN;
	} else {
		newVal[L_EAR] = 0;
		rabbitState &= ~L_EAR_DOWN;
	}
	oldVal[L_EAR] = currVal[L_EAR];
}

void toggleRightArm() {
	if (!(rabbitState & R_ARM_UP)) {
		newVal[U_R_ARM] = ARM_UP_U_ARM_ANGLE;
		newVal[L_R_ARM] = ARM_UP_L_ARM_ANGLE;
		newVal[R_ARM_PAW] = ARM_UP_PAW_ANGLE;
		rabbitState |= R_ARM_UP;
	} else {
		newVal[U_R_ARM] = 0;
		newVal[L_R_ARM] = 0;
		newVal[R_ARM_PAW] = 0;
		rabbitState &= ~R_ARM_UP;
	}
	oldVal[U_R_ARM] = currVal[U_R_ARM];
	oldVal[L_R_ARM] = currVal[L_R_ARM];
	oldVal[R_ARM_PAW] = currVal[R_ARM_PAW];
}

void toggleLeftArm() {
	if (!(rabbitState & L_ARM_UP)) {
		newVal[U_L_ARM] = ARM_UP_U_ARM_ANGLE;
		newVal[L_L_ARM] = ARM_UP_L_ARM_ANGLE;
		newVal[L_ARM_PAW] = ARM_UP_PAW_ANGLE;
		rabbitState |= L_ARM_UP;
	} else {
		newVal[U_L_ARM] = 0;
		newVal[L_L_ARM] = 0;
		newVal[L_ARM_PAW] = 0;
		rabbitState &= ~L_ARM_UP;
	}
	oldVal[U_L_ARM] = currVal[U_L_ARM];
	oldVal[L_L_ARM] = currVal[L_L_ARM];
	oldVal[L_ARM_PAW] = currVal[L_ARM_PAW];
}

void toggleRightLeg(){ 
	if (!(rabbitState & R_LEG_UP)) {
		newVal[U_R_LEG] = LEG_UP_U_LEG_ANGLE;
		newVal[L_R_LEG] = LEG_UP_L_LEG_ANGLE;
		newVal[R_LEG_PAW] = LEG_UP_PAW_ANGLE;
		rabbitState |= R_LEG_UP;
	} else {
		newVal[U_R_LEG] = 0;
		newVal[L_R_LEG] = 0;
		newVal[R_LEG_PAW] = 0;
		rabbitState &= ~R_LEG_UP;
	}
	oldVal[U_R_LEG] = currVal[U_R_LEG];
	oldVal[L_R_LEG] = currVal[L_R_LEG];
	oldVal[R_LEG_PAW] = currVal[R_LEG_PAW];
}

void toggleLeftLeg() {
	if (!(rabbitState & L_LEG_UP)) {
		newVal[U_L_LEG] = LEG_UP_U_LEG_ANGLE;
		newVal[L_L_LEG] = LEG_UP_L_LEG_ANGLE;
		newVal[L_LEG_PAW] = LEG_UP_PAW_ANGLE;
		rabbitState |= L_LEG_UP;
	} else {
		newVal[U_L_LEG] = 0;
		newVal[L_L_LEG] = 0;
		newVal[L_LEG_PAW] = 0;
		rabbitState &= ~L_LEG_UP;
	}
	oldVal[U_L_LEG] = currVal[U_L_LEG];
	oldVal[L_L_LEG] = currVal[L_L_LEG];
	oldVal[L_LEG_PAW] = currVal[L_LEG_PAW];
}

void toggleShutEyes() {
	if (!(rabbitState & SHUT_EYES)) {
		newVal[R_EYE_SHUT] = SHUT_EYES_R_EYE_SHUT;
		newVal[L_EYE_SHUT] = SHUT_EYES_L_EYE_SHUT;
		rabbitState |= SHUT_EYES;
	} else {
		newVal[R_EYE_SHUT] = 0;
		newVal[L_EYE_SHUT] = 0;
		rabbitState &= ~SHUT_EYES;
	}
	oldVal[R_EYE_SHUT] = currVal[R_EYE_SHUT];
	oldVal[L_EYE_SHUT] = currVal[L_EYE_SHUT];
}

void toggleRearUp() {
	// rear up resets these states
	rabbitState &= ~(R_ARM_UP|L_ARM_UP|R_LEG_UP|L_LEG_UP|CURL_UP|JUMP);
	if (!(rabbitState & REAR_UP)) {
		if (!(rabbitState & NECK_DOWN)) {
			toggleHead();
		}
		if (rabbitState & SHUT_EYES) {
			toggleShutEyes();
		}
		newVal[RABBIT_Y] = REAR_UP_Y;
		newVal[U_BODY] = REAR_UP_U_BODY_ANGLE;
		newVal[M_BODY] = REAR_UP_M_BODY_ANGLE;
		newVal[L_BODY] = REAR_UP_L_BODY_ANGLE;
		newVal[TAIL] = REAR_UP_TAIL_ANGLE;
		newVal[U_R_LEG] = newVal[U_L_LEG] = REAR_UP_U_LEG_ANGLE;
		newVal[L_R_LEG] = newVal[L_L_LEG] = REAR_UP_L_LEG_ANGLE;
		newVal[R_LEG_PAW] = newVal[L_LEG_PAW] = REAR_UP_LEG_PAW_ANGLE;
		newVal[U_R_ARM] = newVal[U_L_ARM] = REAR_UP_U_ARM_ANGLE;
		newVal[L_R_ARM] = newVal[L_L_ARM] = REAR_UP_L_ARM_ANGLE;
		newVal[R_ARM_PAW] = newVal[L_ARM_PAW] = REAR_UP_ARM_PAW_ANGLE;
		rabbitState |= REAR_UP;
	} else {
		if (rabbitState & NECK_DOWN) {
			toggleHead();
		}
		newVal[RABBIT_Y] = 0;
		newVal[U_BODY] = 0;
		newVal[M_BODY] = 0;
		newVal[L_BODY] = 0;
		newVal[TAIL] = 0;
		newVal[U_R_LEG] = 0;
		newVal[L_R_LEG] = 0;
		newVal[R_LEG_PAW] = 0;
		newVal[U_L_LEG] = 0;
		newVal[L_L_LEG] = 0;
		newVal[L_LEG_PAW] = 0;
		newVal[U_R_ARM] = 0;
		newVal[L_R_ARM] = 0;
		newVal[R_ARM_PAW] = 0;
		newVal[U_L_ARM] = 0;
		newVal[L_L_ARM] = 0;
		newVal[L_ARM_PAW] = 0;
		rabbitState &= ~REAR_UP;
	}
	oldVal[RABBIT_Y] = currVal[RABBIT_Y];
	oldVal[NECK] = currVal[NECK];
	oldVal[HEAD] = currVal[HEAD];
	oldVal[U_BODY] = currVal[U_BODY];
	oldVal[M_BODY] = currVal[M_BODY];
	oldVal[L_BODY] = currVal[L_BODY];
	oldVal[TAIL] = currVal[TAIL];
	oldVal[U_R_LEG] = currVal[U_R_LEG];
	oldVal[L_R_LEG] = currVal[L_R_LEG];
	oldVal[R_LEG_PAW] = currVal[R_LEG_PAW];
	oldVal[U_L_LEG] = currVal[U_L_LEG];
	oldVal[L_L_LEG] = currVal[L_L_LEG];
	oldVal[L_LEG_PAW] = currVal[L_LEG_PAW];
	oldVal[U_R_ARM] = currVal[U_R_ARM];
	oldVal[L_R_ARM] = currVal[L_R_ARM];
	oldVal[R_ARM_PAW] = currVal[R_ARM_PAW];
	oldVal[U_L_ARM] = currVal[U_L_ARM];
	oldVal[L_L_ARM] = currVal[L_L_ARM];
	oldVal[L_ARM_PAW] = currVal[L_ARM_PAW];
}

void toggleCurlUp() {
	// curl up resets these states
	rabbitState &= ~(NECK_DOWN|R_ARM_UP|L_ARM_UP|R_LEG_UP|L_LEG_UP|REAR_UP|JUMP);
	if (!(rabbitState & CURL_UP)) {
		if (!(rabbitState & SHUT_EYES)) {
			toggleShutEyes();
		}
		newVal[RABBIT_Y] = CURL_UP_Y;
		newVal[NECK] = CURL_UP_NECK_ANGLE;
		newVal[HEAD] = CURL_UP_HEAD_ANGLE;
		newVal[M_BODY] = CURL_UP_MBODY_ANGLE;
		newVal[L_BODY] = CURL_UP_LBODY_ANGLE;
		newVal[U_BODY] = CURL_UP_UBODY_ANGLE;
		newVal[TAIL] = CURL_UP_TAIL_ANGLE;
		newVal[U_R_LEG] = newVal[U_L_LEG] = CURL_UP_U_LEG_ANGLE;
		newVal[L_R_LEG] = newVal[L_L_LEG] = CURL_UP_L_LEG_ANGLE;
		newVal[R_LEG_PAW] = newVal[L_LEG_PAW] = CURL_UP_LEG_PAW_ANGLE;
		newVal[U_R_ARM] = newVal[U_L_ARM] = CURL_UP_U_ARM_ANGLE;
		newVal[L_R_ARM] = newVal[L_L_ARM] = CURL_UP_L_ARM_ANGLE;
		newVal[R_ARM_PAW] = newVal[L_ARM_PAW] = CURL_UP_ARM_PAW_ANGLE;
		rabbitState |= CURL_UP;
	} else {
		if (rabbitState & SHUT_EYES) {
			toggleShutEyes();
		}
		newVal[RABBIT_Y] = 0;
		newVal[NECK] = 0;
		newVal[HEAD] = 0;
		newVal[M_BODY] = 0;
		newVal[L_BODY] = 0;
		newVal[U_BODY] = 0;
		newVal[TAIL] = 0;
		newVal[U_R_LEG] = 0;
		newVal[L_R_LEG] = 0;
		newVal[R_LEG_PAW] = 0;
		newVal[U_L_LEG] = 0;
		newVal[L_L_LEG] = 0;
		newVal[L_LEG_PAW] = 0;
		newVal[U_R_ARM] = 0;
		newVal[L_R_ARM] = 0;
		newVal[R_ARM_PAW] = 0;
		newVal[U_L_ARM] = 0;
		newVal[L_L_ARM] = 0;
		newVal[L_ARM_PAW] = 0;
		rabbitState &= ~CURL_UP;
	}
	oldVal[RABBIT_Y] = currVal[RABBIT_Y];
	oldVal[NECK] = currVal[NECK];
	oldVal[HEAD] = currVal[HEAD];
	oldVal[R_EYE_SHUT] = currVal[R_EYE_SHUT];
	oldVal[L_EYE_SHUT] = currVal[L_EYE_SHUT];
	oldVal[M_BODY] = currVal[M_BODY];
	oldVal[L_BODY] = currVal[L_BODY];
	oldVal[U_BODY] = currVal[U_BODY];
	oldVal[TAIL] = currVal[TAIL];
	oldVal[U_R_LEG] = currVal[U_R_LEG];
	oldVal[L_R_LEG] = currVal[L_R_LEG];
	oldVal[R_LEG_PAW] = currVal[R_LEG_PAW];
	oldVal[U_L_LEG] = currVal[U_L_LEG];
	oldVal[L_L_LEG] = currVal[L_L_LEG];
	oldVal[L_LEG_PAW] = currVal[L_LEG_PAW];
	oldVal[U_R_ARM] = currVal[U_R_ARM];
	oldVal[L_R_ARM] = currVal[L_R_ARM];
	oldVal[R_ARM_PAW] = currVal[R_ARM_PAW];
	oldVal[U_L_ARM] = currVal[U_L_ARM];
	oldVal[L_L_ARM] = currVal[L_L_ARM];
	oldVal[L_ARM_PAW] = currVal[L_ARM_PAW];
}

void toggleJump() {
	// jump resets these states
	rabbitState &= ~(R_LEG_UP|L_LEG_UP|REAR_UP|CURL_UP);
	if (!(rabbitState & JUMP)) {
		if (rabbitState & SHUT_EYES) {
			toggleShutEyes();
		}
		if (rabbitState & NECK_DOWN) {
			toggleHead();
		}
		if (!(rabbitState & R_ARM_UP)) {
			toggleRightArm();
		}
		if (!(rabbitState & L_ARM_UP)) {
			toggleLeftArm();
		}
		newVal[RABBIT_Y] = JUMP_Y;
		newVal[M_BODY] = JUMP_MBODY_ANGLE;
		newVal[L_BODY] = JUMP_LBODY_ANGLE;
		newVal[U_BODY] = JUMP_UBODY_ANGLE;
		newVal[TAIL] = JUMP_TAIL_ANGLE;
		newVal[U_R_LEG] = newVal[U_L_LEG] = JUMP_U_LEG_ANGLE;
		newVal[L_R_LEG] = newVal[L_L_LEG] = JUMP_L_LEG_ANGLE;
		newVal[R_LEG_PAW] = newVal[L_LEG_PAW] = JUMP_LEG_PAW_ANGLE;
		rabbitState |= JUMP;
	} else {
		if (rabbitState & R_ARM_UP) {
			toggleRightArm();
		}
		if (rabbitState & L_ARM_UP) {
			toggleLeftArm();
		}
		newVal[RABBIT_Y] = 0;
		newVal[M_BODY] = 0;
		newVal[L_BODY] = 0;
		newVal[U_BODY] = 0;
		newVal[TAIL] = 0;
		newVal[U_R_LEG] = newVal[U_L_LEG] = 0;
		newVal[L_R_LEG] = newVal[L_L_LEG] = 0;
		newVal[R_LEG_PAW] = newVal[L_LEG_PAW] = 0;
		rabbitState &= ~JUMP;
	}
	oldVal[RABBIT_Y] = currVal[RABBIT_Y];
	oldVal[M_BODY] = currVal[M_BODY];
	oldVal[L_BODY] = currVal[L_BODY];
	oldVal[U_BODY] = currVal[U_BODY];
	oldVal[TAIL] = currVal[TAIL];
	oldVal[U_R_LEG] = currVal[U_R_LEG];
	oldVal[L_R_LEG] = currVal[L_R_LEG];
	oldVal[R_LEG_PAW] = currVal[R_LEG_PAW];
	oldVal[U_L_LEG] = currVal[U_L_LEG];
	oldVal[L_L_LEG] = currVal[L_L_LEG];
	oldVal[L_LEG_PAW] = currVal[L_LEG_PAW];
	oldVal[U_R_ARM] = currVal[U_R_ARM];
	oldVal[L_R_ARM] = currVal[L_R_ARM];
	oldVal[R_ARM_PAW] = currVal[R_ARM_PAW];
	oldVal[U_L_ARM] = currVal[U_L_ARM];
	oldVal[L_L_ARM] = currVal[L_L_ARM];
	oldVal[L_ARM_PAW] = currVal[L_ARM_PAW];
}

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
	glTranslatef(U_ARM_LENGTH/2,0,0);
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
	glRotatef(LBODY_ULEG_ANGLE+uLegAngle,0,0,1);
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

void updateRabbit() {
	// debug printf
	for (int i = 0; i < NUM_VAR; i++) {
		printf("%i-val curr: %f, old: %f, new: %f\n",i,currVal[i], oldVal[i], newVal[i]);
	}
	printf("\n");

	// set current angles to new values if in jump mode
	if (!animToggle) {
		memcpy(currVal,newVal,sizeof(currVal));
		return;
	}

	updated = false;
	// interpolate every variables
	for (int i = 0; i < NUM_VAR; i++) {
		if ((newVal[i] > oldVal[i] && currVal[i] < newVal[i]) || 
			(newVal[i] < oldVal[i] && currVal[i] > newVal[i])) {
				updated = true;
				// If difference between current and target values is small, set current to new value
				if (fabs(newVal[i]-currVal[i]) < DELTA_LOWER_BOUND) {
					currVal[i] = newVal[i];
				} else {
					currVal[i] += (newVal[i]-oldVal[i])/frames;
				}
		}

	}
}

void drawRabbit() {
	glColor3f(1,1,1);

	// mid body
	glPushMatrix();
	glTranslatef(0,DEFAULT_Y+currVal[RABBIT_Y],0);
	glRotatef(GROUND_MBODY_ANGLE+currVal[M_BODY],0,0,1);
	drawBox(M_BODY_LENGTH, M_BODY_WIDTH, M_BODY_DEPTH);
	glPushMatrix();

	// lower body
	glTranslatef(-M_BODY_LENGTH/2,M_BODY_WIDTH/2,0);
	glRotatef(MBODY_LBODY_ANGLE+currVal[L_BODY],0,0,1);
	glTranslatef(-L_BODY_LENGTH/2,-L_BODY_WIDTH/2,0);
	drawBox(L_BODY_LENGTH, L_BODY_WIDTH, L_BODY_DEPTH);
	glPushMatrix();

	// tail
	glTranslated(-L_BODY_LENGTH/2+TAIL_WIDTH/4,L_BODY_WIDTH/2-TAIL_WIDTH/4,0);
	glRotatef(LBODY_TAIL_ANGLE+currVal[TAIL],0,0,1);
	glTranslated(-TAIL_WIDTH/2,TAIL_WIDTH/2,0);
	drawBox(TAIL_WIDTH,TAIL_WIDTH,TAIL_WIDTH);
	glPopMatrix();

	// right leg
	glColor4f(1,0,0,0.5);
	glPushMatrix();
	glTranslatef(-L_BODY_LENGTH/2+U_ARM_WIDTH/4,L_BODY_WIDTH/2-U_ARM_WIDTH/2,L_BODY_DEPTH/2+U_LEG_DEPTH/4);
	drawLeg(currVal[U_R_LEG],currVal[L_R_LEG],currVal[R_LEG_PAW]);
	glPopMatrix();

	// left leg
	glPushMatrix();
	glTranslatef(-L_BODY_LENGTH/2+U_ARM_WIDTH/4,L_BODY_WIDTH/2-U_ARM_WIDTH/2,-L_BODY_DEPTH/2-U_LEG_DEPTH/4);
	drawLeg(currVal[U_L_LEG],currVal[L_L_LEG],currVal[L_LEG_PAW]);
	glPopMatrix();

	// upper torso
	glColor3f(1,1,1);
	glPopMatrix();
	glTranslatef(M_BODY_LENGTH/2,M_BODY_WIDTH/2,0);
	glRotatef(MBODY_UBODY_ANGLE+currVal[U_BODY],0,0,1);
	glTranslatef(U_BODY_LENGTH/2,-U_BODY_WIDTH/2,0);
	drawBox(U_BODY_LENGTH, U_BODY_WIDTH, U_BODY_DEPTH);
	glPushMatrix();

	// right arm
	glColor4f(1,0,0,0.5);
	glTranslatef(U_BODY_LENGTH/2-U_ARM_WIDTH/2,-U_BODY_WIDTH/4,U_BODY_DEPTH/2);
	drawArm(currVal[U_R_ARM],currVal[L_R_ARM],currVal[R_ARM_PAW]);
	glPopMatrix();
	glPushMatrix();

	// left arm
	glTranslatef(U_BODY_LENGTH/2-U_ARM_WIDTH/2,-U_BODY_WIDTH/4,-U_BODY_DEPTH/2);
	drawArm(currVal[U_L_ARM],currVal[L_L_ARM],currVal[L_ARM_PAW]);
	glPopMatrix();

	// neck
	glColor3f(1,1,1);
	glTranslatef(U_BODY_LENGTH/2-NECK_WIDTH/4,U_BODY_WIDTH/2-NECK_WIDTH/2,0);
	glRotatef(UBODY_NECK_ANGLE+currVal[NECK],0,0,1);
	glTranslatef(NECK_LENGTH/2,0,0);
	drawBox(NECK_LENGTH,NECK_WIDTH,NECK_DEPTH);
	glPushMatrix();

	// head
	glTranslatef(NECK_LENGTH/2-HEAD_WIDTH/2,NECK_WIDTH/2-HEAD_WIDTH/4,0);
	glRotatef(NECK_HEAD_ANGLE+currVal[HEAD],0,0,1);
	glTranslatef(HEAD_LENGTH/2,0,0);
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

	drawBox(EYE_WIDTH,EYE_HEIGHT*(1-currVal[R_EYE_SHUT]),EYE_WIDTH);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(HEAD_LENGTH/2,HEAD_WIDTH/4,-HEAD_DEPTH/2+EYE_WIDTH);
	drawBox(EYE_WIDTH,EYE_HEIGHT*(1-currVal[L_EYE_SHUT]),EYE_WIDTH);
	glPopMatrix();

	// right ear
	glColor3f(1,1,1);
	glPushMatrix();
	glTranslatef(0,HEAD_WIDTH/2,HEAD_DEPTH/2);
	glRotatef(HEAD_EAR_X_ANGLE,1,0,0);
	drawEar(currVal[R_EAR]);
	glPopMatrix();

	// left ear
	glPushMatrix();
	glTranslatef(0,HEAD_WIDTH/2,-HEAD_DEPTH/2);
	glRotatef(-HEAD_EAR_X_ANGLE,1,0,0);
	drawEar(currVal[L_EAR]);
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

	updateRabbit();
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

