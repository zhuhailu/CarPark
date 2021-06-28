//
// Created by zhuhailu on 2021/6/22.
//

#include "EglItemGroup.h"


EglItemGroup::EglItemGroup()
    : EglItem()
{

}

EglItemGroup::~EglItemGroup()
{
    mVerticesInfoSet.clear();
}

EglItem::VERTICES_INFO * EglItemGroup::getGlobalVerticesInfo()
{
    // clear global index;
    for (auto it: mVerticesInfoSet) {
        it->globalIndex = 0;
        it->globalIndexTriangles = 0;
        it->globalIndexLines = 0;
    }

    // get new vertices info.
    mVerticesInfoSet.clear();
    for (int index = 0; index < getChildrenCount(); ++index) {
        EglItem* child = getChild(index);
        child->getGlobalVerticesInfo(mVerticesInfoSet);
    }

    VERTICES_INFO* result = new VERTICES_INFO();
    result->isInit = true;

    for (auto it: mVerticesInfoSet) {
        result->numVertices += it->numVertices;
        result->numIndicesTriangles += it->numIndicesTriangles;
        result->numIndicesLines += it->numIndicesLines;
    }

    result->vertices =
            static_cast<GLfloat*>(malloc(sizeof(GLfloat) * 3 * result->numVertices));
    result->indicesTriangles =
            static_cast<GLuint*>(malloc(sizeof (GLuint) * result->numIndicesTriangles));
    result->indicesLines =
            static_cast<GLuint*>(malloc(sizeof (GLuint) * result->numIndicesLines));

    int numVertices = 0;
    int numIndicesTriangles = 0;
    int numIndicesLines = 0;
    for (auto it: mVerticesInfoSet) {
        memcpy(result->vertices + numVertices * 3, it->vertices,
               sizeof(GLfloat) * 3 * it->numVertices);
        it->globalIndex = numVertices;
        numVertices += it->numVertices;

        memcpy(result->indicesTriangles + numIndicesTriangles, it->indicesTriangles,
               sizeof (GLuint) * it->numIndicesTriangles);
        it->globalIndexTriangles = numIndicesTriangles;
        numIndicesTriangles = it->numIndicesTriangles;

        memcpy(result->indicesLines + numIndicesLines, it->indicesLines,
               sizeof (GLuint) * it->numIndicesLines);
        it->globalIndexLines = numIndicesLines;
        numIndicesTriangles = it->numIndicesLines;
    }

    return result;
}

void EglItemGroup::getInstanceColor(GLubyte (*colors)[4], int* curIndex, const int count)
{
    int iChildCount = getChildrenCount();
    for (int index = 0; index < iChildCount; ++index) {
        getChild(index)->getInstanceColor(colors, curIndex, count);
    }
}

void EglItemGroup::getInstanceSize(GLfloat (*sizes)[3], int *curIndex, const int count)
{
    int iChildCount = getChildrenCount();
    for (int index = 0; index < iChildCount; ++index) {
        getChild(index)->getInstanceSize(sizes, curIndex, count);
    }
}

void EglItemGroup::getInstancePostion(GLfloat (*postions)[3], int *curIndex, const int count,
                                      const float* parentPos)
{
    int iChildCount = getChildrenCount();
    float rootPos[] = {0.0f, 0.0f, 0.0f};
    for (int index = 0; index < iChildCount; ++index) {
        getChild(index)->getInstancePostion(postions, curIndex, count, rootPos);
    }
}

void EglItemGroup::getInstanceRotate(GLfloat (*rotates)[3], int *curIndex, const int count,
                                     const float* parentRotate)
{
    int iChildCount = getChildrenCount();
    float rootRotate[] = {0.0f, 0.0f, 0.0f};
    for (int index = 0; index < iChildCount; ++index) {
        getChild(index)->getInstancePostion(rotates, curIndex, count, rootRotate);
    }
}

void EglItemGroup::getInstanceIndices(GLuint (*indices), int *curIndex, const int count)
{
    int iChildCount = getChildrenCount();
    for (int index = 0; index < iChildCount; ++index) {
        getChild(index)->getInstanceIndices(indices, curIndex, count);
    }
}



