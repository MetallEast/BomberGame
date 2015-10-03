#define TERRAIN_LENGTH		100.0
#define CAMERA_STATES		7
#define TEXTURES_NUMBER		4

#define BUILD_START_X		3.0
#define BUILD_START_Y	    0.0
#define BUILD_START_Z		0.0		// Must be 0.0
#define BUILD_SIZE_X		3.0
#define BUILD_SIZE_Y		5.0
#define BUILD_SIZE_Z		3.0

#define WINDOW_SIZE			0.5
#define WINDOW_GAP			0.25
#define WINDOW_LIP			0.01

#define PLAIN_SPEED			0.01
#define PLAIN_START_X	   -20.0
#define PLAIN_START_Y		10.0
#define PLAIN_DIAMETER		0.5
#define TAIL_LENGTH			2.5
#define CORPUS_LENGTH		2.0
#define CABINE_LENGTH		1.0
#define GLASS_HEIGHT		0.05
#define GLASS_WIDTH_MUL		0.5
#define PEEK_LENGTH			1.0
#define KEEL_SIZE_X			0.5
#define KEEL_SIZE_Y			0.8
#define KEEL_SIZE_Z			0.2
#define WING_DEPTH			0.05

#define BOMB_FALLING_SPEED	0.01
#define BOMB_LENGTH			0.5
#define BOMB_DIAMETER		0.2
#define BOMB_PROPORTION		0.75


GLfloat shift		= 0.0;
GLfloat bombShiftY	= 0.0;
GLfloat bombXCoord	= 0.0;
GLfloat bombYCoord	= 0.0;


const GLfloat PLAIN_NOSE_START_X	= PLAIN_START_X + CORPUS_LENGTH;
const GLfloat PLAIN_PEEK_X			= PLAIN_NOSE_START_X + CABINE_LENGTH +  PEEK_LENGTH;
const GLfloat BOMB_CORPUS_LENGTH	= BOMB_LENGTH * BOMB_PROPORTION;

const GLfloat KEEL_LINE				= PLAIN_START_Y + PLAIN_DIAMETER / 4;
const GLfloat KEEL_START_X			= PLAIN_START_X - TAIL_LENGTH * 0.75;
const GLfloat KEEL_START_Y			= KEEL_LINE + KEEL_SIZE_Y;

const GLfloat STABILIZATOR_SIZE_X	= KEEL_SIZE_X * 0.75;
const GLfloat STABILIZATOR_SIZE_Y	= KEEL_SIZE_Z * 0.75;
const GLfloat STABILIZATOR_SIZE_Z	= KEEL_SIZE_Y * 0.75;

const GLfloat WING_START_X			= PLAIN_START_X + CORPUS_LENGTH / 2;
const GLfloat WING_WIDTH			= CORPUS_LENGTH * 0.7;
const GLfloat WING_LENGTH			= CORPUS_LENGTH * 1.2;

const GLfloat CABINE_GLASS_WIDTH	= CABINE_LENGTH * GLASS_WIDTH_MUL;
const GLfloat CABINE_GLASS_START_X	= PLAIN_NOSE_START_X + CABINE_LENGTH / 2 - CABINE_GLASS_WIDTH / 2;

const GLfloat BUILD_CELL_SIZE		= WINDOW_GAP + WINDOW_SIZE;
const GLfloat BUILD_X_LENGTH		= BUILD_SIZE_X * WINDOW_SIZE + BUILD_SIZE_X * (WINDOW_GAP + 1);
const GLfloat BUILD_Y_LENGTH		= BUILD_SIZE_Y * WINDOW_SIZE + BUILD_SIZE_Y * (WINDOW_GAP + 1);
const GLfloat BUILD_Z_LENGTH		= BUILD_SIZE_Z * WINDOW_SIZE + BUILD_SIZE_Z * (WINDOW_GAP + 1);
const GLfloat BUILD_LEFT_XCOORD		= BUILD_START_X - BUILD_X_LENGTH / 2;
const GLfloat BUILD_RIGHT_XCOORD	= BUILD_START_X + BUILD_X_LENGTH / 2;
const GLfloat BUILD_HIGH_YCOORD		= BUILD_START_Y + BUILD_Y_LENGTH;

const GLfloat GRASS_TEX_REPEAT		= TERRAIN_LENGTH / 5.0;


GLuint textures[TEXTURES_NUMBER];
GLshort Xsides = 0;
GLshort Zsides = 0;
GLushort cameraState = 0;
GLfloat bombStartX = PLAIN_START_X + CORPUS_LENGTH / 2 + shift;

bool bombRunning = false;
bool bombExplose = false;
bool buildExplosion	= false;
bool terraExplosion = false;