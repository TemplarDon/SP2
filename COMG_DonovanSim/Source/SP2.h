#ifndef SP_2_H
#define SP_2_H


#include "Mtx44.h"
#include "Material.h"

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
#include "(SP2)Ship.h"

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

		//Buildings/OBJ   
		GEO_TRADEPOST,
		GEO_SPEAKERS,
		GEO_SOFA,
		GEO_COUNTER,
		GEO_FRIDGE,
		GEO_TABLE,
		GEO_VENDING,
		GEO_CHAIR,
		GEO_TOKEN,

		//NPCs
		GEO_CHEF,

		GEO_SPEAKERS,   
		GEO_SOFA, 

        //Space Ship
        GEO_SHIP,

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
        
		U_LIGHTENABLED,
        U_NUMLIGHTS,

        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,

        U_TEXT_ENABLED,
        U_TEXT_COLOR,

        U_TOTAL,
    };

	enum UNIFORM_LIGHT
	{
		UL_POSITION,
		UL_COLOR,
		UL_POWER,
		UL_KC,
		UL_KL,
		UL_KQ,
		UL_TYPE,
		UL_SPOTDIRECTION,
		UL_COSCUTOFF,
		UL_COSINNER,
		UL_EXPONENT,

		UL_TOTAL,
	};

	static const size_t numLights = 3;

	unsigned m_parameters[U_TOTAL];
	unsigned lightUniforms[numLights][UL_TOTAL];

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

    float rotateAngle;
	float heightOfWall;

    Position maxPos;
    Position minPos;

    Position* maxPtr;
    Position* minPtr;

    Player somePlayer;

    std::vector<Node>objsMaxMin; // Vector for storing min and max values of objs created

    vector<InteractableOBJs>InteractablesList;
    vector<Building>BuildingsList;

    Camera *camPointer;

    Camera3 camera3;


    ThirdPersonCamera thirdPersonCamera;
	Camera5 camera5;

    MS modelStack, viewStack, projectionStack;

    Light light[numLights];
    bool toggleLight;
    void RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight);

    void RenderSkybox();
    void createBoundBox(vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList);
    void RenderRoomTemplate(Position pos, Vector3 size = (1,1,1), int groundMeshSize = 100);
    void initRoomTemplate(Position pos, Vector3 size = (1, 1, 1), int groundMeshSize = 100);
    void rayTracing(vector<InteractableOBJs>&InteractablesList);
	void RenderTradingStation();
	void RenderRecRoom();
	void RenderCafeRoom();

    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderTokenOnScreen(Mesh* mesh, float size, float x, float y);

	float TokenTranslate;

	//Bool for interactions (Shania's)
	bool NearVendingText;
	bool TokenOnScreen;


    void interactionCheck(double dt, vector<InteractableOBJs>&InteractablesList, Player &somePlayer);
};

#endif