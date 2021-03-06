/*************************************************************************************************/
/*!
\file   SP2.cpp
\brief
    Contains code for SP2 Project
*/
/*************************************************************************************************/
#include "SP2.h"
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
/******************************************************************************/
/*!
\brief
    SP2 Default Constructor
*/
/******************************************************************************/
SP2::SP2()
{
}

/******************************************************************************/
/*!
\brief
    SP2 Default Destructor
*/
/******************************************************************************/
SP2::~SP2()
{

}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
float FramesPerSecond = 0;

/******************************************************************************/
/*!
\brief
    SP2 Initialise
*/
/******************************************************************************/
void SP2::Init()
{
	S = CAFENOMENU;

	L = SHOPNOMENU;

	//FUNCTIONS TO CALL
	LoadShaderCodes();
	LoadLights();
	Dialogues();


	//RANDOM (MINING)
	srand(unsigned(time(0)));

	//FLOATS
	rotateAngle = 0;

	/******************************************************************************/
	/*!
	\brief
	Float to init the Y axis of the token and then translate when 
	the required button is pressed.
	*/
	/******************************************************************************/
	TokenTranslate = 11;

	/******************************************************************************/
	/*!
	\brief
	Float to init the Y axis of the text and then translate when the 
	required button is pressed.
	the required button is pressed.
	*/
	/******************************************************************************/
	TextTranslate = 20;



	leftGateOffset = 0;
	rightGateOffset = 0;
	frontGateOffset = 0;
	backGateOffset = 0;
	heightOfWall = 12;
	acceleration = -1;
	firstvelo = 0;
	secondvelo = 0;
	t = 1;
	distance = 0;
	firstpos = 0;
	translatePointer = -30;
	mazeTranslateValue = 0;
	safeDoorRotation = 0;
	cafeMenuPointer = 62;
	shopListPointer = 62;

	/******************************************************************************/
	/*!
	\brief
	Float to init the cool down timer for the cafe menu pointer.
	*/
	/******************************************************************************/
	CoolDownTime = 0;

	/******************************************************************************/
	/*!
	\brief
	Float to init the cool down timer for the shop list pointer.
	*/
	/******************************************************************************/
	CoolDownTime2 = 0;

	/******************************************************************************/
	/*!
	\brief
	Float to init the cool down timer for the shop list, Hull options pointer.
	*/
	/******************************************************************************/
	CoolDownTime3 = 0;

	/******************************************************************************/
	/*!
	\brief
	Float to init the cool down timer for the shop list, Wings options pointer.
	*/
	/******************************************************************************/
	CoolDownTime4 = 0;

	/******************************************************************************/
	/*!
	\brief
	Float to init the cool down timer for the shop list, Engine options pointer.
	*/
	/******************************************************************************/
	CoolDownTime5 = 0;

	/******************************************************************************/
	/*!
	\brief
	Float to init the rotation of the cafe food and rotate about the Y axis when
	the OBJ of the food is rendered.
	*/
	/******************************************************************************/
	SpinTheFood = -90;


	//BOOLEANS

	//Instructions booleans
	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the vending machine.
	*/
	/******************************************************************************/
	NearVendingText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the token is only rendered on screen when the player 
	pressed the required key to pick up the token..
	*/
	/******************************************************************************/
	TokenOnScreen = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the coke is only rendered on screen when the player
	pressed the required key to get the coke..
	*/
	/******************************************************************************/
	RenderCoke = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the vending machine and has not gotten any coke yet.
	*/
	/******************************************************************************/
	ConsumeCokeText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the counter.
	*/
	/******************************************************************************/
	testText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the table.
	*/
	/******************************************************************************/
	PickUpTokenText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the spacesuit.
	*/
	/******************************************************************************/
	wearSuitText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the player is required to press certain key and then
	wear the spacesuit.
	*/
	/******************************************************************************/
	wearSuit = false;


	//NPCs Dialogue booleans
	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the NPC Chef.
	*/
	/******************************************************************************/
	chefText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the NPC Spaceguy.
	*/
	/******************************************************************************/
	spaceguyText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the NPC Nurse.
	*/
	/******************************************************************************/
	nurseText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the NPC Doctor.
	*/
	/******************************************************************************/
	doctorText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the NPC Trader.
	*/
	/******************************************************************************/
	traderText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the NPC Soldier.
	*/
	/******************************************************************************/
	soldierText = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the NPC in the cafe.
	*/
	/******************************************************************************/
	NPCInCafeTokenTask = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the text is only to be shown when the player is near
	the NPC in the rec room.
	*/
	/******************************************************************************/
	NPCInRecMazeTask = false;


	//Equip weapon booleans
	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the pickaxe is only to be shown when the player pressed
	the required key to equip it.
	*/
	/******************************************************************************/
	equipPickaxe = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the gun is only to be shown when the player pressed
	the required key to equip it.
	*/
	/******************************************************************************/
	equipGun = false;

	//UI booleans
	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the hand only disappear when the boolean turn true.
	*/
	/******************************************************************************/
	HandDisappear = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the inventory only disappear when the boolean turn true.
	*/
	/******************************************************************************/
	DisplayInventory = false;
	
	//Cafe menu booleans
	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the cafe menu will only appear when the player is near.
	*/
	/******************************************************************************/
	DisplayCafeMenu = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the cafe menu will only appear when the player is near.
	*/
	/******************************************************************************/
	YesShowCafeMenu = false;

	//Cafe food booleans
	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the food will only render when the player chose 
	the option to choose an apple.
	*/
	/******************************************************************************/
	AppleAppear = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the food will only render when the player chose
	the option to choose a bread.
	*/
	/******************************************************************************/
	BreadAppear = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the food will only render when the player chose
	the option to choose a coffee.
	*/
	/******************************************************************************/
	CoffeeAppear = false;


	//Shop list booleans
	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the shop list will only render when the player press
	the required key to look at the shop list.
	*/
	/******************************************************************************/
	YesShowShopList = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the shop list will only render when the player chose
	the option to choose to look at the next list.
	*/
	/******************************************************************************/
	DisplayShopList = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the shop list will only render when the player chose
	the option to choose to look at the next list.
	*/
	/******************************************************************************/
	DisplayShopList2 = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the shop list will only render when the player chose
	the option to choose to look at the next list.
	*/
	/******************************************************************************/
	DisplayShopList3 = false;

	/******************************************************************************/
	/*!
	\brief
	Boolean init to false as the shop list will only render when the player chose
	the option to choose to look at the next list.
	*/
	/******************************************************************************/
	DisplayShopList4 = false;



	MenuBool = false;
	toggleLight = true;
	AsteroidCollision = false;
	shipBuilt = false;
	noMoney = false;
	hullFound = false;
	wingsFound = false;
	engineFound = false;
	frontGateOpening = false;
	backGateOpening = false;
	leftGateOpening = false;
	rightGateOpening = false;
	isSafeOpen = false;
	holdgun = false;

	// Assign Pointers for Ship Building
	LightHull = new Light_Hull;
	MediumHull = new Medium_Hull;
	LargeHull = new Large_Hull;
	G1Engine = new G1_Engine;
	G2Engine = new G2_Engine;
	DualWings = new Dual_Wings;
	QuadWings = new Quad_Wings;

	//Jump
	acceleration = -1;
	firstvelo = 0;
	secondvelo = 0;
	t = 1;
	distance = 0;
	firstpos = 0;
	onGround = true;
	CrystalText = false;
	isInViewSpheres = false;

	// Maze
	mazeTranslateValue = 0;
	mazeRandomTranslate = (float)((rand() % 10 + 1));
	lavaTranslation = 0;
	for (int i = 0; i < 10; ++i)
	{
		mazeRandomTranslateVec.push_back((float)((rand() % 80 - 40)));
	}
	deadText = false;
	treasureTaken = false;
	treasureText = false;

	//FIRST PERSON CAMERA
	firstPersonCamera.Reset();

	//THRID PERSON CAMERA
	thirdPersonCamera.SetMouseEnabled(true);
	thirdPersonCamera.SetCameraDistanceBounds(10, 200);
	thirdPersonCamera.SetCameraDistanceAbsolute(30);

	//INIT CAMERA POINTER
	camPointer = &firstPersonCamera;

	//STARTING POSITION OF PLAYER
	//startingCharPos = charPos = { -350, 17, 370 }; // STARTING POS OF MAZERUNNER
    startingCharPos = charPos = { 300, 17, 300 };
	//300 , 17, 300
	//125, 120 
	//250, 40
	//-350, 17, -270

	//Initialize camera settings (Don's)
	shipStartingPos = shipPos = { 375, 18, -105 };
	shipHorizontalRotateAngle = 0;
	shipVerticalRotateAngle = 0;

	//Initialize camera settings (Don's)
	firstPersonCamera.Init(Vector3(charPos.x, charPos.y, charPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
	thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), &shipPos, 20);

	//Init Player + Stats
	somePlayer.setPlayerStats("TestMan", "Human", 100, charPos, firstPersonCamera); // Name, Race, Money, Pos, camera

	LoadMeshes();

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 2000.f);
	projectionStack.LoadMatrix(projection);

	thirdPersonCamera.SetCameraDistanceBounds(10, 200);
	thirdPersonCamera.SetCameraDistanceAbsolute(30);


	firstPersonCamera.Reset();

	crystalgen();

	asteroidgen();

	InitSafe();
}

