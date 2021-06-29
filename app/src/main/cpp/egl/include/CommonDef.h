//
// Created by zhuhailu on 2021/6/24.
//

#ifndef CARPARK_COMMONDEF_H
#define CARPARK_COMMONDEF_H

#include "android/log.h"

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "esUtil", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "esUtil", __VA_ARGS__))

#define EGLITEM_VERTICES_INFO_DEF_H                                         \
public:                                                                     \
    virtual VERTICES_INFO* getVerticesInfoObj() { return sVerticesInfo; }   \
    virtual bool setVerticesInfoObj(VERTICES_INFO* verticesInfo) {          \
        if (NULL == sVerticesInfo || NULL == verticesInfo) {                \
            sVerticesInfo = verticesInfo;                                   \
            return true;                                                    \
        }                                                                   \
        return false;                                                       \
    }                                                                       \
private:                                                                    \
    static VERTICES_INFO* sVerticesInfo;


#define EGLITEM_VERTICES_INFO_DEF_INIT(Class) \
EglItem::VERTICES_INFO* Class::sVerticesInfo = NULL;



#endif //CARPARK_COMMONDEF_H
