//
// Created by zhuhailu on 2021/6/23.
//

#ifndef CARPARK_CAR_H
#define CARPARK_CAR_H

#include "EglItem.h"

class Camera;

class Car : public EglItem {

EGLITEM_VERTICES_INFO_DEF_H

public:
    Car();
    virtual ~Car();

    virtual void initVerticesInfo(VERTICES_INFO *verticesInfo);

};

EGLITEM_VERTICES_INFO_DEF_INIT(Car)

#endif //CARPARK_CAR_H
