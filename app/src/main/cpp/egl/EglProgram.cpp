//
// Created by zhuha on 2021/6/26.
//

#include "EglProgram.h"
#include "EglItemGroup.h"
#include "Camera.h"

EglProgram::EglProgram()
    : mProgramObject(0)
    , mColorVBO(0)
    , mSizeVBO(0)
    , mIndexVBO(0)
    , mMvpVBO(0)
    , mVerticesVBO(0)
    , mIndicesTrianglesIBO(0)
    , mNumIndicesTriangles(0)
    , mIndicesLinesIBO(0)
    , mNumIndicesLines(0)
    , mRoot(NULL)
    , mInstanceCount(0)
{

}

EglProgram::~EglProgram()
{

}

bool EglProgram::init(ESContext *esContext)
{
    mRoot = createWorld();
    LOGD("EglProgram::%s %p",__FUNCTION__, mRoot);

    char* vShaderStr = NULL;
    char* fShaderStr = NULL;
    getShaderSrc(&vShaderStr, &fShaderStr);

    LOGD("EglProgram::%s getShaderSrc end %p, %p",__FUNCTION__, vShaderStr, fShaderStr);

    // Load the shaders and get a linked program object
    mProgramObject = esLoadProgram ( vShaderStr, fShaderStr );
    free(vShaderStr);
    free(fShaderStr);

    LOGD("EglProgram::%s esLoadProgram end",__FUNCTION__);

    EglItem::VERTICES_INFO* verticesInfo = mRoot->getGlobalVerticesInfo();

    mNumIndicesTriangles = verticesInfo->numIndicesTriangles;
    mNumIndicesLines = verticesInfo->numIndicesLines;

    LOGD("EglProgram::%s getGlobalVerticesInfo end",__FUNCTION__);

    // Index buffer object
    glGenBuffers ( 1, &mIndicesTrianglesIBO );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, mIndicesTrianglesIBO );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER,sizeof ( GLuint ) * mNumIndicesTriangles,
                   verticesInfo->indicesTriangles, GL_STATIC_DRAW );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );

    for (int i = 0; i < mNumIndicesTriangles; i += 3) {
        LOGD("EglProgram::%s indicesTriangles %d %d %d\n",__FUNCTION__,
             verticesInfo->indicesTriangles[i], verticesInfo->indicesTriangles[i+1],
             verticesInfo->indicesTriangles[i+2] );
    }

    LOGD("EglProgram::%s indicesTriangles ------------- end",__FUNCTION__);

    // Index buffer object
    glGenBuffers ( 1, &mIndicesLinesIBO );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, mIndicesLinesIBO );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER,sizeof ( GLuint ) * mNumIndicesLines,
                   verticesInfo->indicesLines, GL_STATIC_DRAW );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );

    for (int i = 0; i < mNumIndicesLines; i += 2) {
        LOGD("EglProgram::%s indicesLines %d %d\n",__FUNCTION__,
             verticesInfo->indicesLines[i], verticesInfo->indicesLines[i+1]);
    }

    LOGD("EglProgram::%s indicesLines ------------- end",__FUNCTION__);

    // vertices VBO for cube model
    glGenBuffers ( 1, &mVerticesVBO );
    glBindBuffer ( GL_ARRAY_BUFFER, mVerticesVBO );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( GLfloat ) * 3 * verticesInfo->numVertices,
                   verticesInfo->vertices, GL_STATIC_DRAW );

//    for (int i = 0; i < verticesInfo->numVertices; ++i) {
//        LOGD("EglProgram::%s Vertices %.2f %.2f %.2f\n",__FUNCTION__,
//             verticesInfo->vertices[i*3], verticesInfo->vertices[i*3+1],
//             verticesInfo->vertices[i*3+2] );
//    }

    LOGD("EglProgram::%s Vertices ------------- end",__FUNCTION__);
    delete verticesInfo;

    LOGD("EglProgram::%s bind vertices buff end",__FUNCTION__);

    mInstanceCount = mRoot->getChildrenTreeInstanceCount();
    const int iInstanceCount = mInstanceCount;

    {
        GLubyte colors[iInstanceCount][4];
        int instance = 0;
        mRoot->getInstanceColor(colors, &instance, iInstanceCount);

        for (int i = 0; i < iInstanceCount; ++i) {
            LOGD("EglProgram::%s getInstanceColor %d %d %d \n",__FUNCTION__,
                 colors[i][0], colors[i][1], colors[i][2]);
        }

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
        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount * 3 * sizeof(GLfloat), sizes, GL_STATIC_DRAW );

        for (int i = 0; i < iInstanceCount; ++i) {
            LOGD("EglProgram::%s getInstanceSize %f %f %f \n",__FUNCTION__,
                 sizes[i][0], sizes[i][1], sizes[i][2]);
        }
    }

    {
        GLuint indices[iInstanceCount][2];
        int instance = 0;
        mRoot->getInstanceIndices(indices, &instance, iInstanceCount);

        glGenBuffers ( 1, &mIndexVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, mIndexVBO );
        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount * 2 * sizeof(GLuint), indices, GL_STATIC_DRAW );

        for (int i = 0; i < iInstanceCount; ++i) {
            LOGD("EglProgram::%s getInstanceIndices %d %d\n",__FUNCTION__, indices[i][0], indices[i][1]);
        }
    }

    {
        glGenBuffers ( 1, &mMvpVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, mMvpVBO );
        glBufferData ( GL_ARRAY_BUFFER, iInstanceCount * sizeof ( ESMatrix ), NULL, GL_DYNAMIC_DRAW );
    }

    glBindBuffer ( GL_ARRAY_BUFFER, 0 );
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );

    return true;
}

