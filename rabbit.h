#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// Rabbit dimensions
#define HEAD_LENGTH 0.7
#define HEAD_WIDTH 0.7
#define HEAD_DEPTH 0.6
#define SNOUT_LENGTH 0.15
#define SNOUT_WIDTH 0.40
#define SNOUT_DEPTH 0.45
#define EYE_WIDTH 0.1
#define EYE_HEIGHT 0.15
#define NOSE_WIDTH 0.15
#define NOSE_DEPTH 0.2
#define EAR_WIDTH 0.9
#define EAR_LENGTH 0.35
#define EAR_DEPTH 0.15
#define NECK_LENGTH 0.7
#define NECK_WIDTH 0.6
#define NECK_DEPTH 0.5
#define M_BODY_LENGTH 0.7
#define M_BODY_WIDTH 0.8
#define M_BODY_DEPTH 0.7
#define U_BODY_LENGTH 0.6
#define U_BODY_WIDTH 0.8
#define U_BODY_DEPTH 0.7
#define L_BODY_LENGTH 0.7
#define L_BODY_WIDTH 0.6
#define L_BODY_DEPTH 0.7
#define TAIL_WIDTH 0.4
#define U_LEG_LENGTH 0.85
#define U_LEG_WIDTH 0.55
#define U_LEG_DEPTH 0.25
#define L_LEG_LENGTH 0.7
#define L_LEG_WIDTH 0.25
#define L_LEG_DEPTH 0.25
#define LEG_PAW_LENGTH 0.65
#define LEG_PAW_WIDTH 0.2
#define LEG_PAW_DEPTH 0.3
#define U_ARM_LENGTH 0.6
#define U_ARM_WIDTH 0.3
#define U_ARM_DEPTH 0.25
#define L_ARM_LENGTH 0.6
#define L_ARM_WIDTH 0.25
#define L_ARM_DEPTH 0.25
#define ARM_PAW_LENGTH 0.35
#define ARM_PAW_WIDTH 0.2
#define ARM_PAW_DEPTH 0.3

// rabbit relative body parts angle
#define DEFAULT_RABBIT_Y 1.0
#define JUMP_RABBIT_Y 2.0
#define UBODY_NECK_ANGLE 20
#define NECK_HEAD_ANGLE -30
#define HEAD_EAR_X_ANGLE 15
#define GROUND_MBODY_ANGLE 20 
#define MBODY_LBODY_ANGLE 20
#define MBODY_UBODY_ANGLE -15
#define LBODY_TAIL_ANGLE 45
#define LBODY_ULEG_ANGLE -45
#define ULEG_LLEG_ANGLE -125
#define LLEG_PAW_ANGLE 130
#define UBODY_UARM_ANGLE -120
#define UARM_LARM_ANGLE 30
#define LARM_PAW_ANGLE 85

// rabbit states
#define NECK_DOWN 0x0001
#define R_ARM_UP 0x0002
#define L_ARM_UP 0x0004
#define R_LEG_UP 0x0008
#define L_LEG_UP 0x0010
#define R_EAR_DOWN 0x0020
#define L_EAR_DOWN 0x0040
#define REAR_UP 0x0080
#define CURL_UP 0x0100
#define JUMP 0x0200

#define NECK_DOWN_NECK_ANGLE -25
#define NECK_DOWN_HEAD_ANGLE -35
#define EAR_DOWN_R_EAR_ANGLE 150
#define ARM_UP_U_ARM_ANGLE 100
#define ARM_UP_L_ARM_ANGLE -25
#define ARM_UP_PAW_ANGLE -45
#define LEG_UP_U_LEG_ANGLE 30
#define LEG_UP_L_LEG_ANGLE -30
#define LEG_UP_PAW_ANGLE 20

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
unsigned int rabbitState = 0;

void drawRabbit();
void drawEar(GLfloat);
void drawArm(GLfloat,GLfloat,GLfloat);
void drawLeg(GLfloat,GLfloat,GLfloat);