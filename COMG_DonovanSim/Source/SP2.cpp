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
    //Initialize camera settings (Gary's)
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

	LoadMeshes();

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
	NearVendingText = (camera5.position.x > 100 && camera5.position.x < 140 && camera5.position.z > 5 && camera5.position.z < 25);

	rayTracing(InteractablesList);
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
	for (vector<InteractableOBJs>::iterator i = InteractablesList.begin(); i < InteractablesList.end(); i++)
	{
		std::cout << i->isInView(Position(camera5.position.x, camera5.position.y, camera5.position.z), camera5.target) << std::endl;
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