void EglProgram::update(ESContext *esContext, float deltaTime)
{
    updateWorld(deltaTime);

    const int iInstanceCount = mInstanceCount;

    ESMatrix *matrixBuf;
    ESMatrix perspective;
    float    aspect;

    Camera* camera = Camera::getActiveCamera();
    float fovy = 60.0f;
    float translate[] = {0.0f, 0.0f, 0.0f};
    if (NULL != camera) {
        // TBD: get Camera fov.

        EglItem* target = camera->getTarget();
        if (NULL != target) {
            target->getGlobalPostion(translate);
            translate[0] = - translate[0] - camera->getPostionX();
            translate[1] = - translate[1] - camera->getPostionY();
            translate[2] = - translate[2] - camera->getPostionZ();
        }
    }

    // Compute the window aspect ratio
    aspect = ( GLfloat ) esContext->width / ( GLfloat ) esContext->height;

    // Generate a perspective matrix with a 60 degree FOV
    esMatrixLoadIdentity ( &perspective );
    esPerspective ( &perspective, fovy, aspect, 1.0f, 20.0f );

    glBindBuffer ( GL_ARRAY_BUFFER, mMvpVBO );
    matrixBuf = ( ESMatrix * ) glMapBufferRange ( GL_ARRAY_BUFFER, 0, sizeof ( ESMatrix ) * iInstanceCount, GL_MAP_WRITE_BIT );

    GLfloat rotates[iInstanceCount][3];
    {
        int index = 0;
        mRoot->getInstanceRotate(rotates, &index, iInstanceCount);
    }

    GLfloat postions[iInstanceCount][3];
    {
        int index = 0;
        mRoot->getInstancePostion(postions, &index, iInstanceCount);
    }

    for ( int instance = 0; instance < iInstanceCount; instance++ )
    {
        ESMatrix modelview;

        // Generate a model view matrix to rotate/translate the cube
        esMatrixLoadIdentity ( &modelview );

        esTranslate ( &modelview, postions[instance][0], postions[instance][1], postions[instance][2] );
//        LOGD("EglProgram::%s translate %.2f, %.2f, %.2f\n", __FUNCTION__,
//             translate[0], translate[1], translate[2]);
        // Per-instance translation
        esTranslate ( &modelview, translate[0], translate[1], translate[2] );

        if ((rotates[instance][0] / 360.0f) >= 1.0f)
            rotates[instance][0] -= 360.0f * (int)(rotates[instance][0] / 360.0f);
        if ((rotates[instance][1] / 360.0f) >= 1.0f)
            rotates[instance][1] -= 360.0f * (int)(rotates[instance][1] / 360.0f);
        if ((rotates[instance][2] / 360.0f) >= 1.0f)
            rotates[instance][2] -= 360.0f * (int)(rotates[instance][2] / 360.0f);

//        LOGD("EglProgram::%s rotates %.2f, %.2f, %.2f\n", __FUNCTION__,
//             rotates[instance][0], rotates[instance][1], rotates[instance][2]);

        // Rotate
        esRotate ( &modelview, rotates[instance][0], 1.0, 0.0, 0.0 );
        esRotate ( &modelview, rotates[instance][1], 0.0, 1.0, 0.0 );
        esRotate ( &modelview, rotates[instance][2], 0.0, 0.0, 1.0 );

        // Compute the final MVP by multiplying the
        // modevleiw and perspective matrices together
        esMatrixMultiply ( &matrixBuf[instance], &modelview, &perspective );

//        LOGD("EglProgram::%s getInstanceIndices\n"
//             "{%.2f, %.2f, %.2f, %.2f\n"
//             " %.2f, %.2f, %.2f, %.2f\n"
//             " %.2f, %.2f, %.2f, %.2f\n"
//             " %.2f, %.2f, %.2f, %.2f}",__FUNCTION__,
//             matrixBuf[i].m[0][0], matrixBuf[i].m[0][1], matrixBuf[i].m[0][2], matrixBuf[i].m[0][3],
//             matrixBuf[i].m[1][0], matrixBuf[i].m[1][1], matrixBuf[i].m[1][2], matrixBuf[i].m[1][3],
//             matrixBuf[i].m[2][0], matrixBuf[i].m[2][1], matrixBuf[i].m[2][2], matrixBuf[i].m[2][3],
//             matrixBuf[i].m[3][0], matrixBuf[i].m[3][1], matrixBuf[i].m[3][2], matrixBuf[i].m[3][3]);
    }

    glUnmapBuffer ( GL_ARRAY_BUFFER );
}

