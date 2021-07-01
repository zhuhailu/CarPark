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

    virtual bool init(ESContext *esContext);
    virtual EglItemGroup* createWorld() = 0;
    virtual void updateWorld(float deltaTime) {}
    virtual void getShaderSrc(char** vertShaderSrc, char** fragShaderSrc) = 0;
    virtual void update(ESContext *esContext, float deltaTime);
    virtual void draw(ESContext *esContext);
    virtual void shutdown(ESContext *esContext);

protected:
    GLuint          mProgramObject;

    // VBOs
    GLuint          mColorVBO;
    GLuint          mSizeVBO;
    GLuint          mIndexVBO;
    GLuint          mMvpVBO;
    GLuint          mVerticesVBO;
    GLuint          mIndicesTrianglesIBO;
    int             mNumIndicesTriangles;
    GLuint          mIndicesLinesIBO;
    int             mNumIndicesLines;

private:
    EglItemGroup*   mRoot;
    int             mInstanceCount;
};

#endif //CARPARK_EGLPROGRAM_H
