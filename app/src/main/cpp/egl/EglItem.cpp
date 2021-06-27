//
// Created by zhuhailu on 2021/6/22.
//

#include "EglItem.h"

EglItem::VERTICES_INFO::VERTICES_INFO()
    : vertices(NULL)
    , numVertices(0)
    , globalIndex(0)
    , indicesTriangles(NULL)
    , numIndicesTriangles(0)
    , globalIndexTriangles(0)
    , indicesLines(NULL)
    , numIndicesLines(0)
    , globalIndexLines(0)
    , isInit(false)
{
}

EglItem::VERTICES_INFO::~VERTICES_INFO()
{
    clear();
}

void EglItem::VERTICES_INFO::clear() {
    if (NULL != vertices) {
        free(vertices);
        vertices = NULL;
        numVertices = 0;
        globalIndex = 0;
    }

    if (NULL != indicesTriangles) {
        free(indicesTriangles);
        indicesTriangles = NULL;
        numIndicesTriangles = 0;
        globalIndexTriangles = 0;
    }

    if (NULL != indicesLines) {
        free(indicesLines);
        indicesLines = NULL;
        numIndicesLines = 0;
        globalIndexLines = 0;
    }

    isInit = false;
}

EglItem::EglItem()
    : mParent(NULL)
    , mScale{0.0f, 0.0f, 0.0f}
    , mPostion{0.0f, 0.0f, 0.0f}
    , mRotate{0.0f, 0.0f, 0.0f}
    , mColor{0, 0, 0, 255}
{

}

EglItem::~EglItem()
{
}


void EglItem::getGlobalVerticesInfo(std::set<VERTICES_INFO *> vertSet) {

    if (0 < getChildrenCount()) {
        for (int index = 0; index < getChildrenCount(); ++index) {
            getChild(index)->getGlobalVerticesInfo(vertSet);
        }
    }

    VERTICES_INFO* vert = getVerticesInfo();
    if (NULL != vert) {
        vertSet.insert(vert);
    }

}

int EglItem::getChildrenTreeInstanceCount()
{
    int iChildCount = getChildrenCount();
    int result = iChildCount;

    for (int index = 0; index < iChildCount; ++index) {
        EglItem* child = getChild(index);
        if (child->isPerspective()) {
            result -= 1;
        }
        else if (0 < child->getChildrenCount()){
            result += child->getChildrenTreeInstanceCount();
        }
        else {
            // result += 0;
        }
    }

    return result;
}

void EglItem::getInstanceColor(GLubyte (*colors)[4], int* curIndex, const int count)
{
    if (*curIndex >= count) {
        return;
    }
    if (!isPerspective()) {
        colors[curIndex][0] = mColor[0];
        colors[curIndex][1] = mColor[1];
        colors[curIndex][2] = mColor[2];
        colors[curIndex][3] = mColor[3];
        (*curIndex)++;

        int iChildCount = getChildrenCount();
        for (int index = 0; index < iChildCount; ++index) {
            getChild(index)->getInstanceColor(colors, curIndex, count);
        }
    }
}

EglItem::VERTICES_INFO* EglItem::getVerticesInfo()
{
    VERTICES_INFO* verticesInfo = getVerticesInfoObj();
    if (NULL == verticesInfo) {
        verticesInfo = new VERTICES_INFO();
        if (!setVerticesInfoObj(verticesInfo)) {
            delete verticesInfo;
            verticesInfo = NULL;
        }
    }
    if (NULL != verticesInfo && !verticesInfo->isInit) {
        initVerticesInfo(verticesInfo);
        verticesInfo->isInit = true;
    }

    return verticesInfo;
}

void EglItem::destroyVerticesInfo()
{
    VERTICES_INFO* verticesInfo = getVerticesInfoObj();
    if (NULL != verticesInfo) {
        setVerticesInfoObj(NULL);
        delete verticesInfo;
    }
}

void EglItem::setScale(float x, float y, float z)
{
    if (x >= 0.0f && y >= 0.0f && z >= 0.0f) {
        mScale[0] = x;
        mScale[1] = y;
        mScale[2] = z;
    }
}

void EglItem::setScaleX(float x)
{
    if (x >= 0.0f)
        mScale[0] = x;
}

void EglItem::setScaleY(float y)
{
    if (y >= 0.0f)
        mScale[1] = y;
}

void EglItem::setScaleZ(float z)
{
    if (z >= 0.0f)
        mScale[2] = z;
}

void EglItem::setPostion(float x, float y, float z)
{
    if (x >= 0.0f && y >= 0.0f && z >= 0.0f) {
        mPostion[0] = x;
        mPostion[1] = y;
        mPostion[2] = z;
    }
}

void EglItem::setPostionX(float x)
{
    if (x >= 0.0f)
        mPostion[0] = x;
}

void EglItem::setPostionY(float y)
{
    if (y >= 0.0f)
        mPostion[1] = y;
}

void EglItem::setPostionZ(float z)
{
    if (z >= 0.0f)
        mPostion[2] = z;
}


void EglItem::setRotate(float x, float y, float z)
{
    if (x >= 0.0f && y >= 0.0f && z >= 0.0f) {
        mRotate[0] = x;
        mRotate[1] = y;
        mRotate[2] = z;
    }
}

void EglItem::setRotateX(float x)
{
    if (x >= 0.0f)
        mRotate[0] = x;
}

void EglItem::setRotateY(float y)
{
    if (y >= 0.0f)
        mRotate[1] = y;
}

void EglItem::setRotateZ(float z)
{
    if (z >= 0.0f)
        mRotate[2] = z;
}

EglItem* EglItem::getChild(const int pos)
{
    return mChildren.at(pos);
}

void EglItem::addChild(EglItem* child, int pos)
{
    if (NULL != child) {
        if (pos >= 0 && pos < getChildrenCount()) {
            mChildren.insert(mChildren.cbegin() + pos, child);
            child->setParent(this);
        }
        else {
            mChildren.push_back(child);
            child->setParent(this);
        }
    }
}

void EglItem::removeChild(EglItem* child)
{
    if (NULL != child) {
        auto it = mChildren.cbegin();
        for (; it != mChildren.cend(); ++it) {
            if (*it == child) {
                mChildren.erase(it);
                child->setParent(NULL);
                break;
            }
        }
    }
}

void EglItem::removeChild(int start, int end)
{
    if (start < 0 && start >= getChildrenCount()) {
        return;
    }

    if (-1 == end) {
        mChildren[start]->setParent(NULL);
        mChildren.erase(mChildren.cbegin() + start);
    }
    else if (end >= start) {
        if (end > getChildrenCount()) {
            end = getChildrenCount();
        }
        for (int index = start; index < end; ++index) {
            mChildren[index]->setParent(NULL);
        }
        mChildren.erase(mChildren.cbegin() + start, mChildren.cbegin() + end);
    }
    else {
        // do nothing.
    }
}

// EOF