/******************************************************************************/
/*!
\brief
    SP2 Update Function
\param  dt
    Delta Time to make animations frame-dependent
*/
/******************************************************************************/
void SP2::Update(double dt)
{
	//PlaySound(TEXT("Music//space.wav"), NULL, SND_SYNC);
	//system("pause");

	//Dont touch this code 
	CrystalText = false;
	AsteroidCollision = false;
	//FPS
	FramesPerSecond = 1 / float(dt);

	//READKEYS FUNCTION
	ReadKeyPresses();

	rotateDirectionalLight(7, float(dt) * 30, { 0, 1, 0 });

	//TESTING FOR CAFE MENU
	if (!MenuBool)
	{
		if (somePlayer.getCameraType() == "first")
		{
			firstPersonCamera.Update(dt, InteractablesList, BuildingsList, somePlayer);
		}
		else
		{
			thirdPersonCamera.Update(dt, InteractablesList, BuildingsList, somePlayer);
		}
	}

	if (CoolDownTime > 0)
	{
		CoolDownTime--;
	}
	else
	{
		CoolDownTime = 0;
	}

	static unsigned firstFrames = 2;
	if (firstFrames > 0)
	{
		firstPersonCamera.Reset();
		firstFrames--;
	}
	;

	if (Application::IsKeyPressed('R'))
	{
		reset();
	}

	//INSTRUCTIONS
	readInstructions();

	//DIALOGUE DO NOT DELETE THIS 
	DialoguesWithNPCs();

	//DO NOT DELETE EQUIP WEAPON STUFF
	EquippingWeapons();

	//CAFE MENU
	CafeMenuPointerInteraction();

	if (Application::IsKeyPressed('U'))
	{
		AppleAppear = false;
		CoffeeAppear = false;
		BreadAppear = false;
	}

	//SHOP LIST
	ShopMenuPointerInteraction();


	//Safe + keypad stuff (Gary's)
	if (isSafeOpen)
	{
		safeDoorRotation += float(dt) * 60;
		safeDoorRotation = min(safeDoorRotation, 115);
	}


	//INTERACTIONS WITH OBJS (SHANIA'S)  IT WORKS
	Vector3 view = (firstPersonCamera.target - firstPersonCamera.position).Normalized();

	for (vector<InteractableOBJs>::iterator it = InteractablesList.begin(); it != InteractablesList.end(); ++it)
	{
		if (it->name != "asteroid" || it->name != "crystal")
		{
			//VENDING MACHINE
			if (it->name == "vending")
			{
				if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
				{
					NearVendingText = true;
					if (Application::IsKeyPressed('Q') && (TokenOnScreen == true))
					{
						TextTranslate = 100;
						TokenOnScreen = false;
						RenderCoke = true;
						ConsumeCokeText = true;
					}

					if (Application::IsKeyPressed('U'))
					{
						ConsumeCokeText = false;
						RenderCoke = false;
					}
				}
				else
				{
					NearVendingText = false;
					ConsumeCokeText = false;
					RenderCoke = false;
				}
			}


			//TOKEN
			if (it->name == "token")
			{
				if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
				{
					PickUpTokenText = true;

					if (Application::IsKeyPressed('Q'))
					{
						TokenOnScreen = true;
						TokenTranslate = 10.5;
					}
				}
				else
				{
					PickUpTokenText = false;
				}
			}

			//COUNTER
			if (it->name == "counter")
			{
				if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
				{
					testText = true;
					if (Application::IsKeyPressed('Y'))
					{
						testText = false;
						chefText = false;
						YesShowCafeMenu = true;
						S = OPTION_APPLE;
					}

					if (YesShowCafeMenu == true)
					{
						testText = false;
						chefText = false;
						DisplayCafeMenu = true;
					}
					else
					{
						testText = true;
						chefText = true;
						DisplayCafeMenu = false;
						S = CAFENOMENU;
					}
				}
				else
				{
					testText = false;
					DisplayCafeMenu = false;
					YesShowCafeMenu = false;
					S = CAFENOMENU;
				}
			}

			//SPACESUIT
			if (it->name == "spacesuit")
			{
				if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
				{
					wearSuitText = true;

					if (Application::IsKeyPressed('T'))
					{
						wearSuit = true;
						DisplayInventory = true;
						HandDisappear = true;
					}

					if (Application::IsKeyPressed('G'))
					{
						wearSuit = false;
						DisplayInventory = false;
					}
				}
				else
				{
					wearSuitText = false;

					if (Application::IsKeyPressed('G'))
					{
						wearSuit = false;
						DisplayInventory = false;
					}
				}
			}

			//SHOP LIST
			if (it->name == "trader")
			{
				if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
				{
					traderText = true;
					if (Application::IsKeyPressed('Y'))
					{
						traderText = false;
						YesShowShopList = true;
						L = OPTION_HULL;
					}

					if (YesShowShopList == true)
					{
						traderText = false;
						DisplayShopList = true;
					}
					else
					{
						traderText = true;
						DisplayShopList = false;
						//L = SHOPNOMENU;
					}


					if (DisplayShopList == true || DisplayShopList2 == true || DisplayShopList3 == true || DisplayShopList4 == true)
					{
						traderText = false;
					}
					else
					{
						traderText = true;
					}
				}
				else
				{
					traderText = false;
					DisplayShopList = false;
					YesShowShopList = false;
					//L = SHOPNOMENU;
					//DisplayShopList2 = false;
					//DisplayShopList3 = false
				}
			}







			// Door Opening & Closing
			if (it->name.find("frontGate") != string::npos)
			{
				if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view)) //IF FRONTGATE IS IN VIEW
				{
					if (Application::IsKeyPressed('E'))
					{
						frontGateOpening = true;
					}
					if (frontGateOpening) { doorInteractions(dt, it, frontGateOffset, frontGateOpening); }
					if (!frontGateOpening) { doorClosing(dt, it, frontGateOffset, frontGateOpening); }
				}
			}

			if (it->name.find("rightGate") != string::npos)
			{
				if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view)) //IF rightGATE IS IN VIEW
				{
					if (Application::IsKeyPressed('E'))
					{
						rightGateOpening = true;
					}
					if (rightGateOpening) { doorInteractions(dt, it, rightGateOffset, rightGateOpening); }
					if (!rightGateOpening) { doorClosing(dt, it, rightGateOffset, rightGateOpening); }
				}
			}

			if (it->name.find("backGate") != string::npos)
			{
				if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view)) //IF backGATE IS IN VIEW
				{
					if (Application::IsKeyPressed('E'))
					{
						backGateOpening = true;
					}
					if (backGateOpening) { doorInteractions(dt, it, backGateOffset, backGateOpening); }
					if (!backGateOpening) { doorClosing(dt, it, backGateOffset, backGateOpening); }
				}
			}

			if (it->name.find("leftGate") != string::npos)
			{
				if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view)) //IF leftGATE IS IN VIEW
				{
					if (Application::IsKeyPressed('E'))
					{
						leftGateOpening = true;
					}
					if (leftGateOpening) { doorInteractions(dt, it, leftGateOffset, leftGateOpening); }
					if (!leftGateOpening) { doorClosing(dt, it, leftGateOffset, leftGateOpening); }
				}
			}

			// Weapon
			if (it->name == "gun rack")
			{
				if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view))
				{
					if (Application::IsKeyPressed('E') && CoolDownTime == 0)
					{
						somePlayer.setWeapon();
						CoolDownTime = 20;
					}
				}

			}

			// Target
			if (it->name == "target dummy")
			{
				if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view))
				{
					if (Application::IsKeyPressed(VK_LBUTTON) &&  (holdgun == true))
					{
						somePlayer.addCrystals(1);
					}
				}
			}

			static bool isHeld = false;

			if (Application::IsKeyPressed('H'))
			{
				if (it->isInView({ firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z }, view))
				{
					if (it->name == "keypadButton1")
					{
						keypad.targetBool.setTargetValue(true);
					}
				}
			}

			// Treasure
			if (it->name == "mazeTreasure")
			{
				if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view))
				{
					treasureText = true;
					if (Application::IsKeyPressed('E') && !treasureTaken)
					{
						treasureTaken = true;
						somePlayer.addCrystals(9001);
					}
				}
				else
				{
					treasureText = false;
				}
			}
		}
	}


	//INTERACTIONS WITH OBJS (BECKHAM'S & DONOVAN'S)
	if (camPointer == &firstPersonCamera)
	{
		Vector3 viewDirection = (firstPersonCamera.target - firstPersonCamera.position).Normalized();
		for (vector<InteractableOBJs>::iterator i = InteractablesList.begin(); i < InteractablesList.end(); i++)
		{
			if (i->name == "crystal")
			{
				if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view))
				{
					CrystalText = true;
					posxcheck = i->pos.x;
					poszcheck = i->pos.z;
					if (Application::IsKeyPressed('E') && equipPickaxe)
					{
						for (int a = 0; a < CrystalNo; a++)
						{
							if (checkCrystalPos(posxcheck, poszcheck, a))
							{

								rendercrystal[a] = 0;
								crystalcount += rand() % 10 + 1;

								somePlayer.addCrystals(rand() % 10 + 1);

								i = this->InteractablesList.erase(i);
								i = InteractablesList.begin();
							}
						}
					}
				}
			}
		}
	}

	//JUMP     

	if (Application::IsKeyPressed(VK_SPACE) && onGround) //s = ut + 0.5 at^2
	{
		firstpos = firstPersonCamera.position.y;
		firstvelo = 35;
		onGround = false;
	}
	if (onGround == false)
	{
		secondvelo = firstvelo + (acceleration * t * t); // a = -2 , t = 1 
		firstvelo = secondvelo;

		distance = ((firstvelo * t) + (0.3f * acceleration * t * t));
		firstPersonCamera.position.y += distance * float(dt);
		firstPersonCamera.target.y += distance * float(dt);

		somePlayer.pos.y += distance * float(dt);
	}

	if (firstpos >= firstPersonCamera.position.y)
	{
		firstPersonCamera.position.y = firstpos;
		onGround = true;
	}

	//ASTEROID MOVEMENT    
	for (int i = 0; i < AsteroidNo; i++)
	{
		asteroidx[i] += movex[i] + 0.05f * float(dt);
		asteroidz[i] += movez[i] + 0.5f * float(dt);
		rotatex[i] += (movex[i] ) + 1 * float(dt);
		rotatez[i] += (movez[i] ) + 1 * float(dt);
		if (asteroidx[i] > 1000 || asteroidx[i] < -1000)
		{
			asteroidx[i] *= -1;
		}
		if (asteroidz[i] > 1000 || asteroidz[i] < -1000)
		{
			asteroidz[i] *= -1;
		}
	}
	for (int i = 0; i < AsteroidNo; i++)
	{
		posxcheck = asteroidx[i];
		poszcheck = asteroidz[i];
		posycheck = asteroidy[i];
		posxcheck = (posxcheck - somePlayer.pos.x) * (posxcheck - somePlayer.pos.x);
		posycheck = (posycheck - somePlayer.pos.y) * (posycheck - somePlayer.pos.y);
		poszcheck = (poszcheck - somePlayer.pos.z) * (poszcheck - somePlayer.pos.z);
		between = posxcheck + posycheck + poszcheck;
		between = sqrt(between);
		if (between <= 30)
		{
			reset();
		}
	}

	//Entering / Exiting Ship
	shipToggle(dt, InteractablesList, somePlayer);

	// Ship Flying + Animation
	shipFlying(dt);

	// Maze Movement
	mazeTranslate(dt);

	SpinTheFood += 70 * float(dt);
}

