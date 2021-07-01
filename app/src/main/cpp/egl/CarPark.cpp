//
// Created by zhuhailu on 2021/6/22.
//

#include "CarPark.h"
#include "EglItemGroup.h"
#include "Floor.h"
#include "Car.h"
#include "Camera.h"


CarPark::CarPark()
    : EglProgram()
    , mRoot(NULL)
    , mCar(NULL)
    , mIsForward(true)
{}

CarPark::~CarPark()
{}

EglItemGroup* CarPark::createWorld()
{
    mRoot = new EglItemGroup();

    Floor* floor = new Floor();
    floor->setScale(15, 5, 1);
    floor->setRotate(20.0f, 0.0f, 0.0f);
    floor->setPostion(0, 0, 0);
    floor->setColor(153, 229, 238);
    mRoot->addChild(floor);

    int count = 11;
    for (int i = 0; i < count; ++i) {
        Car* car = new Car();
        car->setScale(1, 1, 1);
        car->setRotate(0.0f, 0.0f, 90.0f);
        car->setPostion(i - int(count / 2), 1, 0);
        car->setColor(255, 255, 0);
        floor->addChild(car);
    }

    for (int i = 0; i < count; ++i) {
        Car* car = new Car();
        car->setScale(1, 1, 1);
        car->setRotate(0.0f, 0.0f, 270.0f);
        car->setPostion(i - int(count / 2), -1, 0);
        car->setColor(255, 255, 0);
        floor->addChild(car);
    }

    mCar = new Car();
    mCar->setScale(1, 1, 1);
    mCar->setRotate(0.0f, 0.0f, 0.0f);
    mCar->setPostion(0, 0, 0);
    mCar->setColor(255, 0, 0);
    floor->addChild(mCar);

    Camera* camera = new Camera();
    Camera::setActiveCamera(camera);
    camera->setTarget(mCar);
    camera->setPostion(0, 0, 10);

    return mRoot;
}

void CarPark::updateWorld(float deltaTime)
{
    float x = mCar->getPostionX();
    float speed = 10.0f/10;
    float range = 5.0f;
    if (mIsForward) {
        if (x >= range) {
            mIsForward = false;
            x = x - deltaTime * speed;
        }
        else {
            x = x + deltaTime * speed;
        }
    }
    else {
        if (x <= -range) {
            mIsForward = true;
            x = x + deltaTime * speed;
        }
        else {
            x = x - deltaTime * speed;
        }
    }
    mCar->setPostionX(x);


//    EglItem* item = mRoot->getChild(0);
//    item->setRotateX(item->getRotateX() + deltaTime * 20.0f);
}

void CarPark::getShaderSrc(char** vertShaderSrc, char** fragShaderSrc)
{
    const char vShaderStr[] =
            "#version 300 es                                                    \n"
            "layout(location = 0) in vec4 i_vertices;                           \n"
            "layout(location = 1) in vec4 i_color;                              \n"
            "layout(location = 2) in vec3 i_size;                               \n"
            "layout(location = 3) in vec2 i_index;                            \n"
            "layout(location = 4) in mat4 i_mvpMatrix;                          \n"
            "out vec4 v_color;                                                  \n"
            "void main()                                                        \n"
            "{                                                                  \n"
            "   if (gl_VertexID >= int(i_index.x) && gl_VertexID < int(i_index.y) ) {     \n"
            "       vec4 u_vertices = vec4(i_vertices.x * i_size.x, i_vertices.y * i_size.y, \
                                  i_vertices.z * i_size.z, i_vertices.w);       \n"
            "       gl_Position = i_mvpMatrix * u_vertices;                     \n"
            "   }                                                               \n"
            "   else {                                                          \n"
            "       gl_Position = vec4(0.0f);                                   \n"
            "   }                                                               \n"
            "       v_color = i_color;                                          \n"
            "}                                                                  \n";



    const char fShaderStr[] =
            "#version 300 es                                \n"
            "precision mediump float;                       \n"
            "in vec4 v_color;                               \n"
            "layout(location = 0) out vec4 outColor;        \n"
            "void main()                                    \n"
            "{                                              \n"
            "  outColor = v_color;                          \n"
            "}                                              \n";

    *vertShaderSrc = static_cast<char*>(malloc(sizeof(vShaderStr)));
    memcpy(*vertShaderSrc, vShaderStr, sizeof(vShaderStr));

    *fragShaderSrc = static_cast<char*>(malloc(sizeof(fShaderStr)));
    memcpy(*fragShaderSrc, fShaderStr, sizeof(fShaderStr));
}

