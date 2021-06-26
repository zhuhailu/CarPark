//
// Created by zhuhailu on 2021/6/23.
//

#include "Camera.h"

Camera* Camera::sActiveCamera = NULL;

Camera::Camera()
    : mTarget(NULL)
{}

Camera::~Camera()
{
    if (this == sActiveCamera) {
        sActiveCamera = NULL;
    }
}

