//
// Created by zhuhailu on 2021/6/22.
//

#include "EglItem.h"

EglItem::VERTICE_INFO* EglItem::sVerticeInfo = NULL;

EglItem::VERTICE_INFO::VERTICE_INFO()
    : vertices(NULL)
    , indicesTriangles(NULL)
    , numIndicesTriangles(0)
    , indicesLines(NULL)
    , numIndicesLines(0)
{
}

EglItem::VERTICE_INFO::~VERTICE_INFO()
{
    clear();
}

void EglItem::VERTICE_INFO::clear() {
    if (NULL != vertices) {
        free(vertices);
        vertices = NULL;
    }

    if (NULL != indicesTriangles) {
        free(indicesTriangles);
        indicesTriangles = NULL;
        numIndicesTriangles = 0;
    }

    if (NULL != indicesLines) {
        free(indicesLines);
        indicesLines = NULL;
        numIndicesLines = 0;
    }
}

EglItem::EglItem()
    : mParent(NULL)
    , mScale{0.0f, 0.0f, 0.0f}
    , mPostion{0.0f, 0.0f, 0.0f}
    , mRotate{0.0f, 0.0f, 0.0f}
{

}

EglItem::~EglItem()
{
}

const EglItem::VERTICE_INFO* EglItem::getVerticeInfo()
{
    if (NULL == sVerticeInfo) {
        sVerticeInfo = new VERTICE_INFO();
        initVerticeInfo(sVerticeInfo);
    }
    return sVerticeInfo;
}

void EglItem::destroyVerticeInfo()
{
    if (NULL != sVerticeInfo) {
        delete sVerticeInfo;
        sVerticeInfo = NULL;
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