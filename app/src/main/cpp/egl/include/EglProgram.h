//
// Created by zhuhailu on 2021/6/25.
//

#ifndef CARPARK_EGLPROGRAM_H
#define CARPARK_EGLPROGRAM_H

#include "esUtil.h"

class EglProgram {
public:
    EglProgram() {}
    virtual ~EglProgram() {}

    virtual bool init(ESContext *esContext) = 0;
    virtual void update(ESContext *esContext, float deltaTime) = 0;
    virtual void draw(ESContext *esContext) = 0;
    virtual void shutdown(ESContext *esContext) = 0;

};

#endif //CARPARK_EGLPROGRAM_H
