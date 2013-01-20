#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// Rabbit bodyy parts dimensions
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
#define M_BODY_WIDTH 0.75
#define M_BODY_DEPTH 0.7
#define U_BODY_LENGTH 0.6
#define U_BODY_WIDTH 0.7
#define U_BODY_DEPTH 0.7
#define L_BODY_LENGTH 0.7
#define L_BODY_WIDTH 0.7
#define L_BODY_DEPTH 0.7
#define TAIL_WIDTH 0.4
#define U_LEG_LENGTH 0.75
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


// rabbit relative body parts default angles
#define DEFAULT_Y 1.0
#define UBODY_NECK_ANGLE 20
#define NECK_HEAD_ANGLE -30
#define HEAD_EAR_X_ANGLE 15
#define GROUND_MBODY_ANGLE 20 
#define MBODY_LBODY_ANGLE 10
#define MBODY_UBODY_ANGLE -15
#define LBODY_TAIL_ANGLE 0
#define LBODY_ULEG_ANGLE -45
#define ULEG_LLEG_ANGLE -130
#define LLEG_PAW_ANGLE 145
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


// states-specific values
#define NECK_DOWN_NECK_ANGLE -25
#define NECK_DOWN_HEAD_ANGLE -35

#define EAR_DOWN_R_EAR_ANGLE 150

#define ARM_UP_U_ARM_ANGLE 100
#define ARM_UP_L_ARM_ANGLE -25
#define ARM_UP_PAW_ANGLE -45

#define LEG_UP_U_LEG_ANGLE 30
#define LEG_UP_L_LEG_ANGLE -30
#define LEG_UP_PAW_ANGLE 20

#define REAR_UP_Y 0.5
#define REAR_UP_NECK_ANGLE -25
#define REAR_UP_HEAD_ANGLE -35
#define REAR_UP_U_BODY_ANGLE 15
#define REAR_UP_M_BODY_ANGLE 70
#define REAR_UP_L_BODY_ANGLE -10
#define REAR_UP_TAIL_ANGLE -45
#define REAR_UP_U_LEG_ANGLE -40
#define REAR_UP_L_LEG_ANGLE -20
#define REAR_UP_LEG_PAW_ANGLE 0
#define REAR_UP_U_ARM_ANGLE -60
#define REAR_UP_L_ARM_ANGLE 60
#define REAR_UP_ARM_PAW_ANGLE -150

#define CURL_UP_Y -0.3
#define CURL_UP_MBODY_ANGLE -20
#define CURL_UP_LBODY_ANGLE 10
#define CURL_UP_UBODY_ANGLE -10
#define CURL_UP_NECK_ANGLE 90
#define CURL_UP_HEAD_ANGLE -60
#define CURL_UP_R_EYE_SHUT 0.8
#define CURL_UP_L_EYE_SHUT 0.8
#define CURL_UP_TAIL_ANGLE 45
#define CURL_UP_U_LEG_ANGLE 0
#define CURL_UP_L_LEG_ANGLE -10
#define CURL_UP_LEG_PAW_ANGLE 20
#define CURL_UP_U_ARM_ANGLE -55
#define CURL_UP_L_ARM_ANGLE 90
#define CURL_UP_ARM_PAW_ANGLE -5


// rabbit varibles indices
#define RABBIT_Y 0
#define NECK RABBIT_Y+1
#define HEAD NECK+1
#define R_EYE_SHUT HEAD+1
#define L_EYE_SHUT R_EYE_SHUT+1
#define R_EAR L_EYE_SHUT+1
#define L_EAR R_EAR+1
#define U_BODY L_EAR+1
#define M_BODY U_BODY+1
#define L_BODY M_BODY+1
#define TAIL L_BODY+1
#define U_R_LEG TAIL+1
#define L_R_LEG U_R_LEG+1
#define R_LEG_PAW L_R_LEG+1
#define U_L_LEG R_LEG_PAW+1
#define L_L_LEG U_L_LEG+1
#define L_LEG_PAW L_L_LEG+1
#define U_R_ARM L_LEG_PAW+1
#define L_R_ARM U_R_ARM+1
#define R_ARM_PAW L_R_ARM+1
#define U_L_ARM R_ARM_PAW+1
#define L_L_ARM U_L_ARM+1
#define L_ARM_PAW L_L_ARM+1
#define NUM_VAR L_ARM_PAW+1

// rabbit variables
unsigned int rabbitState = 0;
GLfloat currVal[NUM_VAR] = {};

// animation variables
#define DELTA_LOWER_BOUND 0.01
GLfloat oldVal[NUM_VAR] = {};
GLfloat newVal[NUM_VAR] = {};


// function declarations
void updateRabbit();
void drawRabbit();
void drawEar(GLfloat);
void drawArm(GLfloat,GLfloat,GLfloat);
void drawLeg(GLfloat,GLfloat,GLfloat);
void drawBox(GLfloat,GLfloat,GLfloat);
void drawCube();

void toggleHead();
void toggleRightEar();
void toggleLeftEar();
void toggleRightArm();
void toggleLeftArm();
void toggleRightLeg();
void toggleLeftLeg();
void toggleRearUp();
void toggleCurlUp();