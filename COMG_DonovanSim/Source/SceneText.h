#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Mesh.h"
#include "vertex.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Node.h"

#include <vector>

class SceneText : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_QUAD,
        GEO_LEFT,
        GEO_RIGHT,
        GEO_TOP,
        GEO_BOTTOM,
        GEO_FRONT,
        GEO_BACK,
        GEO_HEMISPHERE,
        GEO_LIGHTBALL,

        GEO_TEXT,
        GEO_MODEL1,
        GEO_MODEL2,

        GEO_GROUND,
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
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,

        U_TOTAL,
    };
public:
    SceneText();
    ~SceneText();

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

    std::vector<Position> * verticeNum;
    Position maxPos;
    Position minPos;

    std::vector<Node>objsMaxMin; // Vector for storing min and max values of objs created
    std::vector<Position>MaxMinPos; //Vector containing max and min

    Camera2 camera;
    Camera3 camera3;

    MS modelStack, viewStack, projectionStack;

    Light light[1];
    bool toggleLight;
    void RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight);

    void RenderSkybox();
    void createBoundBox(std::vector<Node>&objsMaxMin, std::vector<Position>* verticeNum, std::vector<Position>& MaxMinPos);

    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

};

#endif