/******************************************************************************/
/*!
\brief
Function for switching the position of the shop's pointer and then change the render on screen obj.
*/
/******************************************************************************/
void SP2::ShopMenuPointerInteraction()
{
	//EXIT THE LIST
	if (Application::IsKeyPressed('B') && CoolDownTime2 == 1)
	{
		DisplayShopList = false;
		DisplayShopList2 = false;
		DisplayShopList3 = false;
		DisplayShopList4 = false;
	}



	if (CoolDownTime2 > 1)
	{
		CoolDownTime2--;
	}
	else
	{
		CoolDownTime2 = 1;
	}

	//FIRST LIST
	switch (L)
	{
	case OPTION_HULL:   //HULL                                           //Position 1 HULL
		shopListPointer = 62;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime2 == 1)    //press up to position 3
		{
			CoolDownTime2 = 15;
			L = OPTION_CREATESHIP;
		}
		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime2 == 1)   //press down to position 2
		{
			CoolDownTime2 = 15;
			L = OPTION_WINGS;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)        //press Enter will close the list
		{
			CoolDownTime2 = 15;
			YesShowShopList = false;
			DisplayShopList = false;
			DisplayShopList2 = true;                                    //SHOW NEW HULL LIST
			L = OPTION_LIGHTHULL;
		}


		break;

	case OPTION_WINGS:     //WINGS                                        //Position 2  WINGS
		shopListPointer = 50;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime2 == 1)    //press up to position 1
		{
			CoolDownTime2 = 15;
			L = OPTION_HULL;
		}

		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime2 == 1)   //press down to position 3
		{
			CoolDownTime2 = 15;
			L = OPTION_ENGINE;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)                       //press Enter will close the list
		{
			CoolDownTime2 = 15;
			YesShowShopList = false;
			DisplayShopList = false;
			DisplayShopList3 = true;                                    //SHOW NEW WINGS LIST
			L = OPTION_DUALWINGS;
		}

		break;

	case OPTION_ENGINE:           //ENGINE                                 //Position 3  ENGINE
		shopListPointer = 38;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime2 == 1)    //press up to Position 2
		{
			CoolDownTime2 = 15;
			L = OPTION_WINGS;
		}
		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime2 == 1)   //press down to Position 1
		{
			CoolDownTime2 = 15;
			L = OPTION_CREATESHIP;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)                       //press Enter will close the list
		{
			CoolDownTime2 = 15;
			YesShowShopList = false;
			DisplayShopList = false;
			DisplayShopList4 = true;
			L = OPTION_G1ENGINE;
		}
		break;

	case OPTION_CREATESHIP:                                                                    //Create ship
		shopListPointer = 26;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime2 == 1)
		{
			CoolDownTime2 = 15;
			L = OPTION_ENGINE;
		}

		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime2 == 1)
		{
			CoolDownTime2 = 15;
			L = OPTION_HULL;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)                       //press Enter will close the list
		{
			CoolDownTime2 = 15;
			YesShowShopList = false;
			DisplayShopList = false;

			if (somePlayer.getParts().size() >= 3)
			{
				shipCreation();
				shipBuilt = true;
			}

		}

		break;

	}

	if (CoolDownTime3 > 2)
	{
		CoolDownTime3--;
	}
	else
	{
		CoolDownTime3 = 2;
	}


	//SECOND LIST
	switch (L)
	{
	case OPTION_LIGHTHULL:                                                                //SMALL HULL
		shopListPointer = 62;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime3 == 2)
		{
			CoolDownTime3 = 16;
			L = OPTION_LARGEHULL;
		}

		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime3 == 2)
		{
			CoolDownTime3 = 16;
			L = OPTION_MEDIUMHULL;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)
		{
			L = SHOPNOMENU;
			CoolDownTime2 = 16;
			DisplayShopList2 = false;


			//REMOVE CYRSTAL
			if (somePlayer.getCrystals() >= 10)
			{
				somePlayer.removeCrystals(10);
				somePlayer.addPart(LightHull);
			}
			else { noMoney = true; }

		}
		break;

	case OPTION_MEDIUMHULL:                                                          //MEDIUM HULL
		shopListPointer = 50;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime3 == 2)
		{
			CoolDownTime3 = 16;
			L = OPTION_LIGHTHULL;
		}

		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime3 == 2)
		{
			CoolDownTime3 = 16;
			L = OPTION_LARGEHULL;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)
		{
			L = SHOPNOMENU;
			CoolDownTime2 = 16;
			DisplayShopList2 = false;


			//REMOVE CRYSTAL
			if (somePlayer.getCrystals() >= 20)
			{
				somePlayer.removeCrystals(20);
				somePlayer.addPart(MediumHull);
			}
			else { noMoney = true; }
		}
		break;


	case OPTION_LARGEHULL:                                                             //LARGE HULL
		shopListPointer = 38;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime3 == 2)
		{
			CoolDownTime3 = 16;
			L = OPTION_MEDIUMHULL;
		}

		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime3 == 2)
		{
			CoolDownTime3 = 16;
			L = OPTION_LIGHTHULL;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)
		{
			L = SHOPNOMENU;
			CoolDownTime2 = 16;
			DisplayShopList2 = false;


			//REMOVE CRYSTAL
			if (somePlayer.getCrystals() >= 30)
			{
				somePlayer.removeCrystals(30);
				somePlayer.addPart(LargeHull);
			}
			else { noMoney = true; }

		}
		break;
	}





	if (CoolDownTime4 > 3)
	{
		CoolDownTime4--;
	}
	else
	{
		CoolDownTime4 = 3;
	}
	//THIRD LIST
	switch (L)
	{
	case OPTION_DUALWINGS:                                                         //DUAL WINGS
		shopListPointer = 62;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime4 == 3)
		{
			CoolDownTime4 = 17;
			L = OPTION_QUADWINGS;
		}

		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime4 == 3)
		{
			CoolDownTime4 = 17;
			L = OPTION_QUADWINGS;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)
		{
			L = SHOPNOMENU;
			CoolDownTime2 = 16;
			DisplayShopList3 = false;


			//REMOVE CRYSTAL
			if (somePlayer.getCrystals() >= 20)
			{
				somePlayer.removeCrystals(20);
				somePlayer.addPart(DualWings);
			}
			else { noMoney = true; }
		}

		break;

	case OPTION_QUADWINGS:                                                                 //QUAD WINGS
		shopListPointer = 50;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime4 == 3)
		{
			CoolDownTime4 = 17;
			L = OPTION_DUALWINGS;
		}

		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime4 == 3)
		{
			CoolDownTime4 = 17;
			L = OPTION_DUALWINGS;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)
		{
			L = SHOPNOMENU;
			CoolDownTime2 = 16;
			DisplayShopList3 = false;


			//REMOVE CRYSTAL
			if (somePlayer.getCrystals() >= 30)
			{
				somePlayer.removeCrystals(30);
				somePlayer.addPart(QuadWings);
			}
			else { noMoney = true; }
		}

		break;
	}





	if (CoolDownTime5 > 4)
	{
		CoolDownTime5--;
	}
	else
	{
		CoolDownTime5 = 4;
	}
	//FOURTH LIST
	switch (L)
	{
	case OPTION_G1ENGINE:                                                                     //G1 ENGINE
		shopListPointer = 62;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime5 == 4)
		{
			CoolDownTime5 = 18;
			L = OPTION_G2ENGINE;
		}

		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime5 == 4)
		{
			CoolDownTime5 = 18;
			L = OPTION_G2ENGINE;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)
		{
			L = SHOPNOMENU;
			CoolDownTime2 = 16;
			DisplayShopList4 = false;


			//REMOVE CRYSTAL
			if (somePlayer.getCrystals() >= 20)
			{
				somePlayer.removeCrystals(20);
				somePlayer.addPart(G1Engine);
			}
			else { noMoney = true; }
		}

		break;

	case OPTION_G2ENGINE:
		shopListPointer = 50;                                                         //G2 ENGINE
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime5 == 4)
		{
			CoolDownTime5 = 18;
			L = OPTION_G1ENGINE;
		}

		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime5 == 4)
		{
			CoolDownTime5 = 18;
			L = OPTION_G1ENGINE;
		}

		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime2 == 1)
		{
			L = SHOPNOMENU;
			CoolDownTime2 = 16;
			DisplayShopList4 = false;


			//REMOVE CRYSTAL
			if (somePlayer.getCrystals() >= 30)
			{
				somePlayer.removeCrystals(30);
				somePlayer.addPart(G2Engine);
			}
			else { noMoney = true; }
		}

		break;
	}

}

