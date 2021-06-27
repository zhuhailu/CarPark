//
// Created by zhuha on 2021/6/26.
//

#include "EglProgram.h"
#include "EglItemGroup.h"


EglProgram::EglProgram()
    : mProgramObject(0)
    , mColorVBO(0)
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

    // Position VBO for cube model
    glGenBuffers ( 1, &mVerticesVBO );
    glBindBuffer ( GL_ARRAY_BUFFER, mVerticesVBO );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( GLfloat ) * 3 * verticesInfo->numVertices,
                   verticesInfo->vertices, GL_STATIC_DRAW );

    delete verticesInfo;

    const int iInstanceCount = mRoot->getChildrenTreeInstanceCount();

    // Random color for each instance
    {
        GLubyte colors[iInstanceCount][4];
        int instance = 0;
        mRoot->getInstanceColor(colors, &instance, iInstanceCount);

        glGenBuffers ( 1, &mColorVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, mColorVBO );
        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount * 4, colors, GL_STATIC_DRAW );
    }

//    // Allocate storage to store MVP per instance
//    {
//        int instance;
//
//        // Random angle for each instance, compute the MVP later
//        for ( instance = 0; instance < iInstanceCount; instance++ )
//        {
//            userData->angle[instance] = ( float ) ( random() % 32768 ) / 32767.0f * 360.0f;
//        }
//
//        glGenBuffers ( 1, &userData->mvpVBO );
//        glBindBuffer ( GL_ARRAY_BUFFER, userData->mvpVBO );
//        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount * sizeof ( ESMatrix ), NULL, GL_DYNAMIC_DRAW );
//    }
//    glBindBuffer ( GL_ARRAY_BUFFER, 0 );
//
//    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
//    return GL_TRUE;


    return true;
}

