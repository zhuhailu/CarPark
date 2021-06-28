//
// Created by zhuhailu on 2021/6/22.
//

#include "CarPark.h"
#include "EglItemGroup.h"


CarPark::CarPark()
    : EglProgram()
{}

CarPark::~CarPark()
{}

EglItemGroup* CarPark::createWorld()
{
    return new EglItemGroup();
}

void CarPark::getShaderSrc(char* vertShaderSrc, char* fragShaderSrc)
{
    const char vShaderStr[] =
            "#version 300 es                             \n"
            "layout(location = 0) in vec4 i_vertices;    \n"
            "layout(location = 1) in vec4 i_color;       \n"
            "layout(location = 2) in mat4 i_mvpMatrix;   \n"
            "layout(location = 3) in vec3 i_size;        \n"
            "layout(location = 4) in vec3 i_postion;     \n"
            "layout(location = 5) in vec3 i_rotate;      \n"
            "layout(location = 6) in int  i_index;       \n"
            "out vec4 v_color;                           \n"
            "void main()                                 \n"
            "{                                           \n"
            "   if (gl_VertexID < i_index)               \n"
            "       return;                              \n"
            "   vec4 u_vertices = vec4(i_vertices.x * i_size.x, i_vertices.y * i_size.y, "
            "                          i_vertices.z * i_size.z, i_vertices.w);         \n"
            "   v_color = i_color;                       \n"
            "   gl_Position = a_mvpMatrix * u_vertices;  \n"
            "}                                           \n";

    const char fShaderStr[] =
            "#version 300 es                                \n"
            "precision mediump float;                       \n"
            "in vec4 v_color;                               \n"
            "layout(location = 0) out vec4 outColor;        \n"
            "void main()                                    \n"
            "{                                              \n"
            "  outColor = v_color;                          \n"
            "}                                              \n";

    vertShaderSrc = static_cast<char*>(malloc(sizeof(vShaderStr)));
    memcpy(vertShaderSrc, vShaderStr, sizeof(vShaderStr));

    fragShaderSrc = static_cast<char*>(malloc(sizeof(fShaderStr)));
    memcpy(fragShaderSrc, fShaderStr, sizeof(fShaderStr));
}


///
// Update MVP matrix based on time
//
void CarPark::update ( ESContext *esContext, float deltaTime )
{
//    UserData *userData = ( UserData * ) esContext->userData;
//    ESMatrix *matrixBuf;
//    ESMatrix perspective;
//    float    aspect;
//    int      instance = 0;
//    int      numRows;
//    int      numColumns;
//
//
//    // Compute the window aspect ratio
//    aspect = ( GLfloat ) esContext->width / ( GLfloat ) esContext->height;
//
//    // Generate a perspective matrix with a 60 degree FOV
//    esMatrixLoadIdentity ( &perspective );
//    esPerspective ( &perspective, 60.0f, aspect, 1.0f, 20.0f );
//
//    glBindBuffer ( GL_ARRAY_BUFFER, userData->mvpVBO );
//    matrixBuf = ( ESMatrix * ) glMapBufferRange ( GL_ARRAY_BUFFER, 0, sizeof ( ESMatrix ) * NUM_INSTANCES, GL_MAP_WRITE_BIT );
//
//    // Compute a per-instance MVP that translates and rotates each instance differnetly
//    numRows = ( int ) sqrtf ( NUM_INSTANCES );
//    numColumns = numRows;
//
//    for ( instance = 0; instance < NUM_INSTANCES; instance++ )
//    {
//        ESMatrix modelview;
//        float translateX = ( ( float ) ( instance % numRows ) / ( float ) numRows ) * 2.0f - 1.0f;
//        float translateY = ( ( float ) ( instance / numColumns ) / ( float ) numColumns ) * 2.0f - 1.0f;
//
//        // Generate a model view matrix to rotate/translate the cube
//        esMatrixLoadIdentity ( &modelview );
//
//        // Per-instance translation
//        esTranslate ( &modelview, translateX, translateY, -2.0f );
//
//        // Compute a rotation angle based on time to rotate the cube
//        userData->angle[instance] += ( deltaTime * 40.0f );
//
//        if ( userData->angle[instance] >= 360.0f )
//        {
//            userData->angle[instance] -= 360.0f;
//        }
//
//        // Rotate the cube
//        esRotate ( &modelview, userData->angle[instance], 1.0, 0.0, 1.0 );
//
//        // Compute the final MVP by multiplying the
//        // modevleiw and perspective matrices together
//        esMatrixMultiply ( &matrixBuf[instance], &modelview, &perspective );
//    }
//
//    glUnmapBuffer ( GL_ARRAY_BUFFER );
}

