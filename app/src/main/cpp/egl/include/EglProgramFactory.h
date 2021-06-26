//
// Created by zhuhailu on 2021/6/25.
//

#ifndef CARPARK_EGLPROGRAMFACTORY_H
#define CARPARK_EGLPROGRAMFACTORY_H

#include <string>
#include <map>

class EglProgram;

class EglProgramFactory {
public:
    static EglProgramFactory* getInstance();
    static void destroyInstance();

    EglProgram* getEglProgram(std::string name);
    EglProgram* createEglProgram(std::string name);
    bool hasEglProgram(std::string name);
    void destroyEglProgram(std::string name);
    bool destroyEglProgram(EglProgram* program);

private:
    EglProgramFactory();
    ~EglProgramFactory();

private:
    static EglProgramFactory* sInstance;
    std::map<std::string, EglProgram*> mProgramMap;
};


#endif //CARPARK_EGLPROGRAMFACTORY_H
