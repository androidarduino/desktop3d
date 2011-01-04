/*
 * This code was created by Jeff Molofee
 * (ported to Linux/SDL by Edgar Costanzo)
 *
 * If you've found this code useful, please let me know.
 *
 * Visit Jeff at http://nehe.gamedev.net/
 * 
 * or for port-specific comments, questions, bugreports etc. 
 * email to edgarcostanzo@tiscalinet.it
 */

#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <stdarg.h>
#include <string.h>
#include <time.h>												// For Random Seed

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

/* This is our SDL surface */
SDL_Surface *surface;

typedef int (*compfn)(const void*, const void*);				// Typedef For Our Compare Function

/* User Defined Variables  */
GLint		kills;												// Level Kill Counter
GLfloat		roll;												// Rolling Clouds
GLdouble    Width;
GLdouble    Height;
GLint		miss;												// Missed Targets
GLint		level=1;											// Current Level
GLuint		base;												// Font Display List
GLint		score;												// Current Score
bool		game;												// Game Over?
int	mouse_x, mouse_y;											// The Current Position Of The Mouse
Uint32 lastTickCount;

/* Mix_Chunk is like Mix_Music, only it's for ordinary sounds. */
Mix_Chunk *Shot = NULL;

struct objects {
	GLuint	rot;												// Rotation (0-None, 1-Clockwise, 2-Counter Clockwise)
	bool	hit;												// Object Hit?
	GLuint	frame;												// Current Explosion Frame
	GLuint	dir;												// Object Direction (0-Left, 1-Right, 2-Up, 3-Down)
	GLuint	texid;												// Object Texture ID
	GLfloat	x;													// Object X Position
	GLfloat y;													// Object Y Position
	GLfloat	spin;												// Object Spin
	GLfloat	distance;											// Object Distance
};

objects	object[30];												// Storage For 30 Objects

typedef struct													// Create A Structure
{
	GLubyte	*imageData;											// Image Data (Up To 32 Bits)
	GLuint	bpp;												// Image Color Depth In Bits Per Pixel.
	GLuint	width;												// Image Width
	GLuint	height;												// Image Height
	GLuint	texID;												// Texture ID Used To Select A Texture
} TextureImage;													// Structure Name

TextureImage textures[10] =										// Storage For 10 Textures
{
	{NULL, 1, 2, 3, 4},	{NULL, 5, 6, 7, 8},
	{NULL, 1, 2, 3, 4},	{NULL, 5, 6, 7, 8},
	{NULL, 1, 2, 3, 4},	{NULL, 5, 6, 7, 8},
	{NULL, 1, 2, 3, 4},	{NULL, 5, 6, 7, 8},
	{NULL, 1, 2, 3, 4},	{NULL, 5, 6, 7, 8}
};

struct dimensions {												// Object Dimensions
	GLfloat	w;													// Object Width
	GLfloat h;													// Object Height
};

/* Size Of Each Object: Blueface,    Bucket,      Target,      Coke,        Vase           */
dimensions size[5] = { {1.0f,1.0f}, {1.0f,1.0f}, {1.0f,1.0f}, {0.5f,1.0f}, {0.75f,1.5f} };

GLvoid glPrint(GLint x, GLint y, const char *string, ...)		// Where The Printing Happens
{
	char		text[256];										// Holds Our String
	va_list		ap;												// Pointer To List Of Arguments

	if (string == NULL)											// If There's No Text
		return;													// Do Nothing

	va_start(ap, string);										// Parses The String For Variables
	    vsprintf(text, string, ap);								// And Converts Symbols To Actual Numbers
	va_end(ap);													// Results Are Stored In Text

	glBindTexture(GL_TEXTURE_2D, textures[9].texID);			// Select Our Font Texture
	glPushMatrix();												// Store The Modelview Matrix
	glLoadIdentity();											// Reset The Modelview Matrix
	glTranslated(x,y,0);										// Position The Text (0,0 - Bottom Left)
	glListBase(base-32);										// Choose The Font Set
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);			// Draws The Display List Text
	glPopMatrix();												// Restore The Old Projection Matrix
}

int Compare(struct objects *elem1, struct objects *elem2)		// Compare Function *** MSDN CODE MODIFIED FOR THIS TUT ***
{
   if ( elem1->distance < elem2->distance)						// If First Structure distance Is Less Than The Second
      return -1;												// Return -1
   else if (elem1->distance > elem2->distance)					// If First Structure distance Is Greater Than The Second
      return 1;													// Return 1
   else															// Otherwise (If The distance Is Equal)
      return 0;													// Return 0
}