///
// Draw a triangle using the shader pair created in Init()
//
void CarPark::draw ( ESContext *esContext )
{
//    UserData *userData = esContext->userData;
//
//    // Set the viewport
//    glViewport ( 0, 0, esContext->width, esContext->height );
//
//    // Clear the color buffer
//    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//    // Use the program object
//    glUseProgram ( userData->programObject );
//
//    // Load the vertex position
//    glBindBuffer ( GL_ARRAY_BUFFER, userData->positionVBO );
//    glVertexAttribPointfer ( POSITION_LOC, 3, GL_FLOAT,
//                             GL_FALSE, 3 * sizeof ( GLfloat ), ( const void * ) NULL );
//    glEnableVertexAttribArray ( POSITION_LOC );
//
//    // Load the instance color buffer
//    glBindBuffer ( GL_ARRAY_BUFFER, userData->colorVBO );
//    glVertexAttribPointer ( COLOR_LOC, 4, GL_UNSIGNED_BYTE,
//                            GL_TRUE, 4 * sizeof ( GLubyte ), ( const void * ) NULL );
//    glEnableVertexAttribArray ( COLOR_LOC );
//    glVertexAttribDivisor ( COLOR_LOC, 1 ); // One color per instance
//
//
//    // Load the instance MVP buffer
//    glBindBuffer ( GL_ARRAY_BUFFER, userData->mvpVBO );
//
//    // Load each matrix row of the MVP.  Each row gets an increasing attribute location.
//    glVertexAttribPointer ( MVP_LOC + 0, 4, GL_FLOAT, GL_FALSE, sizeof ( ESMatrix ), ( const void * ) NULL );
//    glVertexAttribPointer ( MVP_LOC + 1, 4, GL_FLOAT, GL_FALSE, sizeof ( ESMatrix ), ( const void * ) ( sizeof ( GLfloat ) * 4 ) );
//    glVertexAttribPointer ( MVP_LOC + 2, 4, GL_FLOAT, GL_FALSE, sizeof ( ESMatrix ), ( const void * ) ( sizeof ( GLfloat ) * 8 ) );
//    glVertexAttribPointer ( MVP_LOC + 3, 4, GL_FLOAT, GL_FALSE, sizeof ( ESMatrix ), ( const void * ) ( sizeof ( GLfloat ) * 12 ) );
//    glEnableVertexAttribArray ( MVP_LOC + 0 );
//    glEnableVertexAttribArray ( MVP_LOC + 1 );
//    glEnableVertexAttribArray ( MVP_LOC + 2 );
//    glEnableVertexAttribArray ( MVP_LOC + 3 );
//
//    // One MVP per instance
//    glVertexAttribDivisor ( MVP_LOC + 0, 1 );
//    glVertexAttribDivisor ( MVP_LOC + 1, 1 );
//    glVertexAttribDivisor ( MVP_LOC + 2, 1 );
//    glVertexAttribDivisor ( MVP_LOC + 3, 1 );
//
//    // Bind the index buffer
//    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, userData->indicesIBO );
//
//    // Draw the cubes
//    glDrawElementsInstanced ( GL_TRIANGLES, userData->numIndices, GL_UNSIGNED_INT, ( const void * ) NULL, NUM_INSTANCES );
}

