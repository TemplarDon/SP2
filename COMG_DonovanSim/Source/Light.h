#ifndef LIGHT_H
#define LIGHT_H

#include "vertex.h"
#include "Vector3.h"

struct Light
{
    enum LIGHT_TYPE
    {
        LIGHT_POINT = 0,
        LIGHT_DIRECTIONAL,
        LIGHT_SPOT,
    };
    Position position;
    Color color;
    float power;
    float kC, kL, kQ; //constant, linear, quadratic

    LIGHT_TYPE type;
    Vector3 spotDirection;
    float cosCutoff;
    float cosInner;
    float exponent;

    Light()
    {
        type = LIGHT_POINT;
        position.Set(0, 0, 0);
        color.Set(1, 1, 1);
        power = 0.f;
        kC = kL = kQ = 1;
		cosCutoff = cosInner = 0;
		exponent = 1;
    }
};

#endif