/******************************************************************************/
/*!
\brief
Function for switching the position of the cafe's pointer and then render the ojb of the chosen option.
*/
/******************************************************************************/
void SP2::CafeMenuPointerInteraction()
{
	if (CoolDownTime > 0)
	{
		CoolDownTime--;
	}
	else
	{
		CoolDownTime = 0;
	}
	// Moved to Update - Don
	//if (CoolDownTime > 0)
	//{
	//	CoolDownTime--;
	//}
	//else
	//{
	//	CoolDownTime == 0;
	//}

	switch (S)
	{
	case OPTION_APPLE:
		cafeMenuPointer = 62;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = PLACE3;
		}
		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = OPTION_COFFEE;
		}
		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			AppleAppear = true;
		}
		break;
	case OPTION_COFFEE:
		cafeMenuPointer = 50;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = OPTION_APPLE;
		}
		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = PLACE3;
		}
		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			CoffeeAppear = true;
		}
		break;
	case PLACE3:
		cafeMenuPointer = 38;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = OPTION_COFFEE;
		}
		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = OPTION_APPLE;
		}
		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			BreadAppear = true;
		}
		break;
	}

	if (Application::IsKeyPressed(VK_RETURN))
	{
		YesShowCafeMenu = false;
		DisplayCafeMenu = false;
	}
}

