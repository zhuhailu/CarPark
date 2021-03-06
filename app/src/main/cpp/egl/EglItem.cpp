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


void EglItem::getGlobalVerticesInfo(std::set<VERTICES_INFO *>* vertSet)
{
    LOGD("EglItem::%s getGlobalVerticesInfo %p\n",__FUNCTION__, vertSet);
    if (0 < getChildrenCount()) {
        for (int index = 0; index < getChildrenCount(); ++index) {
            getChild(index)->getGlobalVerticesInfo(vertSet);
        }
    }
    VERTICES_INFO* vert = getVerticesInfo();
    LOGD("EglItem::%s getVerticesInfo %p\n",__FUNCTION__, vert);
    if (NULL != vert) {
        LOGD("EglItem::%s insert %p\n",__FUNCTION__, vert);
        vertSet->insert(vert);
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
        colors[*curIndex][0] = mColor[0];
        colors[*curIndex][1] = mColor[1];
        colors[*curIndex][2] = mColor[2];
        colors[*curIndex][3] = mColor[3];
        (*curIndex)++;

        int iChildCount = getChildrenCount();
        for (int index = 0; index < iChildCount; ++index) {
            getChild(index)->getInstanceColor(colors, curIndex, count);
        }
    }
}

void EglItem::getInstanceSize(GLfloat (*sizes)[3], int* curIndex, const int count)
{
    if (*curIndex >= count) {
        return;
    }
    if (!isPerspective()) {
        sizes[*curIndex][0] = mScale[0];
        sizes[*curIndex][1] = mScale[1];
        sizes[*curIndex][2] = mScale[2];
        (*curIndex)++;

        int iChildCount = getChildrenCount();
        for (int index = 0; index < iChildCount; ++index) {
            getChild(index)->getInstanceSize(sizes, curIndex, count);
        }
    }
}

void EglItem::getInstancePostion(GLfloat (*postions)[3], int* curIndex, const int count,
                                 const float* parentPos)
{
    if (*curIndex >= count) {
        return;
    }
    if (!isPerspective()) {
        float pos[3] = {mPostion[0] + parentPos[0],
                        mPostion[1] + parentPos[1],
                        mPostion[2] + parentPos[2]};

        postions[*curIndex][0] = pos[0];
        postions[*curIndex][1] = pos[1];
        postions[*curIndex][2] = pos[2];
        (*curIndex)++;

        int iChildCount = getChildrenCount();
        for (int index = 0; index < iChildCount; ++index) {
            getChild(index)->getInstancePostion(postions, curIndex, count, pos);
        }
    }
}

void EglItem::getInstanceRotate(GLfloat (*rotates)[3], int* curIndex, const int count,
                                const float* parentRotate)
{
    if (*curIndex >= count) {
        return;
    }
    if (!isPerspective()) {
        float rotate[3] = {mRotate[0] + parentRotate[0],
                           mRotate[1] + parentRotate[1],
                           mRotate[2] + parentRotate[2]};

        rotates[*curIndex][0] = rotate[0];
        rotates[*curIndex][1] = rotate[1];
        rotates[*curIndex][2] = rotate[2];
        (*curIndex)++;

        int iChildCount = getChildrenCount();
        for (int index = 0; index < iChildCount; ++index) {
            getChild(index)->getInstanceRotate(rotates, curIndex, count, rotate);
        }
    }
}

void EglItem::getInstanceIndices(GLuint (*indices)[2], int* curIndex, const int count)
{
    if (*curIndex >= count) {
        return;
    }
    if (!isPerspective()) {
        indices[*curIndex][0] = getVerticesInfoObj()->globalIndex;
        indices[*curIndex][1] = getVerticesInfoObj()->globalIndex + getVerticesInfoObj()->numVertices;
        (*curIndex)++;

        int iChildCount = getChildrenCount();
        for (int index = 0; index < iChildCount; ++index) {
            getChild(index)->getInstanceIndices(indices, curIndex, count);
        }
    }
}

void EglItem::getGlobalPostion(float* pos)
{
    memcpy(pos, mPostion, sizeof(mPostion));

    EglItem* it = this;
    while (NULL != it->getParent()) {
        it = it->getParent();
        pos[0] += it->getPostionX();
        pos[1] += it->getPostionY();
        pos[2] += it->getPostionZ();
    }
}

void EglItem::getGlobalRotate(float* rotate)
{
    memcpy(rotate, mRotate, sizeof(mRotate));
    EglItem* it = this;
    while (NULL != it->getParent()) {
        it = it->getParent();
        rotate[0] += rotate[0] + it->getPostionX();
        rotate[1] += rotate[1] + it->getPostionY();
        rotate[2] += rotate[2] + it->getPostionZ();
    }
}

EglItem::VERTICES_INFO* EglItem::getVerticesInfo()
{
    LOGD("EglItem::%s\n",__FUNCTION__);
    VERTICES_INFO* verticesInfo = getVerticesInfoObj();
    if (NULL == verticesInfo) {
        verticesInfo = new VERTICES_INFO();
        if (!setVerticesInfoObj(verticesInfo)) {
            delete verticesInfo;
            LOGE("EglItem::%s delete verticesInfo\n",__FUNCTION__);
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
    mPostion[0] = x;
    mPostion[1] = y;
    mPostion[2] = z;
}

void EglItem::setPostionX(float x)
{
    mPostion[0] = x;
}

void EglItem::setPostionY(float y)
{
    mPostion[1] = y;
}

void EglItem::setPostionZ(float z)
{
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

void EglItem::setColor(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
{
    mColor[0] = r;
    mColor[1] = g;
    mColor[2] = b;
    mColor[3] = a;
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