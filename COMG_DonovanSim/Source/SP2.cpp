#include "SP2.h"

SP2::SP2()
{
}

SP2::~SP2()
{

}

void SP2::Init()
{
    //Bools
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


	NearCrystal = false;
	HoldCrystal = false;
	int crystals = 0;

    gateClosing = false;
    gateOpening = true;

	//Floats
	TokenTranslate = 11;
	TextTranslate = 20;
	TestRotation = 90;
	SuitTranslate = 2;

    gateOffset = 0;

	LoadShaderCodes();
	LoadLights();


    //variable to rotate geometry
    rotateAngle = 0;
    toggleLight = true;

	heightOfWall = 12;


    // Starting Pos Of Player
	startingPos.Set(250, 17, 150);
    startingPosPtr = &startingPos;

    // Starting Pos of Ship
    shipStartingPos.Set(180, 18, 300);
    shipStartingPosPtr = &shipStartingPos;
    shipHorizontalRotateAngle = 0;
    shipVerticalRotateAngle = 0;

	charPos = { 150, 17, -36 };
    //Initialize camera settings (Gary's)
    //camera5.Init(Vector3(charPos.x, charPos.y, charPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    //thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), &charPos, 10);

    //Initialize camera settings (Don's)
    camera5.Init(Vector3(startingPos.x, startingPos.y, startingPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), shipStartingPosPtr, 25);

    // Init Cam Pointer
    camPointer = &camera5;

    // Init Player
    somePlayer.setPlayerStats("TestMan", "Human", 100, *startingPosPtr, camera5); // Name, Race, Money, Pos, camera
	//somePlayer.setPlayerStats("TestMan", "Human", 100, charPos, camera5); // Name, Race, Money, Pos, camera

    LoadMeshes();

    //camPointer = &thirdPersonCamera;
    //somePlayer.setCameraType("third");

    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
    projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
float FramesPerSecond = 0;

void SP2::Update(double dt)
{
    FramesPerSecond = 1 / dt;

	ReadKeyPresses();

    createBoundBox(InteractablesList, BuildingsList);
    interactionCheck(dt, InteractablesList, somePlayer);

	if (MENUBOOL == false)
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
   
    
	TestRotation += 0.001f;
    

	//INTERACTABLEOBJS DECTECTION
	Vector3 view = (camera5.target - camera5.position).Normalized();


	//VENDING MACHINE
	for (int i = 0; InteractablesList.size() > i; i++)
	{
		if (InteractablesList[i].name == "vending")
		{

			if (InteractablesList[i].isInView(Position(camera5.position.x, camera5.position.y, camera5.position.z), view) == true) // move up
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
        if (InteractablesList[i].name == "token")
        {

            if (InteractablesList[i].isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view))
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
        if (InteractablesList[i].name == "counter")
        {

            if (InteractablesList[i].isInView(Position(camera5.position.x, camera5.position.y, camera5.position.z), view) == true)
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
            else
            {
                testText = false;
                DisplayCafeMenu = false;
                YesShowCafeMenu = false;
            }
        }




        //SPACESUIT
        if (InteractablesList[i].name == "spacesuit")
        {

            if (InteractablesList[i].isInView(Position(camera5.position.x, camera5.position.y, camera5.position.z), view) == true)
            {
                wearSuitText = true;
                if (Application::IsKeyPressed('T'))
                {
                    SuitTranslate = -50;
                    wearSuit = true;
                }
            }
            else
            {
                wearSuitText = false;

            }

            if (Application::IsKeyPressed('G'))
            {
                wearSuit = false;
            }
        }
        //Gate Interaction
        string gate = "Gate";
        if (InteractablesList[i].isInView(Position(somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z), view) == true && InteractablesList[i].name.find(gate) != string::npos)
        //if (somePlayer.pos.x < InteractablesList[i].pos.x + 20 && somePlayer.pos.x > InteractablesList[i].pos.x - 20 && somePlayer.pos.z < InteractablesList[i].pos.z + 20 && somePlayer.pos.z > InteractablesList[i].pos.z - 20)
        {
            gateOpening = true;
        }
        else
        {
            gateOpening = false;
        }

        // Moving Gate
        if (gateOpening == true)
        {
            if (gateOffset <= 10)
            {
                gateOffset += (float)(dt);
                InteractablesList[i].pos.y += gateOffset;
            }

        }

        if (gateOpening == false)
        {
            if (gateOffset > 0)
            {
                gateOffset -= (float)(dt);
                InteractablesList[i].pos.y -= gateOffset;
            }
        }
        
            
	

		
	}



    // Ship Animation
    if (thirdPersonCamera.yawingLeft == true && shipHorizontalRotateAngle >= -90) { shipHorizontalRotateAngle += (float)(10 * dt); }
    if (thirdPersonCamera.yawingRight == true && shipHorizontalRotateAngle <= 90) { shipHorizontalRotateAngle -= (float)(10 * dt); }
    if (thirdPersonCamera.pitchingDown == true && shipVerticalRotateAngle >= -90) { shipVerticalRotateAngle += (float)(10 * dt); }
    if (thirdPersonCamera.pitchingUp == true && shipHorizontalRotateAngle <= 90) { shipVerticalRotateAngle -= (float)(10 * dt); }
    
    // Reset Ship to original orientation
    if (thirdPersonCamera.yawingRight == false )
    {
        if (shipHorizontalRotateAngle >= -90 && shipHorizontalRotateAngle < 0)
        {
            shipHorizontalRotateAngle += (float)(2 * dt);
        }
    }

    if (thirdPersonCamera.yawingLeft == false)
    {
        if (shipHorizontalRotateAngle <= 90 && shipHorizontalRotateAngle > 0)
        {
            shipHorizontalRotateAngle -= (float)(2 * dt);
        }

    }

    if (thirdPersonCamera.pitchingDown == false)
    {
        if (shipVerticalRotateAngle >= -90 && shipVerticalRotateAngle < 0)
        {
            shipVerticalRotateAngle += (float)(2 * dt);
        }
    }

    if (thirdPersonCamera.pitchingUp == false)
    {
        if (shipVerticalRotateAngle <= 90 && shipVerticalRotateAngle > 0)
        {
            shipVerticalRotateAngle -= (float)(2 * dt);
        }

    }

    // Ship Creation
    if (Application::IsKeyPressed('E'))
    {
        // Space Ship Template
        meshList[GEO_SHIP] = MeshBuilder::GenerateOBJ("ship", "OBJ//V_Art Spaceship.obj");
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
	if (isFalling == true)
	{
		camera5.position.y -= 20 * dt; // "gravity" when falling , modify this value to change how fast player falls 
	}
	if (camera5.position.y != 17)
	{
		isFalling = true; //sets falling state to true once player is off the ground 
	}
	if (camera5.position.y <= 17)
	{
		isFalling = false; //sets falling state to false once player is on the ground  
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		camera5.position.y += moving * dt;
		moving -= 10;  // modify this value to change how long player can jump  
		if (moving < 0)
		{
			moving = 0;
		}
	}
	if (isFalling == false)
	{
		moving = 100;  // resets gravity once player hits the ground
	}

	//Mining   
	if ((camera5.position.x <= -80 && camera5.position.x >= -120) && (camera5.position.z <= -80 && camera5.position.z >= -120))
	{
		NearCrystal = true;
		if (Application::IsKeyPressed('O'))
		{
			HoldCrystal = true;
		}
	}
	else
	{
		NearCrystal = false;
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
