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

	//Floats
	TokenTranslate = 11;
	TextTranslate = 20;
	TestRotation = 90;

	LoadShaderCodes();
	LoadLights();
	LoadMeshes();

    //variable to rotate geometry
    rotateAngle = 0;
    toggleLight = true;

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
    //Initialize camera settings (Garry's)
    //camera5.Init(Vector3(charPos.x, charPos.y, charPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    //thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), &charPos, 10);

    //Initialize camera settings (Don's)
    camera5.Init(Vector3(startingPos.x, startingPos.y, startingPos.z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    thirdPersonCamera.Init(Vector3(shipStartingPos.x - 30, shipStartingPos.y + 10, shipStartingPos.z - 30), Vector3(0, 1, 0), shipStartingPosPtr, 10);

    // Init Cam Pointer
    camPointer = &camera5;

    // Init Player
    somePlayer.setPlayerStats("TestMan", "Human", 100, *startingPosPtr, camera5); // Name, Race, Money, Pos, camera
	//somePlayer.setPlayerStats("TestMan", "Human", 100, charPos, camera5); // Name, Race, Money, Pos, camera

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

   
    
	TestRotation += float( dt * 100);
    
  
    //VENDING
	if (camera5.position.x > 100 && camera5.position.x < 123 && camera5.position.z > 5 && camera5.position.z < 35)
	{
		NearVendingText = true;
	}
	else
	{
		NearVendingText = false;
	}


	//COLLECT TOKEN
	if (camera5.position.x > 150 && camera5.position.x < 180 && camera5.position.z > 10 && camera5.position.z < 20)
	{
		if (Application::IsKeyPressed('Q'))
		{
			TokenOnScreen = true;
			TokenTranslate = 10.5;
		}
	}

	//INSERT COIN INTO VENDING
	if (camera5.position.x > 100 && camera5.position.x < 123 && camera5.position.z > 5 && camera5.position.z < 35)
	{
		if (Application::IsKeyPressed('Q'))
		{
			TokenOnScreen = false;
			TextTranslate = 100;
			RenderCoke = true;
			ConsumeCokeText = true;
		}
	}

	if (Application::IsKeyPressed('U'))
	{
		ConsumeCokeText = false;
		RenderCoke = false;
	}
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

void SP2::RenderCokeOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderRecRoom()
{
	//SOFA
	modelStack.PushMatrix();
	modelStack.Translate(8, 0, 8);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);
	modelStack.PopMatrix();

	//SPEAKER
	modelStack.PushMatrix();
	modelStack.Translate(10, 0, 10);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPEAKERS], true, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderTradingStation()
{
	//TRADING STATION
	modelStack.PushMatrix();
	modelStack.Translate(-5, 0, 5);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_TRADEPOST], true, toggleLight);
	modelStack.PopMatrix();
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
    //modelStack.PushMatrix();
    //modelStack.Translate(-100, 2, 50);
    //modelStack.Scale(4, 4, 4);
    //RenderMesh(meshList[GEO_MINE], true, toggleLight);
    //modelStack.PopMatrix();

	// POSITION OF X Y Z
	std::ostringstream ss;
	ss.str("");
	ss << "Position: X(" << thirdPersonCamera.GetFocusPoint()->x << ") Y(" << thirdPersonCamera.GetFocusPoint()->y << ") Z(" << thirdPersonCamera.GetFocusPoint()->z << ")";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 1.2f, 3, 4);

	//VENDING TEXT
	if (NearVendingText)
	{

		RenderTextOnScreen(meshList[GEO_TEXT], "Requires token", Color(1, 0, 0), 2, 6, 14);

		RenderTextOnScreen(meshList[GEO_TEXT], "PLEASE INSERT THE TOKEN", Color(1, 0, 0), 2, 6, TextTranslate);
	}

	//COKE TEXT
	if (ConsumeCokeText)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "PRESS U TO DRINK", Color(1, 0, 0), 2, 6, 18);

	}

	if (RenderCoke == true)
	{
		RenderCokeOnScreen(meshList[GEO_COKE], 5, 8, 6);
	}

	//RenderCokeOnScreen(meshList[GEO_COKE], 5, 8, 6);

	if (TokenOnScreen == true)
	{
		RenderTokenOnScreen(meshList[GEO_TOKEN], 5, 8, 6);
	}

//TOKEN
	modelStack.PushMatrix();
	modelStack.Translate(175, TokenTranslate, 30);
	modelStack.Scale(1, 1.5, 1);
	RenderMesh(meshList[GEO_TOKEN], true, toggleLight);
	modelStack.PopMatrix();

	//TEST
	glBlendFunc(1, 1);
	modelStack.PushMatrix();
	modelStack.Translate(150, 13, 10);
	modelStack.Scale(5, 5, 5);
	modelStack.Rotate(TestRotation, 0, 1, 0);
	RenderMesh(meshList[GEO_COKE], true, toggleLight);
	modelStack.PopMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//MOUSE
	RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0, 1, 0), 2, 20, 15);
}

void SP2::Exit()
{
    // Cleanup VBO here
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
