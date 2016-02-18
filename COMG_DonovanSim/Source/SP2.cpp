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

	//Floats
	TokenTranslate = 12;

	LoadShaderCodes();
	LoadLights();
	LoadMeshes();

    //variable to rotate geometry
    rotateAngle = 0;
    toggleLight = true;

    //Position maxPos = Position(0, 0, 0); // Vector for max pos
    //Position minPos = Position(0, 0, 0); // Vector for min pos

    maxPtr = 0;
    minPtr = 0;

	heightOfWall = 12;


    // Starting Pos Of Player
    Position startingPos;
    Position * startingPosPtr = &startingPos;
    startingPos.Set(150, 17, -36);

    // Starting Pos of Ship
    Position shipStartingPos;
    Position * shipStartingPosPtr = &shipStartingPos;
    shipStartingPos.Set(200, 2, 100);

	charPos = { 150, 17, -36 };
    //Initialize camera settings
    camera5.Init(Vector3(charPos.x, charPos.y, charPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), &charPos, 10);

    //Initialize camera settings
    camera5.Init(Vector3(startingPos.x, startingPos.y, startingPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    thirdPersonCamera.Init(Vector3(shipStartingPos.x - 30, shipStartingPos.y + 10, shipStartingPos.z - 30), Vector3(0, 1, 0), shipStartingPosPtr, 10);

    // Init Cam Pointer
    camPointer = &camera5;

    // Init Player
    somePlayer.setPlayerStats("TestMan", "Human", 100, *startingPosPtr, camera5); // Name, Race, Money, Pos, camera
	somePlayer.setPlayerStats("TestMan", "Human", 100, charPos, camera5); // Name, Race, Money, Pos, camera



	//Text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//5.tga");



	//AXES
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);



	//LIGHTBALL
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1));




	//SKYBOX
    meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
    meshList[GEO_QUAD]->textureID = LoadTGA("Image//spaceground.tga");

    meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
    meshList[GEO_FRONT]->textureID = LoadTGA("Image//purplenebula_ft.tga");

    meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
    meshList[GEO_BACK]->textureID = LoadTGA("Image//purplenebula_bk.tga");

    meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
    meshList[GEO_TOP]->textureID = LoadTGA("Image//purplenebula_up.tga");

    meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
    meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//purplenebula_dn.tga");

    meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
    meshList[GEO_LEFT]->textureID = LoadTGA("Image//purplenebula_lf.tga");

    meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
    meshList[GEO_RIGHT]->textureID = LoadTGA("Image//purplenebula_rt.tga");
	



	//WALLS
    meshList[GEO_WALL] = MeshBuilder::GenerateOBJ("wall", "OBJ//TestWall2.obj");
    meshList[GEO_WALL]->textureID = LoadTGA("Image//TestWall.tga");

    meshList[GEO_WALL2] = MeshBuilder::GenerateOBJ("wall2", "OBJ//TestWall.obj");
    meshList[GEO_WALL2]->textureID = LoadTGA("Image//TestWall.tga");

    meshList[GEO_GATETOP] = MeshBuilder::GenerateOBJ("wall", "OBJ//gateTop.obj");
    meshList[GEO_GATETOP]->textureID = LoadTGA("Image//gateTopUV.tga");

    meshList[GEO_GATE] = MeshBuilder::GenerateOBJ("wall", "OBJ//gate.obj");
    meshList[GEO_GATE]->textureID = LoadTGA("Image//gateUV.tga");




	//GROUND MESH
    meshList[GEO_GROUND] = MeshBuilder::GenerateQuad("ground", Color(1, 1, 1));
    meshList[GEO_GROUND]->textureID = LoadTGA("Image//castleFloor.tga");

    meshList[GEO_GROUND]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_GROUND]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_GROUND]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_GROUND]->material.kShininess = 1;



	//TRADE POST
	meshList[GEO_TRADEPOST] = MeshBuilder::GenerateOBJ("Tradepost", "OBJ//TradingPost.obj");
	meshList[GEO_TRADEPOST]->textureID = LoadTGA("Image//TradingPostTexture2.tga");


	//init collision, then render room
    
	//CAFE ROOM
    initRoomTemplate(Position(0, 2, 0));            //Collision

	//COUNTER
	meshList[GEO_COUNTER] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Counter.obj");
	meshList[GEO_COUNTER]->textureID = LoadTGA("Image//Counter.tga");

	//FRIDGE
	meshList[GEO_FRIDGE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Fridge.obj");
	meshList[GEO_FRIDGE]->textureID = LoadTGA("Image//Fridge.tga");

	//CHEF
	meshList[GEO_CHEF] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Chef.obj");
	meshList[GEO_CHEF]->textureID = LoadTGA("Image//Chef.tga");


	//TABLE
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Table.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//Table.tga");

	//VENDING
	meshList[GEO_VENDING] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Vending.obj");
	meshList[GEO_VENDING]->textureID = LoadTGA("Image//Vending.tga");

	//CHAIR
	meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Chair.obj");
	meshList[GEO_CHAIR]->textureID = LoadTGA("Image//Chair.tga");

	//Token
	meshList[GEO_TOKEN] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Token.obj");
	meshList[GEO_TOKEN]->textureID = LoadTGA("Image//Token.tga");




	//Recreational Room
	initRoomTemplate(Position(150, 2, 0));          //Collision

	//SPEAKERS
	meshList[GEO_SPEAKERS] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//RecRoomSpeakers.obj");
	meshList[GEO_SPEAKERS]->textureID = LoadTGA("Image//RecRoomSpeakers.tga");

	//SOFA
	meshList[GEO_SOFA] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//sofa.obj");
	meshList[GEO_SOFA]->textureID = LoadTGA("Image//sofa.tga");

    // Space Ship
    meshList[GEO_SHIP] = MeshBuilder::GenerateOBJ("ship", "OBJ//V_Art Spaceship.obj");
    Ship someShip = Ship("ship", *shipStartingPosPtr);
    ShipList.push_back(someShip);

    meshList[GEO_MINE] = MeshBuilder::GenerateOBJ("ship", "OBJ//mine.obj");
    meshList[GEO_MINE]->textureID = LoadTGA("Image//mineUV.tga");

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

    if (somePlayer.getCameraType() == "first")
    {
        camera5.Update(dt, InteractablesList, BuildingsList, somePlayer);
    }
    else
    {
        thirdPersonCamera.Update(dt, InteractablesList, BuildingsList, somePlayer);
    }

    // TEST FOR BULLET COLLISION
    //if (Application::IsKeyPressed('B'))
    //{
    //    rayTracing(InteractablesList);
    //}
  
    //VENDING
	NearVendingText = (camera5.position.x > 100 && camera5.position.x < 140 && camera5.position.z > 5 && camera5.position.z < 25);

}

