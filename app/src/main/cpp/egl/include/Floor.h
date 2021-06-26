//
// Created by zhuhailu on 2021/6/22.
//

#ifndef CARPARK_FLOOR_H
#define CARPARK_FLOOR_H

#include "EglItem.h"

class Floor : public EglItem {

public:
    Floor();
    virtual ~Floor();

    virtual void initVerticeInfo(EglItem::VERTICE_INFO* verticeInfo);

private:

};


#endif //CARPARK_FLOOR_H
