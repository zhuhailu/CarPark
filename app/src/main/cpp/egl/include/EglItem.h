//
// Created by zhuhailu on 2021/6/22.
//

#ifndef CARPARK_EGLITEM_H
#define CARPARK_EGLITEM_H

#include <GLES3/gl3.h>
#include <vector>

class EglItem {

public:
    EglItem();
    virtual ~EglItem();

    struct VERTICE_INFO {
        GLfloat*    vertices;
        GLuint*     indicesTriangles;
        int         numIndicesTriangles;
        GLuint*     indicesLines;
        int         numIndicesLines;

        VERTICE_INFO();
        virtual ~VERTICE_INFO();

        void clear();
    };

    const VERTICE_INFO* getVerticeInfo();
    virtual void initVerticeInfo(VERTICE_INFO* verticeInfo) = 0;
    virtual bool isPerspective() { return false; }
    static void destroyVerticeInfo();

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

    inline void setParent(EglItem* parent) { mParent = parent; }
    inline EglItem* getParent() { return mParent; }

    inline int getChildrenCount() { return  mChildren.size(); }
    void addChild(EglItem* child, const int pos = -1);
    void removeChild(EglItem* child);
    void removeChild(int start, int end = -1);

private:
    static VERTICE_INFO*    sVerticeInfo;

    EglItem*                mParent;
    std::vector<EglItem*>   mChildren;

    float       mScale[3];
    float       mPostion[3];
    float       mRotate[3];

};


#endif //CARPARK_EGLITEM_H
