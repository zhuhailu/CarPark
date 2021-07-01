//
// Created by zhuhailu on 2021/6/22.
//

#ifndef CARPARK_CARPARK_H
#define CARPARK_CARPARK_H

#include "EglProgram.h"

class EglItem;

class CarPark : public EglProgram {
public:
    CarPark();
    virtual ~CarPark();

    virtual EglItemGroup* createWorld();
    virtual void updateWorld(float deltaTime);
    virtual void getShaderSrc(char** vertShaderSrc, char** fragShaderSrc);

private:
    EglItemGroup* mRoot;
    EglItem* mCar;
    bool mIsForward;
};

#endif //CARPARK_CARPARK_H
