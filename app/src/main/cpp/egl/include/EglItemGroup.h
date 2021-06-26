//
// Created by zhuhailu on 2021/6/22.
//

#ifndef CARPARK_EGLITEMGROUP_H
#define CARPARK_EGLITEMGROUP_H

#include "EglItem.h"

class EglItemGroup : protected EglItem {
public:
    EglItemGroup();
    virtual ~EglItemGroup();

    virtual void initVerticeInfo(VERTICE_INFO *verticeInfo) {}



private:


};


#endif //CARPARK_EGLITEMGROUP_H