void EglProgram::draw(ESContext *esContext)
{
    // Set the viewport
    glViewport ( 0, 0, esContext->width, esContext->height );

    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearDepthf(1.0f);
    glEnable(GL_DEPTH_TEST);

    // Use the program object
    glUseProgram ( mProgramObject );

    // Load the vertex position
    glBindBuffer ( GL_ARRAY_BUFFER, mVerticesVBO );
    glVertexAttribPointer ( 0, 3, GL_FLOAT,
                             GL_FALSE, 3 * sizeof ( GLfloat ), ( const void * ) NULL );
    glEnableVertexAttribArray ( 0 );

    // Load the instance color buffer
    glBindBuffer ( GL_ARRAY_BUFFER, mColorVBO );
    glVertexAttribPointer ( 1, 4, GL_UNSIGNED_BYTE,
                            GL_TRUE, 4 * sizeof ( GLubyte ), ( const void * ) NULL );
    glEnableVertexAttribArray ( 1 );
    glVertexAttribDivisor ( 1, 1 ); // One color per instance

    // Load the instance indices buffer
    glBindBuffer ( GL_ARRAY_BUFFER, mIndexVBO );
    glVertexAttribPointer ( 3, 2, GL_UNSIGNED_INT,
                            GL_FALSE, 2 * sizeof ( GLuint ), ( const void * ) NULL );
    glEnableVertexAttribArray ( 3 );
    glVertexAttribDivisor ( 3, 1 ); // One size per instance

    // Load the instance size buffer
    glBindBuffer ( GL_ARRAY_BUFFER, mSizeVBO );
    glVertexAttribPointer ( 2, 3, GL_FLOAT,
                            GL_FALSE, 3 * sizeof ( GLfloat ), ( const void * ) NULL );
    glEnableVertexAttribArray ( 2 );
    glVertexAttribDivisor ( 2, 1 ); // One size per instance

    // Load the instance MVP buffer
    glBindBuffer ( GL_ARRAY_BUFFER, mMvpVBO );

    int MVP_LOC = 4;
    // Load each matrix row of the MVP.  Each row gets an increasing attribute location.
    glVertexAttribPointer ( MVP_LOC + 0, 4, GL_FLOAT, GL_FALSE, sizeof ( ESMatrix ), ( const void * ) NULL );
    glVertexAttribPointer ( MVP_LOC + 1, 4, GL_FLOAT, GL_FALSE, sizeof ( ESMatrix ), ( const void * ) ( sizeof ( GLfloat ) * 4 ) );
    glVertexAttribPointer ( MVP_LOC + 2, 4, GL_FLOAT, GL_FALSE, sizeof ( ESMatrix ), ( const void * ) ( sizeof ( GLfloat ) * 8 ) );
    glVertexAttribPointer ( MVP_LOC + 3, 4, GL_FLOAT, GL_FALSE, sizeof ( ESMatrix ), ( const void * ) ( sizeof ( GLfloat ) * 12 ) );
    glEnableVertexAttribArray ( MVP_LOC + 0 );
    glEnableVertexAttribArray ( MVP_LOC + 1 );
    glEnableVertexAttribArray ( MVP_LOC + 2 );
    glEnableVertexAttribArray ( MVP_LOC + 3 );

    // One MVP per instance
    glVertexAttribDivisor ( MVP_LOC + 0, 1 );
    glVertexAttribDivisor ( MVP_LOC + 1, 1 );
    glVertexAttribDivisor ( MVP_LOC + 2, 1 );
    glVertexAttribDivisor ( MVP_LOC + 3, 1 );

    // Bind the index buffer
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, mIndicesTrianglesIBO );
    // Draw the cubes
    glDrawElementsInstanced ( GL_TRIANGLES, mNumIndicesTriangles, GL_UNSIGNED_INT, ( const void * ) NULL, mInstanceCount );

    glDisableVertexAttribArray ( 1 );
    glVertexAttrib4f ( 1, 0.0f, 0.0f, 0.0f, 1.0f );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, mIndicesLinesIBO );
    glDrawElementsInstanced ( GL_LINES, mNumIndicesLines, GL_UNSIGNED_INT, ( const void * ) NULL, mInstanceCount );

}

void EglProgram::shutdown ( ESContext *esContext )
{
    glDeleteBuffers ( 1, &mColorVBO );
    glDeleteBuffers ( 1, &mSizeVBO );
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

