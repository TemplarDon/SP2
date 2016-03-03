/*************************************************************************************************/
/*!
\file   SP2.h
\brief
    Header File for the SP2 Class with parent class Scene, contains all functions and code for SP2
*/
/*************************************************************************************************/

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


/*************************************************************************************************/
/*!
Class SP2 : public Scene
\brief
    Class SP2, with parent class Scene. Contains Constructor/ Destructor for SP2 and contains enums, functions and variables for SP2
*/
/*************************************************************************************************/

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
		GEO_HELIPADSIGN,


		GEO_WINDOW,
		GEO_HUD,
		GEO_INVENTORY,
		GEO_HAND,

		//WEAPON
		GEO_HOLDGUN,
		GEO_HOLDPICKAXE,
		GEO_POINTER,
		GEO_THISGUNBETTERWORKS,

		GEO_ASTEROID,


		//INVENTORY
		GEO_FIRSTBOX,
		GEO_SECONDBOX,
		GEO_THIRDBOX,
		GEO_FOURTHBOX,
		GEO_FIFTHBOX,
		GEO_SIXTHBOX,
		GEO_SEVENTHBOX,

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


		//INSTRUCTIONS BOX
		GEO_INSTRUCTIONBOX,

		//NPC dialogue box
		GEO_NPCDIALOGUEBOX,

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

		//Keypad + Safe
		GEO_KEYPAD,
		GEO_SAFE_BOX,
		GEO_SAFE_DOOR,

		//CAFE MENU
		GEO_CAFEPOINTER,
		GEO_BREAD,
		GEO_COFFEE,
		GEO_APPLE,


		//HEALTH BAR
		GEO_DEADHEALTHBAR,
		GEO_ALIVEHEALTHBAR,



		//SHOP
		GEO_SHOPPOINTER1,
		GEO_SHOPLIST1,
		GEO_SHOPLIST2,
		GEO_SHOPLIST3,
		GEO_SHOPLIST4,


		//Maze Walls
		GEO_MAZE_SIDE_WALL,
		GEO_MAZE_OBSTACLE,
		GEO_MAZE_ROOF,
		GEO_MAZE_TREASURE,
		GEO_PEDASTAL,
		GEO_SIGNBOARD,
		GEO_LAVA,

		// Mountains for Boundary
		GEO_MOUNTAIN,

		// Base
		GEO_BASE,
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


	//CAFE MENU
	enum CafeMenu
	{
		OPTION_APPLE,
		OPTION_COFFEE,
		PLACE3,
		CAFENOMENU,
	};


	//SHOP LIST
	enum ShopList
	{
		OPTION_HULL,
		OPTION_WINGS,
		OPTION_ENGINE,
		OPTION_CREATESHIP,
		OPTION_LIGHTHULL,
		OPTION_MEDIUMHULL,
		OPTION_LARGEHULL,
		OPTION_DUALWINGS,
		OPTION_QUADWINGS,
		OPTION_G1ENGINE,
		OPTION_G2ENGINE,
		POSITION12,
		POSITION13,
		POSITION14,
		POSITION15,
		SHOPNOMENU,
	};

	//Light data. Variable numLights is used to define the number of lights this scene has.
	static const size_t numLights = 8; Light light[numLights];
	unsigned m_parameters[U_TOTAL];
	unsigned lightUniforms[numLights][UL_TOTAL];

	void setLightData(
		const size_t &index,
		const Light::LIGHT_TYPE &type,
		const Position &pos,
		const Color &color,
		const float &power,
		const float &kC,
		const float &kL,
		const float &kQ,
		const float &cutoff,
		const float &inner,
		const float &exponent,
		const Vector3 &spotDirection);

	void setLightColor(const size_t &index, const Color &C);
	void setLightPower(const size_t &index, const float &P);
	void setLightCutoff(const size_t &index, const float &D);
	void setLightInner(const size_t &index, const float &D);
	void moveLightPosition(const size_t &index, const Vector3 &M, const bool &absolute);
	void rotateSpotlight(const size_t &index, const float &degrees, const Vector3 &axis);
	void rotateDirectionalLight(const size_t &index, const float &degrees, const Vector3 &axis);

	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];
	Mesh *meshList[NUM_GEOMETRY];
	unsigned m_programID;

	void MeshInit(GEOMETRY_TYPE G,
		Mesh *mesh,
		const unsigned &textureID = 0,
		const Component &ambient = { 0.4f, 0.4f, 0.4f },
		const Component &diffuse = { 0.5f, 0.5f, 0.5f },
		const Component &specular = { 0, 0, 0 },
		const float &shininess = 1
		);