GLvoid InitObject(int num)										// Initialize An Object
{
	object[num].rot=1;											// Clockwise Rotation
	object[num].frame=0;										// Reset The Explosion Frame To Zero
	object[num].hit=false;										// Reset Object Has Been Hit Status To False
	object[num].texid=rand()%5;									// Assign A New Texture
	object[num].distance=-(float(rand()%4001)/100.0f);			// Random Distance
	object[num].y=-1.5f+(float(rand()%451)/100.0f);				// Random Y Position
	// Random Starting X Position Based On Distance Of Object And Random Amount For A Delay (Positive Value)
	object[num].x=((object[num].distance-15.0f)/2.0f)-(5*level)-float(rand()%(5*level));
	object[num].dir=(rand()%2);									// Pick A Random Direction

	if (object[num].dir==0)										// Is Random Direction Right
	{
		object[num].rot=2;										// Counter Clockwise Rotation
		object[num].x=-object[num].x;							// Start On The Left Side (Negative Value)
	}

	if (object[num].texid==0)									// Blue Face
		object[num].y=-2.0f;									// Always Rolling On The Ground

	if (object[num].texid==1)									// Bucket
	{
		object[num].dir=3;										// Falling Down
		object[num].x=float(rand()%int(object[num].distance-10.0f))+((object[num].distance-10.0f)/2.0f);
		object[num].y=4.5f;										// Random X, Start At Top Of The Screen
	}

	if (object[num].texid==2)									// Target
	{
		object[num].dir=2;										// Start Off Flying Up
		object[num].x=float(rand()%int(object[num].distance-10.0f))+((object[num].distance-10.0f)/2.0f);
		object[num].y=-3.0f-float(rand()%(5*level));			// Random X, Start Under Ground + Random Value
	}

	// Sort Objects By Distance:	Beginning Address Of Our object Array	*** MSDN CODE MODIFIED FOR THIS TUT ***
	//								Number Of Elements To Sort
	//								Size Of Each Element
	//								Pointer To Our Compare Function
	qsort((void *) &object, level, sizeof(struct objects), (compfn)Compare );
}

void Explosion(int num)											// Draws An Animated Explosion For Object "num"
{
	float ex = (float)((object[num].frame/4)%4)/4.0f;			// Calculate Explosion X Frame (0.0f - 0.75f)
	float ey = (float)((object[num].frame/4)/4)/4.0f;			// Calculate Explosion Y Frame (0.0f - 0.75f)

	glBindTexture(GL_TEXTURE_2D, textures[5].texID);			// Select The Explosion Texture
	glBegin(GL_QUADS);											// Begin Drawing A Quad
	{
		glTexCoord2f(ex      ,1.0f-(ey      )); glVertex3f(-1.0f,-1.0f,0.0f);	// Bottom Left
		glTexCoord2f(ex+0.25f,1.0f-(ey      )); glVertex3f( 1.0f,-1.0f,0.0f);	// Bottom Right
		glTexCoord2f(ex+0.25f,1.0f-(ey+0.25f)); glVertex3f( 1.0f, 1.0f,0.0f);	// Top Right
		glTexCoord2f(ex      ,1.0f-(ey+0.25f)); glVertex3f(-1.0f, 1.0f,0.0f);	// Top Left
	}
	glEnd();													// Done Drawing Quad

	object[num].frame+=1;										// Increase Current Explosion Frame
	if (object[num].frame>63)									// Have We Gone Through All 16 Frames?
	{
		InitObject(num);										// Init The Object (Assign New Values)
	}
}

void Object(float width,float height,GLuint texid)				// Draw Object Using Requested Width, Height And Texture
{
	glBindTexture(GL_TEXTURE_2D, textures[texid].texID);		// Select The Correct Texture
	glBegin(GL_QUADS);											// Start Drawing A Quad
	{
		glTexCoord2f(0.0f,0.0f); glVertex3f(-width,-height,0.0f);	// Bottom Left
		glTexCoord2f(1.0f,0.0f); glVertex3f( width,-height,0.0f);	// Bottom Right
		glTexCoord2f(1.0f,1.0f); glVertex3f( width, height,0.0f);	// Top Right
		glTexCoord2f(0.0f,1.0f); glVertex3f(-width, height,0.0f);	// Top Left
	}
	glEnd();													// Done Drawing Quad
}

