#include "SP2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Utility.h"
#include "LoadTGA.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "timer.h"
#include <sstream>

SP2::SP2()
{
}

SP2::~SP2()
{

}

void SP2::Init()
{
    // Init VBO here

    // Set background color to dark blue
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

    //Enable depth buffer and depth testing
    glEnable(GL_DEPTH_TEST);

    //Enable back face culling
    glEnable(GL_CULL_FACE);

    //Default to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //Shaders
    m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Mapping variables to tell gpu what is what
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
    m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
    m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
    m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
    m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
    m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	for (size_t S = 0; S < numLights; S++)
	{
		std::string baseString = "lights[" + std::to_string(S);

		static vector<std::string> endings =
		{
			"].position_cameraspace",
			"].color",
			"].power",
			"].kC",
			"].kL",
			"].kQ",
			"].type",
			"].spotDirection",
			"].cosCutoff",
			"].cosInner",
			"].exponent"
		};

		vector<std::string>::iterator i = endings.begin();

		lightUniforms[S][UL_POSITION] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_COLOR] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_POWER] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_KC] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_KL] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_KQ] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_TYPE] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_SPOTDIRECTION] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_COSCUTOFF] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_COSINNER] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_EXPONENT] = glGetUniformLocation(m_programID, (baseString + *i).c_str());
	}

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

    // Get a handle for our "colorTexture" uniform
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Get a handle for our "textColor" uniform
    m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
    m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(-60, 12, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.0f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.0f;
	light[0].spotDirection.Set(0.2f, 1.0f, 0.2f);

	light[1].type = Light::LIGHT_SPOT;
	light[1].position.Set(0, 10, 0);
	light[1].color.Set(0, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.0f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.0f;
	light[1].spotDirection.Set(-0.2f, 1.0f, -0.2f);

	light[2].type = Light::LIGHT_SPOT;
	light[2].position.Set(3, 10, 0);
	light[2].color.Set(1, 0, 0);
	light[2].power = 1;
	light[2].kC = 1.0f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.0f;
	light[2].spotDirection.Set(-0.2f, 1.0f, 0);

	glUniform1i(m_parameters[U_NUMLIGHTS], numLights);

	for (size_t S = 0; S < numLights; S++)
	{
		glUniform1i(lightUniforms[S][UL_TYPE], light[S].type);
		glUniform3fv(lightUniforms[S][UL_COLOR], 1, &light[S].color.r);
		glUniform1f(lightUniforms[S][UL_POWER], light[S].power);
		glUniform1f(lightUniforms[S][UL_KC], light[S].kC);
		glUniform1f(lightUniforms[S][UL_KL], light[S].kL);
		glUniform1f(lightUniforms[S][UL_KQ], light[S].kQ);
		glUniform1f(lightUniforms[S][UL_COSCUTOFF], light[S].cosCutoff);
		glUniform1f(lightUniforms[S][UL_COSINNER], light[S].cosInner);
		glUniform1f(lightUniforms[S][UL_EXPONENT], light[S].exponent);
	}

    // Make sure you pass uniform parameters after glUseProgram()
    glUniform1i(m_parameters[U_NUMLIGHTS], numLights);

    //variable to rotate geometry
    rotateAngle = 0;
    toggleLight = true;

    Position maxPos = Position(0, 0, 0); // Vector for max pos
    Position minPos = Position(0, 0, 0); // Vector for min pos

    maxPtr = 0;
    minPtr = 0;

    Position * startingPos = new Position(0,0,0);
    startingPos->Set(20, 4, -8);

	charPos = { 4, 0, 0 };
    //Initialize camera settings
    camera5.Init(Vector3(startingPos->x, startingPos->y, startingPos->z), Vector3(1, 1, 1), Vector3(0, 1, 0));
    thirdPersonCamera.Init(Vector3(10, 8, -5), Vector3(0, 1, 0), startingPos, 10);

    // Init Cam Pointer
    camPointer = &camera5;

    // Init Player
    somePlayer.setPlayerStats("TestMan", "Human", 100, *startingPos, camera5); // Name, Race, Money, Pos, camera

	//Text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//5.tga");


	//AXES
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1));

	meshList[GEO_WALL] = MeshBuilder::GenerateOBJ("wall", "OBJ//castleWall.obj");
	meshList[GEO_WALL]->textureID = LoadTGA("Image//wallUV.tga");

	meshList[GEO_WALL]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
	meshList[GEO_WALL]->material.kDiffuse.Set(0.6, 0.6, 0.6);
	meshList[GEO_WALL]->material.kSpecular.Set(0.4, 0.4, 0.4);
	meshList[GEO_WALL]->material.kShininess = 10;


	//SKYBOX
    meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_QUAD]->textureID = LoadTGA("Image//spaceground.tga");

    meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_FRONT]->textureID = LoadTGA("Image//spacefront.tga");

    meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_BACK]->textureID = LoadTGA("Image//spaceback.tga");

    meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_TOP]->textureID = LoadTGA("Image//spacetop.tga");

    meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//spacebottom.tga");

    meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_LEFT]->textureID = LoadTGA("Image//spaceleft.tga");

    meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_RIGHT]->textureID = LoadTGA("Image//spaceright.tga");
	
    meshList[GEO_WALL] = MeshBuilder::GenerateOBJ("wall", "OBJ//castleWall.obj");
    meshList[GEO_WALL]->textureID = LoadTGA("Image//wallUV.tga");

    meshList[GEO_WALL2] = MeshBuilder::GenerateOBJ("wall2", "OBJ//castleWall2.obj");
    meshList[GEO_WALL2]->textureID = LoadTGA("Image//wallUV.tga");

    meshList[GEO_GATETOP] = MeshBuilder::GenerateOBJ("wall", "OBJ//gateTop.obj");
    meshList[GEO_GATETOP]->textureID = LoadTGA("Image//gateTopUV.tga");

    meshList[GEO_GATE] = MeshBuilder::GenerateOBJ("wall", "OBJ//gate.obj");
    meshList[GEO_GATE]->textureID = LoadTGA("Image//gateUV.tga");

	//GROUND MESH
    meshList[GEO_GROUND] = MeshBuilder::GenerateQuad("ground", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_GROUND]->textureID = LoadTGA("Image//castleFloor.tga");

    meshList[GEO_GROUND]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_GROUND]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_GROUND]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_GROUND]->material.kShininess = 1;

    // Collision 
    //initRoom(Position(20, 2, 0));

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

    if (Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if (Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Application::IsKeyPressed('A'))
	{
		charPos.x -= (float)dt * 50;
	}

    createBoundBox(InteractablesList, BuildingsList);





    rotateAngle += (float)(15 * dt);

    if (Application::IsKeyPressed('I'))
    {
        light[0].position.z -= (float)(10 * dt);
    }
    if (Application::IsKeyPressed('K'))
    {
        light[0].position.z += (float)(10 * dt);
    }
    if (Application::IsKeyPressed('J'))
    {
        light[0].position.x -= (float)(10 * dt);
    }
    if (Application::IsKeyPressed('L'))
    {
        light[0].position.x += (float)(10 * dt);
    }
    if (Application::IsKeyPressed('O'))
    {
        light[0].position.y -= (float)(10 * dt);
    }
    if (Application::IsKeyPressed('P'))
    {
        light[0].position.y += (float)(10 * dt);
    }

    if (Application::IsKeyPressed('T'))
    {
        if (toggleLight == true)
        {
            toggleLight = false;
        }
        else
        {
            toggleLight = true;
        }
    }

    if (Application::IsKeyPressed('5'))
    {
        light[0].type = Light::LIGHT_SPOT;
        glUniform1i(lightUniforms[0][UL_TYPE], light[0].type);
    }
    if (Application::IsKeyPressed('6'))
    {
        light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(lightUniforms[0][UL_TYPE], light[0].type);
    }
    if (Application::IsKeyPressed('7'))
    {
        light[0].type = Light::LIGHT_POINT;
		glUniform1i(lightUniforms[0][UL_TYPE], light[0].type);
    }


    // TEST FOR BULLET COLLISION
    //if (Application::IsKeyPressed('B'))
    //{
    //    rayTracing(InteractablesList);
    //}

   
    
        if (somePlayer.getCameraType() == "first")
        {
            camera5.Update(dt, InteractablesList, BuildingsList, somePlayer);
            if (Application::IsKeyPressed('T'))
            {
                //somePlayer.setCameraPtr(thirdPersonCamera);
                camPointer = &thirdPersonCamera;
                somePlayer.setCameraType("third");
            }

        }
        else
        {
            thirdPersonCamera.Update(dt, InteractablesList, BuildingsList, somePlayer);
            if (Application::IsKeyPressed('T'))
            {
                //somePlayer.setCameraPtr(camera5);
                camPointer = &camera5;
                somePlayer.setCameraType("first");
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

void SP2::RenderText(Mesh* mesh, std::string text, Color color)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;

    glDisable(GL_DEPTH_TEST);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
    glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
    glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textureID);
    glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    for (unsigned i = 0; i < text.length(); ++i)
    {
        Mtx44 characterSpacing;
        characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
        Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

        mesh->Render((unsigned)text[i] * 6, 6);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
    glEnable(GL_DEPTH_TEST);
}

void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;


    glDisable(GL_DEPTH_TEST);
    //Add these code just after glDisable(GL_DEPTH_TEST);
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


    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
    glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
    glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textureID);
    glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    for (unsigned i = 0; i < text.length(); ++i)
    {
        Mtx44 characterSpacing;
        characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
        Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

        mesh->Render((unsigned)text[i] * 6, 6);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void SP2::RenderSkybox()
{
    // FRONT
    modelStack.PushMatrix();
    modelStack.Translate(thirdPersonCamera.position.x, thirdPersonCamera.position.y, -249.5 + thirdPersonCamera.position.z);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Rotate(-90, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_FRONT], false, toggleLight);
    modelStack.PopMatrix();

    // BACK
    modelStack.PushMatrix();
    modelStack.Translate(thirdPersonCamera.position.x, thirdPersonCamera.position.y, 249.5 + thirdPersonCamera.position.z);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_BACK], false, toggleLight);
    modelStack.PopMatrix();

    // LEFT
    modelStack.PushMatrix();
    modelStack.Translate(-249.5 + thirdPersonCamera.position.x, thirdPersonCamera.position.y, thirdPersonCamera.position.z);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Rotate(0, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_LEFT], false, toggleLight);
    modelStack.PopMatrix();

    // RIGHT
    modelStack.PushMatrix();
    modelStack.Translate(249.5 + thirdPersonCamera.position.x, thirdPersonCamera.position.y, thirdPersonCamera.position.z);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_RIGHT], false, toggleLight);
    modelStack.PopMatrix();

    // BOTTOM
    modelStack.PushMatrix();
    modelStack.Translate(thirdPersonCamera.position.x, -249.5 + thirdPersonCamera.position.y, thirdPersonCamera.position.z);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_BOTTOM], false, toggleLight);
    modelStack.PopMatrix();

    // TOP
    modelStack.PushMatrix();
    modelStack.Translate(thirdPersonCamera.position.x, 249.5 + thirdPersonCamera.position.y, thirdPersonCamera.position.z);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_TOP], false, toggleLight);
    modelStack.PopMatrix();
}

