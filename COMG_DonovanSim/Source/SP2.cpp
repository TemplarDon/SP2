#include "SP2.h"

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
float FramesPerSecond = 0;

SP2::SP2()
{
}

SP2::~SP2()
{

}

void SP2::Init()
{
	LoadShaderCodes();
	LoadLights();

	srand(time(0));

	//variable to rotate geometry
	rotateAngle = 0;

	//Bools

	NearVendingText = false;
	TokenOnScreen = false;
	RenderCoke = false;
	ConsumeCokeText = false;
	testText = false;
	PickUpTokenText = false;
	DisplayCafeMenu = false;
	YesShowCafeMenu = false;
	
	toggleLight = true;
	
	MENUBOOL = false;
	
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

	thirdPersonCamera.SetMouseEnabled(true);

	//Floats

	TokenTranslate = 11;
	TextTranslate = 20;
	TestRotation = 90;
	
	SuitTranslate = 2;

    leftGateOffset = 0;
    rightGateOffset = 0;
    frontGateOffset = 0;
    backGateOffset = 0;

	heightOfWall = 12;


	startingCharPos = charPos = { 600, 17, -36 };

	shipStartingPos = shipPos = { -100, 18, 160 };
    shipHorizontalRotateAngle = 0;
    shipVerticalRotateAngle = 0;

    //Initialize camera settings (Don's)
	firstPersonCamera.Init(Vector3(charPos.x, charPos.y, charPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), &shipPos, 20);

    // Init Cam Pointer
    camPointer = &firstPersonCamera;

    // Init Player
	//somePlayer.setPlayerStats("TestMan", "Human", 100, playerStartingPos, firstPersonCamera); // Name, Race, Money, Pos, camera
	somePlayer.setPlayerStats("TestMan", "Human", 100, charPos, firstPersonCamera); // Name, Race, Money, Pos, camera

    LoadMeshes();

    //camPointer = &thirdPersonCamera;
    //somePlayer.setCameraType("third");

    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
    projectionStack.LoadMatrix(projection);

	thirdPersonCamera.SetCameraDistanceBounds(10, 200);
	thirdPersonCamera.SetCameraDistanceAbsolute(60);


	firstPersonCamera.Reset();

	//Assigning coords to array  
    CrystalNo = 100;
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

void SP2::Update(double dt)
{
	FramesPerSecond = 1 / dt;

	ReadKeyPresses();

	CrystalText = false;
    //createBoundBox(InteractablesList, BuildingsList);
    interactionCheck(dt, InteractablesList, somePlayer);

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
    
	TestRotation += float(dt * 100);


	//Movements with OBJs. NOTE: Cameras should have a name to define.
	if (camPointer == &thirdPersonCamera)
	{
		Vector3 view = (camPointer->target - camPointer->position).Normalized();
		if (Application::IsKeyPressed('W'))
		{
			shipPos.x += view.x;
			shipPos.y += view.y;
			shipPos.z += view.z;
		}
	}

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

	//Interactions with OBJs.
    //if (camPointer == &firstPersonCamera)
    //{
    //    Vector3 viewDirection = (firstPersonCamera.target - firstPersonCamera.position).Normalized();
    //    for (vector<InteractableOBJs>::iterator i = InteractablesList.begin(); i < InteractablesList.end(); i++)
    //    {
    //        if (i->name == "crystal")
    //        {
    //            if (i->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), viewDirection) == true)
    //            {
				//CrystalText = true;
				//posxcheck = i->pos.x;
				//poszcheck = i->pos.z;
				//if (Application::IsKeyPressed('M'))
				//	{
				//	for (int i = 0; i < CrystalNo; i++)
				//		{
				//		if ((posxcheck == xcoords[i]) && (poszcheck == zcoords[i]) && (rendercrystal[i] == 1))
				//			{
				//			rendercrystal[i] = 0;
				//			crystalcount += rand() % 10 + 1;
				//			}
				//		}
				//	}
    //            }
				//else
				//{

				//}
    //        }
    //        
    //        if (i->name == "vending")
    //        {
    //            if (i->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), viewDirection) == true)
    //            {
    //                NearVendingText = true;
    //                if (Application::IsKeyPressed('Q'))
    //                {
    //                    TextTranslate = 100;
    //                    TokenOnScreen = false;
    //                    RenderCoke = true;
    //                    ConsumeCokeText = true;
    //                }

    //                if (Application::IsKeyPressed('U'))
    //                {
    //                    ConsumeCokeText = false;
    //                    RenderCoke = false;
    //                }
    //            }
    //            else
    //            {
    //                NearVendingText = false;
    //                ConsumeCokeText = false;
    //                RenderCoke = false;
    //            }
    //        }

    //        if (i->name == "token")
    //        {

    //            if (i->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), viewDirection) == true)
    //            {
    //                PickUpTokenText = true;

    //                if (Application::IsKeyPressed('Q'))
    //                {
    //                    TokenOnScreen = true;
    //                    TokenTranslate = 10.5;
    //                }
    //            }
    //            else
    //            {
    //                PickUpTokenText = false;
    //            }
    //        }

    //        if (i->name == "counter")
    //        {
    //            if (i->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), viewDirection) == true)
    //            {
    //                testText = true;
    //                if (Application::IsKeyPressed('Y')) YesShowCafeMenu = true;
    //                DisplayCafeMenu = YesShowCafeMenu;
    //            }
    //            else
    //            {
    //                testText = false;
    //                DisplayCafeMenu = false;
    //                YesShowCafeMenu = false;
    //            }
    //        }

    //        // Door Opening & Closing - Don't Touch - Donovan
    //        if (i->name.find("frontGate") != string::npos) // If InteractableOBJ is a frontGate
    //        {
    //            if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), viewDirection)) // If the frontGate is in view
    //            {
    //                gateOpening = true;
    //                doorInteractions(dt, i, frontGateOffset);
    //            }
    //            //else 
    //            //{
    //            //    gateOpening = false;
    //            //    doorClosing(dt, i, frontGateOffset);
    //            //}
    //            //
    //        }
    //        else if (i->name.find("backGate") != string::npos)
    //        {
    //            if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), viewDirection))
    //            {
    //                doorInteractions(dt, i, backGateOffset);
    //            }
    //        }
    //        else if (i->name.find("leftGate") != string::npos)
    //        {
    //            if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), viewDirection))
    //            {
    //                doorInteractions(dt, i, leftGateOffset);
    //            }
    //        }
    //        else if (i->name.find("rightGate") != string::npos)
    //        {
    //            if (i->isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), viewDirection))
    //            {
    //                doorInteractions(dt, i, rightGateOffset);
    //            }   
    //        }

    //        
    //        /*
    //        else if (i->name == "spacesuit")
    //        {
    //        spaceSuitInteractions();
    //        }
    //        else
    //        {
    //        wearSuitText = false;
    //        }
    //        */

    //        if (i->name == "shop")
    //        {
    //            //if (i->isInView(Position(firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z), viewDirection))
    //            //{
    //                if (Application::IsKeyPressed('E'))
    //                {
    //                    askedShipBuild = true;
    //                    askedHull = true;
    //                }
    //            //}

    //        }
    //    }
    //}


    // Ship Creation - Don't Touch - Donovan
    //if (Application::IsKeyPressed('E') && ShipList.size() == 0)
    //{
    //    shipCreation();
    //}

    if (askedShipBuild)
    {
        shopInteractions();
    }

    
	//JUMP
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

void SP2::shopInteractions()
{
    if (askedHull)
    {
        if (Application::IsKeyPressed('1'))
        {
            somePlayer.addPart(LightHull);
            askedHull = false;
            askedWings = true;
        }
        else if (Application::IsKeyPressed('2'))
        {
            somePlayer.addPart(MediumHull);
            askedHull = false;
            askedWings = true;
        }
        else if (Application::IsKeyPressed('3'))
        {
            somePlayer.addPart(LargeHull);
            askedHull = false;
            askedWings = true;
        }
    }

    if (askedWings)
    {
        if (Application::IsKeyPressed('4'))
        {
            somePlayer.addPart(DualWings);
            askedWings = false;
            askedEngine = true;
        }
        else if (Application::IsKeyPressed('5'))
        {
            somePlayer.addPart(QuadWings);
            askedWings = false;
            askedEngine = true;
        }
    }

    if (askedEngine)
    {
        if (Application::IsKeyPressed('6'))
        {
            somePlayer.addPart(G1Engine);
            askedEngine = false; 
            shipCreation();
            askedShipBuild = false;
            shipBuilt = true;
        }
        else if (Application::IsKeyPressed('7'))
        {
            somePlayer.addPart(G2Engine);
            askedEngine = false;
            shipCreation();
            askedShipBuild = false;
            shipBuilt = true;
        }
    }
    

}

void SP2::vendingMachineInteractions()
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

void SP2::tokenInteractions()
{
    PickUpTokenText = true;

    if (Application::IsKeyPressed('Q'))
    {
        TokenOnScreen = true;
        TokenTranslate = 10.5;
    }
}

void SP2::counterInteractions()
{
    testText = true;
    if (Application::IsKeyPressed('Y'))
    {
        MENUBOOL = true;
        YesShowCafeMenu = true;
    }

    if (Application::IsKeyPressed('I'))
    {
        MENUBOOL = false;
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

void SP2::spaceSuitInteractions()
{
    wearSuitText = true;
    if (Application::IsKeyPressed('T'))
    {
        SuitTranslate = -50;
        wearSuit = true;
    }

    if (Application::IsKeyPressed('G'))
    {
        wearSuit = false;
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