void DrawTargets(void)											// Draws The Targets (Needs To Be Seperate)
{
	glLoadIdentity();											// Reset The Modelview Matrix
	glTranslatef(0.0f,0.0f,-10.0f);								// Move Into The Screen 20 Units
	for (int loop=0; loop<level; loop++)						// Loop Through 9 Objects
	{
		glLoadName(loop);										// Assign Object A Name (ID)
		glPushMatrix();											// Push The Modelview Matrix
		glTranslatef(object[loop].x,object[loop].y,object[loop].distance);		// Position The Object (x,y)
		if (object[loop].hit)									// If Object Has Been Hit
		{
			Explosion(loop);									// Draw An Explosion
		}
		else													// Otherwise
		{
			glRotatef(object[loop].spin,0.0f,0.0f,1.0f);		// Rotate The Object
			Object(size[object[loop].texid].w,size[object[loop].texid].h,object[loop].texid);	// Draw The Object
		}
		glPopMatrix();											// Pop The Modelview Matrix
	}
}

void Draw(void)													// Draw Our Scene
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The Modelview Matrix

	glPushMatrix();												// Push The Modelview Matrix
	glBindTexture(GL_TEXTURE_2D, textures[7].texID);			// Select The Sky Texture
	glBegin(GL_QUADS);											// Begin Drawing Quads
	{
		glTexCoord2f(1.0f,roll/1.5f+1.0f); glVertex3f( 28.0f,+7.0f,-50.0f);	// Top Right
		glTexCoord2f(0.0f,roll/1.5f+1.0f); glVertex3f(-28.0f,+7.0f,-50.0f);	// Top Left
		glTexCoord2f(0.0f,roll/1.5f+0.0f); glVertex3f(-28.0f,-3.0f,-50.0f);	// Bottom Left
		glTexCoord2f(1.0f,roll/1.5f+0.0f); glVertex3f( 28.0f,-3.0f,-50.0f);	// Bottom Right

		glTexCoord2f(1.5f,roll+1.0f); glVertex3f( 28.0f,+7.0f,-50.0f);		// Top Right
		glTexCoord2f(0.5f,roll+1.0f); glVertex3f(-28.0f,+7.0f,-50.0f);		// Top Left
		glTexCoord2f(0.5f,roll+0.0f); glVertex3f(-28.0f,-3.0f,-50.0f);		// Bottom Left
		glTexCoord2f(1.5f,roll+0.0f); glVertex3f( 28.0f,-3.0f,-50.0f);		// Bottom Right

		glTexCoord2f(1.0f,roll/1.5f+1.0f); glVertex3f( 28.0f,+7.0f,0.0f);	// Top Right
		glTexCoord2f(0.0f,roll/1.5f+1.0f); glVertex3f(-28.0f,+7.0f,0.0f);	// Top Left
		glTexCoord2f(0.0f,roll/1.5f+0.0f); glVertex3f(-28.0f,+7.0f,-50.0f);	// Bottom Left
		glTexCoord2f(1.0f,roll/1.5f+0.0f); glVertex3f( 28.0f,+7.0f,-50.0f);	// Bottom Right

		glTexCoord2f(1.5f,roll+1.0f); glVertex3f( 28.0f,+7.0f,0.0f);		// Top Right
		glTexCoord2f(0.5f,roll+1.0f); glVertex3f(-28.0f,+7.0f,0.0f);		// Top Left
		glTexCoord2f(0.5f,roll+0.0f); glVertex3f(-28.0f,+7.0f,-50.0f);		// Bottom Left
		glTexCoord2f(1.5f,roll+0.0f); glVertex3f( 28.0f,+7.0f,-50.0f);		// Bottom Right
	}
	glEnd();													// Done Drawing Quads

	glBindTexture(GL_TEXTURE_2D, textures[6].texID);			// Select The Ground Texture
	glBegin(GL_QUADS);											// Draw A Quad
	{
		glTexCoord2f(7.0f,4.0f-roll); glVertex3f( 27.0f,-3.0f,-50.0f);	// Top Right
		glTexCoord2f(0.0f,4.0f-roll); glVertex3f(-27.0f,-3.0f,-50.0f);	// Top Left
		glTexCoord2f(0.0f,0.0f-roll); glVertex3f(-27.0f,-3.0f,0.0f);	// Bottom Left
		glTexCoord2f(7.0f,0.0f-roll); glVertex3f( 27.0f,-3.0f,0.0f);	// Bottom Right
	}
	glEnd();													// Done Drawing Quad

	DrawTargets();												// Draw Our Targets
	glPopMatrix();												// Pop The Modelview Matrix

	// Crosshair (In Ortho View)
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPushMatrix();												// Store The Projection Matrix
	glLoadIdentity();											// Reset The Projection Matrix
	glOrtho(0,Width,0,Height,-1,1);								// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	glTranslated(mouse_x,Height-mouse_y,0.0f);					// Move To The Current Mouse Position
	Object(16,16,8);											// Draw The Crosshair

	// Game Stats / Title
	glPrint(240,450,"NeHe Productions");						// Print Title
	glPrint(10,10,"Level: %i",level);							// Print Level
	glPrint(250,10,"Score: %i",score);							// Print Score

	if (miss>9)													// Have We Missed 10 Objects?
	{
		miss=9;													// Limit Misses To 10
		game=true;												// Game Over TRUE
	}

	if (game)													// Is Game Over?
		glPrint(490,10,"GAME OVER");							// Game Over Message
	else
		glPrint(490,10,"Morale: %i/10",10-miss);				// Print Morale #/10

	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix

	glFlush();													// Flush The GL Rendering Pipeline
}