void SP2::initRoom(Position pos, Vector3 size, int groundMeshSize)
{
    Building floor1 = Building("floor1", meshList[GEO_GROUND]->maxPos, meshList[GEO_GROUND]->minPos, Position(pos.x, pos.y, pos.z - 20), groundMeshSize, 0, Vector3(0, 0, 0));
    BuildingsList.push_back(floor1);

    Building ceiling1 = Building("ceiling1", meshList[GEO_GROUND]->maxPos, meshList[GEO_GROUND]->minPos, Position(pos.x, pos.y + 30, pos.z - 20), groundMeshSize, 0, Vector3(0, 0, 0));
    BuildingsList.push_back(ceiling1);

    Building wall1 = Building("wall1", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x, pos.y, pos.z + (groundMeshSize / 2)), 10, 0, Vector3(0, 0, 0));
    BuildingsList.push_back(wall1);

    Building wall2 = Building("wall2", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x, pos.y, pos.z + (-groundMeshSize / 2)), 10, 0, Vector3(0, 0, 0));
    BuildingsList.push_back(wall2);

    Building wall3 = Building("wall3", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y, pos.z - 85), 10, 0, Vector3(0, 0, 0));
    BuildingsList.push_back(wall3);

    Building wall4 = Building("wall4", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y, pos.z + 85), 10, 0, Vector3(0, 0, 0));
    BuildingsList.push_back(wall4);

    Building gatetop1 = Building("gatetop1", meshList[GEO_GATETOP]->maxPos, meshList[GEO_GATETOP]->minPos, Position(pos.x + (groundMeshSize / 2) - 4, pos.y - 5, pos.z + 85), 8, 0, Vector3(0, 0, 0));
    BuildingsList.push_back(gatetop1);

    Building wall5 = Building("wall5", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x - (groundMeshSize / 2), pos.y, pos.z), 8, 0, Vector3(0, 0, 0));
    BuildingsList.push_back(wall5);
}

