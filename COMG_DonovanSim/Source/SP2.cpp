#include "SP2.h"
#include <fstream>

using std::cout;
using std::cin;
using std::endl;

SP2::SP2()
{
}

SP2::~SP2()
{

}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
float FramesPerSecond = 0;

void SP2::Init()
{
	S = PLACE1;

	//FUNCTIONS TO CALL
	LoadShaderCodes();
	LoadLights();
	Dialogues();


	//RANDOM (MINING)
	srand(time(0));

	//FLOATS
	rotateAngle = 0;
	TokenTranslate = 11;
	TextTranslate = 20;
	TestRotation = 90;
	SuitTranslate = 2;
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
	cafeMenuPointer = 62;
	BounceTime = 0;
	CoolDownTime = 0;

	//BOOLEANS
	NearVendingText = false;
	TokenOnScreen = false;
	RenderCoke = false;
	ConsumeCokeText = false;
	testText = false;
	PickUpTokenText = false;
	DisplayCafeMenu = false;
	YesShowCafeMenu = false;
	MENUBOOL = false;
	wearSuitText = false;
	wearSuit = false;
	DisplayInventory = false;
	toggleLight = true;
	wearSuitText = false;
	wearSuit = false;
	chefText = false;
	spaceguyText = false;
	nurseText = false;
	doctorText = false;
	traderText = false;
	soldierText = false;
	shopkeeperText = false;
	equipPickaxe = false;
	equipGun = false;
	HandDisappear = false;
	DisplayShopList = false;
	BreadAppear = false;
	CoffeeAppear = false;



	AsteroidCollision = false;


	askedEngine = false;
	askedHull = false;
	askedWings = false;
	askedShipBuild = false;
	shipBuilt = false;

	gateOpening = false;
	frontGateOpening = false;
	backGateOpening = false;
	leftGateOpening = false;
	rightGateOpening = false;

	keypadBool = false;

	// Assign Pointers for Ship Building
	LightHull = new Light_Hull;
	MediumHull = new Medium_Hull;
	LargeHull = new Large_Hull;

	G1Engine = new G1_Engine;
	G2Engine = new G2_Engine;

	DualWings = new Dual_Wings;
	QuadWings = new Quad_Wings;

	//JUmp
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
        mazeRandomTranslateVec.push_back((float)((rand() % 100 - 50)));    
    }
    deadText = false;

	//FIRST PERSON CAMERA
	firstPersonCamera.Reset();

	//THRID PERSON CAMERA
	thirdPersonCamera.SetMouseEnabled(true);
	thirdPersonCamera.SetCameraDistanceBounds(10, 200);
	thirdPersonCamera.SetCameraDistanceAbsolute(30);

	//INIT CAMERA POINTER
	camPointer = &firstPersonCamera;

	//STARTING POSITION OF PLAYER


	//startingCharPos = charPos = { -350, 17, -370 }; // STARTING POS OF MAZERUNNER
    startingCharPos = charPos = { 108, 17, 130 };



	//Initialize camera settings (Don's)
	shipStartingPos = shipPos = { 375, 18, -105 };
    shipHorizontalRotateAngle = 0;
    shipVerticalRotateAngle = 0;

	//Initialize camera settings (Don's)
	firstPersonCamera.Init(Vector3(charPos.x, charPos.y, charPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
	thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), &shipPos, 20);

	// Init Cam Pointer
	camPointer = &firstPersonCamera;

	//Init Player + Stats
	somePlayer.setPlayerStats("TestMan", "Human", 100, charPos, firstPersonCamera); // Name, Race, Money, Pos, camera

	LoadMeshes();

    Mtx44 projection;
    projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 2000.f);
    projectionStack.LoadMatrix(projection);

	thirdPersonCamera.SetCameraDistanceBounds(10, 200);
	thirdPersonCamera.SetCameraDistanceAbsolute(30);


	firstPersonCamera.Reset();

	//CRYSTAL
	//ASSIGNING COORD INTO ARRAY   x - 30 , 350  z - -190 , 250
	CrystalNo = 20;
	for (int i = 0; i < CrystalNo; i++)
	{
		coord1 = rand() % 474 - 42;
		coord2 = rand() % 763 - 381;
		if (((coord1 < 30) || coord1 > 350) || ((coord2 < -190) || (coord2 > 250)))
		{
			xcoords[i] = coord1;
			zcoords[i] = coord2;
			rendercrystal[i] = 1;
			cout << coord1 << "," << coord2 << endl;
		}
	}
	for (int i = 0; i < CrystalNo; i++)
	{
			InteractableOBJs crystal = InteractableOBJs("crystal", meshList[GEO_CRYSTAL]->maxPos, meshList[GEO_CRYSTAL]->minPos, Position(xcoords[i], 0, zcoords[i]), 5, 0, Vector3(0, 0, 0));
			crystal.setRequirements(30, 5);
			InteractablesList.push_back(crystal);
	}
	AsteroidNo = 40;
	for (int i = 0; i < AsteroidNo; i++)
	{
		coord1 = rand() % 1000 - 500;
		coord2 = rand() % 1000 - 500;   
		coord3 = rand() % 20 + 90;   
		asteroidx[i] = coord1;
		asteroidy[i] = coord3;   
		asteroidz[i] = coord2;
		coord1 = rand() % 10 -5 ;   
		if (coord1 == 0)
		{
			coord1 = 1;
		}
		coord2 = rand() % 10 - 5;    
		if (coord2 == 0)
		{
			coord1 = 1;
		}
		movex[i] = coord1;
		movez[i] = coord2;
	}
	for (int i = 0; i < AsteroidNo; i++)
	{
		InteractableOBJs asteroid = InteractableOBJs("asteroid", meshList[GEO_ASTEROID]->maxPos, meshList[GEO_ASTEROID]->minPos, Position(asteroidx[i],asteroidy[i],asteroidz[i]), 1, 0, Vector3(0, 0, 0));
		asteroid.setRequirements(30, 5);
		InteractablesList.push_back(asteroid);
	}
	crystalcount = 0;

	keypads.clear();

	InitKeypads();
}

