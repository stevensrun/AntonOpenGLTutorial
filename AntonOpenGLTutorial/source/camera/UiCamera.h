#pragma once

#include "Camera.h"

class UiCamera : public Camera
{
public:
    UiCamera(int width, int height);
    virtual ~UiCamera() = default;
};