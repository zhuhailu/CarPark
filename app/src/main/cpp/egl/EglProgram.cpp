//
// Created by zhuha on 2021/6/26.
//

#include "EglProgram.h"
#include "EglItemGroup.h"


EglProgram::EglProgram()
    : mProgramObject(0)
    , mColorVBO(0)
    , mSizeVBO(0)
    , mPostionVBO(0)
    , mRotateVBO(0)
    , mIndexVBO(0)
    , mMvpVBO(0)
    , mVerticesVBO(0)
    , mIndicesTrianglesIBO(0)
    , mNumIndicesTriangles(0)
    , mIndicesLinesIBO(0)
    , mNumIndicesLines(0)
    , mRoot(NULL)
{

}

EglProgram::~EglProgram()
{

}

bool EglProgram::init(ESContext *esContext)
{
    mRoot = createWorld();

    char* vShaderStr = NULL;
    char* fShaderStr = NULL;
    getShaderSrc(vShaderStr, fShaderStr);

    // Load the shaders and get a linked program object
    mProgramObject = esLoadProgram ( vShaderStr, fShaderStr );
    free(vShaderStr);
    free(fShaderStr);


    EglItem::VERTICES_INFO* verticesInfo = mRoot->getGlobalVerticesInfo();

    mNumIndicesTriangles = verticesInfo->numIndicesTriangles;
    mNumIndicesLines = verticesInfo->numIndicesLines;

    // Index buffer object
    glGenBuffers ( 1, &mIndicesTrianglesIBO );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, mIndicesTrianglesIBO );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER,sizeof ( GLuint ) * mNumIndicesTriangles,
                   verticesInfo->indicesTriangles, GL_STATIC_DRAW );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );

    // Index buffer object
    glGenBuffers ( 1, &mIndicesLinesIBO );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, mIndicesLinesIBO );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER,sizeof ( GLuint ) * mNumIndicesLines,
                   verticesInfo->indicesLines, GL_STATIC_DRAW );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );

    // vertices VBO for cube model
    glGenBuffers ( 1, &mVerticesVBO );
    glBindBuffer ( GL_ARRAY_BUFFER, mVerticesVBO );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( GLfloat ) * 3 * verticesInfo->numVertices,
                   verticesInfo->vertices, GL_STATIC_DRAW );

    delete verticesInfo;

    const int iInstanceCount = mRoot->getChildrenTreeInstanceCount();

    {
        GLubyte colors[iInstanceCount][4];
        int instance = 0;
        mRoot->getInstanceColor(colors, &instance, iInstanceCount);

        glGenBuffers ( 1, &mColorVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, mColorVBO );
        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount * 4, colors, GL_STATIC_DRAW );
    }

    {
        GLfloat sizes[iInstanceCount][3];
        int instance = 0;
        mRoot->getInstanceSize(sizes, &instance, iInstanceCount);

        glGenBuffers ( 1, &mSizeVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, mSizeVBO );
        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount * 3, sizes, GL_STATIC_DRAW );
    }

    {
        GLfloat postions[iInstanceCount][3];
        int instance = 0;
        mRoot->getInstancePostion(postions, &instance, iInstanceCount);

        glGenBuffers ( 1, &mPostionVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, mPostionVBO );
        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount * 3, postions, GL_STATIC_DRAW );
    }

    {
        GLfloat rotates[iInstanceCount][3];
        int instance = 0;
        mRoot->getInstancePostion(rotates, &instance, iInstanceCount);

        glGenBuffers ( 1, &mRotateVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, mRotateVBO );
        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount * 3, rotates, GL_STATIC_DRAW );
    }

    {
        GLuint indices[iInstanceCount];
        int instance = 0;
        mRoot->getInstanceIndices(indices, &instance, iInstanceCount);

        glGenBuffers ( 1, &mIndexVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, mIndexVBO );
        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount, indices, GL_STATIC_DRAW );
    }

    glBindBuffer ( GL_ARRAY_BUFFER, 0 );
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );

    return true;
}

void EglProgram::update(ESContext *esContext, float deltaTime)
{

}

void EglProgram::draw(ESContext *esContext)
{

}

void EglProgram::shutdown ( ESContext *esContext )
{
    glDeleteBuffers ( 1, &mColorVBO );
    glDeleteBuffers ( 1, &mSizeVBO );
    glDeleteBuffers ( 1, &mPostionVBO );
    glDeleteBuffers ( 1, &mRotateVBO );
    glDeleteBuffers ( 1, &mIndexVBO );
    glDeleteBuffers ( 1, &mMvpVBO );
    glDeleteBuffers ( 1, &mVerticesVBO );
    glDeleteBuffers ( 1, &mIndicesTrianglesIBO );
    mNumIndicesTriangles = 0;
    glDeleteBuffers ( 1, &mIndicesLinesIBO );
    mNumIndicesLines = 0;

    // Delete program object
    glDeleteProgram ( mProgramObject );
}

