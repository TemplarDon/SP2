#ifndef ASN_1_H
#define ASN_1_H

#include "Scene.h"

class Asn1 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_RECTANGLE = 0,
        GEO_BATTLEMENT,
        GEO_WALLS,
        GE0_BRIDGE,
        GEO_GATE,
        GEO_SUN,
        GEO_TRIANGLE,
        GEO_BACKGROUND,
        GEO_DARKBLUE,
        GEO_RED,

        NUM_GEOMETRY,

    };

    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_TOTAL,
    };

private:
    unsigned m_vertexArrayID;
    unsigned m_vertexBuffer[NUM_GEOMETRY];
    unsigned m_colorBuffer[NUM_GEOMETRY];
    unsigned m_parameters[U_TOTAL];
    unsigned m_programID;
    float sun_count;
    float rotateAngle;
    float translateX;

    //fire variables
    float scaleAll;
    float translateY;
    bool fireBreakOff;
    
    //human variables
    float humanTranslate;
    float humanHand;
    bool firstLap;

    //gate variables
    float gateAnimation;
    bool gateOpen;

    //cloud variables
    float cloudTranslate;

public:
    Asn1();
    ~Asn1();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
};

#endif