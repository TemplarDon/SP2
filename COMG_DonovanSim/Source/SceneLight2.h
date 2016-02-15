#ifndef SCENE_LIGHT_2_H
#define SCENE_LIGHT_2_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "vertex.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneLight2 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_QUAD,
        GEO_CUBE,
        GEO_CIRCLE,
        GEO_RING,
        GEO_SPHERE,
        GEO_SPHERE1,
        GEO_SPHERE2,
        GEO_SPHERE3,
        GEO_SPHERE4,
        GEO_SPHERE5,
        GEO_SPHERE6,
        GEO_SPHERE7,
        GEO_SPHERE8,
        GEO_HEMISPHERE,
        GEO_LIGHTBALL,
        NUM_GEOMETRY,
    };
    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_MODELVIEW,
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_MATERIAL_AMBIENT,
        U_MATERIAL_DIFFUSE,
        U_MATERIAL_SPECULAR,
        U_MATERIAL_SHININESS,
        U_LIGHT0_POSITION,
        U_LIGHT0_COLOR,
        U_LIGHT0_POWER,
        U_LIGHT0_KC,
        U_LIGHT0_KL,
        U_LIGHT0_KQ,
        U_LIGHTENABLED,
        U_LIGHT0_TYPE,
        U_LIGHT0_SPOTDIRECTION,
        U_LIGHT0_COSCUTOFF,
        U_LIGHT0_COSINNER,
        U_LIGHT0_EXPONENT,
        U_NUMLIGHTS,
        U_TOTAL,
    };
public:
    SceneLight2();
    ~SceneLight2();

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

    Camera2 camera;

    MS modelStack, viewStack, projectionStack;

    Light light[1];
    bool toggleLight;
    void RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight);
};

#endif