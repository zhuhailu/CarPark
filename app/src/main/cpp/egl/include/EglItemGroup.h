//
// Created by zhuhailu on 2021/6/22.
//

#ifndef CARPARK_EGLITEMGROUP_H
#define CARPARK_EGLITEMGROUP_H

#include "EglItem.h"
#include <set>

class EglItemGroup : public EglItem {
public:
    EglItemGroup();
    virtual ~EglItemGroup();


    VERTICES_INFO* getGlobalVerticesInfo();
    virtual void getInstanceColor(GLubyte (*colors)[4], int* curIndex, const int count);
    virtual void getInstanceSize(GLfloat (*sizes)[3], int* curIndex, const int count);
    virtual void getInstancePostion(GLfloat (*postions)[3], int* curIndex, const int count,
                                    const float* parentPos = NULL);
    virtual void getInstanceRotate(GLfloat (*rotates)[3], int* curIndex, const int count,
                                   const float* parentRotate = NULL);
    virtual void getInstanceIndices(GLuint (*indices)[2], int* curIndex, const int count);

private:
    virtual void initVerticesInfo(VERTICES_INFO *verticesInfo) {}
    virtual VERTICES_INFO* getVerticesInfoObj() { return NULL; }
    virtual bool setVerticesInfoObj(VERTICES_INFO*) { return false; }

private:
    std::set<VERTICES_INFO*>    mVerticesInfoSet;

};


#endif //CARPARK_EGLITEMGROUP_H
