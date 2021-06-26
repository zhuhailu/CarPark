//
// Created by zhuhailu on 2021/6/23.
//

#ifndef CARPARK_CAMERA_H
#define CARPARK_CAMERA_H

#include "EglItem.h"

class Camera : public EglItem{

public:
    Camera();
    virtual ~Camera();

    virtual void initVerticeInfo(VERTICE_INFO *verticeInfo) final {}
    virtual bool isPerspective() { return true; }

    void setTarget(EglItem* target) { mTarget = target; }
    inline EglItem* getTarget() { return mTarget; }

    static void setActiveCamera(Camera* camera) { sActiveCamera = camera; }
    static Camera* getActiveCamera() { return sActiveCamera; }

private:
    void setParent(EglItem* parent) = delete;
    void addChild(EglItem* child, const int pos = -1) = delete;

private:
    static Camera* sActiveCamera;

    EglItem*    mTarget;

};


#endif //CARPARK_CAMERA_H
