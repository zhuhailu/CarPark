//
// Created by zhuhailu on 2021/6/24.
//

#include "EglMain.h"
#include "EglProgramFactory.h"
#include "EglProgramDef.h"
#include "EglProgram.h"

EglMain* EglMain::sInstance = NULL;
//
//int esMain (ESContext *esContext)
//{
//    EglMain* main = EglMain::getInstance(esContext);
//
//    esCreateWindow ( esContext, "EglMain", 640, 480, ES_WINDOW_RGB | ES_WINDOW_DEPTH );
//
//    if (!main->init ( esContext ) )
//    {
//        EglMain::destroyInstance();
//        return GL_FALSE;
//    }
//
//    esRegisterShutdownFunc ( esContext, Shutdown );
//    esRegisterUpdateFunc ( esContext, Update );
//    esRegisterDrawFunc ( esContext, Draw );
//
//    return GL_TRUE;
//}

void Update ( ESContext *esContext, float deltaTime )
{
    EglMain::getInstance(esContext)->update(esContext, deltaTime);
}

void Draw ( ESContext *esContext )
{
    EglMain::getInstance(esContext)->draw(esContext);
}

void Shutdown ( ESContext *esContext )
{
    EglMain::getInstance(esContext)->shutdown(esContext);
}

EglMain* EglMain::getInstance(ESContext *esContext)
{
    if (NULL == sInstance) {
        sInstance = new EglMain(esContext);
    }
    return sInstance;
}

void EglMain::destroyInstance()
{
    if (NULL != sInstance) {
        delete sInstance;
        sInstance = NULL;
    }
}

EglMain::EglMain(ESContext *esContext)
    : mCurrentProgram(NULL)
{

}

EglMain::~EglMain()
{
    EglProgramFactory::destroyInstance();
}

bool EglMain::init(ESContext *esContext)
{
    mCurrentProgram = EglProgramFactory::getInstance()->createEglProgram(PROGRAM_CARPACK);
    if (NULL == mCurrentProgram)
        return false;

    return mCurrentProgram->init(esContext);
}

void EglMain::update ( ESContext *esContext, float deltaTime )
{
    if (NULL != mCurrentProgram) {
        mCurrentProgram->update(esContext, deltaTime);
    }
}

void EglMain::draw ( ESContext *esContext )
{
    if (NULL != mCurrentProgram) {
        mCurrentProgram->draw(esContext);
    }
}

void EglMain::shutdown ( ESContext *esContext )
{
    if (NULL != mCurrentProgram) {
        mCurrentProgram->shutdown(esContext);

        EglProgramFactory::getInstance()->destroyEglProgram(mCurrentProgram);
        if (NULL != mCurrentProgram) {
            delete mCurrentProgram;
        }
        mCurrentProgram = NULL;
    }
}

// EOF