void SP2::Update(double dt)
{
	//Dont touch this code 
	CrystalText = false;
	AsteroidCollision = false;
	//FPS
	FramesPerSecond = 1 / dt;

	//READKEYS FUNCTION
	ReadKeyPresses();

    //TESTING FOR CAFE MENU
    if (!MENUBOOL)
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


    static unsigned firstFrames = 2;
    if (firstFrames > 0)
    {
        firstPersonCamera.Reset();
        firstFrames--;
    }

    if (Application::IsKeyPressed('R'))
    {
        somePlayer.pos = startingCharPos;
        firstPersonCamera.Reset();
    }


	//DIALOGUE DO NOT DELETE THIS 
	DialoguesWithNPCs();

	//DO NOT DELETE EQUIP WEAPON STUFF
	EquippingWeapons();

	//DO NOT DELETE CAFE MENU STUFF 
	//CAFE MENU
	CafeMenuPointerInteraction();

	//DO NOT DELETE SHOP MENU STUFF
	//ShopMenuPointerInteraction();


	//INTERACTIONS WITH OBJS (SHANIA'S)  IT WORKS
	Vector3 view = (firstPersonCamera.target - firstPersonCamera.position).Normalized();

	for (vector<InteractableOBJs>::iterator it = InteractablesList.begin(); it != InteractablesList.end(); ++it)
	{
        //VENDING MACHINE
        if (it->name == "vending")
        {
            if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
            {
                NearVendingText = true;
                if (Application::IsKeyPressed('Q'))
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
                }
            }
            else
            {
				testText = false;
                testText = false;
                DisplayCafeMenu = false;
                YesShowCafeMenu = false;
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
                    SuitTranslate = -50;
                    wearSuit = true;
                    DisplayInventory = true;
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
				if (Application::IsKeyPressed('Y'))
				{
					DisplayShopList = true;
				}
			}
			else
			{

				DisplayShopList = false;
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

        // Shop
        if (it->name == "shop")
        {
            if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view))
            {
                if (Application::IsKeyPressed('E'))
                {
                    askedShipBuild = true;
                    askedHull = true;
                }
            }
        }

        // Weapon
        if (it->name == "gun rack")
        {
            if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view))
            {
                if (Application::IsKeyPressed('E'))
                {
                    somePlayer.setWeapon();
                }
            }

        }

        // Target
        if (it->name == "target dummy")
        {
            if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view))
            {
                if (Application::IsKeyPressed('E') && somePlayer.checkWeapon() == true)
                {
                    somePlayer.addCrystals(1);
                }
            }
        }
		if (it->name == "crystal")
		{
			if (it->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view))
			{
				CrystalText = true;
				posxcheck = it->pos.x;
				poszcheck = it->pos.z;
				if (Application::IsKeyPressed('E'))
				{
					for (int a = 0; a < CrystalNo; a++)
					{
						if (checkCrystalPos(posxcheck, poszcheck, a))
						{

							rendercrystal[a] = 0;
							crystalcount += rand() % 10 + 1;

							somePlayer.addCrystals(rand() % 10 + 1);

							it = this->InteractablesList.erase(it);
							it = InteractablesList.begin();
						}
					}
				}
			}
		}
		if (it->name == "asteroid") 
		{
			posxcheck = it->pos.x;
			poszcheck = it->pos.z;
			posycheck = it->pos.y;
			posxcheck = (posxcheck - somePlayer.pos.x) * (posxcheck - somePlayer.pos.x);
			posycheck = (posycheck - somePlayer.pos.y) * (posycheck - somePlayer.pos.y);
			poszcheck = (poszcheck - somePlayer.pos.z) * (poszcheck - somePlayer.pos.z);
			between = posxcheck + posycheck + poszcheck; 
			between = sqrt(between);
			if (between <= 30)
			{
				AsteroidCollision = true;
			}
		}
    }
	if (Application::IsKeyPressed(VK_SPACE) && (onGround == true)) //s = ut + 0.5 at^2
	{
		firstpos = firstPersonCamera.position.y;
		firstvelo = 35;
		onGround = false;
	}
	if (onGround == false)
	{
		secondvelo = firstvelo + (acceleration * t * t); // a = -2 , t = 1 
		firstvelo = secondvelo;

		distance = ((firstvelo * t) + (0.3 * acceleration * t * t));
		firstPersonCamera.position.y += distance * dt;
		firstPersonCamera.target.y += distance * dt;

		somePlayer.pos.y += distance * dt;
	}

	if (firstpos >= firstPersonCamera.position.y)
	{
		firstPersonCamera.position.y = firstpos;
		onGround = true;
	}

	//INTERACTIONS WITH OBJS (BECKHAM'S & DONOVAN'S)
	if (camPointer == &firstPersonCamera)
	{
		Vector3 viewDirection = (firstPersonCamera.target - firstPersonCamera.position).Normalized();
	
		if (askedShipBuild)
		{
			shopInteractions();
		}
	}

	for (int i = 0; i < AsteroidNo; i++)
	{
		asteroidx[i] += movex[i] + 0.05 * dt;
		asteroidz[i] += movez[i] + 0.5 * dt;
		if (asteroidx[i] > 1000 || asteroidx[i] < -1000)
		{
			asteroidx[i] *= -1;
		}
		if (asteroidz[i] > 1000 || asteroidz[i] < -1000)
		{
			asteroidz[i] *= -1;
		}
	}
	
    //Entering / Exiting Ship
    shipToggle(dt, InteractablesList, somePlayer);

    // Ship Flying + Animation
    shipFlying(dt);

    // Maze Movement
    mazeTranslate(dt);
}