bool LoadTGA(TextureImage *texture, char *filename)				// Loads A TGA File Into Memory
{
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};		// Uncompressed TGA Header
	GLubyte		TGAcompare[12];									// Used To Compare TGA Header
	GLubyte		header[6];										// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;									// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;										// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;											// Temporary Variable
	GLuint		type=GL_RGBA;									// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");							// Open The TGA File

	if(	file==NULL ||											// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file != NULL)											// Did The File Even Exist? *Added Jim Strong*
			fclose(file);											// If Anything Failed, Close The File
		
		return false;												// Return False
	}

	texture->width  = header[1] * 256 + header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
                                                	
 	if(	texture->width	<=0	||										// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||										// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))							// Is The TGA 24 or 32 Bit?
	{
		fclose(file);												// If Anything Failed, Close The File
		return false;												// Return False
	}

	texture->bpp	= header[4];									// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;								// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData = (GLubyte *)malloc(imageSize);				// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||									// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)								// Was Image Data Loaded
		{
			free(texture->imageData);								// If So, Release The Image Data
			texture->imageData = NULL;
		}		

		fclose(file);												// Close The File
		return false;												// Return False
	}

	for(GLuint i=0; i<(unsigned int)imageSize; i+=bytesPerPixel)	// Loop Through The Image Data
	{																// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];									// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];			// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;							// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);													// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);							// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);					// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	
	if (texture[0].bpp==24)											// Was The TGA 24 Bits
	{
		type=GL_RGB;												// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height,
		0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;													// Texture Building Went Ok, Return True
}

GLvoid BuildFont()										// Build Our Font Display List
{
	base=glGenLists(95);										// Creating 95 Display Lists
	glBindTexture(GL_TEXTURE_2D, textures[9].texID);			// Bind Our Font Texture
	for (int loop=0; loop<95; loop++)							// Loop Through All 95 Lists
	{
		float cx=float(loop%16)/16.0f;							// X Position Of Current Character
		float cy=float(loop/16)/8.0f;							// Y Position Of Current Character

		glNewList(base+loop,GL_COMPILE);						// Start Building A List
		{
			glBegin(GL_QUADS);									// Use A Quad For Each Character
			{
				glTexCoord2f(cx,         1.0f-cy-0.120f); glVertex2i(0,0);	// Texture / Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f, 1.0f-cy-0.120f); glVertex2i(16,0);	// Texutre / Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f, 1.0f-cy);		  glVertex2i(16,16);// Texture / Vertex Coord (Top Right)
				glTexCoord2f(cx,         1.0f-cy);		  glVertex2i(0,16);	// Texture / Vertex Coord (Top Left)
			}
			glEnd();											// Done Building Our Quad (Character)
			glTranslated(10,0,0);								// Move To The Right Of The Character
		}
		glEndList();											// Done Building The Display List
	}															// Loop Until All 256 Are Built
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
	int nCont;
	
	glDeleteLists(base,95);										// Delete All 95 Font Display Lists
	
	for (nCont = 0; nCont < 10; nCont++)
		free(textures[nCont].imageData);
}

void Selection(void)											// This Is Where Selection Is Done
{
	GLuint	buffer[512];										// Set Up A Selection Buffer
	GLint	hits;												// The Number Of Objects That We Selected
	
	if (game)													// Is Game Over?
		return;													// If So, Don't Bother Checking For Hits
	
	/* Mix_PlayChannel takes, as its arguments, the channel that
	   the given sound should be played on, the sound itself, and
	   the number of times it should be looped.  If you don't care
	   what channel the sound plays on, just pass in -1.  Looping
	   works like Mix_PlayMusic. This function returns the channel
	   that the sound was assigned to. */
	Mix_PlayChannel(-1, Shot, 0);								// Play Gun Shot Sound

	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint	viewport[4];

	// This Sets The Array <viewport> To The Size And Location Of The Screen Relative To The Window
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(512, buffer);								// Tell OpenGL To Use Our Array For Selection

	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	(void) glRenderMode(GL_SELECT);

	glInitNames();												// Initializes The Name Stack
	glPushName(0);												// Push 0 (At Least One Entry) Onto The Stack

	glMatrixMode(GL_PROJECTION);								// Selects The Projection Matrix
	glPushMatrix();												// Push The Projection Matrix
	glLoadIdentity();											// Resets The Matrix

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	gluPickMatrix((GLdouble) mouse_x, (GLdouble) (viewport[3]-mouse_y), 1.0f, 1.0f, viewport);

	// Apply The Perspective Matrix
	gluPerspective(45.0f, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	DrawTargets();												// Render The Targets To The Selection Buffer
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	hits=glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many
																// Objects Were Drawn Where The Mouse Was
	if (hits > 0)												// If There Were More Than 0 Hits
	{
		int	choose = buffer[3];									// Make Our Selection The First Object
		int depth = buffer[1];									// Store How Far Away It Is

		for (int loop = 1; loop < hits; loop++)					// Loop Through All The Detected Hits
		{
			// If This Object Is Closer To Us Than The One We Have Selected
			if (buffer[loop*4+1] < GLuint(depth))
			{
				choose = buffer[loop*4+3];						// Select The Closer Object
				depth = buffer[loop*4+1];						// Store How Far Away It Is
			}
		}

		if (!object[choose].hit)								// If The Object Hasn't Already Been Hit
		{
			object[choose].hit=true;							// Mark The Object As Being Hit
			score+=1;											// Increase Score
			kills+=1;											// Increase Level Kills
			if (kills>level*5)									// New Level Yet?
			{
				miss=0;											// Misses Reset Back To Zero
				kills=0;										// Reset Level Kills
				level+=1;										// Increase Level
				if (level>30)									// Higher Than 30?
					level=30;									// Set Level To 30 (Are You A God?)
			}
		}
    }
}

void Update(unsigned long milliseconds)									// Perform Motion Updates Here
{
	roll-=milliseconds*0.00005f;								// Roll The Clouds

	for (int loop=0; loop<level; loop++)						// Loop Through The Objects
	{
		if (object[loop].rot==1)								// If Rotation Is Clockwise
			object[loop].spin-=0.2f*(float(loop+milliseconds));	// Spin Clockwise

		if (object[loop].rot==2)								// If Rotation Is Counter Clockwise
			object[loop].spin+=0.2f*(float(loop+milliseconds));	// Spin Counter Clockwise
		
		if (object[loop].dir==1)								// If Direction Is Right
			object[loop].x+=0.012f*float(milliseconds);			// Move Right

		if (object[loop].dir==0)								// If Direction Is Left
			object[loop].x-=0.012f*float(milliseconds);			// Move Left

		if (object[loop].dir==2)								// If Direction Is Up
			object[loop].y+=0.012f*float(milliseconds);			// Move Up

		if (object[loop].dir==3)								// If Direction Is Down
			object[loop].y-=0.0025f*float(milliseconds);		// Move Down

		// If We Are To Far Left, Direction Is Left And The Object Was Not Hit
		if ((object[loop].x<(object[loop].distance-15.0f)/2.0f) && (object[loop].dir==0) && !object[loop].hit)
		{
			miss+=1;											// Increase miss (Missed Object)
			object[loop].hit=true;								// Set hit To True To Manually Blow Up The Object
		}

		// If We Are To Far Right, Direction Is Left And The Object Was Not Hit
		if ((object[loop].x>-(object[loop].distance-15.0f)/2.0f) && (object[loop].dir==1) && !object[loop].hit)
		{
			miss+=1;											// Increase miss (Missed Object)
			object[loop].hit=true;								// Set hit To True To Manually Blow Up The Object
		}

		// If We Are To Far Down, Direction Is Down And The Object Was Not Hit
		if ((object[loop].y<-2.0f) && (object[loop].dir==3) && !object[loop].hit)
		{
			miss+=1;											// Increase miss (Missed Object)
			object[loop].hit=true;								// Set hit To True To Manually Blow Up The Object
		}

		if ((object[loop].y>4.5f) && (object[loop].dir==2))		// If We Are To Far Up And The Direction Is Up
			object[loop].dir=3;									// Change The Direction To Down
	}
}

/* function to release/destroy our resources and restoring the old desktop */
void Quit( int returnCode )
{
	/* Application Is Finished */
	Deinitialize();						// User Defined DeInitialization

	Mix_FreeChunk(Shot);
	Mix_CloseAudio();
	
    /* clean up the window     */
    SDL_Quit( );

    /* and exit appropriately  */
    exit( returnCode );
}

/* function to reset our viewport after a window resize */
bool resizeWindow( int width, int height )
{
    /* Height / width ration */
    GLfloat ratio;
 
    /* Protect against a divide by zero */
    if ( height == 0 )
		height = 1;

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLint )width, ( GLint )height );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );

    Width  = width;
    Height = height;

    return( true );
}

