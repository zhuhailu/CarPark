//
// Created by zhuhailu on 2021/6/25.
//

#ifndef CARPARK_EGLPROGRAM_H
#define CARPARK_EGLPROGRAM_H

#include "esUtil.h"

class EglItemGroup;

class EglProgram {
public:
    EglProgram();
    virtual ~EglProgram();

    bool init(ESContext *esContext);
    virtual EglItemGroup* createWorld() = 0;


    virtual void getShaderSrc(char* vertShaderSrc, char* fragShaderSrc) = 0;


    virtual void update(ESContext *esContext, float deltaTime) = 0;
    virtual void draw(ESContext *esContext) = 0;
    virtual void shutdown(ESContext *esContext) = 0;

protected:
    GLuint          mProgramObject;

    // VBOs
    GLuint          mColorVBO;
    GLuint          mMvpVBO;
    GLuint          mVerticesVBO;
    GLuint          mIndicesTrianglesIBO;
    int             mNumIndicesTriangles;
    GLuint          mIndicesLinesIBO;
    int             mNumIndicesLines;

private:
    EglItemGroup*   mRoot;
};

#endif //CARPARK_EGLPROGRAM_H