//PLEASE DO NOT DELETE THIS !!!!
void SP2::CafeMenuPointerInteraction()
{
	if (CoolDownTime > 0)
	{
		CoolDownTime--;
	}
	else
	{
		CoolDownTime == 0;
	}

	switch (S)
	{
	case PLACE1:
		cafeMenuPointer = 62;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = PLACE3;
		}
		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = PLACE2;
		}
		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			AppleAppear = true;
		}
		if (Application::IsKeyPressed('U'))
		{
			AppleAppear = false;
		}
		break;
	case PLACE2:
		cafeMenuPointer = 50;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = PLACE1;
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
		if (Application::IsKeyPressed('U'))
		{
			CoffeeAppear = false;
		}
		break;
	case PLACE3:
		cafeMenuPointer = 38;
		if (Application::IsKeyPressed(VK_UP) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = PLACE2;
		}
		if (Application::IsKeyPressed(VK_DOWN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			S = PLACE1;
		}
		if (Application::IsKeyPressed(VK_RETURN) && CoolDownTime == 0)
		{
			CoolDownTime = 20;
			BreadAppear = true;
		}
		if (Application::IsKeyPressed('U'))
		{
			BreadAppear = false;
		}
		break;
	}

}

//PLEASE DO NOT DELETE THIS TOO !!!!
void SP2::EquippingWeapons()
{
	//EQUIP GUN, HAND DISAPPEAR
	if (Application::IsKeyPressed(VK_F1))
	{
		equipGun = true;
		translatePointer = 127;
		HandDisappear = true;
	}

	//EQUIP PICKAXE , HAND DISAPPEAR
	if (Application::IsKeyPressed(VK_F2))
	{
		equipPickaxe = true;
		translatePointer = 141;
		HandDisappear = true;
	}

	//F3 TO MAKE INVENTORY AND HAND APPEAR
	if (Application::IsKeyPressed(VK_F3))
	{
		equipGun = false;
		equipPickaxe = false;
		translatePointer = -10;
		HandDisappear = false;
	}
}