/******************************************************************************/
/*!
\brief
Function to lock the weapon when equipped. Cannot equip two weapon at one time.
*/
/******************************************************************************/
void SP2::EquippingWeapons()
{
	//EQUIP GUN, HAND DISAPPEAR
	if (Application::IsKeyPressed(VK_F1))
	{
		if (somePlayer.checkWeapon())
		{
			holdgun = true;
			equipGun = true;
			translatePointer = 127;
			HandDisappear = true;
		}
	}

	//EQUIP PICKAXE , HAND DISAPPEAR
	if (Application::IsKeyPressed(VK_F2))
	{
		equipPickaxe = true;
		translatePointer = 141;
		HandDisappear = true;
		holdgun = false;
	}

	//F3 TO MAKE INVENTORY AND HAND APPEAR
	if (Application::IsKeyPressed(VK_F3) && (wearSuit == false))
	{
		holdgun = false;
		equipGun = false;
		equipPickaxe = false;
		translatePointer = -10;
		HandDisappear = false;
	}

	if (equipGun == true)
	{
		equipPickaxe = false;
		translatePointer = 127;
	}

	if (equipPickaxe == true)
	{
		equipGun = false;
		translatePointer = 141;
	}
}

/******************************************************************************/
/*!
\brief
    Function for moving the player while flying the spaceship
\param  dt
    delta time, used to make animations frame-dependent
*/
/******************************************************************************/
void SP2::shipFlying(double dt)
{
	for (vector<Ship>::iterator i = ShipList.begin(); i != ShipList.end(); ++i)
	{
		if (camPointer == &thirdPersonCamera)
		{
			Vector3 view = (camPointer->target - camPointer->position).Normalized();
			Vector3 up = camPointer->up;
			Vector3 right = view.Cross(up);

			// Sets Ships direction to be the same as the camera
			if (!i->shipTakeoff)
			{
				i->setDirectionalVectors(view.Normalized());
			}

			if (Application::IsKeyPressed(VK_SPACE) && i->shipTakeoff == false) { i->shipTakeoff = true; } /// Press 'SpaceBar' to take off

			if (i->shipTakeoff)
			{
				// Set ship's new direction
				i->setDirectionalVectors((i->shipDirection + view).Normalized());

				// Check Bounds
				Position camPos;

				camPos.x = shipPos.x + i->shipDirection.x + (float)(i->shipSpeed * dt);
				camPos.y = shipPos.y + i->shipDirection.y + (float)(i->shipSpeed * dt);
				camPos.z = shipPos.z + i->shipDirection.z + (float)(i->shipSpeed * dt);

				// Move Ship's position (For Translation)
				if (thirdPersonCamera.createBoundary(InteractablesList, BuildingsList, somePlayer, camPos))
				{
					shipPos.x = shipPos.x + i->shipDirection.x + (float)(i->shipSpeed * dt);
					shipPos.y = shipPos.y + i->shipDirection.y + (float)(i->shipSpeed * dt);
					shipPos.z = shipPos.z + i->shipDirection.z + (float)(i->shipSpeed * dt);
				}
				else
				{
					shipPos.x = shipPos.x - (i->shipDirection.x + (float)(i->shipSpeed * dt));
					shipPos.y = shipPos.y - (i->shipDirection.y + (float)(i->shipSpeed * dt));
					shipPos.z = shipPos.z - (i->shipDirection.z + (float)(i->shipSpeed * dt));
					//reset();
				}

				// Check to stop Ship from going into the ground
				if (shipPos.y <= 2)
				{
					shipPos.y = shipPos.y - (i->shipDirection.y + (float)(i->shipSpeed * dt));
					i->pos.y = i->pos.y - (i->shipDirection.y + (float)(i->shipSpeed * dt));
					somePlayer.pos.y = somePlayer.pos.y - (i->shipDirection.y + (float)(i->shipSpeed * dt));
				}

				// Make Positions the same
				i->pos = somePlayer.pos = shipPos;

				if (Application::IsKeyPressed('W')) // Increase Speed
				{
					if (i->shipSpeed <= i->shipMaxSpeed)
					{
						i->shipSpeed += (float)(i->shipSpeedGain * dt);
					}
				}

				if (Application::IsKeyPressed('S')) // Decrease Speed
				{
					if (i->shipSpeed >= i->shipLandingSpeed)
					{
						i->shipSpeed -= (float)(i->shipSpeedGain * dt);
					}
				}
			}


			// Ship Animation - Don't Touch - Donovan
			shipAnimation(dt, i);

		}
	}
}

