#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "vertex.h"
#include "MatrixStack.h"

class Scene4 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_QUAD,
        GEO_CUBE,
        GEO_CIRCLE,
        GEO_RING,
        GEO_SPHERE,
        GEO_HEMISPHERE,
        GEO_PLANET1,
        GEO_MOON1,
        GEO_SUN,
        GEO_RING1,
        GEO_MERCURY,
        GEO_VENUS,
        GEO_EARTH,
        GEO_MOON,
        GEO_MARS,
        GEO_JUPITER,
        GEO_SATURN,
        GEO_SATURNRING,
        GEO_URANUS,
        GEO_NEPTUNE,
        NUM_GEOMETRY,
    };
    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_TOTAL,
    };
public:
    Scene4();
    ~Scene4();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
private:
    unsigned m_vertexArrayID;
    unsigned m_vertexBuffer[NUM_GEOMETRY];
    unsigned m_colorBuffer[NUM_GEOMETRY];
    unsigned m_indexBuffer[NUM_GEOMETRY];
    Mesh *meshList[NUM_GEOMETRY];
    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    float rotateAngle;
    float planet1RevAngle, planet1RotAngle, moon1RotAngle;
    float venusRevAngle, venusRotAngle;
    float earthRevAngle, earthRotAngle, moonRevAngle;
    float marsRevAngle, marsRotAngle;
    float jupiterRevAngle, jupiterRotAngle;
    float saturnRevAngle, saturnRotAngle;
    float uranusRevAngle, uranusRotAngle;
    float neptuneRevAngle, neptuneRotAngle;

    Camera camera;

    MS modelStack, viewStack, projectionStack;
};

#endif