//
// Created by zhuhailu on 2021/6/22.
//

#ifndef CARPARK_CARPACK_H
#define CARPARK_CARPACK_H

#include "EglProgram.h"

class CarPack : public EglProgram {
public:
    CarPack();

    virtual bool init (ESContext *esContext);
    virtual void update (ESContext *esContext, float deltaTime);
    virtual void draw (ESContext *esContext);
    virtual void shutdown (ESContext *esContext);

private:



};

#endif //CARPARK_CARPACK_H
