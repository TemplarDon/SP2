#ifndef ASN_2_H
#define ASN_2_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "vertex.h"
#include "MatrixStack.h"
#include "Light.h"

class Asn2 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_QUAD,
        GEO_CUBE,
        GEO_CIRCLE,
        GEO_RING,
        GEO_SPHERE,
        GEO_TORUS,
        GEO_HEMISPHERE,
        GEO_CYLINDER,

        GEO_SHIPBODY,
        GEO_SHIPTORUS,
        GEO_SHIPLIPS,
        GEO_SHIPMOUTH,
        GEO_SHIPCANNON,
        GEO_SHIPCANNONTORUS,
        GEO_EYES,
        GEO_EYESSIDES,
        GEO_PROPELLOR,
        GEO_BOWSERBODY,
        GEO_BOWSERBELLY,
        GEO_BOWSERHEAD,
        GEO_BOWSERHAIR,
        GEO_BOWSERCHIN,
        GEO_INSIDEMOUTH,
        GEO_OUTERSHELL,
        GEO_INNERSHELL,
        GEO_SPIKETORUS,
        GEO_SPIKECONE,
        GEO_ARM,
        GEO_ARMCONNECTOR,
        
        GEO_BOMBTORUS,
        GEO_BOMBBODY,
        GEO_BOMBSTRING,
        GEO_BOMBFIRE,

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
        U_TOTAL,
    };
public:
    Asn2();
    ~Asn2();

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
    float propellorWingAngle; // For individual wings
    float propellorRotateAngle; // For entire propellor

    bool waveArmAnimation; // Toggle wave arm animation
    float armWaveAngle; // For arm waving
    bool armGoingUp; // If arm is going up or down

    bool mouthRotateAnimation;
    float mouthRotateAngle;
    bool mouthOpen;

    float fireExpand;
    bool fireExpanding;

    float cannonFireDistance;
    bool cannonFiring;
    bool bombExploding;
    float bombExplosion;
    bool bombDestroyed;

    float modelXLocation;
    float modelYLocation;
    float modelZLocation;
    float directionAngle;
    float leanAngle;
    bool leanAngleReset;

    Camera2 camera;

    MS modelStack, viewStack, projectionStack;

    Light light[1];
    bool toggleLight;
    void RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight);
};

#endif