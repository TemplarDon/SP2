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

void SP2::Init()
{
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


    askedEngine = false;
    askedHull = false;
    askedWings = false;
    askedShipBuild = false;
    shipBuilt = false;

	//JUmp
	acceleration = -1;
	firstvelo = 0;
	secondvelo = 0;
	t = 1;
	distance = 0; 
	firstpos = 0;

	onGround = true;
	gateOpening = false;
	CrystalText = false;

	//FIRST PERSON CAMERA
	firstPersonCamera.Reset();

	//THRID PERSON CAMERA
	thirdPersonCamera.SetMouseEnabled(true);
	thirdPersonCamera.SetCameraDistanceBounds(10, 200);
	thirdPersonCamera.SetCameraDistanceAbsolute(60);

	//INIT CAMERA POINTER
	camPointer = &firstPersonCamera;

	//STARTING POSITION OF PLAYER
	startingCharPos = charPos = { 600, 17, -36 };


	//Initialize camera settings (Don's)

	shipStartingPos = shipPos = { -100, 18, 160 };
    shipHorizontalRotateAngle = 0;
    shipVerticalRotateAngle = 0;

    //Initialize camera settings (Don's)
	firstPersonCamera.Init(Vector3(charPos.x, charPos.y, charPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), &shipPos, 20);

    // Init Cam Pointer
    camPointer = &firstPersonCamera;

	//INIT PLAYER
	somePlayer.setPlayerStats("TestMan", "Human", 100, charPos, firstPersonCamera); // Name, Race, Money, Pos, camera


	//SHIP INIT
	shipStartingPos = shipPos = { 75, 18, 150 };
    shipHorizontalRotateAngle = 0;
    shipVerticalRotateAngle = 0;



	LoadMeshes();

    //camPointer = &thirdPersonCamera;
    //somePlayer.setCameraType("third");

    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
    projectionStack.LoadMatrix(projection);

	thirdPersonCamera.SetCameraDistanceBounds(10, 200);
	thirdPersonCamera.SetCameraDistanceAbsolute(60);


	firstPersonCamera.Reset();

	//CRYSTAL
	//ASSIGNING COORD INTO ARRAY   
    CrystalNo = 10;
	for (int i = 0; i < CrystalNo; i++)
	{
		xcoords[i] = rand() % 900 - 450;
		zcoords[i] = rand() % 900 - 450;
		rendercrystal[i] = 1;
	}
	for (int i = 0; i < CrystalNo; i++)
	{
		InteractableOBJs crystal = InteractableOBJs("crystal", meshList[GEO_CRYSTAL]->maxPos, meshList[GEO_CRYSTAL]->minPos, Position(xcoords[i], 0, zcoords[i]), 5, 0, Vector3(0, 0, 0));
		crystal.setRequirements(30, 5);
		InteractablesList.push_back(crystal);
	}
	crystalcount = 0;

}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
float FramesPerSecond = 0;
void SP2::Update(double dt)
{
	//FPS
	FramesPerSecond = 1 / dt;

	//READKEYS FUNCTION
	ReadKeyPresses();

	//COLLISION
    interactionCheck(dt, InteractablesList, somePlayer);


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


	//WTF IS THIS PLEASE COMMENT
	static unsigned firstFrames = 2;
	if (firstFrames > 0)
	{
		firstPersonCamera.Reset();
		firstFrames--;
	}
    

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
					YesShowCafeMenu = true;
				}

				if (YesShowCafeMenu == true)
				{
					DisplayCafeMenu = true;
				}
				else
				{
					DisplayCafeMenu = false;
				}
			}
			else
			{
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

	}


	//SHIP INTERACTIONS (DONOVAN'S)
>>>>>>> origin/master
    for (vector<Ship>::iterator i = ShipList.begin(); i != ShipList.end(); ++i)
    {
        //Movements with OBJs. NOTE: Cameras should have a name to define.
        if (camPointer == &thirdPersonCamera)
        {
            Vector3 view = (camPointer->target - camPointer->position).Normalized();
            if (Application::IsKeyPressed('W'))
            {
                shipPos.x = shipPos.x + view.x + i->shipSpeed;
                shipPos.y = shipPos.y + view.y + i->shipSpeed;
                shipPos.z = shipPos.z + view.z + i->shipSpeed;

                // Ship Animation - Don't Touch - Donovan
                shipAnimation(dt);
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
                if (i->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), viewDirection) == true)
                {
					CrystalText = true;
					posxcheck = i->pos.x;
					poszcheck = i->pos.z;
					
					if (Application::IsKeyPressed('M'))
					{
						for (int i = 0; i < CrystalNo; i++)
						{
							if ((posxcheck == xcoords[i]) && (poszcheck == zcoords[i]) && (rendercrystal[i] == 1))
							{
								rendercrystal[i] = 0;
								crystalcount += rand() % 10 + 1;
							}
						}
					}
                }

            }
            //DOOR OPEN AND CLOSE (DONOVAN'S)    - DO NOT TOUCH
            else if (i->name.find("frontGate") != string::npos) //IF InteractableOBJ IS A FRONTGATE
            {
                if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), viewDirection)) //IF FRONTGATE IS IN VIEW
                {
                    gateOpening = true;
                    doorInteractions(dt, i, frontGateOffset);
                }
            }
            else if (i->name.find("backGate") != string::npos)
            {
                if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), viewDirection))
                {
                    doorInteractions(dt, i, backGateOffset);
                }
            }
            else if (i->name.find("leftGate") != string::npos)
            {
                if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), viewDirection))
                {
                    doorInteractions(dt, i, leftGateOffset);
                }
            }
            else if (i->name.find("rightGate") != string::npos)
            {
                if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), viewDirection))
                {
                    doorInteractions(dt, i, rightGateOffset);
                }   
            }
        }
    }


    //SHIP CREATION (DONOVAN'S)  - DO NOT TOUCH
    if (Application::IsKeyPressed('E') && ShipList.size() == 0)
    // Ship Creation - Don't Touch - Donovan
    //if (Application::IsKeyPressed('E') && ShipList.size() == 0)
    //{
    //    shipCreation();
    //}

    if (askedShipBuild)