public:
	SP2();
	~SP2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
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
	bool toggleLight;
	void RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight);

	//SHIP BUILDER & SHIP POINTER
    /******************************************************************************/
    /*!
    \brief
        ShipBuilder Object, used to create the ship
    */
    /******************************************************************************/
	ShipBuilder ShipBuilder;

    /******************************************************************************/
    /*!
    \brief
        Ship Template that is used to build ship
    */
    /******************************************************************************/
	Ship* shipTemplatePtr;

	//SHIP PARTS
    /******************************************************************************/
    /*!
    \brief
        Light_Hull class object used for shipBuilding
    */
    /******************************************************************************/
	Light_Hull* LightHull;

    /******************************************************************************/
    /*!
    \brief
        Medium_Hull class object for shipBuilding
    */
    /******************************************************************************/
	Medium_Hull* MediumHull;

    /******************************************************************************/
    /*!
    \brief
        Large_Hull class object for shipBuilding
    */
    /******************************************************************************/
	Large_Hull* LargeHull;

    /******************************************************************************/
    /*!
    \brief
        G1_Engine class object for shipBuilding
    */
    /******************************************************************************/
	G1_Engine* G1Engine;

    /******************************************************************************/
    /*!
    \brief
        G2_Engine class object for shipBuilding
    */
    /******************************************************************************/
	G2_Engine* G2Engine;

    /******************************************************************************/
    /*!
    \brief
        Dual_Wings class object for shipBuilding
    */
    /******************************************************************************/
	Dual_Wings* DualWings;

    /******************************************************************************/
    /*!
    \brief
        Quad_Wings class object for shipBuilding
    */
    /******************************************************************************/
	Quad_Wings* QuadWings;


	//FLOATS (SHANIA'S)
	float TokenTranslate;
	float TextTranslate;
	float TestRotation;
	float rotateAngle;
	float heightOfWall;
	float translatePointer;
	double BounceTime;
	float SpinTheFood;

	//DOUBLE
	double testDouble;

	//BOOLEANS (SHANIA'S)
	bool NearVendingText;
	bool TokenOnScreen;
	bool GetCokeText;
	bool RenderCoke;
	bool ConsumeCokeText;
	bool PickUpTokenText;
	bool testText;
	bool MenuBool;
	bool wearSuitText;
	bool wearSuit;
	bool DisplayInventory;
	bool chefText;
	bool spaceguyText;
	bool nurseText;
	bool doctorText;
	bool traderText;
	bool soldierText;
	bool equipPickaxe;
	bool equipGun;
	bool HandDisappear;
	bool BreadAppear;
	bool CoffeeAppear;
	bool AppleAppear;
	bool NPCInCafeTokenTask;
	bool NPCInRecMazeTask;

	//DOOR (DONOVAN'S)
    /******************************************************************************/
    /*!
    \brief
        value to move the left gate of the room
    */
    /******************************************************************************/
	float leftGateOffset;

    /******************************************************************************/
    /*!
    \brief
        value to move the right gate of the room
    */
    /******************************************************************************/
	float rightGateOffset;

    /******************************************************************************/
    /*!
    \brief
        value to move the front gate of the room
    */
    /******************************************************************************/
	float frontGateOffset;

    /******************************************************************************/
    /*!
    \brief
        value to move the back gate of the room
    */
    /******************************************************************************/
	float backGateOffset;

    /******************************************************************************/
    /*!
    \brief
        bool to know if front gate of the room is opening
    */
    /******************************************************************************/
	bool frontGateOpening;

    /******************************************************************************/
    /*!
    \brief
    bool to know if back gate of the room is opening
    */
    /******************************************************************************/
	bool backGateOpening;

    /******************************************************************************/
    /*!
    \brief
    bool to know if left gate of the room is opening
    */
    /******************************************************************************/
	bool leftGateOpening;

    /******************************************************************************/
    /*!
    \brief
    bool to know if right gate of the room is opening
    */
    /******************************************************************************/
	bool rightGateOpening;

	// Maze
    /******************************************************************************/
    /*!
    \brief
        value of translation to move maze wall
    */
    /******************************************************************************/
	float mazeTranslateValue;

    /******************************************************************************/
    /*!
    \brief
        random value to move maze wall
    */
    /******************************************************************************/
	float mazeRandomTranslate;

    /******************************************************************************/
    /*!
    \brief
        value to move the lava by
    */
    /******************************************************************************/
	float lavaTranslation;

    /******************************************************************************/
    /*!
    \brief
        vector to hold randomMazeTranslateValues
    */
    /******************************************************************************/
	vector<float>mazeRandomTranslateVec;

    /******************************************************************************/
    /*!
    \brief
        bool to show if players' dead
    */
    /******************************************************************************/
	bool deadText;

    /******************************************************************************/
    /*!
    \brief
        bool to show text when near treasure
    */
    /******************************************************************************/
	bool treasureText;

    /******************************************************************************/
    /*!
    \brief
        bool to know that treasure has been taken
    */
    /******************************************************************************/
	bool treasureTaken;

	//JUMP (BECKHAM'S)
	/******************************************************************************/
	/*!
	\brief
	float to determine jump speed 
	*/
	/******************************************************************************/
	float acceleration;
	/******************************************************************************/
	/*!
	\brief
	float to determine jump speed    
	*/
	/******************************************************************************/
	float t;
	/******************************************************************************/
	/*!
	\brief
	float to take in initial velocity  
	*/
	/******************************************************************************/
	float firstvelo;
	/******************************************************************************/
	/*!
	\brief
	float to take in final velocity    
	*/
	/******************************************************************************/
	float secondvelo;
	/******************************************************************************/
	/*!
	\brief
	float to determine how high up the player is during the jump animation  
	*/
	/******************************************************************************/
	float distance;
	/******************************************************************************/
	/*!
	\brief
	float to bring the player position down while he's in the air 
	*/
	/******************************************************************************/
	float gravity;
	/******************************************************************************/
	/*!
	\brief
	float to take in player's ycoord before jumping   
	*/
	/******************************************************************************/
	float firstpos;
	/******************************************************************************/
	/*!
	\brief
	bool to determine if player is currently on the ground or not   
	*/
	/******************************************************************************/
	bool onGround;

	//Booleans by Gary Goh.
	bool isInViewSpheres;


	//MINING INTERACTIONS (BECKHAM'S)    
	/******************************************************************************/
	/*!
	\brief
	bool to determine if within range to show text on how to mine crystal   
	*/
	/******************************************************************************/
	bool CrystalText;
	/******************************************************************************/
	/*!
	\brief
	int to take in how many crystals should be rendered on the map  
	*/
	/******************************************************************************/
	int CrystalNo;
	/******************************************************************************/
	/*!
	\brief
	float to take in current x coord the player is at  
	*/
	/******************************************************************************/
	float posxcheck;
	/******************************************************************************/
	/*!
	\brief
	float to take in current z coord the player is at 
	*/
	/******************************************************************************/
	float poszcheck;    
	/******************************************************************************/
	/*!
	\brief
	array to take in xcoord of all crystals  
	*/
	/******************************************************************************/
	float xcoords[100];
	/******************************************************************************/
	/*!
	\brief
	array to take in zcoord of all crystals  
	*/
	/******************************************************************************/
	float zcoords[100];
	/******************************************************************************/
	/*!
	\brief
	array to determine if the crystal at that position should be rendered  
	*/
	/******************************************************************************/
	bool rendercrystal[100];    
	/******************************************************************************/
	/*!
	\brief
	float to hold value while calculating movement of asteroids   
	*/
	/******************************************************************************/
	float coord1;
	/******************************************************************************/
	/*!
	\brief
	float to hold value while calculating movement of asteroids    
	*/
	/******************************************************************************/
	float coord2;

	//ASTEROID RELATED    
	/******************************************************************************/
	/*!
	\brief
	int to determined how many asteroids should be rendered    
	*/
	/******************************************************************************/
	int AsteroidNo;
	/******************************************************************************/
	/*!
	\brief
	array to take in x coord of all asteroids  
	*/
	/******************************************************************************/
	float asteroidx[50];
	/******************************************************************************/
	/*!
	\brief
	array to take in movement along xcoord of all asteroids  
	*/
	/******************************************************************************/
	float movex[50];
	/******************************************************************************/
	/*!
	\brief
	array to take in rotation along xcoord of all asteroids  
	*/
	/******************************************************************************/
	float rotatex[50];
	/******************************************************************************/
	/*!
	\brief
	array to take in z coord of all asteroids   
	*/
	/******************************************************************************/
	float asteroidz[50];
	/******************************************************************************/
	/*!
	\brief
	array to take in movement along z coord of all asteroids   
	*/
	/******************************************************************************/
	float movez[50];
	/******************************************************************************/
	/*!
	\brief
	float to take in rotation along z coord of all asteroids   
	*/
	/******************************************************************************/
	float rotatez[50];
	/******************************************************************************/
	/*!
	\brief
	float to take in y coord of all asteroids  
	*/
	/******************************************************************************/
	float asteroidy[50];
	/******************************************************************************/
	/*!
	\brief
	float to determine if the asteroid in that position of the array should be rendered   
	*/
	/******************************************************************************/
	float renderasteroid[50];   
	/******************************************************************************/
	/*!
	\brief
	float to hold a value while calculating asteroid movement  
	*/
	/******************************************************************************/
	float coord3;   
	/******************************************************************************/
	/*!
	\brief
	float to check current y position of the player   
	*/
	/******************************************************************************/
	float posycheck;   
	/******************************************************************************/
	/*!
	\brief
	double to check distance between player and all asteroids   
	*/
	/******************************************************************************/
	double between;  
	/******************************************************************************/
	/*!
	\brief
	bool to check if player has collided with an asteroid    
	\return   
	return true if player collided with an asteroid , else return false  
	*/
	/******************************************************************************/
	bool AsteroidCollision;



	//Keypad stuff (Gary's)
	bool isSafeOpen;
	float safeDoorRotation;
	Keypad keypad;
	void InitSafe();

	bool keypadBool;
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
	/******************************************************************************/
	/*!
	\brief
	Function to render skybox, and make it center around the player 
	*/
	/******************************************************************************/
	void RenderSkybox();
	void RenderTradingStation();

	/******************************************************************************/
	/*!
	\brief
	Function to render obj inside the recreational room    
	*/
	/******************************************************************************/
	void RenderRecRoom();
	void RenderCafeRoom();
	void RenderBunkRoom();
	void RenderScienceLab();
	/******************************************************************************/
	/*!
	\brief
	Function to render crystals on the map     
	*/
	/******************************************************************************/
	void RenderCrystals();
	void RenderArmouryAndShop();
	void RenderInfirmary();
	void RenderBread();
	void RenderCoffee();
	void RenderApple();
	/******************************************************************************/
	/*!
	\brief
	Function to render asteroids on the map   
	*/
	/******************************************************************************/
	void RenderAsteroids();
	void RenderWeaponsWhenSelected();
	void RenderShopLists();
	void RenderCafeInteractions();
	void RenderHandAndInventory();

	//INSTRUCTION
	void readInstructions(); //
	string file_contents2;//
	vector<string>instruct_vec;//
	void Instructions();
	void RenderInstructions();  //
	void RenderInstructionBoxOnScreen(Mesh* mesh, float size, float x, float y);


	//DIALOUGE SYSTEM
	void Dialogues();
	string file_contents;
	vector<string>dialogue_vec;
	void DialoguesWithNPCs();
	void RenderNPCDialogues();
	void RenderNPCTextBoxOnScreen(Mesh* mesh, float size, float x, float y);

	//CAFE MENU
	CafeMenu S;
	float cafeMenuPointer;
	float CoolDownTime;
	void CafeMenuPointerInteraction();
	bool DisplayCafeMenu;
	bool YesShowCafeMenu;
	bool CafeStuff;
	void RenderFood();
	void RenderCafeTextboxOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderCafePointerOnScreen(Mesh* mesh, float size, float x, float y);

	//SHOP LIST
	ShopList L;
	float shopListPointer;
	float CoolDownTime2;
	float CoolDownTime3;
	float CoolDownTime4;
	float CoolDownTime5;
	void ShopMenuPointerInteraction();
	bool DisplayShopList;
	bool YesShowShopList;
	bool DisplayShopList2;
	bool DisplayShopList3;
	bool DisplayShopList4;
	bool List2Appear;
	bool firstList;
	bool ShopStuff;
	bool secondList;
	void RenderShopTextboxOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderShopPointerOnScreen(Mesh* mesh, float size, float x, float y);

	//RENDER TEXT
	void RenderText(Mesh* mesh, std::string text, Color color);

	//RENDER ON SCREEN
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderTokenOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderCokeOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderHandOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderHandOnScreen2(Mesh* mesh, float size, float x, float y);
	/******************************************************************************/
	/*!
	\brief
	Function to render crystal in the inventory box on screen    
	*/
	/******************************************************************************/
	void RenderCrystalOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderSpacemaskOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderInventoryOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderWeaponOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderPointerOnScreen(Mesh* mesh, float size, float x, float y); //weapon pointer
	void RenderPickaxeOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderGunOnScreen(Mesh* mesh, float size, float x, float y);
	void RenderHealthBarOnScreen(Mesh* mesh, float size, float x, float y);

	// Toggle between 1st and 3rd person camera
	void shipToggle(double dt, vector<InteractableOBJs>&InteractablesList, Player &somePlayer);

	//INTERACTION FUNCTIONS
	void vendingMachineInteractions();
	void tokenInteractions();
	void counterInteractions();
	void spaceSuitInteractions();
	void doorInteractions(double dt, vector<InteractableOBJs>::iterator it, float& gateOffset, bool &gateOpening);
	void doorClosing(double dt, vector<InteractableOBJs>::iterator it, float& gateOffset, bool &gateOpening);
	void shipFlying(double dt);
	void shipAnimation(double dt, vector<Ship>::iterator i);
	void shipCreation();
	void mazeTranslate(double dt);
	void EquippingWeapons();
	bool holdgun;

	//FUNCTION TO CREATE A ROOM. initRoomTempalte TO MAKE COLLISION, RenderRoomTemplate TO RENDER ROOM
	void initRoomTemplate(Position pos, Vector3 size = { 1, 1, 1 }, float groundMeshSize = 100);
	void RenderRoomTemplate(Position pos, Vector3 size = { 1, 1, 1 }, float groundMeshSize = 100);

	/******************************************************************************/
	/*!
	\brief
	Function to reset the game      
	*/
	/******************************************************************************/
	void reset();

	//Functions to init & render Maze
	void initMaze();
	void renderMaze();

	//Functions to init & render Mountains (For Boundary)
	void initMountains();
	void renderMountains();

	// TEMP BOOLS FOR SHIP BUILDING
    /******************************************************************************/
    /*!
    \brief
        bool to check if a ship has been built
    */
    /******************************************************************************/
	bool shipBuilt;

    /******************************************************************************/
    /*!
    \brief
        bool to check if player tries to buy without enought money
    */
    /******************************************************************************/
	bool noMoney;

    /******************************************************************************/
    /*!
    \brief
        bool to check if hull obj exists in the players' partsVector
    */
    /******************************************************************************/
	bool hullFound;


    /******************************************************************************/
    /*!
    \brief
        bool to check if wings obj exists in the players' partsVector
    */
    /******************************************************************************/
	bool wingsFound;


    /******************************************************************************/
    /*!
    \brief
    bool to check if engine obj exists in the players' partsVector
    */
    /******************************************************************************/
	bool engineFound;

	//CRYSTAL RELATED STUFF   
	/******************************************************************************/
	/*!
	\brief
	Function to check position of crystals on the map    
	\param xcoord, zcoord, i 
	xcoord and zcoord take in the current position the player is looking at, while i
	is the position of the crystal coords in the array 
	\return    
	bool to return true if there is a crystal on the position the player is looking at, else false    
	*/
	/******************************************************************************/
	bool checkCrystalPos(float xcoord, float zcoord, int i);
	/******************************************************************************/
	/*!
	\brief
	Function to randomly generate crystals on the map 
	*/
	/******************************************************************************/
	void crystalgen();
	/******************************************************************************/
	/*!
	\brief
	Function to randomly generate asteroids on the map   
	*/
	/******************************************************************************/
	void asteroidgen();
	/******************************************************************************/
	/*!
	\brief
	Function to allow player to jump  
	*/
	/******************************************************************************/
	void jump();
};

#endif