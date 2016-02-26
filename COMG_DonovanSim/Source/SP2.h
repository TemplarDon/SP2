#ifndef SP_2_H
#define SP_2_H

#include "GL\glew.h"
#include "shader.hpp"
#include "Utility.h"

#include "Mtx44.h"

#include "Application.h"
#include "Scene.h"
#include "Camera.h"
#include "FirstPersonCamera.h"
#include "ThirdPersonCamera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "Material.h"
#include "LoadTGA.h"
#include "vertex.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Node.h"
#include "timer.h"

#include "InteractableOBJs.h"
#include "Building.h"
#include "Player.h"
#include "ShipBuilder.h"
#include "Keypad.h"

#include <vector>
#include <sstream>
#include <cstdlib>
#include <time.h>

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

		//ROOM TEMPLATE
		GEO_WALL,
		GEO_WALL2,
		GEO_GATETOP,
        GEO_GATETOP2,
		GEO_GATE,
		GEO_TESTDOOR,

		//OBJS
		GEO_TRADEPOST,
		GEO_SPEAKERS,
		GEO_SOFA,
		GEO_COUNTER,
		GEO_FRIDGE,
		GEO_TABLE,
		GEO_VENDING,
		GEO_CHAIR,
		GEO_TOKEN,
		GEO_COKE,
		GEO_CAFETEXTBOX,
		GEO_BUNK,
		GEO_SPACEMASK,
		GEO_SPACESUIT,



        // ARMOURY / SHOP

		GEO_WINDOW,
		GEO_HUD,
		GEO_INVENTORY,
		GEO_HAND,

        GEO_HELIPAD,


        //ARMOURY / SHOP

        GEO_GUN,
        GEO_GUN_RACK,
        GEO_SHOOTING_RANGE,
        GEO_TARGET,
        GEO_SHOP,


        // Infirmary
        
        GEO_BED,
        GEO_HEALING_TUBE,


		//NPCs
		GEO_CHEF,
		GEO_SPACEGUY,
		GEO_NURSE,
		GEO_DOCTOR,
		GEO_TRADER,
		GEO_SOLDIER,
		GEO_SHOPKEEPER,


        //SPACE SHIP
        GEO_SHIP,
        GEO_HULL,
        GEO_WINGS,
        GEO_ENGINE,
        GEO_GROUND,


		//MINE
        GEO_MINE,
		GEO_CRYSTAL,


		//SCIENCE LAB
		GEO_SCIENCELAB_TABLE,
		GEO_SCIENCELAB_CUPBOARD,
		GEO_SCIENCELAB_BEAKER,

		//Keypad
		GEO_KEYPAD,


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

    unsigned m_vertexArrayID;
    unsigned m_vertexBuffer[NUM_GEOMETRY];
    unsigned m_colorBuffer[NUM_GEOMETRY];
    unsigned m_indexBuffer[NUM_GEOMETRY];
    Mesh *meshList[NUM_GEOMETRY];
    unsigned m_programID;


	MS modelStack, viewStack, projectionStack;

    Player somePlayer;

	//Starting position for player
	Position startingCharPos;
    Position charPos;

    // Starting position for ship
    Position shipStartingPos;
	Position shipPos;
	

    // Variable to allow ship to rotate while moving
    float shipHorizontalRotateAngle;
    float shipVerticalRotateAngle;

    vector<InteractableOBJs>InteractablesList;
    vector<Building>BuildingsList;
    vector<Ship>ShipList;

	//CAMERA
    Camera *camPointer;
	FirstPersonCamera firstPersonCamera;
	ThirdPersonCamera thirdPersonCamera;

	//LIGHTS
    Light light[numLights];
    bool toggleLight;
    void RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight);

    //SHIP BUILDER & SHIP POINTER
    ShipBuilder ShipBuilder;
    Ship* shipTemplatePtr;

    //SHIP PARTS
    Light_Hull* LightHull;

    Medium_Hull* MediumHull;
    Large_Hull* LargeHull;

    G1_Engine* G1Engine;
    G2_Engine* G2Engine;
    Dual_Wings* DualWings;
    Quad_Wings* QuadWings;

	//FLOATS (SHANIA'S)
	float TokenTranslate;
	float TextTranslate;
	float TestRotation;
	float SuitTranslate;
	float rotateAngle;
	float heightOfWall;

	//BOOLEANS (SHANIA'S)
	bool NearVendingText;
	bool TokenOnScreen;
	bool GetCokeText;
	bool RenderCoke;
	bool ConsumeCokeText;
	bool PickUpTokenText;
	bool testText;
	bool DisplayCafeMenu;
	bool YesShowCafeMenu;
	bool MENUBOOL;
	bool wearSuitText;
	bool wearSuit;
	bool DisplayInventory;
	bool chefText;
	bool spaceguyText;
	bool nurseText;	
	bool doctorText;
	bool traderText;	
	bool soldierText;
	bool shopkeeperText;

    //DOOR (DONOVAN'S)
    float leftGateOffset;
    float rightGateOffset;
    float frontGateOffset;
    float backGateOffset;
    bool gateOpening;
    bool frontGateOpening;
    bool backGateOpening;
    bool leftGateOpening;
    bool rightGateOpening;

	//JUMP (BECKHAM'S)
	int acceleration;
	int t;
	int firstvelo;
	int secondvelo;
	int distance;
	int gravity; 
	int firstpos;
	bool onGround;


	//MINING INTERACTIONS (BECKHAM'S)    
	bool CrystalText;
	int CrystalNo;
	int posxcheck; 
	int poszcheck; 
	int crystalcount;
	int xcoords[100];
	int zcoords[100];
	bool rendercrystal[100];
	int coord1;
	int coord2;

	//Keypad stuff (Gary's)

	vector<Keypad> keypads;
	void InitKeypads();


	//SHORTHAND CODES FOR EASIER CODINGS (GARY'S)
	void LoadShaderCodes();
	void LoadLights();
	void LoadMeshes();
	void ReadKeyPresses();
	void RenderCode();

	//FUNCTION TO INIT AND RENDER SPACESHIP
	void initSpaceShip();
	void RenderSpaceShip();

	//RENDERING FUNCTION (IN SHORTHAND.CPP)
	void RenderSkybox();
	void RenderTradingStation();
	void RenderRecRoom();
	void RenderCafeRoom();
	void RenderBunkRoom();
	void RenderScienceLab();
	void RenderCrystals();
    void RenderArmouryAndShop();
    void RenderInfirmary();

	//DIALOUGE SYSTEM
	void Dialogues();
	string file_contents;
	vector<string>dialogue_vec;
	void DialoguesWithNPCs();
	void RenderNPCDialogues();

	//RENDER TEXT
	void RenderText(Mesh* mesh, std::string text, Color color);

	//RENDER ON SCREEN
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderTokenOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderCokeOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderCafeTextboxOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderHandOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderHandOnScreen2(Mesh* mesh, float size, float x, float y);
	void RenderCrystalOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderSpacemaskOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderInventoryOnScreen(Mesh* mesh, float size, float x, float y);
	
    
	//INTERACTION DECTECTION
    void interactionCheck(double dt, vector<InteractableOBJs>&InteractablesList, Player &somePlayer);
	
	//INTERACTION FUNCTIONS
    void vendingMachineInteractions();
    void tokenInteractions();
    void counterInteractions();
    void spaceSuitInteractions();
    void doorInteractions(double dt, vector<InteractableOBJs>::iterator it, float& gateOffset, bool &gateOpening);
    void doorClosing(double dt, vector<InteractableOBJs>::iterator it, float& gateOffset, bool &gateOpening);
    void shopInteractions();
    void shipAnimation(double dt, vector<Ship>::iterator i);
    void shipCreation();


	//FUNCTION TO CREATE A ROOM. initRoomTempalte TO MAKE COLLISION, RenderRoomTemplate TO RENDER ROOM
	void initRoomTemplate(Position pos, Vector3 size = (1, 1, 1), int groundMeshSize = 100);
	void RenderRoomTemplate(Position pos, Vector3 size = (1, 1, 1), int groundMeshSize = 100);

    // TEMP BOOLS FOR SHIP BUILDING
    bool askedHull;
    bool askedWings;
    bool askedEngine;
    bool askedShipBuild;
    bool shipBuilt;

	//CRYSTAL RELATED STUFF   
	bool checkCrystalPos(int xcoord, int zcoord, int i);

};

#endif