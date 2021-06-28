//
// Created by zhuhailu on 2021/6/24.
//

#ifndef CARPARK_EGLMAIN_H
#define CARPARK_EGLMAIN_H

#include "esUtil.h"



//int esMain (ESContext *esContext);
void Update ( ESContext *esContext, float deltaTime );
void Draw ( ESContext *esContext );
void Shutdown ( ESContext *esContext );

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


int esMain (ESContext *esContext)
{
    EglMain* main = EglMain::getInstance(esContext);

    esCreateWindow ( esContext, "EglMain", 640, 480, ES_WINDOW_RGB | ES_WINDOW_DEPTH );

    if (!main->init ( esContext ) )
    {
        EglMain::destroyInstance();
        return GL_FALSE;
    }

    esRegisterShutdownFunc ( esContext, Shutdown );
    esRegisterUpdateFunc ( esContext, Update );
    esRegisterDrawFunc ( esContext, Draw );

    return GL_TRUE;
}

#endif //CARPARK_EGLMAIN_H
