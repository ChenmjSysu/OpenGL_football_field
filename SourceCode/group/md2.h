#ifndef __MD2_H
#define __MD2_H


//#include <windows.h>			// standard Windows app include
//#include <gl/gl.h>				// standard OpenGL include
//#include <gl/glu.h>				// OpenGL utilties

#include <stdio.h>
#include "base.h"

#include "CTargaImage.h"


const float KEYFRAMES_PER_S = 8;

// a single vertex
typedef struct
{
  union
  {
    struct
    {
      GLfloat x, y, z;
    };
    GLfloat v[3];
  };
} xyz_t;

struct sphere_t
{
  xyz_t center;
  GLfloat radius;
};

// texture coordinate
typedef struct
{
   float s;
   float t;
} texCoord_t;

// texture coordinate index
typedef struct
{
   short s;
   short t;
} stIndex_t;

// info for a single frame point
typedef struct
{
   unsigned char v[3];
   unsigned char normalIndex;	// not used
} framePoint_t;

// information for a single frame
typedef struct
{
  float scale[3];
  float translate[3];
  char name[16];
  framePoint_t fp[1];
} frame_t;

// data for a single triangle
typedef struct
{
  unsigned short meshIndex[3];		// vertex indices
  unsigned short stIndex[3];		// texture coordinate indices
} mesh_t;

typedef struct
{
  int ident;		 // identifies as MD2 file "IDP2"
  int version;	 // mine is 8
  int skinwidth;    // width of texture
  int skinheight;   // height of texture
  int framesize;    // number of bytes per frame
  int numSkins;     // number of textures
  int numXYZ;       // number of points
  int numST;        // number of texture
  int numTris;      // number of triangles
  int numGLcmds;
  int numFrames;    // total number of frames
  int offsetSkins;  // offset to skin names (64 bytes each)
  int offsetST;     // offset of texture s-t values
  int offsetTris;   // offset of triangle mesh
  int offsetFrames; // offset of frame data (points)
  int offsetGLcmds; // type of OpenGL commands to use
  int offsetEnd;    // end of file
} modelHeader_t;


class CMD2Model
{
public:
  CMD2Model();        // constructor
  ~CMD2Model();       // destructor
  
  // load model and skin/texture at the same time
  bool Load(char *modelFile, char *skinFile, GLfloat scale = 1.0f);
  
  // render model with interpolation to get animation
  void SetAnimationCustom(int startFrame, int endFrame);
  void SetAnimation(int state, int nextState = _REPEAT);
  void Animate(float seconds);
  
  void Render();
  
  // free memory of model
  void Unload();
  
  // retrieve animation state of model
  int GetAnimation() { return m_state; }

  const sphere_t &GetBoundingSphere() { return m_boundingSphere; }

  void Move(GLfloat x, GLfloat y, GLfloat z);
  void Rotate(GLfloat angle) { m_rotate = angle; }

  // model animation states
  enum
  {
	  IDLE,
	  RUN,
	  ATTACK,
	  PAIN1,
	  PAIN2,
	  PAIN3,
    JUMP,
    FLIPOFF,
    SAULTE,
    TAUNT,
    WAVE,
    POINT,
    CROUCH_IDLE,
    CROUCH_WALK,
    CROUCH_ATTACK,
    CROUCH_PAIN,
    CROUCH_DEATH,
    DEATH1,
    DEATH2,
    DEATH3,
    _REPEAT,
    _CUSTOM
  };

private:
  int m_state;        // current model animation state
  int m_nextState;    // state to automatically transition to after the current state is finished
  int m_currentFrame; // current frame # in animation
  int m_nextFrame;    // next frame # in animation
  int m_startFrame;   // first frame in current animation
  int m_endFrame;     // last frame in current animation

  sphere_t m_boundingSphere;
  float m_interpol;          // percent through current frame
  

  modelHeader_t m_info;
  GLuint m_texID;  // texture ID
  
  mesh_t *m_tris;           // triangle list
  texCoord_t *m_texCoords;  // texture coordinate list
  xyz_t *m_verts;           // vertex list
  xyz_t *m_currentVerts;    // working vertex list

  GLfloat m_miny;
  xyz_t m_pos;
  GLfloat m_rotate;
};

#endif