void SP2::shipFlying(double dt)
{
    //SHIP INTERACTIONS (DONOVAN'S)
    for (vector<Ship>::iterator i = ShipList.begin(); i != ShipList.end(); ++i)
    {
        if (camPointer == &thirdPersonCamera)
        {
            Vector3 view = (camPointer->target - camPointer->position).Normalized();
            Vector3 up = camPointer->up;
            Vector3 right = view.Cross(up);

            if (!i->shipTakeoff) { i->setDirectionalVectors(view.Normalized()); }

            if (Application::IsKeyPressed(VK_SPACE) && i->shipTakeoff == false) { i->shipTakeoff = true; } /// Press 'SpaceBar' to take off

            if (i->shipTakeoff)
            {
                // Ship Animation - Don't Touch - Donovan
                shipAnimation(dt, i);

                // Set ship's new direction
                i->setDirectionalVectors((i->shipDirection + view).Normalized());

                shipPos.x = shipPos.x + i->shipDirection.x + (float)(i->shipSpeed * dt);
                shipPos.y = shipPos.y + i->shipDirection.y + (float)(i->shipSpeed * dt);
                shipPos.z = shipPos.z + i->shipDirection.z + (float)(i->shipSpeed * dt);

                somePlayer.pos.x = somePlayer.pos.x + i->shipDirection.x + (float)(i->shipSpeed * dt);
                somePlayer.pos.y = somePlayer.pos.y + i->shipDirection.y + (float)(i->shipSpeed * dt);
                somePlayer.pos.z = somePlayer.pos.z + i->shipDirection.z + (float)(i->shipSpeed * dt);

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
        }
    }
}

void SP2::shipAnimation(double dt, vector<Ship>::iterator i)
{
    // Ship Animation
    Vector3 view = (camPointer->target - camPointer->position).Normalized();
    Vector3 up = camPointer->up;
    Vector3 right = view.Cross(up);

    // Find angle to pitch
    float pitchAngleDiff = Math::RadianToDegree(acos(thirdPersonCamera.defaultUpVec.Dot(up)) / (thirdPersonCamera.defaultUpVec.Length() * up.Length()));

    // Find angle to yaw
    float yawAngleDiff = Math::RadianToDegree(acos(thirdPersonCamera.defaultRightVec.Dot(right) / thirdPersonCamera.defaultRightVec.Length() * right.Length()));

    // Check which direction ship is turning in and rotate ship
    if (thirdPersonCamera.yawingLeft && shipHorizontalRotateAngle <= yawAngleDiff)
    {
        shipHorizontalRotateAngle += (float)(i->turningSpeed * dt);
    }

    if (thirdPersonCamera.yawingRight && shipHorizontalRotateAngle >= -yawAngleDiff)
    {
        shipHorizontalRotateAngle -= (float)(i->turningSpeed * dt);
    }

    if (thirdPersonCamera.pitchingDown && shipVerticalRotateAngle <= pitchAngleDiff)
    {
        shipVerticalRotateAngle += (float)(i->turningSpeed * dt);
    }

    if (thirdPersonCamera.pitchingUp && shipVerticalRotateAngle >= -pitchAngleDiff)
    {
        shipVerticalRotateAngle -= (float)(i->turningSpeed * dt);
    }
    
    if (shipVerticalRotateAngle >= 360) { shipVerticalRotateAngle = 0; }
    if (shipHorizontalRotateAngle >= 360) { shipHorizontalRotateAngle = 0; }
}

void SP2::mazeTranslate(double dt)
{
    //float randomScale = (float)((rand() % 10 + 1));
    //for (vector<InteractableOBJs>::iterator it = InteractablesList.begin(); it != InteractablesList.end(); ++it)
    //{
    //    if (it->name == "leftObstacle" || it->name == "rightObstacle")
    //    {
    //        if (mazeTranslateValue <= 10 && !mazeOpening)
    //        {
    //            mazeTranslateValue += (float)(randomScale * dt);
    //            it->pos.z += (float)(randomScale * dt);
    //            if (mazeTranslateValue >= 10)
    //            {
    //                mazeOpening = true;
    //            }
    //        }
    //        else
    //        {
    //            mazeTranslateValue -= (float)(randomScale * dt);
    //            it->pos.z -= (float)(randomScale * dt);
    //            if (mazeTranslateValue <= 0)
    //            {
    //                mazeOpening = false;
    //            }
    //        }

    //        //if ((somePlayer.pos.x < it->maxPos.x * it->scaleOffSet + it->pos.x && somePlayer.pos.x > it->minPos.x * it->scaleOffSet + it->pos.x) && (somePlayer.pos.z < it->maxPos.z * it->scaleOffSet + it->pos.z && somePlayer.pos.z > it->minPos.z * it->scaleOffSet + it->pos.z))
    //        //{
    //        //    firstPersonCamera.Reset();
    //        //}

    //        for (int zAxis = 300; zAxis >= -300; zAxis -= 100)
    //        {
    //            //-330 to -350
    //            if (somePlayer.pos.x >= -350 && somePlayer.pos.x <= -330 && somePlayer.pos.z >= zAxis - 3 && somePlayer.pos.z <= zAxis + 3)
    //            {
    //                if (!mazeOpening)
    //                firstPersonCamera.Reset();
    //            }
    //        }

    //    }
    //}

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
            if ((somePlayer.pos.z <= 350 && somePlayer.pos.z >= -350) && (somePlayer.pos.x <= -420 + lavaTranslation + 5 && somePlayer.pos.x >= -420 + lavaTranslation - 5) && (somePlayer.pos.y <= 17))
            {
                deadText = true;
            }
            else
            {
                deadText = false;
            }
        }
    }

}

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