/* function to handle key press events */
void handleKeyPress( SDL_keysym *keysym )
{
    switch ( keysym->sym )
	{
		case SDLK_ESCAPE:
		    /* ESC key was pressed */
		    Quit( 0 );
		    break;
		case SDLK_F1:
		    /* 'f' key was pressed
		     * this toggles fullscreen mode
		     */
		    SDL_WM_ToggleFullScreen( surface );
		    break;
		case SDLK_SPACE:
			if (game)													// Space Bar Being Pressed After Game Has Ended?
			{
				for (int loop=0; loop<30; loop++)						// Loop Through 30 Objects
					InitObject(loop);									// Initialize Each Object
	
				game=false;												// Set game (Game Over) To False
				score=0;												// Set score To 0
				level=1;												// Set level Back To 1
				kills=0;												// Zero Player Kills
				miss=0;													// Set miss (Missed Shots) To 0
			}	
			break;
		default:
		    break;
	}

    return;
}

/* general OpenGL initialization function */
bool initGL( )
{
	srand( (unsigned)time( NULL ) );							// Randomize Things
	
	lastTickCount = SDL_GetTicks();								// Get The Tick Count
	
	if ((!LoadTGA(&textures[0], "Data/BlueFace.tga" )) ||		// Load The BlueFace Texture
		(!LoadTGA(&textures[1], "Data/Bucket.tga"   )) ||		// Load The Bucket Texture
		(!LoadTGA(&textures[2], "Data/Target.tga"   )) ||		// Load The Target Texture
		(!LoadTGA(&textures[3], "Data/Coke.tga"     )) ||		// Load The Coke Texture
		(!LoadTGA(&textures[4], "Data/Vase.tga"     )) ||		// Load The Vase Texture
		(!LoadTGA(&textures[5], "Data/Explode.tga"  )) ||		// Load The Explosion Texture
		(!LoadTGA(&textures[6], "Data/Ground.tga"   )) ||		// Load The Ground Texture
		(!LoadTGA(&textures[7], "Data/Sky.tga"      )) ||		// Load The Sky Texture
		(!LoadTGA(&textures[8], "Data/Crosshair.tga")) ||		// Load The Crosshair Texture
		(!LoadTGA(&textures[9], "Data/Font.tga"     )))			// Load The Crosshair Texture
	{
		return false;											// If Loading Failed, Return False
	}

	BuildFont();												// Build Our Font Display List

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);						// Black Background
	glClearDepth(1.0f);											// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);										// Type Of Depth Testing
	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending (disable alpha testing)
	glEnable(GL_BLEND);											// Enable Blending       (disable alpha testing)