/******************************************************************************/
/*!
\brief
    Function for rotating the ship while player is flying the ship
\param  dt
    delta time, used to make animations frame-dependent
\param  i
    vector<Ship> iterator used to access ship class' variables
*/
/******************************************************************************/
void SP2::shipAnimation(double dt, vector<Ship>::iterator i)
{
	// Ship Animation
	Vector3 view = (camPointer->target - camPointer->position).Normalized();
	Vector3 up = camPointer->up;
	Vector3 right = view.Cross(up);

	Vector3 defaultHorizontalPlane = { -i->defaultShipDirection.x, 0, -i->defaultShipDirection.z };
	Vector3 horizontalPlane = { i->shipDirection.x, 0, i->shipDirection.z };

	// Find angle to pitch
	float pitchAngleDiff = Math::RadianToDegree(acos(thirdPersonCamera.defaultUpVec.Dot(up)) / (thirdPersonCamera.defaultUpVec.Length() * up.Length()));

	// Find angle to yaw
	float yawAngleDiff = Math::RadianToDegree(acos(defaultHorizontalPlane.Dot(horizontalPlane) / defaultHorizontalPlane.Length() * horizontalPlane.Length()));

	// Check which direction ship is turning in and rotate ship
	if (thirdPersonCamera.yawingLeft && shipHorizontalRotateAngle <= yawAngleDiff && shipHorizontalRotateAngle <= 180)
	{
		shipHorizontalRotateAngle += (float)(i->turningSpeed * dt);
	}
	else if (thirdPersonCamera.yawingLeft && shipHorizontalRotateAngle <= 360 - yawAngleDiff && shipHorizontalRotateAngle > 180)
	{
		shipHorizontalRotateAngle += (float)(i->turningSpeed * dt);
	}
	//else if (shipHorizontalRotateAngle >= yawAngleDiff)
	//{
	//    shipHorizontalRotateAngle -= (float)(i->turningSpeed * dt);
	//}

	if (thirdPersonCamera.yawingRight && shipHorizontalRotateAngle >= -yawAngleDiff && shipHorizontalRotateAngle >= -180)
	{
		shipHorizontalRotateAngle -= (float)(i->turningSpeed * dt);
	}
	else if (thirdPersonCamera.yawingLeft && shipHorizontalRotateAngle >= -(360 + -yawAngleDiff) && shipHorizontalRotateAngle < -180)
	{
		shipHorizontalRotateAngle -= (float)(i->turningSpeed * dt);
	}
	//else if (shipHorizontalRotateAngle <= -yawAngleDiff)
	//{
	//    shipHorizontalRotateAngle += (float)(i->turningSpeed * dt);
	//}

	//cout << "yawAngleDiff: " << yawAngleDiff << " shipHorizontalRotateAngle: " << shipHorizontalRotateAngle << endl;

	if (thirdPersonCamera.pitchingDown && shipVerticalRotateAngle <= pitchAngleDiff)
	{
		shipVerticalRotateAngle += (float)(i->turningSpeed * dt);
	}

	if (thirdPersonCamera.pitchingUp && shipVerticalRotateAngle >= -pitchAngleDiff)
	{
		shipVerticalRotateAngle -= (float)(i->turningSpeed * dt);
	}

	if (shipVerticalRotateAngle >= 360) { shipVerticalRotateAngle = 0; }
	if (shipHorizontalRotateAngle >= 360 || shipHorizontalRotateAngle <= -360) { shipHorizontalRotateAngle = 0; }
}


/******************************************************************************/
/*!
\brief
    Function for moving lava pools in the maze
\param  dt
    delta time, used to make animations frame-dependent
*/
/******************************************************************************/
void SP2::mazeTranslate(double dt)
{
	// Lava Movement
	if (lavaTranslation <= 140)
	{
		lavaTranslation += (float)(10 * dt);
		if (lavaTranslation >= 140)
		{
			lavaTranslation = 0;
		}
	}

	for (vector<InteractableOBJs>::iterator it = InteractablesList.begin(); it != InteractablesList.end(); ++it)
	{
		if (it->name == "lava")
		{
			if ((somePlayer.pos.z <= 350 && somePlayer.pos.z >= -350) && (somePlayer.pos.y <= 17))
			{
				if ((somePlayer.pos.x <= -420 + lavaTranslation + 5 && somePlayer.pos.x >= -420 + lavaTranslation - 5) || ((somePlayer.pos.x <= -280 - lavaTranslation + 5 && somePlayer.pos.x >= -280 - lavaTranslation - 5)))
				{
					deadText = true;
					reset();
				}
				else
				{
					deadText = false;
				}
			}
		}
	}
}


/******************************************************************************/
/*!
\brief
    Function for opening the doors
\param  dt
    delta time, used to make animations frame-dependent
\param  it
    vector<InteractableOBJs> iterator used to access InteractablesList (vector)
\param  gateOffset
    amount to move the door by
\param gateOpening
    bool to check if door is opening (true) or not (false)
*/
/******************************************************************************/
void SP2::doorInteractions(double dt, vector<InteractableOBJs>::iterator it, float& gateOffset, bool &gateOpening)
{
	if (gateOffset < 30)
	{
		gateOffset += (float)(40 * dt);
	}

	if (it->pos.y < 30)
	{
		it->pos.y += (float)(40 * dt);
	}

	if (gateOffset >= 30 && it->pos.y >= 30)
	{
		gateOpening = false;
	}
}

/******************************************************************************/
/*!
\brief
    Function for closing the doors
\param  dt
    delta time, used to make animations frame-dependent
\param  it
    vector<InteractableOBJs> iterator used to access InteractablesList (vector)
\param  gateOffset
    amount to move the door by
\param gateOpening
    bool to check if door is opening (true) or not (false)
*/
/******************************************************************************/
void SP2::doorClosing(double dt, vector<InteractableOBJs>::iterator it, float& gateOffset, bool &gateOpening)
{
	if (gateOffset > 0)
	{
		gateOffset -= (float)(60 * dt);
	}

	if (it->pos.y > 17)
	{
		it->pos.y -= (float)(60 * dt);
	}
}

