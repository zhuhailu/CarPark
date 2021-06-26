//
// Created by zhuhailu on 2021/6/23.
//

#ifndef CARPARK_CAR_H
#define CARPARK_CAR_H

#include "EglItem.h"

class Camera;

class Car : public EglItem {

public:
    Car();
    virtual ~Car();

    virtual void initVerticeInfo(VERTICE_INFO *verticeInfo);

private:
};


#endif //CARPARK_CAR_H
