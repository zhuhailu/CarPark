//
// Created by zhuhailu on 2021/6/22.
//

#ifndef CARPARK_FLOOR_H
#define CARPARK_FLOOR_H

#include "EglItem.h"

class Floor : public EglItem {

EGLITEM_VERTICES_INFO_DEF_H

public:
    Floor();
    virtual ~Floor();

    virtual void initVerticesInfo(EglItem::VERTICES_INFO* verticesInfo);

private:

};

#endif //CARPARK_FLOOR_H
