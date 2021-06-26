//
// Created by zhuhailu on 2021/6/23.
//

#include "Car.h"

Car::Car()
    : EglItem()
{}

Car::~Car()
{}

void Car::initVerticeInfo(VERTICE_INFO *verticeInfo)
{
    if (NULL != verticeInfo) {
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

    if (NULL != verticeInfo->vertices)
        free(verticeInfo->vertices);

    verticeInfo->vertices = static_cast<GLfloat*>(malloc(sizeof(GLfloat) * 3 * numVertices));
    memcpy(verticeInfo->vertices, carVerts, sizeof(carVerts));


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

    if (NULL != verticeInfo->indicesTriangles)
        free(verticeInfo->indicesTriangles);

    verticeInfo->indicesTriangles = static_cast<GLuint*>(malloc(sizeof(GLuint) * numIndicesTriangles));
    memcpy(verticeInfo->indicesTriangles, carIndicesTriangles, sizeof (carIndicesTriangles));
    verticeInfo->numIndicesTriangles = numIndicesTriangles;


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

    if (NULL != verticeInfo->indicesLines)
        free(verticeInfo->indicesLines);

    verticeInfo->indicesLines = static_cast<GLuint*>(malloc(sizeof(GLuint) * numIndicesLines));
    memcpy(verticeInfo->indicesLines, carIndicesLines, sizeof(carIndicesLines));
    verticeInfo->numIndicesLines = numIndicesLines;
}


// EOF