void SP2::RenderRoom(Position pos, Vector3 size, int groundMeshSize)
{
    // Whole Room
    modelStack.PushMatrix();
    modelStack.Translate(pos.x, pos.y, pos.z);

    // Render Floor + Ceiling
    modelStack.PushMatrix();

    modelStack.PushMatrix();
    modelStack.Scale(groundMeshSize, groundMeshSize, groundMeshSize);
    RenderMesh(meshList[GEO_GROUND], false, toggleLight); // Floor
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 30, 0);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Scale(groundMeshSize, groundMeshSize, groundMeshSize);
    RenderMesh(meshList[GEO_GROUND], false, toggleLight); // Ceiling
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // Render Walls
    modelStack.PushMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 0, (groundMeshSize / 2));
    modelStack.Scale(10, 10, 10);
    RenderMesh(meshList[GEO_WALL], false, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 0, -(groundMeshSize / 2));
    modelStack.Scale(10, 10, 10);
    RenderMesh(meshList[GEO_WALL], false, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate((groundMeshSize / 2), 0, 0);

    // Wall w/ Hole for Gate;
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, -85);
    modelStack.Scale(10, 10, 10);
    RenderMesh(meshList[GEO_WALL2], false, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 85);
    modelStack.Scale(10, 10, 10);
    RenderMesh(meshList[GEO_WALL2], false, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-4, -5, 0);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(5, 8, 5);
    RenderMesh(meshList[GEO_GATETOP], false, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate((-groundMeshSize / 2), 0, 0);
    modelStack.Scale(10, 10, 10);
    RenderMesh(meshList[GEO_WALL2], false, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PopMatrix();

}

void SP2::createBoundBox(vector<InteractableOBJs>&InteractablesList, vector<Building>&BuildingsList)
{
    Vector3 view = (thirdPersonCamera.target - thirdPersonCamera.position).Normalized();

    Position maxPos;
    Position minPos;

    Position cameraPos;

    if (somePlayer.getCameraType() == "first")
    {
        cameraPos.x = camera5.position.x + view.x;
        cameraPos.y = camera5.position.y + view.y;
        cameraPos.z = camera5.position.z + view.z;

        //cameraPos.x = somePlayer.pos.x + view.x;
        //cameraPos.y = somePlayer.pos.y + view.y;
        //cameraPos.z = somePlayer.pos.z + view.z;
    }
    else
    {
        cameraPos.x = thirdPersonCamera.GetFocusPoint()->x + 3;
        cameraPos.y = thirdPersonCamera.GetFocusPoint()->y + 3;
        cameraPos.z = thirdPersonCamera.GetFocusPoint()->z + 3;
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

    //AXES
    //RenderMesh(meshList[GEO_AXES], false, toggleLight);

    //modelStack.PushMatrix();
    //modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    //RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
    //modelStack.PopMatrix();


    modelStack.PushMatrix();
    modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(charPos.x, charPos.y, charPos.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
	modelStack.PopMatrix();



	//modelStack.PushMatrix();
	//modelStack.Rotate(camera5.verticalAngle, 1, 0, 0);
	//modelStack.Rotate(camera5.horizontalAngle, 0, 1, 0);
	////RENDER HAND PIVOT
	//RenderHandPivot();
	////RENDER HANDS
	//modelStack.PushMatrix();
	//RenderHandInfronOfScreen();
	//modelStack.PopMatrix();
	//modelStack.PopMatrix();


	////modelStack.Rotate(camera5.verticalAngle, 1, 0, 0);
	////modelStack.Rotate(camera5.horizontalAngle, 0, 1, 0);

	//RENDER HANDS
	//modelStack.PushMatrix();
	//modelStack.Translate(camera5.position.x, camera5.position.y - 1, camera5.position.z);
	//RenderHandInfronOfScreen();
	//modelStack.PopMatrix();


	//RENDER SKYBOX
    RenderSkybox();

    modelStack.PushMatrix();
    modelStack.Scale(1000, 1000, 1000);
    RenderMesh(meshList[GEO_QUAD], true, toggleLight);
    modelStack.PopMatrix();

    //modelStack.PushMatrix();
    //modelStack.Translate(0, 5, -5);
    //modelStack.Scale(4, 4, 4);
    //RenderMesh(meshList[GEO_SWITCH], true, toggleLight);
    //InteractableOBJs test_switch = InteractableOBJs("switch", meshList[GEO_SWITCH]->maxPos, meshList[GEO_SWITCH]->minPos, (0, 5, -5), 4, 0, (0, 0, 0));
    //InteractablesList.push_back(test_switch);
    //modelStack.PopMatrix();

    //RenderRoom(Position(20, 2, 0));

	std::ostringstream ss;


	//ss.str("");
	//ss << "POSIION: X(" << camera5.position.x << ") Y(" << camera5.position.y << ") Z(" << camera5.position.z << ")";
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 2, 3, 4);


 

    //modelStack.PushMatrix();
    //modelStack.Translate(3, 0, 0);
    //modelStack.Scale(3, 3, 3);
    //RenderMesh(meshList[GEO_WALL], true, toggleLight);
    //InteractableOBJs shootingTestwall = InteractableOBJs("testwall", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(3, 0, 0), 3, 0, Vector3(0, 0, 0));
    //InteractablesList.push_back(shootingTestwall);
    //modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(thirdPersonCamera.GetFocusPoint()->x, thirdPersonCamera.GetFocusPoint()->y, thirdPersonCamera.GetFocusPoint()->z);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();
}

void SP2::Exit()
{
    // Cleanup VBO here
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
