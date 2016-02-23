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


	//JUmp
	acceleration = -1;
	firstvelo = 0;
	secondvelo = 0;
	t = 1;
	distance = 0; 
	firstpos = 0;
	onGround = true;

    gateClosing = false;
    gateOpening = true;

	thirdPersonCamera.SetMouseEnabled(true);

	//Floats

	TokenTranslate = 11;
	TextTranslate = 20;
	TestRotation = 90;
	
	SuitTranslate = 2;

    gateOffset = 0;

	heightOfWall = 12;


	startingCharPos = charPos = { 150, 17, -36 };

	shipStartingPos = shipPos = { 75, 18, 150 };
    shipHorizontalRotateAngle = 0;
    shipVerticalRotateAngle = 0;
    //Initialize camera settings (Gary's)
    //camera5.Init(Vector3(charPos.x, charPos.y, charPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    //thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), &charPos, 10);

    //Initialize camera settings (Don's)
	camera5.Init(Vector3(charPos.x, charPos.y, charPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), &shipPos, 10);

    // Init Cam Pointer
    camPointer = &camera5;

    // Init Player
	//somePlayer.setPlayerStats("TestMan", "Human", 100, playerStartingPos, camera5); // Name, Race, Money, Pos, camera
	somePlayer.setPlayerStats("TestMan", "Human", 100, charPos, camera5); // Name, Race, Money, Pos, camera

    LoadMeshes();

    //camPointer = &thirdPersonCamera;
    //somePlayer.setCameraType("third");

    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
    projectionStack.LoadMatrix(projection);

	thirdPersonCamera.SetCameraDistanceBounds(10, 200);
	thirdPersonCamera.SetCameraDistanceAbsolute(60);

	//Assigning coords to array  
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

    createBoundBox(InteractablesList, BuildingsList);
    interactionCheck(dt, InteractablesList, somePlayer);

	if (!MENUBOOL)
	{
    	if (somePlayer.getCameraType() == "first")
    	{
    	    camera5.Update(dt, InteractablesList, BuildingsList, somePlayer);
    	}
    	else
    	{
    	    thirdPersonCamera.Update(dt, InteractablesList, BuildingsList, somePlayer);
    	}
    }
    
	TestRotation += float(dt * 100);


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
            }
        }
    }

	//Interactions with OBJs.
	if (camPointer == &camera5)
	{
		Vector3 viewDirection = (camera5.target - camera5.position).Normalized();
		for (vector<InteractableOBJs>::iterator i = InteractablesList.begin(); i < InteractablesList.end(); i++)
		{
			if (i->name == "crystal")
			{
				if (i->isInView(Position(camera5.position.x, camera5.position.y, camera5.position.z), viewDirection) == true)
				{
					CrystalText = true;
					posxcheck = i->pos.x; 
					poszcheck = i->pos.z;
					if (Application::IsKeyPressed('M'))
					{
						for (int i = 0; i < CrystalNo; i++)
						{
							if (posxcheck == xcoords[i])
							{
								for (int i = 0; i < CrystalNo; i++)
								{
									if (poszcheck == zcoords[i])
									{
										rendercrystal[i] = 0;
										crystalcount += 1;
                                        
									}
								}
							}
						}
					}
				}			
			}
			else if (i->name == "vending")
			{
				if (i->isInView(Position(camera5.position.x, camera5.position.y, camera5.position.z), viewDirection) == true)
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

			else if (i->name == "token")
			{

				if (i->isInView(Position(camera5.position.x, camera5.position.y, camera5.position.z), viewDirection) == true)
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

			else if (i->name == "counter")
			{
				if (i->isInView(Position(camera5.position.x, camera5.position.y, camera5.position.z), viewDirection) == true)
				{
					testText = true;
					if (Application::IsKeyPressed('Y')) YesShowCafeMenu = true;
					DisplayCafeMenu = YesShowCafeMenu;
				}
				else
				{
					testText = false;
					DisplayCafeMenu = false;
					YesShowCafeMenu = false;
				}
			}
			/*
			else if (i->name == "spacesuit")
            {
                spaceSuitInteractions();
            }
            else
            {
                wearSuitText = false;
            }
			*/
		}
	}

    // Ship Animation
    if (thirdPersonCamera.yawingLeft == true /*&& shipHorizontalRotateAngle >= -20*/) { shipHorizontalRotateAngle += (float)(30 * dt); }
    if (thirdPersonCamera.yawingRight == true /*&& shipHorizontalRotateAngle <= 20*/) { shipHorizontalRotateAngle -= (float)(30 * dt); }
    if (thirdPersonCamera.pitchingDown == true /*&& shipVerticalRotateAngle >= -20*/) { shipVerticalRotateAngle += (float)(30 * dt); }
    if (thirdPersonCamera.pitchingUp == true /*&& shipHorizontalRotateAngle <= 20*/) { shipVerticalRotateAngle -= (float)(30 * dt); }
    
    // Reset Ship to original orientation
    /*if (thirdPersonCamera.yawingRight == false )
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

    }*/

	//Gate Interaction
    //string gate = "Gate";
    //if (InteractablesList[i].isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view) == true && InteractablesList[i].name.find(gate) != string::npos)
    ////if (somePlayer.pos.x < InteractablesList[i].pos.x + 20 && somePlayer.pos.x > InteractablesList[i].pos.x - 20 && somePlayer.pos.z < InteractablesList[i].pos.z + 20 && somePlayer.pos.z > InteractablesList[i].pos.z - 20)
    //{
    //    gateOpening = true;
    //}
    //else
    //{
    //    gateOpening = false;
    //}

    //// Moving Gate
    //if (gateOpening == true)
    //{
    //    if (gateOffset <= 10)
    //    {
    //        gateOffset += (float)(dt);
    //        InteractablesList[i].pos.y += gateOffset;
    //    }

    //}

    //if (gateOpening == false) 
    //{
    //    if (gateOffset > 0)
    //    {
    //        gateOffset -= (float)(dt);
    //        InteractablesList[i].pos.y -= gateOffset;
    //    }
    //}
    

    // Ship Creation
    if (Application::IsKeyPressed('E') && ShipList.size() == 0)
    {
        // Space Ship Template
		//WHY SHOULD YOU LOAD A MESH IN THE MIDDLE OF THE PROGRAM? WHO WAS DOING IT? (comment by Gary Goh)
        //meshList[GEO_SHIP] = MeshBuilder::GenerateOBJ("ship", "OBJ//V_Art Spaceship.obj");

        Ship someShip = Ship("ship", meshList[GEO_SHIP]->maxPos, meshList[GEO_SHIP]->minPos, shipStartingPos, 4, 0, Vector3(0, 0, 0));
        someShip.setRequirements(50, 500);

        shipTemplatePtr = &someShip;

        ShipList.push_back(ShipBuilder.createShip(shipTemplatePtr, LightHull, QaudWings, G1Engine));

        // Load Meshes for specific ship parts
        for (vector<Ship>::iterator i = ShipList.begin(); i < ShipList.end(); ++i)
        {
            if (i->hullType == "LightHull")
            {
                meshList[GEO_HULL] = MeshBuilder::GenerateOBJ("shipHull", "OBJ//Ship Models//LightHull.obj");
            }
            else if (i->hullType == "MediumHull")
            {

            }
            else if (i->hullType == "LargeHull")
            {

            }

            if (i->wingType == "DualWings")
            {
                meshList[GEO_WINGS] = MeshBuilder::GenerateOBJ("shipWings", "OBJ//Ship Models//DualWings.obj");
            }
            else if (i->wingType == "QuadWings")
            {
                meshList[GEO_WINGS] = MeshBuilder::GenerateOBJ("shipWings", "OBJ//Ship Models//QuadWings.obj");
            }

            if (i->engineType == "G1Engine")
            {
                meshList[GEO_ENGINE] = MeshBuilder::GenerateOBJ("shipEngine", "OBJ//Ship Models//G1Engine.obj");
            }
            else if (i->engineType == "G2Engine")
            {
                meshList[GEO_ENGINE] = MeshBuilder::GenerateOBJ("shipEngine", "OBJ//Ship Models//G2Engine.obj");
            }
        }

    }
    
	//JUMP
	if (Application::IsKeyPressed(VK_SPACE) &&  (onGround == true)) //s = ut + 0.5 at^2
	{ 
		firstpos = camera5.position.y;
		firstvelo = 50;
		onGround = false;
	}
	if (onGround == false)
	{
		secondvelo = firstvelo + (acceleration * t * t); // a = -2 , t = 1 
		firstvelo = secondvelo;

		distance = ((firstvelo * t) + (0.5 * acceleration * t * t));
		camera5.position.y += distance * dt;
		if (firstpos >= camera5.position.y)
		{
			camera5.position.y = firstpos;
			onGround = true;
		}
	}
}

void SP2::interactionCheck(double dt, vector<InteractableOBJs>&InteractablesList, Player &somePlayer)
{
	Vector3 view = (camera5.target - camera5.position).Normalized();
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
                    camPointer = &camera5;
                    somePlayer.setCameraType("first");
                }
            }
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

