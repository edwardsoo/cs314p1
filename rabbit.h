#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

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
#define EAR_WIDTH 0.8
#define EAR_LENGTH 0.4
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


#define DEFAULT_RABBIT_Y 1.0
#define JUMP_RABBIT_Y 2.0
#define HEAD_NECK_ANGLE 45
#define UBODY_HEAD_ANGLE -45
#define HEAD_EAR_X_ANGLE 15
#define GROUND_MBODY_ANGLE 25 
#define MBODY_LBODY_ANGLE 35
#define LBODY_TAIL_ANGLE 45
#define MBODY_ULEG_ANGLE -45
#define ULEG_LLEG_ANGLE -150
#define LLEG_PAW_ANGLE 135
#define MBODY_UBODY_ANGLE -30
#define UBODY_UARM_ANGLE -150
#define UARM_LARM_ANGLE 90
#define LARM_PAW_ANGLE 65

GLfloat rabbitY = DEFAULT_RABBIT_Y;
GLfloat neckAngle = 0;
GLfloat headAngle = 0;
GLfloat rEarAngle = 0;
GLfloat lEarAngle = 0;
GLfloat mBodyAngle = 0; 
GLfloat lBodyAngle = 0;
GLfloat uRLegAngle = 0;
GLfloat lRLegAngle = 0;
GLfloat rLegPawAngle = 0;
GLfloat uLLegAngle = 0;
GLfloat lLLegAngle = 0;
GLfloat lLegPawAngle = 0;
GLfloat uBodyAngle = 0;
GLfloat uRArmAngle = 0;
GLfloat lRArmAngle = 0;
GLfloat rArmPaw = 0;
GLfloat uLArmAngle = 0;
GLfloat lLArmAngle = 0;
GLfloat lArmPaw = 0;

void drawRabbit();
void drawEar(GLfloat);
void drawArm(GLfloat,GLfloat,GLfloat);
void drawLeg(GLfloat,GLfloat,GLfloat);