/******************************************************************************/
/*!
\brief
    Function for shipCreation, loads meshes and creates a ship
*/
/******************************************************************************/
void SP2::shipCreation()
{
	// Space Ship Template
	//WHY SHOULD YOU LOAD A MESH IN THE MIDDLE OF THE PROGRAM? WHO WAS DOING IT? (comment by Gary Goh)
	//meshList[GEO_SHIP] = MeshBuilder::GenerateOBJ("ship", "OBJ//V_Art Spaceship.obj");

	Vector3 view = (thirdPersonCamera.target - thirdPersonCamera.position).Normalized();
	Vector3 up = thirdPersonCamera.up;
	Vector3 right = view.Cross(up);

	Ship someShip = Ship("ship", meshList[GEO_SHIP]->maxPos, meshList[GEO_SHIP]->minPos, shipStartingPos, 4, 0, Vector3(0, 0, 0), view);

	someShip.setRequirements(50, 500);

	shipTemplatePtr = &someShip;

	ShipList.push_back(ShipBuilder.createShip(shipTemplatePtr, somePlayer.getParts()));

	for (vector<Ship>::iterator i = ShipList.begin(); i < ShipList.end(); ++i)
	{
		i->setDirectionalVectors(view, right);
	}

	// Load Meshes for specific ship parts
	for (vector<Ship>::iterator i = ShipList.begin(); i < ShipList.end(); ++i)
	{
		// Load Meshes for Light Ship
		if (i->hullType == "LightHull")
		{
			meshList[GEO_HULL] = MeshBuilder::GenerateOBJ("shipHull", "OBJ//Ship Models//LightHull.obj");

			if (i->wingType == "DualWings")
			{
				meshList[GEO_WINGS] = MeshBuilder::GenerateOBJ("shipWings", "OBJ//Ship Models//Light_DualWings.obj");
			}
			else if (i->wingType == "QuadWings")
			{
				meshList[GEO_WINGS] = MeshBuilder::GenerateOBJ("shipWings", "OBJ//Ship Models//Light_QuadWings.obj");
			}

			if (i->engineType == "G1Engine")
			{
				meshList[GEO_ENGINE] = MeshBuilder::GenerateOBJ("shipEngine", "OBJ//Ship Models//Light_G1Engine.obj");
			}
			else if (i->engineType == "G2Engine")
			{
				meshList[GEO_ENGINE] = MeshBuilder::GenerateOBJ("shipEngine", "OBJ//Ship Models//Light_G2Engine.obj");
			}

			meshList[GEO_HULL]->textureID = LoadTGA("Image//Ship//lightShip.tga");
			meshList[GEO_WINGS]->textureID = LoadTGA("Image//Ship//lightShip.tga");
			meshList[GEO_ENGINE]->textureID = LoadTGA("Image//Ship//lightShip.tga");
			thirdPersonCamera.SetCameraDistanceAbsolute(100);
		}

		// Load Meshes for Medium Hull
		else if (i->hullType == "MediumHull")
		{
			meshList[GEO_HULL] = MeshBuilder::GenerateOBJ("shipHull", "OBJ//Ship Models//MediumHull.obj");

			if (i->wingType == "DualWings")
			{
				meshList[GEO_WINGS] = MeshBuilder::GenerateOBJ("shipWings", "OBJ//Ship Models//Medium_DualWings.obj");
			}
			else if (i->wingType == "QuadWings")
			{
				meshList[GEO_WINGS] = MeshBuilder::GenerateOBJ("shipWings", "OBJ//Ship Models//Medium_QuadWings.obj");
			}

			if (i->engineType == "G1Engine")
			{
				meshList[GEO_ENGINE] = MeshBuilder::GenerateOBJ("shipEngine", "OBJ//Ship Models//Medium_G1Engine.obj");
			}
			else if (i->engineType == "G2Engine")
			{
				meshList[GEO_ENGINE] = MeshBuilder::GenerateOBJ("shipEngine", "OBJ//Ship Models//Medium_G2Engine.obj");
			}

			meshList[GEO_HULL]->textureID = LoadTGA("Image//Ship//mediumShip.tga");
			meshList[GEO_WINGS]->textureID = LoadTGA("Image//Ship//mediumShip.tga");
			meshList[GEO_ENGINE]->textureID = LoadTGA("Image//Ship//mediumShip.tga");
			thirdPersonCamera.SetCameraDistanceAbsolute(100);
		}

		// Load Meshes for Heavy Hull
		else if (i->hullType == "LargeHull")
		{
			meshList[GEO_HULL] = MeshBuilder::GenerateOBJ("shipHull", "OBJ//Ship Models//LargeHull.obj");

			if (i->wingType == "DualWings")
			{
				meshList[GEO_WINGS] = MeshBuilder::GenerateOBJ("shipWings", "OBJ//Ship Models//Large_DualWings.obj");
			}
			else if (i->wingType == "QuadWings")
			{
				meshList[GEO_WINGS] = MeshBuilder::GenerateOBJ("shipWings", "OBJ//Ship Models//Large_QuadWings.obj");
			}

			if (i->engineType == "G1Engine")
			{
				meshList[GEO_ENGINE] = MeshBuilder::GenerateOBJ("shipEngine", "OBJ//Ship Models//Large_G1Engine.obj");
			}
			else if (i->engineType == "G2Engine")
			{
				meshList[GEO_ENGINE] = MeshBuilder::GenerateOBJ("shipEngine", "OBJ//Ship Models//Large_G2Engine.obj");
			}

			meshList[GEO_HULL]->textureID = LoadTGA("Image//Ship//largeShip.tga");
			meshList[GEO_WINGS]->textureID = LoadTGA("Image//Ship//largeShip.tga");
			meshList[GEO_ENGINE]->textureID = LoadTGA("Image//Ship//largeShip.tga");
			thirdPersonCamera.SetCameraDistanceAbsolute(100);
		}
	}
}

/******************************************************************************/
/*!
\brief
    Function for ging in and out of the ship
\param  dt
    delta time, used to make animations frame-dependent
\param  InteractablesList
    vector<InteractableOBJs> InteractablesList used to access InteractablesList (vector)
\param  somePlayer
    object of player class, used to access player's pos etc.
*/
/******************************************************************************/
void SP2::shipToggle(double dt, vector<InteractableOBJs>&InteractablesList, Player &somePlayer)
{
	Vector3 view = (firstPersonCamera.target - firstPersonCamera.position).Normalized();
	for (vector<Ship>::iterator shipIt = ShipList.begin(); shipIt < ShipList.end(); ++shipIt)
	{
		// Getting into Ship
		if (shipIt->isInView(somePlayer.pos, view))
		{
			if (somePlayer.getCameraType() == "first")
			{
				if (Application::IsKeyPressed('F') && CoolDownTime == 0)
				{
					camPointer = &thirdPersonCamera;
					somePlayer.setCameraType("third");
					CoolDownTime = 20;
					DisplayInventory = true;
					HandDisappear = true;
				}
			}
		}

		// Getting out of ship
		if (somePlayer.getCameraType() == "third")
		{
			if (Application::IsKeyPressed('F') && CoolDownTime == 0)
			{
				if (somePlayer.pos.y <= 30 && shipIt->shipSpeed <= shipIt->shipLandingSpeed)
				{
					camPointer = &firstPersonCamera;
					somePlayer.setCameraType("first");

					// Sets player's position to original y - axis
					somePlayer.pos.y = charPos.y;

					// Sets 1st person camera new position to the player's position
					camPointer->position.x = somePlayer.pos.x;
					camPointer->position.y = somePlayer.pos.y;
					camPointer->position.z = somePlayer.pos.z;

					// Set Ship To 'Straight' Orientation
					shipVerticalRotateAngle = 0;

					shipIt->shipTakeoff = false;

					CoolDownTime = 20;

					DisplayInventory = false;
					HandDisappear = false;
				}
			}
		}
	}
}

/******************************************************************************/
/*!
\brief
Function to read the NPCDialogues text file and store the lines in a vector.
*/
/******************************************************************************/
void SP2::Dialogues()
{
	std::ifstream file("TextFiles//NPCDialogues.txt");
	std::string str;
	while (std::getline(file, str))
	{
		file_contents = str;
		if (str != "end")
		{
			dialogue_vec.push_back(file_contents);
			//cout << file_contents << endl;
		}
		else
		{
			break;
		}

	}
}

/******************************************************************************/
/*!
\brief
Function to detect the NPCs position and use booleans to render out the line read from the dialogue file.
*/
/******************************************************************************/
void SP2::DialoguesWithNPCs()
{
	Vector3 view = (firstPersonCamera.target - firstPersonCamera.position).Normalized();

	for (vector<InteractableOBJs>::iterator it = InteractablesList.begin(); it != InteractablesList.end(); ++it)
	{

		//NURSE
		if (it->name == "nurse")
		{
			if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
			{
				nurseText = true;
			}
			else
			{
				nurseText = false;
			}
		}

		//DOCTOR
		if (it->name == "doctor")
		{
			if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
			{
				doctorText = true;
			}
			else
			{
				doctorText = false;
			}
		}

		//TRADER
		if (it->name == "trader")
		{
			if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
			{
				traderText = true;
			}
			else
			{
				traderText = false;
			}
		}

		//SOLDIER
		if (it->name == "soldier")
		{
			if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
			{
				soldierText = true;
			}
			else
			{
				soldierText = false;
			}
		}

		//CHEF
		if (it->name == "chef")
		{
			if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
			{
				chefText = true;
			}
			else
			{
				chefText = false;
			}
		}

		//SPACE GUY
		if (it->name == "spaceguy")
		{
			if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
			{
				spaceguyText = true;
			}
			else
			{
				spaceguyText = false;
			}
		}

		//NPC IN CAFE
		if (it->name == "shopkeeper")
		{
			if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
			{
				NPCInCafeTokenTask = true;

			}
			else
			{

				NPCInCafeTokenTask = false;
			}
		}


		//NPC IN REC ROOM
		if (it->name == "spaceguy2")
		{
			if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
			{
				NPCInRecMazeTask = true;

			}
			else
			{

				NPCInRecMazeTask = false;
			}
		}




	}
}