void SP2::createBoundBox(vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList)
{
	Position maxPos;
	Position minPos;

	Position cameraPos;

	if (somePlayer.getCameraType() == "first")
	{
		Vector3 view = (camera5.target - camera5.position).Normalized();
		cameraPos.x = camera5.position.x + view.x;
		cameraPos.y = camera5.position.y + view.y;
		cameraPos.z = camera5.position.z + view.z;
	}
	else
	{
		Vector3 view = (thirdPersonCamera.target - thirdPersonCamera.position).Normalized();
		cameraPos.x = thirdPersonCamera.GetFocusPoint()->x + view.x;
		cameraPos.y = thirdPersonCamera.GetFocusPoint()->y + view.y;
		cameraPos.z = thirdPersonCamera.GetFocusPoint()->z + view.z;
	}


	for (int i = 0; i < InteractablesList.size(); ++i)
	{
		maxPos.x = InteractablesList[i].maxPos.x;
		maxPos.y = InteractablesList[i].maxPos.y;
		maxPos.z = InteractablesList[i].maxPos.z;

		minPos.x = InteractablesList[i].minPos.x;
		minPos.y = InteractablesList[i].minPos.y;
		minPos.z = InteractablesList[i].minPos.z;

		// Scaling
		maxPos.x = maxPos.x * InteractablesList[i].scaleOffSet;
		maxPos.y = maxPos.y * InteractablesList[i].scaleOffSet;
		maxPos.z = maxPos.z * InteractablesList[i].scaleOffSet;

		minPos.x = minPos.x * InteractablesList[i].scaleOffSet;
		minPos.y = minPos.y * InteractablesList[i].scaleOffSet;
		minPos.z = minPos.z * InteractablesList[i].scaleOffSet;

		// Rotation
		Mtx44 rotation;
		Vector3 tempMax;
		Vector3 tempMin;

		tempMax.x = maxPos.x;
		tempMax.y = maxPos.y;
		tempMax.z = maxPos.z;

		tempMin.x = minPos.x;
		tempMin.y = minPos.y;
		tempMin.z = minPos.z;
		if (InteractablesList[i].rotateAxis.x == 1)
		{
			rotation.SetToRotation(InteractablesList[i].rotateAngle, 1, 0, 0);
			tempMax = rotation * tempMax;
			tempMin = rotation * tempMin;
		}
		if (InteractablesList[i].rotateAxis.y == 1)
		{
			rotation.SetToRotation(InteractablesList[i].rotateAngle, 0, 1, 0);
			tempMax = rotation * tempMax;
			tempMin = rotation * tempMin;
		}
		if (InteractablesList[i].rotateAxis.z == 1)
		{
			rotation.SetToRotation(InteractablesList[i].rotateAngle, 0, 0, 1);
			tempMax = rotation * tempMax;
			tempMin = rotation * tempMin;
		}

		maxPos.x = tempMax.x;
		maxPos.y = tempMax.y;
		maxPos.z = tempMax.z;

		minPos.x = tempMin.x;
		minPos.y = tempMin.y;
		minPos.z = tempMin.z;

		// Translating
		maxPos.x += InteractablesList[i].pos.x;
		maxPos.y += InteractablesList[i].pos.y;
		maxPos.z += InteractablesList[i].pos.z;

		minPos.x += InteractablesList[i].pos.x;
		minPos.y += InteractablesList[i].pos.y;
		minPos.z += InteractablesList[i].pos.z;

		if ((cameraPos.x > maxPos.x || cameraPos.x < minPos.x) || (cameraPos.y > maxPos.y || cameraPos.y < minPos.y) || (cameraPos.z > maxPos.z || cameraPos.z < minPos.z))
		{
			InteractablesList[i].canMove = true;
		}
		else
		{
			InteractablesList[i].canMove = false;
		}
	}


	for (int i = 0; i < BuildingsList.size(); ++i)
	{
		maxPos.x = BuildingsList[i].maxPos.x;
		maxPos.y = BuildingsList[i].maxPos.y;
		maxPos.z = BuildingsList[i].maxPos.z;

		minPos.x = BuildingsList[i].minPos.x;
		minPos.y = BuildingsList[i].minPos.y;
		minPos.z = BuildingsList[i].minPos.z;

		// Scaling
		maxPos.x = maxPos.x * BuildingsList[i].scaleOffSet;
		maxPos.y = maxPos.y * BuildingsList[i].scaleOffSet;
		maxPos.z = maxPos.z * BuildingsList[i].scaleOffSet;

		minPos.x = minPos.x * BuildingsList[i].scaleOffSet;
		minPos.y = minPos.y * BuildingsList[i].scaleOffSet;
		minPos.z = minPos.z * BuildingsList[i].scaleOffSet;

		// Rotation
		Mtx44 rotation;
		Vector3 tempMax;
		Vector3 tempMin;

		tempMax.x = maxPos.x;
		tempMax.y = maxPos.y;
		tempMax.z = maxPos.z;

		tempMin.x = minPos.x;
		tempMin.y = minPos.y;
		tempMin.z = minPos.z;
		if (BuildingsList[i].rotateAxis.x == 1)
		{
			rotation.SetToRotation(BuildingsList[i].rotateAngle, 1, 0, 0);
			tempMax = rotation * tempMax;
			tempMin = rotation * tempMin;
		}
		if (BuildingsList[i].rotateAxis.y == 1)
		{
			rotation.SetToRotation(BuildingsList[i].rotateAngle, 0, 1, 0);
			tempMax = rotation * tempMax;
			tempMin = rotation * tempMin;
		}
		if (BuildingsList[i].rotateAxis.z == 1)
		{
			rotation.SetToRotation(BuildingsList[i].rotateAngle, 0, 0, 1);
			tempMax = rotation * tempMax;
			tempMin = rotation * tempMin;
		}

		maxPos.x = tempMax.x;
		maxPos.y = tempMax.y;
		maxPos.z = tempMax.z;

		minPos.x = tempMin.x;
		minPos.y = tempMin.y;
		minPos.z = tempMin.z;

		// Translating
		maxPos.x += BuildingsList[i].pos.x;
		maxPos.y += BuildingsList[i].pos.y;
		maxPos.z += BuildingsList[i].pos.z;

		minPos.x += BuildingsList[i].pos.x;
		minPos.y += BuildingsList[i].pos.y;
		minPos.z += BuildingsList[i].pos.z;

		if ((cameraPos.x > maxPos.x || cameraPos.x < minPos.x) || (cameraPos.y > maxPos.y || cameraPos.y < minPos.y) || (cameraPos.z > maxPos.z || cameraPos.z < minPos.z))
		{
			BuildingsList[i].canMove = true;
		}
		else
		{
			BuildingsList[i].canMove = false;
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
