//
// Created by zhuhailu on 2021/6/22.
//

#include "Floor.h"


Floor::Floor()
    : EglItem()
{

}

Floor::~Floor()
{

}

void Floor::initVerticeInfo(EglItem::VERTICE_INFO* verticeInfo)
{
    if (NULL != verticeInfo) {
        return;
    }

    int numVertices = 4;
    GLfloat rectVerts[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f,  0.0f,
        0.5f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f
    };

    if ( NULL != verticeInfo->vertices)
        free(verticeInfo->vertices);

    verticeInfo->vertices =
            static_cast<GLfloat *>(malloc(sizeof(GLfloat) * 3 * numVertices));
    memcpy(verticeInfo->vertices, rectVerts, sizeof(rectVerts));


    int numIndicesTriangles = 6;
    GLuint rectIndicesTriangles[] = {
        0, 1, 2,
        0, 2, 3
    };

    if (NULL != verticeInfo->indicesTriangles)
        free(verticeInfo->indicesTriangles);

    verticeInfo->indicesTriangles =
            static_cast<GLuint*>(malloc(sizeof (GLuint) * numIndicesTriangles));
    memcpy(verticeInfo->indicesTriangles, rectIndicesTriangles, sizeof(rectIndicesTriangles));
    verticeInfo->numIndicesTriangles = numIndicesTriangles;


    int numIndicesLines = 8;
    GLuint rectIndicesLines[] ={
        0, 1,
        1, 2,
        2, 3,
        0, 3
    };

    if (NULL != verticeInfo->indicesLines)
        free(verticeInfo->indicesLines);

    verticeInfo->indicesLines =
            static_cast<GLuint*>(malloc(sizeof(GLuint) * numIndicesLines));
    memcpy(verticeInfo->indicesLines, rectIndicesLines, sizeof(rectIndicesLines));
    verticeInfo->numIndicesLines = numIndicesLines;

}

// EOF