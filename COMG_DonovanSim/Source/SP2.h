#ifndef SP_2_H
#define SP_2_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Camera5.h"
#include "ThirdPersonCamera.h"
#include "Mesh.h"
#include "vertex.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Node.h"

#include "(SP2)InteractableOBJs.h"
#include "(SP2)Building.h"
#include "(SP2)Player.h"

#include <vector>

class SP2 : public Scene
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
        GEO_LIGHTBALL,
        GEO_TEXT,
        GEO_HANDS,

        // For Testing / PlaceHolders
        GEO_WALL,
        GEO_WALL2,
        GEO_GATETOP,
        GEO_GATE,

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

        // Light2
        U_LIGHT1_POSITION,
        U_LIGHT1_COLOR,
        U_LIGHT1_POWER,
        U_LIGHT1_KC,
        U_LIGHT1_KL,
        U_LIGHT1_KQ,
        U_LIGHT1ENABLED,
        U_LIGHT1_TYPE,
        U_LIGHT1_SPOTDIRECTION,
        U_LIGHT1_COSCUTOFF,
        U_LIGHT1_COSINNER,
        U_LIGHT1_EXPONENT,

        // Light3
        U_LIGHT3_POSITION,
        U_LIGHT3_COLOR,
        U_LIGHT3_POWER,
        U_LIGHT3_KC,
        U_LIGHT3_KL,
        U_LIGHT3_KQ,
        U_LIGHT3ENABLED,
        U_LIGHT3_TYPE,
        U_LIGHT3_SPOTDIRECTION,
        U_LIGHT3_COSCUTOFF,
        U_LIGHT3_COSINNER,
        U_LIGHT3_EXPONENT,

        U_NUMLIGHTS,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,

        U_TOTAL,
    };
public:
    SP2();
    ~SP2();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
private:
    Position charPos;

    unsigned m_vertexArrayID;
    unsigned m_vertexBuffer[NUM_GEOMETRY];
    unsigned m_colorBuffer[NUM_GEOMETRY];
    unsigned m_indexBuffer[NUM_GEOMETRY];
    Mesh *meshList[NUM_GEOMETRY];
    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    float rotateAngle;

    Position maxPos;
    Position minPos;

    Position* maxPtr;
    Position* minPtr;

    std::vector<Node>objsMaxMin; // Vector for storing min and max values of objs created

    vector<InteractableOBJs>InteractablesList;
    vector<Building>BuildingsList;

    Camera2 camera;
    Camera3 camera3;
    Camera5 camera5;

    ThirdPersonCamera thirdPersonCamera;


    MS modelStack, viewStack, projectionStack;

    Light light[3];
    bool toggleLight;
    void RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight);

    void RenderSkybox();
    void createBoundBox(vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList);
    void RenderRoom(Position pos, Vector3 size = (1,1,1), int groundMeshSize = 100);

    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

    void gateInteractions(double dt);
    void thwumpMovement(double dt);
    void ifDead(double dt);
    void peachInteractions(double dt);
    void keyInteractions(double dt);
    void doorInteractions(double dt);
    void pipeInteractions(double dt);


	//Equipping
	void RenderHandInfronOfScreen();
};

#endif