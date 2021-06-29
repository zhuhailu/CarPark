//
// Created by zhuhailu on 2021/6/22.
//

#include "CarPark.h"
#include "EglItemGroup.h"
#include "Floor.h"


CarPark::CarPark()
    : EglProgram()
{}

CarPark::~CarPark()
{}

EglItemGroup* CarPark::createWorld()
{
    EglItemGroup* root = new EglItemGroup();

//    for (int i = 0; i < 10; ++i) {
//
//    }

    Floor* f = new Floor();
    f->setScale(10, 2, 0);
    f->setRotateX(45.0f);
    f->setColor(255, 0, 0);
    root->addChild(f);

    return root;
}

void CarPark::getShaderSrc(char** vertShaderSrc, char** fragShaderSrc)
{
    const char vShaderStr[] =
            "#version 300 es                             \n"
            "layout(location = 0) in vec4 i_vertices;    \n"
            "layout(location = 1) in vec4 i_color;       \n"
            "layout(location = 2) in int  i_index;       \n"
            "layout(location = 3) in vec3 i_size;        \n"
            "layout(location = 4) in mat4 i_mvpMatrix;   \n"
            "out vec4 v_color;                           \n"
            "void main()                                 \n"
            "{                                           \n"
            "   if (gl_VertexID < i_index)               \n"
            "       return;                              \n"
            "                                            \n"
            "   vec4 u_vertices = vec4(i_vertices.x * i_size.x, i_vertices.y * i_size.y, \
                                  i_vertices.z * i_size.z, i_vertices.w);         \n"
            "   v_color = i_color;                       \n"
            "   gl_Position = i_mvpMatrix * u_vertices;  \n"
            "}                                           \n";

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