void SP2::shipCreation()
{
    // Space Ship Template
    //WHY SHOULD YOU LOAD A MESH IN THE MIDDLE OF THE PROGRAM? WHO WAS DOING IT? (comment by Gary Goh)
    //meshList[GEO_SHIP] = MeshBuilder::GenerateOBJ("ship", "OBJ//V_Art Spaceship.obj");

    Ship someShip = Ship("ship", meshList[GEO_SHIP]->maxPos, meshList[GEO_SHIP]->minPos, shipStartingPos, 4, 0, Vector3(0, 0, 0));
    someShip.setRequirements(50, 500);

    shipTemplatePtr = &someShip;

    ShipList.push_back(ShipBuilder.createShip(shipTemplatePtr, somePlayer.getParts()));
    
    Vector3 view = (thirdPersonCamera.target - thirdPersonCamera.position).Normalized();
    Vector3 up = thirdPersonCamera.up;
    Vector3 right = view.Cross(up);
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

void SP2::shipToggle(double dt, vector<InteractableOBJs>&InteractablesList, Player &somePlayer)
{
	Vector3 view = (firstPersonCamera.target - firstPersonCamera.position).Normalized();
	for (vector<Ship>::iterator shipIt = ShipList.begin(); shipIt < ShipList.end(); ++shipIt)
	{
		if (shipIt->isInView(somePlayer.pos, view) == true)
		{
			if (Application::IsKeyPressed('F'))
			{
				if (somePlayer.getCameraType() == "first")
				{
					camPointer = &thirdPersonCamera;
					somePlayer.setCameraType("third");
				}
				else
				{
					view = (thirdPersonCamera.target - thirdPersonCamera.position).Normalized();
					for (vector<InteractableOBJs>::iterator i = InteractablesList.begin(); i < InteractablesList.end(); i++)
					{
						if (i->name == "helipad")
						{
							if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view) && shipIt->shipSpeed <= shipIt->shipLandingSpeed)
							{
								camPointer = &firstPersonCamera;
								somePlayer.setCameraType("first");
							}
						}
					}
				}
			}
		}
	}
}

