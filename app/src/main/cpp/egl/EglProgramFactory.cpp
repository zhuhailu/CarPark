//
// Created by zhuhailu on 2021/6/25.
//

#include "EglProgramFactory.h"
#include "EglProgram.h"
#include "EglProgramDef.h"
#include "CarPark.h"

EglProgramFactory* EglProgramFactory::sInstance = NULL;

EglProgramFactory* EglProgramFactory::getInstance()
{
    if (NULL == sInstance) {
        sInstance = new EglProgramFactory();
    }
    return sInstance;
}

void EglProgramFactory::destroyInstance()
{
    if (NULL != sInstance) {
        delete sInstance;
        sInstance = NULL;
    }
}

EglProgramFactory::EglProgramFactory()
{
}

EglProgramFactory::~EglProgramFactory()
{
    for (auto& it: mProgramMap) {
        delete it.second;
        it.second = NULL;
    }
    mProgramMap.clear();
}

EglProgram* EglProgramFactory::getEglProgram(std::string name)
{
    EglProgram* ret = NULL;

    auto it = mProgramMap.find(name);
    if (it != mProgramMap.end()) {
        ret = it->second;
    }
    else {
        ret = createEglProgram(name);
    }

    return ret;
}


EglProgram* EglProgramFactory::createEglProgram(std::string name)
{
    EglProgram* program = NULL;
    if (PROGRAM_CARPACK == name) {
        program = static_cast<EglProgram*>(new CarPark());
    }
    else {
        // do nothing.
    }

    if (NULL != program) {
        auto pair = mProgramMap.insert(std::pair<std::string, EglProgram*>(name, program));
        if (!pair.second) {
            delete program;
            program = pair.first->second;
        }
    }

    return program;
}

bool EglProgramFactory::hasEglProgram(std::string name)
{
    if (PROGRAM_CARPACK == name) {
        return true;
    }

    return false;
}

void EglProgramFactory::destroyEglProgram(std::string name)
{
    auto it = mProgramMap.find(name);
    if (it != mProgramMap.end()) {
        EglProgram* program = it->second;
        mProgramMap.erase(it);
        delete program;
    }
}

bool EglProgramFactory::destroyEglProgram(EglProgram *program)
{
    auto it = mProgramMap.cbegin();
    for (; it != mProgramMap.cend(); ++it) {
        if (it->second == program) {
            mProgramMap.erase(it);
            delete program;
            program = NULL;
            return true;
        }
    }
    return false;
}

// EOF