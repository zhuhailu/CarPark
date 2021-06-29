//
// Created by zhuhailu on 2021/6/22.
//

#ifndef CARPARK_EGLITEM_H
#define CARPARK_EGLITEM_H

#include <GLES3/gl3.h>
#include <vector>
#include <set>
#include "CommonDef.h"

class EglItem {

public:
    EglItem();
    virtual ~EglItem();

    struct VERTICES_INFO {
        GLfloat*    vertices;
        int         numVertices;
        int         globalIndex;
        GLuint*     indicesTriangles;
        int         numIndicesTriangles;
        int         globalIndexTriangles;
        GLuint*     indicesLines;
        int         numIndicesLines;
        int         globalIndexLines;
        bool        isInit;

        VERTICES_INFO();
        virtual ~VERTICES_INFO();

        void clear();
    };

    void getGlobalVerticesInfo(std::set<VERTICES_INFO*>* vertSet);
    int getChildrenTreeInstanceCount();
    virtual void getInstanceColor(GLubyte (*colors)[4], int* curIndex, const int count);
    virtual void getInstanceSize(GLfloat (*sizes)[3], int* curIndex, const int count);
    virtual void getInstancePostion(GLfloat (*postions)[3], int* curIndex, const int count,
                                    const float* parentPos);
    virtual void getInstanceRotate(GLfloat (*rotates)[3], int* curIndex, const int count,
                                   const float* parentRotate);
    virtual void getInstanceIndices(GLuint (*indices), int* curIndex, const int count);

    void getGlobalPostion(float* pos);
    void getGlobalRotate(float* rotate);

    VERTICES_INFO* getVerticesInfo();
    virtual VERTICES_INFO* getVerticesInfoObj() = 0;
    virtual bool setVerticesInfoObj(VERTICES_INFO*) = 0;
    virtual void initVerticesInfo(VERTICES_INFO* verticesInfo) = 0;
    virtual bool isPerspective() { return false; }
    void destroyVerticesInfo();

    void setScale(float x, float y, float z);
    void setScaleX(float x);
    void setScaleY(float y);
    void setScaleZ(float z);
    inline float getScaleX() { return mScale[0]; }
    inline float getScaleY() { return mScale[1]; }
    inline float getScaleZ() { return mScale[2]; }

    void setPostion(float x, float y, float z);
    void setPostionX(float x);
    void setPostionY(float y);
    void setPostionZ(float z);
    inline float getPostionX() { return mPostion[0]; }
    inline float getPostionY() { return mPostion[1]; }
    inline float getPostionZ() { return mPostion[2]; }

    void setRotate(float x, float y, float z);
    void setRotateX(float x);
    void setRotateY(float y);
    void setRotateZ(float z);
    inline float getRotateX() { return mRotate[0]; }
    inline float getRotateY() { return mRotate[1]; }
    inline float getRotateZ() { return mRotate[2]; }

    void setColor(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a = 255);

    inline void setParent(EglItem* parent) { mParent = parent; }
    inline EglItem* getParent() { return mParent; }

    inline int getChildrenCount() { return  mChildren.size(); }
    EglItem* getChild(const int pos);
    void addChild(EglItem* child, const int pos = -1);
    void removeChild(EglItem* child);
    void removeChild(int start, int end = -1);

private:
    EglItem*                mParent;
    std::vector<EglItem*>   mChildren;

    float       mScale[3];
    float       mPostion[3];
    float       mRotate[3];
    uint8_t     mColor[4];

};


#endif //CARPARK_EGLITEM_H
