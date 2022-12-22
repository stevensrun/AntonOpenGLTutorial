#pragma once

#include "Mesh.h"

class Triangle : public Mesh
{
public:
    static void* operator new(std::size_t size);
    static void operator delete(void* ptr, std::size_t size);

    Triangle();
    virtual ~Triangle() = default;

private:
    int m_count = 0;
};