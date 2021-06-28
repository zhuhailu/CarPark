//
// Created by zhuhailu on 2021/6/22.
//

#include "Floor.h"

EGLITEM_VERTICES_INFO_DEF_INIT(Floor)

Floor::Floor()
    : EglItem()
{

}

Floor::~Floor()
{

}

void Floor::initVerticesInfo(EglItem::VERTICES_INFO* verticesInfo)
{
    if (NULL != verticesInfo) {
        return;
    }

    int numVertices = 4;
    GLfloat rectVerts[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f,  0.0f,
        0.5f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f
    };

    if ( NULL != verticesInfo->vertices)
        free(verticesInfo->vertices);

    verticesInfo->vertices =
            static_cast<GLfloat *>(malloc(sizeof(GLfloat) * 3 * numVertices));
    memcpy(verticesInfo->vertices, rectVerts, sizeof(rectVerts));
    verticesInfo->numVertices = numVertices;


    int numIndicesTriangles = 6;
    GLuint rectIndicesTriangles[] = {
        0, 1, 2,
        0, 2, 3
    };

    if (NULL != verticesInfo->indicesTriangles)
        free(verticesInfo->indicesTriangles);

    verticesInfo->indicesTriangles =
            static_cast<GLuint*>(malloc(sizeof (GLuint) * numIndicesTriangles));
    memcpy(verticesInfo->indicesTriangles, rectIndicesTriangles, sizeof(rectIndicesTriangles));
    verticesInfo->numIndicesTriangles = numIndicesTriangles;


    int numIndicesLines = 8;
    GLuint rectIndicesLines[] ={
        0, 1,
        1, 2,
        2, 3,
        0, 3
    };

    if (NULL != verticesInfo->indicesLines)
        free(verticesInfo->indicesLines);

    verticesInfo->indicesLines =
            static_cast<GLuint*>(malloc(sizeof(GLuint) * numIndicesLines));
    memcpy(verticesInfo->indicesLines, rectIndicesLines, sizeof(rectIndicesLines));
    verticesInfo->numIndicesLines = numIndicesLines;

}

// EOF