void SP2::shopInteractions()
{
    if (askedHull)
    {
        if (Application::IsKeyPressed('1'))
        {
            if (somePlayer.removeCrystals(10))
            {
                somePlayer.removeCrystals(10); 
                somePlayer.addPart(LightHull);
                askedHull = false;
                askedWings = true;
            }
 
        }
        else if (Application::IsKeyPressed('2'))
        {
            if (somePlayer.removeCrystals(20)) 
            {
                somePlayer.removeCrystals(20); 
                somePlayer.addPart(MediumHull);
                askedHull = false;
                askedWings = true;
            }

        }
        else if (Application::IsKeyPressed('3'))
        {
            if (somePlayer.removeCrystals(30)) 
            { 
                somePlayer.removeCrystals(30); 
                somePlayer.addPart(LargeHull);
                askedHull = false;
                askedWings = true;
            }
        }
    }

    if (askedWings)
    {
        if (Application::IsKeyPressed('1'))
        {
            if (somePlayer.removeCrystals(20)) 
            { 
                somePlayer.removeCrystals(20); 
                somePlayer.addPart(DualWings);
                askedWings = false;
                askedEngine = true;
            }
        }
        else if (Application::IsKeyPressed('2'))
        {
            if (somePlayer.removeCrystals(30)) 
            { 
                somePlayer.removeCrystals(30); 
                somePlayer.addPart(QuadWings);
                askedWings = false;
                askedEngine = true;
            }

        }
    }

    if (askedEngine)
    {
        if (Application::IsKeyPressed('1'))
        {

            if (somePlayer.removeCrystals(20)) 
            {
                somePlayer.removeCrystals(20); 
                somePlayer.addPart(G1Engine);
                askedEngine = false;
                shipCreation();
                askedShipBuild = false;
                shipBuilt = true;
            }

        }
        else if (Application::IsKeyPressed('2'))
        {
            if (somePlayer.removeCrystals(30)) 
            { 
                somePlayer.removeCrystals(30);
                somePlayer.addPart(G2Engine);
                askedEngine = false;
                shipCreation();
                askedShipBuild = false;
                shipBuilt = true;
            }
        }
    }


}

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
			cout << file_contents << endl;
		}
		else
		{
			break;
		}

	}
}

void SP2::DialoguesWithNPCs()
{
	Vector3 view = (firstPersonCamera.target - firstPersonCamera.position).Normalized();

	for (vector<InteractableOBJs>::iterator it = InteractablesList.begin(); it != InteractablesList.end(); ++it)
	{

		//SHOPKEEPER
		if (it->name == "shopkeeper")
		{
			if (it->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), view))
			{
				shopkeeperText = true;
			}
			else
			{
				shopkeeperText = false;
			}
		}

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
	}
}

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

void SP2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

bool SP2::checkCrystalPos(int posxcheck, int poszcheck, int i)
{
	if ((posxcheck == xcoords[i]) && (poszcheck == zcoords[i]) && (rendercrystal[i] == 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}


