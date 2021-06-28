//
// Created by zhuhailu on 2021/6/22.
//

#ifndef CARPARK_CARPARK_H
#define CARPARK_CARPARK_H

#include "EglProgram.h"


class CarPark : public EglProgram {
public:
    CarPark();
    virtual ~CarPark();

    virtual EglItemGroup* createWorld();
    virtual void getShaderSrc(char* vertShaderSrc, char* fragShaderSrc);

private:
};

#endif //CARPARK_CARPARK_H