//	glAlphaFunc(GL_GREATER,0.1f);								// Set Alpha Testing     (disable blending)
//	glEnable(GL_ALPHA_TEST);									// Enable Alpha Testing  (disable blending)
	glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping

	glEnable(GL_CULL_FACE);										// Remove Back Face

	for (int loop=0; loop<30; loop++)							// Loop Through 30 Objects
		InitObject(loop);										// Initialize Each Object
	
	return true;												// Return TRUE (Initialization Successful)
}

/* Here goes our drawing code */
bool drawGLScene( )
{
	Uint32 tickCount = SDL_GetTicks();				// Get The Tick Count
	Update (tickCount - lastTickCount);				// Update The Counter
	lastTickCount = tickCount;						// Set Last Count To Current Count
	Draw();										// Draw Our Scene

    /* Draw it to the screen */
    SDL_GL_SwapBuffers( );

    return( true );
}

int main( int argc, char **argv )
{
    /* Flags to pass to SDL_SetVideoMode */
    int videoFlags;
    /* main loop variable */
    bool done = false;
    /* used to collect events */
    SDL_Event event;
    /* this holds some info about our display */
    const SDL_VideoInfo *videoInfo;
    /* whether or not the window is active */
    bool isActive = true;
   	int bpp;
   	/* Audio */
	int audio_rate      = 22050;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels  = 2;
	int audio_buffers   = 4096;

    /* initialize SDL */
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
	    fprintf( stderr, "Video/Audio initialization failed: %s\n", SDL_GetError( ) );
	    Quit( 1 );
	}

	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
	{
	    fprintf( stderr, "Unable to open audio!\n" );
	    Quit( 1 );
	}

	/* We're going to pre-load the sound effects that we need right here */
	Shot = Mix_LoadWAV("Data/Shot.wav");
	if(!Shot)
	{
    	fprintf( stderr, "Mix_LoadWAV: %s\n", Mix_GetError( ) );
	    Quit( 1 );
	}
		
    /* Fetch the video info */
    videoInfo = SDL_GetVideoInfo( );

    if ( !videoInfo )
	{
	    fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
	    Quit( 1 );
	}

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

    /* This checks to see if surfaces can be stored in memory */
    if ( videoInfo->hw_available )
		videoFlags |= SDL_HWSURFACE;
    else
		videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoInfo->blit_hw )
		videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* get a SDL surface */
   	bpp = videoInfo->vfmt->BitsPerPixel;
    surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, bpp, videoFlags );

    /* Verify there is a surface */
    if ( !surface )
	{
	    fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
	    Quit( 1 );
	}

    /* initialize OpenGL */
	if (!initGL())
	{
	    fprintf( stderr,  "OpenGL initialization failed!\n");
	    Quit( 1 );
	}

    /* resize the initial window */
    resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );
	
    /* Hides the cursor */
    SDL_ShowCursor(0);

    /* wait for events */
    while ( !done )
	{
	    /* handle the events in the queue */
	    while ( SDL_PollEvent( &event ) )
		{
		    switch( event.type )
			{
			case SDL_ACTIVEEVENT:
			    /* Something's happend with our focus
			     * If we lost focus or we are iconified, we
			     * shouldn't draw the screen
			     */
			    if ( event.active.gain == 0 )
					isActive = false;
			    else
				{
					isActive = true;
					lastTickCount = SDL_GetTicks();	// Get The Tick Count
				}
			    break;			    
			case SDL_VIDEORESIZE:
			    /* handle resize event */
			    surface = SDL_SetVideoMode( event.resize.w, event.resize.h, 16, videoFlags );
			    if ( !surface )
				{
				    fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
				    Quit( 1 );
				}
			    resizeWindow( event.resize.w, event.resize.h );
			    break;
			case SDL_KEYDOWN:
			    /* handle key presses */
			    handleKeyPress( &event.key.keysym );
			    break;
			case SDL_QUIT:
			    /* handle quit requests */
			    done = true;
			    break;
			case SDL_MOUSEBUTTONDOWN:
				/* handle left click */
				if (event.button.button == SDL_BUTTON_LEFT)
				{
	            	mouse_x = event.button.x;
					mouse_y = event.button.y;
					Selection();
				}
				break;
			case SDL_MOUSEMOTION:			
				/* handle mouse movements */
	            mouse_x = event.motion.x;
				mouse_y = event.motion.y;
				break;			
			default:
			    break;
			}
		}

	    /* draw the scene */
	    if ( isActive && !done)
			drawGLScene();
	}

    /* clean ourselves up and exit */
    Quit( 0 );

    /* Should never get here */
    return( 0 );
}
