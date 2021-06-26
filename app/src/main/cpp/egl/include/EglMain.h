//
// Created by zhuhailu on 2021/6/24.
//

#ifndef CARPARK_EGLMAIN_H
#define CARPARK_EGLMAIN_H

#include "esUtil.h"

#define NUM_INSTANCES   100
#define POSITION_LOC    0
#define COLOR_LOC       1
#define MVP_LOC         2

int esMain (ESContext *esContext);
void Update ( ESContext *esContext, float deltaTime );
void Draw ( ESContext *esContext );
void Shutdown ( ESContext *esContext );

class EglProgram;

class EglMain {
public:
    static EglMain* getInstance(ESContext *esContext);
    static void destroyInstance();

    bool init ( ESContext *esContext );
    void update ( ESContext *esContext, float deltaTime );
    void draw ( ESContext *esContext );
    void shutdown ( ESContext *esContext );

    typedef struct
    {
        // Handle to a program object
        GLuint programObject;

        // VBOs
        GLuint positionVBO;
        GLuint colorVBO;
        GLuint mvpVBO;
        GLuint indicesIBO;

        // Number of indices
        int       numIndices;

        // Rotation angle
        GLfloat   angle[NUM_INSTANCES];

    } UserData;

private:
    EglMain(ESContext* esContext);
    virtual ~EglMain();

private:
    static EglMain* sInstance;

    EglProgram* mCurrentProgram;
    ESContext*  mEsContext;
    UserData*   mUserData;
};

#endif //CARPARK_EGLMAIN_H