/******************************************************************************/
/*!
\brief
Function to read the Instructions text file and store the lines in a vector.
*/
/******************************************************************************/
void SP2::readInstructions()
{
	std::ifstream file("TextFiles//Instructions.txt");
	std::string str;
	while (std::getline(file, str))
	{
		file_contents2 = str;
		if (str != "end")
		{
			instruct_vec.push_back(file_contents2);
			//cout << file_contents2 << endl;
		}
		else
		{
			break;
		}

	}

}

/******************************************************************************/
/*!
\brief
    Function for rendering a mesh
\param  mesh
    Mesh to be loaded
\param  enableLight
    bool to check if light will apply to mesh
\param  toggleLight
    bool to toggle light on/off
*/
/******************************************************************************/
void SP2::RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight && toggleLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();

		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);


		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}


	mesh->Render(); //this line should only be called once 
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

/******************************************************************************/
/*!
\brief
    Function for rendering scene
*/
/******************************************************************************/
void SP2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camPointer->position.x, camPointer->position.y, camPointer->position.z,
		camPointer->target.x, camPointer->target.y, camPointer->target.z,
		camPointer->up.x, camPointer->up.y, camPointer->up.z
		);

	modelStack.LoadIdentity();

	Mtx44 MVP;

	for (size_t S = 0; S < numLights; S++)
	{
		if (light[S].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(light[S].position.x, light[S].position.y, light[S].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(lightUniforms[S][UL_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if (light[S].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[S].position;
			glUniform3fv(lightUniforms[S][UL_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * light[S].spotDirection;
			glUniform3fv(lightUniforms[S][UL_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
			glUniform3fv(lightUniforms[0][UL_POSITION], 1, &lightPosition_cameraspace.x);
		}
	}

	RenderCode();
}

/******************************************************************************/
/*!
\brief
    Function for cleaning up the scene
*/
/******************************************************************************/
void SP2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

	delete LightHull;
	delete MediumHull;
	delete LargeHull;

	delete DualWings;
	delete QuadWings;

	delete G1Engine;
	delete G2Engine;
}
/******************************************************************************/
/*!
\brief
Function to check for each individual crystal's position    

\param posxcheck , poszcheck , i    
posxcheck and poszcheck checks the current position of where the player is 
looking at, i is the position of the crystal's xcoord,zcoord in the array    

\return
returns bool, true if there is a crystal at that position, false if not 
*/
/******************************************************************************/

bool SP2::checkCrystalPos(float posxcheck, float poszcheck, int i)
{
	return (posxcheck == xcoords[i]) && (poszcheck == zcoords[i]) && (rendercrystal[i] == 1);
}
/******************************************************************************/
/*!
\brief
Function that resets the game     
*/
/******************************************************************************/
void SP2::reset()
{
	somePlayer.removeCrystals(somePlayer.getCrystals()); //sets amount of crystals to 0;    
	somePlayer.addCrystals(50);
	//removes ship obj and collision  
	shipBuilt = false; //doesnt render ship obj collision is still there 
	if (somePlayer.getCameraType() != "first")
	{
		camPointer = &firstPersonCamera;
		somePlayer.setCameraType("first");
		DisplayInventory = false;
		HandDisappear = false;
	}
	somePlayer.pos = startingCharPos;
    shipPos = shipStartingPos;
	firstPersonCamera.Reset();
	//resets third person camera      
	thirdPersonCamera.Reset();
	if (ShipList.size() > 0)
	{
		ShipList.pop_back();
	}
	//render space suit    
	wearSuit = false;
	//render crystals    

	for (vector<InteractableOBJs>::iterator it = InteractablesList.begin(); it != InteractablesList.end(); ++it)
	{
		if (it->name == "crystal")
		{
			it = this->InteractablesList.erase(it);
			it = InteractablesList.begin();
		}
	}
	for (int i = 0; i < CrystalNo; i++) //create collision for all crystal again 
	{
		InteractableOBJs crystal = InteractableOBJs("crystal", meshList[GEO_CRYSTAL]->maxPos, meshList[GEO_CRYSTAL]->minPos, Position(xcoords[i], 0, zcoords[i]), 5, 0, Vector3(0, 0, 0));
		crystal.setRequirements(30, 5);
		InteractablesList.push_back(crystal);
	}
	for (int a = 0; a < CrystalNo; a++)
	{
		rendercrystal[a] = 1;  //set all crystal to render    
	}

	// Removes ShipParts
	for (list<ShipParts*>::iterator it = somePlayer.getParts().begin(); it != somePlayer.getParts().end(); ++it)
	{
		it = this->somePlayer.getParts().erase(it);
		it = somePlayer.getParts().begin();
	}
	if (somePlayer.getParts().size() == 1)
	{
		somePlayer.getParts().pop_back();
	}
}

/******************************************************************************/
/*!
\brief
Function that randomly generates crystals (OBJ and hitbox)    
*/
/******************************************************************************/
void SP2::crystalgen()
{
	CrystalNo = 20;
	for (int i = 0; i < CrystalNo; i++)
	{
		coord1 = float(rand() % 474 - 42);
		coord2 = float(rand() % 763 - 381);
		if (((coord1 < 30) || coord1 > 350) || ((coord2 < -190) || (coord2 > 250)))
		{
			xcoords[i] = coord1;
			zcoords[i] = coord2;
			rendercrystal[i] = 1;
			//cout << coord1 << "," << coord2 << endl;
		}
	}
	for (int i = 0; i < CrystalNo; i++)
	{
		InteractableOBJs crystal = InteractableOBJs("crystal", meshList[GEO_CRYSTAL]->maxPos, meshList[GEO_CRYSTAL]->minPos, Position(xcoords[i], 0, zcoords[i]), 5, 0, Vector3(0, 0, 0));
		crystal.setRequirements(30, 5);
		InteractablesList.push_back(crystal);
	}
}

/******************************************************************************/
/*!
\brief
Function that randomly generates asteroid (OBJ + hitbox + movement + rotation)      
*/
/******************************************************************************/
void SP2::asteroidgen()
{
	AsteroidNo = 40;
	for (int i = 0; i < AsteroidNo; i++)
	{
		coord1 = float(rand() % 1000 - 500);
		coord2 = float(rand() % 1000 - 500);
		coord3 = float(rand() % 20 + 90);
		asteroidx[i] = coord1;
		asteroidy[i] = coord3;
		asteroidz[i] = coord2;
		coord1 = float(rand() % 10 - 5);
		if (coord1 == 0)
		{
			coord1 = 1;
		}
		coord2 = float(rand() % 10 - 5);
		if (coord2 == 0)
		{
			coord1 = 1;
		}
		movex[i] = coord1;
		movez[i] = coord2;
	}

	for (int i = 0; i < AsteroidNo; i++)
	{
		InteractableOBJs asteroid = InteractableOBJs("asteroid", meshList[GEO_ASTEROID]->maxPos, meshList[GEO_ASTEROID]->minPos, Position(asteroidx[i], asteroidy[i], asteroidz[i]), 1, 0, Vector3(0, 0, 0));
		asteroid.setRequirements(30, 5);
		InteractablesList.push_back(asteroid);
	}

} 