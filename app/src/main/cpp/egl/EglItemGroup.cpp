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
    LOGD("EglItemGroup::%s",__FUNCTION__);

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
        child->getGlobalVerticesInfo(&mVerticesInfoSet);
    }

    LOGD("EglItemGroup::%s getGlobalVerticesInfo size %d \n",__FUNCTION__, mVerticesInfoSet.size());

    VERTICES_INFO* result = new VERTICES_INFO();
    result->isInit = true;

    for (auto it: mVerticesInfoSet) {
        result->numVertices += it->numVertices;
        result->numIndicesTriangles += it->numIndicesTriangles;
        result->numIndicesLines += it->numIndicesLines;
    }

    LOGD("EglItemGroup::%s result count %d %d %d \n",__FUNCTION__, result->numVertices,
         result->numIndicesTriangles, result->numIndicesLines);

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

//        for (int i = 0; i < it->numIndicesTriangles; i += 3) {
//            LOGD("EglItemGroup::%s indicesTriangles %d %d %d\n",__FUNCTION__,
//                 it->indicesTriangles[i], it->indicesTriangles[i+1],
//                 it->indicesTriangles[i+2] );
//        }
//        LOGD("EglItemGroup::%p %p",__FUNCTION__, result->indicesTriangles,
//             result->indicesTriangles + numIndicesTriangles);
//        LOGD("EglItemGroup::%s indicesTriangles ------------- end",__FUNCTION__);

        for (int index = 0; index < it->numIndicesTriangles; ++index) {
            result->indicesTriangles[index + numIndicesTriangles] = it->indicesTriangles[index] + it->globalIndex;
        }
        it->globalIndexTriangles = numIndicesTriangles;
        numIndicesTriangles += it->numIndicesTriangles;

//        for (int i = 0; i < it->numIndicesLines; i += 2) {
//            LOGD("EglItemGroup::%s indicesLines %d %d\n",__FUNCTION__,
//                 it->indicesLines[i], it->indicesLines[i+1]);
//        }
//        LOGD("EglItemGroup::%p %p",__FUNCTION__, result->indicesLines,
//             result->indicesLines + numIndicesLines);
//        LOGD("EglItemGroup::%s indicesLines ------------- end",__FUNCTION__);

        for (int index = 0; index < it->numIndicesLines; ++index) {
            result->indicesLines[index + numIndicesLines] = it->indicesLines[index] + it->globalIndex;
        }
        it->globalIndexLines = numIndicesLines;
        numIndicesLines += it->numIndicesLines;
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
        getChild(index)->getInstanceRotate(rotates, curIndex, count, rootRotate);
    }
}

void EglItemGroup::getInstanceIndices(GLuint (*indices)[2], int *curIndex, const int count)
{
    int iChildCount = getChildrenCount();
    for (int index = 0; index < iChildCount; ++index) {
        getChild(index)->getInstanceIndices(indices, curIndex, count);
    }
}