>>>>>>> origin/master
    {
        shopInteractions();
    }


    //SHIP ANIMATIONS (DONOVAN'S)  - DO NOT TOUCH
    shipAnimation(dt);


    
	//JUMP (BECKHAM'S)
	if (Application::IsKeyPressed(VK_SPACE) &&  (onGround == true)) //s = ut + 0.5 at^2
	{ 
		firstpos = firstPersonCamera.position.y;
		firstvelo = 50;
		onGround = false;
	}
	if (onGround == false)
	{
		secondvelo = firstvelo + (acceleration * t * t); // a = -2 , t = 1 
		firstvelo = secondvelo;

		distance = ((firstvelo * t) + (0.5 * acceleration * t * t));
		firstPersonCamera.position.y += distance * dt;
        firstPersonCamera.target.y += distance * dt;

        somePlayer.pos.y += distance * dt;
	}

	if (firstpos >= firstPersonCamera.position.y)
	{
		firstPersonCamera.position.y = firstpos;
		onGround = true;
	}
	
}

void SP2::doorInteractions(double dt, vector<InteractableOBJs>::iterator it, float& gateOffset)
{
    if (gateOffset <= 35)
    {
        gateOffset += (float)(10 * dt);
        it->pos.y += (float)(10 * dt);
    }
}

void SP2::doorClosing(double dt, vector<InteractableOBJs>::iterator it, float& gateOffset)
{
    if (gateOffset > 0)
    {
        gateOffset -= (float)(10 * dt);
        it->pos.y -= (float)(10 * dt);
    }
}

void SP2::shipAnimation(double dt)
{
    // Ship Animation
    if (thirdPersonCamera.yawingLeft == true /*&& shipHorizontalRotateAngle >= -20*/) { shipHorizontalRotateAngle += (float)(40 * dt); }
    if (thirdPersonCamera.yawingRight == true /*&& shipHorizontalRotateAngle <= 20*/) { shipHorizontalRotateAngle -= (float)(40 * dt); }
    if (thirdPersonCamera.pitchingDown == true /*&& shipVerticalRotateAngle >= -20*/) { shipVerticalRotateAngle += (float)(40 * dt); }
    if (thirdPersonCamera.pitchingUp == true /*&& shipHorizontalRotateAngle <= 20*/) { shipVerticalRotateAngle -= (float)(40 * dt); }

    // Reset Ship to original orientation
    if (thirdPersonCamera.yawingRight == false )
    {
        if (shipHorizontalRotateAngle >= -20 && shipHorizontalRotateAngle < 0)
        {
            shipHorizontalRotateAngle += (float)(10 * dt);
        }
    }

    if (thirdPersonCamera.yawingLeft == false)
    {
        if (shipHorizontalRotateAngle <= 20 && shipHorizontalRotateAngle > 0)
        {
            shipHorizontalRotateAngle -= (float)(10 * dt);
        }
    }

    if (thirdPersonCamera.pitchingDown == false)
    {
        if (shipVerticalRotateAngle >= -20 && shipVerticalRotateAngle < 0)
        {
            shipVerticalRotateAngle += (float)(10 * dt);
        }
    }

    if (thirdPersonCamera.pitchingUp == false)
    {
        if (shipVerticalRotateAngle <= 20 && shipVerticalRotateAngle > 0)
        {
            shipVerticalRotateAngle -= (float)(10 * dt);
        }
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

    //ShipList.push_back(ShipBuilder.createShip(shipTemplatePtr, LargeHull, QuadWings, G1Engine));
    ShipList.push_back(ShipBuilder.createShip(shipTemplatePtr, somePlayer.getParts()));

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
        }

        

        
    }
}

void SP2::interactionCheck(double dt, vector<InteractableOBJs>&InteractablesList, Player &somePlayer)
{
	Vector3 view = (firstPersonCamera.target - firstPersonCamera.position).Normalized();
    for (vector<Ship>::iterator i = ShipList.begin(); i < ShipList.end(); ++i)
    {
        if (i->isInView(somePlayer.pos, view) == true)
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
                    camPointer = &firstPersonCamera;
                    somePlayer.setCameraType("first");
                }
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
        camPointer->position.x,    camPointer->position.y,    camPointer->position.z,
        camPointer->target.x,      camPointer->target.y,      camPointer->target.z,
        camPointer->up.x,          camPointer->up.y,          camPointer->up.z
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
