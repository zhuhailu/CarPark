//
// Created by zhuhailu on 2021/6/24.
//

#ifndef CARPARK_EGLMAIN_H
#define CARPARK_EGLMAIN_H

#include "esUtil.h"


extern "C" {
    int esMain(ESContext *esContext);
    void Update(ESContext *esContext, float deltaTime);
    void Draw(ESContext *esContext);
    void Shutdown(ESContext *esContext);
};

class EglProgram;

class EglMain {
public:
    static EglMain* getInstance(ESContext *esContext);
    static void destroyInstance();

    bool init ( ESContext *esContext );
    void update ( ESContext *esContext, float deltaTime );
    void draw ( ESContext *esContext );
    void shutdown ( ESContext *esContext );

private:
    EglMain(ESContext* esContext);
    virtual ~EglMain();

private:
    static EglMain* sInstance;

    EglProgram* mCurrentProgram;
};

#endif //CARPARK_EGLMAIN_H