void SP2::interactionCheck(double dt, vector<InteractableOBJs>&InteractablesList, Player &somePlayer)
{
	for (vector<InteractableOBJs>::iterator i = InteractablesList.begin(); i < InteractablesList.end(); ++i)
    {
        if (i->name == "ship"/* && somePlayer.pos.x < i->maxPos.x + 3 && somePlayer.pos.x > i->minPos.x - 3 && somePlayer.pos.z < i->maxPos.z + 3 && somePlayer.pos.z > i->minPos.z - 3*/)
        {
            if (Application::IsKeyPressed('E'))
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

		std::cout << i->isInView(*thirdPersonCamera.GetFocusPoint(), thirdPersonCamera.camDirection) << std::endl;
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



void SP2::rayTracing(vector<InteractableOBJs>&InteractablesList)
{
    Vector3 view = (camera5.target - camera5.position).Normalized();

    for (size_t i = 0; i < InteractablesList.size(); ++i)
    {
        Vector3 objPos = (InteractablesList[i].pos.x, InteractablesList[i].pos.y, InteractablesList[i].pos.z);
        //Vector3 viewNormal = view.Normalized();

        //distance = objPos.Dot(viewNormal);

        Vector3 projection = (objPos.Dot(view.Normalized()) * view.Normalized());

        Vector3 distVec = -objPos + projection;

        if (distVec.Length() < 1)
        {
            std::cout << "HIT" << std::endl;
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


	//RENDER LIGHTBALL
    modelStack.PushMatrix();
    modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(charPos.x, charPos.y, charPos.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
	modelStack.PopMatrix();


	//RENDER SKYBOX
    RenderSkybox();


	//RENDER CAFE
	RenderCafeRoom();

	//GROUND MESH
    modelStack.PushMatrix();
    modelStack.Scale(1000, 1000, 1000);
    RenderMesh(meshList[GEO_QUAD], true, toggleLight);
    modelStack.PopMatrix();



	//TRADING STATION
	//modelStack.PushMatrix();
	//RenderRoomTemplate(Position(100, 2, 0));
	//modelStack.Translate(100, 2, 0);
	//RenderTradingStation();
	//modelStack.PopMatrix();
	
    //RENDER ROOM (WALLS)
    RenderRoomTemplate(Position(0, 2, 0));     //RECREATIONAL ROOM


	//RENDER ROOM (WALLS)
	RenderRoomTemplate(Position(150, 2, 0));   //CAFE



	//INTERACTIONS

    // SpaceShip
    modelStack.PushMatrix();
    modelStack.Translate(thirdPersonCamera.GetFocusPoint()->x, thirdPersonCamera.GetFocusPoint()->y, thirdPersonCamera.GetFocusPoint()->z);
    modelStack.Scale(4, 4, 4);
    RenderMesh(meshList[GEO_SHIP], true, toggleLight);
    modelStack.PopMatrix();

    // Mine
    modelStack.PushMatrix();
    modelStack.Translate(-100, 2, 50);
    modelStack.Scale(4, 4, 4);
    RenderMesh(meshList[GEO_MINE], true, toggleLight);
    modelStack.PopMatrix();

	//POSITION OF X Y Z
	std::ostringstream ss;
	ss.str("");
	ss << "Position: X(" << thirdPersonCamera.GetFocusPoint()->x << ") Y(" << thirdPersonCamera.GetFocusPoint()->y << ") Z(" << thirdPersonCamera.GetFocusPoint()->z << ")";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 1.2f, 3, 4);

	//VENDING TEXT
	if (NearVendingText)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Requires token", Color(1, 0, 0), 2, 6, 14);
	}

	if (TokenOnScreen == true)
	{
		RenderTokenOnScreen(meshList[GEO_TOKEN], 5, 8, 6);
	}
}

void SP2::Exit()
{
    // Cleanup VBO here
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
