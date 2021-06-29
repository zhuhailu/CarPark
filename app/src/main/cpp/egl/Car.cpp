//
// Created by zhuhailu on 2021/6/23.
//

#include "Car.h"

EGLITEM_VERTICES_INFO_DEF_INIT(Car)

Car::Car()
    : EglItem()
{}

Car::~Car()
{}

void Car::initVerticesInfo(VERTICES_INFO *verticesInfo)
{
    if (NULL == verticesInfo) {
        return;
    }

    int numVertices = 24;
    GLfloat carVerts[] = {
        -0.5f, -0.25f, 0.02f,
        -0.5f, -0.25f,  0.5f,
         0.5f, -0.25f,  0.5f,
         0.5f, -0.25f, 0.02f,
        -0.5f,  0.25f, 0.02f,
        -0.5f,  0.25f,  0.5f,
         0.5f,  0.25f,  0.5f,
         0.5f,  0.25f, 0.02f,
        -0.5f, -0.25f, 0.02f,
        -0.5f,  0.25f, 0.02f,
         0.5f,  0.25f, 0.02f,
         0.5f, -0.25f, 0.02f,
        -0.5f, -0.25f,  0.5f,
        -0.5f,  0.25f,  0.5f,
         0.5f,  0.25f,  0.5f,
         0.5f, -0.25f,  0.5f,
        -0.5f, -0.25f, 0.02f,
        -0.5f, -0.25f,  0.5f,
        -0.5f,  0.25f,  0.5f,
        -0.5f,  0.25f, 0.02f,
         0.5f, -0.25f, 0.02f,
         0.5f, -0.25f,  0.5f,
         0.5f,  0.25f,  0.5f,
         0.5f,  0.25f, 0.02f,
    };

    if (NULL != verticesInfo->vertices)
        free(verticesInfo->vertices);

    verticesInfo->vertices =
            static_cast<GLfloat*>(malloc(sizeof(GLfloat) * 3 * numVertices));
    memcpy(verticesInfo->vertices, carVerts, sizeof(carVerts));
    verticesInfo->numVertices = numVertices;


    int numIndicesTriangles = 36;
    GLuint carIndicesTriangles[] = {
        0, 2, 1,
        0, 3, 2,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 15, 14,
        12, 14, 13,
        16, 17, 18,
        16, 18, 19,
        20, 23, 22,
        20, 22, 21
    };

    if (NULL != verticesInfo->indicesTriangles)
        free(verticesInfo->indicesTriangles);

    verticesInfo->indicesTriangles =
            static_cast<GLuint*>(malloc(sizeof(GLuint) * numIndicesTriangles));
    memcpy(verticesInfo->indicesTriangles, carIndicesTriangles, sizeof (carIndicesTriangles));
    verticesInfo->numIndicesTriangles = numIndicesTriangles;


    int numIndicesLines = 24;
    GLuint carIndicesLines[] = {
        0, 3,
        3, 2,
        2, 1,
        1, 0,
        1, 5,
        5, 4,
        4, 0,
        4, 7,
        7, 6,
        7, 3,
        6, 5,
        6, 2
    };

    if (NULL != verticesInfo->indicesLines)
        free(verticesInfo->indicesLines);

    verticesInfo->indicesLines =
            static_cast<GLuint*>(malloc(sizeof(GLuint) * numIndicesLines));
    memcpy(verticesInfo->indicesLines, carIndicesLines, sizeof(carIndicesLines));
    verticesInfo->numIndicesLines = numIndicesLines;
}


// EOF