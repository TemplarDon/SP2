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
    m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
    m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
    m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
    m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
    m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
    m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
    m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
    m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
    m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
    m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
    m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
    m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

    //Light2
    m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
    m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
    m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
    m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
    m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
    m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
    m_parameters[U_LIGHT1ENABLED] = glGetUniformLocation(m_programID, "light1Enabled");
    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
    m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
    m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
    m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
    m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
    m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

    //Light3
    m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
    m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
    m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
    m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
    m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
    m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
    m_parameters[U_LIGHT3ENABLED] = glGetUniformLocation(m_programID, "light3Enabled");
    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
    m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
    m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
    m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
    m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
    m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

    // Get a handle for our "colorTexture" uniform
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Get a handle for our "textColor" uniform
    m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
    m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

    glUseProgram(m_programID);

    light[0].type = Light::LIGHT_POINT;
    light[0].position.Set(50, 35, 0);
    light[0].color.Set(0.2, 0, 0);
    light[0].power = 2;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.f;

    light[0].cosCutoff = cos(Math::DegreeToRadian(45));
    light[0].cosInner = cos(Math::DegreeToRadian(30));
    light[0].exponent = 3.f;
    light[0].spotDirection.Set(0.f, 1.f, 0.f);

    //Make sure you pass uniform parameters after glUseProgram()
    glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
    glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
    glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
    glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
    glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

    glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
    glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
    glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

    // Light2
    light[1].type = Light::LIGHT_SPOT;
    light[1].position.Set(200, 35, 0);
    light[1].color.Set(0.6, 0.21, 0.21);
    light[1].power = 0.8;
    light[1].kC = 1.f;
    light[1].kL = 0.01f;
    light[1].kQ = 0.f;

    light[1].cosCutoff = cos(Math::DegreeToRadian(45));
    light[1].cosInner = cos(Math::DegreeToRadian(30));
    light[1].exponent = 3.f;
    light[1].spotDirection.Set(0.f, -1.f, 0.f);

    //Make sure you pass uniform parameters after glUseProgram()
    glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
    glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
    glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
    glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
    glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
    glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);

    glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
    glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
    glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

    // Light3
    light[2].type = Light::LIGHT_SPOT;
    light[2].position.Set(300, 35, 300);
    light[2].color.Set(0.2, 0.21, 0.21);
    light[2].power = 1;
    light[2].kC = 1.f;
    light[2].kL = 0.01f;
    light[2].kQ = 0.f;

    light[2].cosCutoff = cos(Math::DegreeToRadian(45));
    light[2].cosInner = cos(Math::DegreeToRadian(30));
    light[2].exponent = 3.f;
    light[2].spotDirection.Set(0.f, -1.f, 0.f);

    //Make sure you pass uniform parameters after glUseProgram()
    glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
    glUniform3fv(m_parameters[U_LIGHT3_COLOR], 3, &light[3].color.r);
    glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
    glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
    glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
    glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);

    glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
    glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
    glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[1].exponent);

    // Make sure you pass uniform parameters after glUseProgram()
    glUniform1i(m_parameters[U_NUMLIGHTS], 3);

    //variable to rotate geometry
    rotateAngle = 0;
    toggleLight = true;

    Position maxPos = Position(0, 0, 0); // Vector for max pos
    Position minPos = Position(0, 0, 0); // Vector for min pos

    maxPtr = 0;
    minPtr = 0;

    // Init Player
    Player somePlayer("TestMan", "Human", 100); // Name, Race, Money

    //Initialize camera settings
    camera5.Init(Vector3(-20, 3, -8/*300,3,300*/), Vector3(0, 0, 0), Vector3(0, 1, 0)); 
    //thirdPersonCamera.Init(Vector3(-20, 3, -8/*300,3,300*/), Vector3(0, 1, 0), Vector3(0, 0, 0), 5);

	//HANDS
	meshList[GEO_HANDS] = MeshBuilder::GenerateOBJ("Hands", "OBJ//Hands.obj");
	meshList[GEO_HANDS]->textureID = LoadTGA("Image//handsTexture.tga");

	//AXES
    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

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
	
	//GROUND MESH
    meshList[GEO_GROUND] = MeshBuilder::GenerateQuad("ground", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_GROUND]->textureID = LoadTGA("Image//castleFloor.tga");

    meshList[GEO_GROUND]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_GROUND]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_GROUND]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_GROUND]->material.kShininess = 10;

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



    createBoundBox(objsMaxMin);
    camera5.Update(dt);
    //thirdPersonCamera.Update(dt);



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
        glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    }
    if (Application::IsKeyPressed('6'))
    {
        light[0].type = Light::LIGHT_DIRECTIONAL;
        glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    }
    if (Application::IsKeyPressed('7'))
    {
        light[0].type = Light::LIGHT_POINT;
        glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    }

}

void SP2::RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight)
{
    Mtx44 MVP, modelView, modelView_inverse_transpose;

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    modelView = viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
    if (enableLight && toggleLight == true)
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
    modelStack.Translate(camera5.position.x, camera5.position.y, -249.5 + camera5.position.z);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Rotate(-90, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_FRONT], false, toggleLight);
    modelStack.PopMatrix();

    // BACK
    modelStack.PushMatrix();
    modelStack.Translate(camera5.position.x, camera5.position.y, 249.5 + camera5.position.z);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_BACK], false, toggleLight);
    modelStack.PopMatrix();

    // LEFT
    modelStack.PushMatrix();
    modelStack.Translate(-249.5 + camera5.position.x, camera5.position.y, camera5.position.z);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Rotate(0, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_LEFT], false, toggleLight);
    modelStack.PopMatrix();

    // RIGHT
    modelStack.PushMatrix();
    modelStack.Translate(249.5 + camera5.position.x, camera5.position.y, camera5.position.z);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_RIGHT], false, toggleLight);
    modelStack.PopMatrix();

    // BOTTOM
    modelStack.PushMatrix();
    modelStack.Translate(camera5.position.x, -249.5 + camera5.position.y, camera5.position.z);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_BOTTOM], false, toggleLight);
    modelStack.PopMatrix();

    // TOP
    modelStack.PushMatrix();
    modelStack.Translate(camera5.position.x, 249.5 + camera5.position.y, camera5.position.z);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(500, 500, 500);
    RenderMesh(meshList[GEO_TOP], false, toggleLight);
    modelStack.PopMatrix();
}

void SP2::RenderHandInfronOfScreen()
{
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_HANDS], false, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderRoom(Vector3 size, unsigned groundMeshSize)
{

}

void SP2::createBoundBox(std::vector<Node>&objsMaxMin)
{
    Vector3 view = (camera5.target - camera5.position).Normalized();

    Position maxPos;
    Position minPos;

    Position cameraPos;

    for (int i = 0; i < objsMaxMin.size(); ++i)
    {

        cameraPos.x = camera5.position.x + view.x;
        cameraPos.y = camera5.position.y + view.y;
        cameraPos.z = camera5.position.z + view.z;


        maxPos.x = objsMaxMin[i].maxPos.x;
        maxPos.y = objsMaxMin[i].maxPos.y;
        maxPos.z = objsMaxMin[i].maxPos.z;

        minPos.x = objsMaxMin[i].minPos.x;
        minPos.y = objsMaxMin[i].minPos.y;
        minPos.z = objsMaxMin[i].minPos.z;

        // Scaling
        maxPos.x = maxPos.x * objsMaxMin[i].scaleOffSet;
        maxPos.y = maxPos.y * objsMaxMin[i].scaleOffSet;
        maxPos.z = maxPos.z * objsMaxMin[i].scaleOffSet;

        minPos.x = minPos.x * objsMaxMin[i].scaleOffSet;
        minPos.y = minPos.y * objsMaxMin[i].scaleOffSet;
        minPos.z = minPos.z * objsMaxMin[i].scaleOffSet;

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
        if (objsMaxMin[i].rotateAxis.x == 1)
        {
            rotation.SetToRotation(objsMaxMin[i].rotateAngle, 1, 0, 0);
            tempMax = rotation * tempMax;
            tempMin = rotation * tempMin;
        }
        if (objsMaxMin[i].rotateAxis.y == 1)
        {
            rotation.SetToRotation(objsMaxMin[i].rotateAngle, 0, 1, 0);
            tempMax = rotation * tempMax;
            tempMin = rotation * tempMin;
        }
        if (objsMaxMin[i].rotateAxis.z == 1)
        {
            rotation.SetToRotation(objsMaxMin[i].rotateAngle, 0, 0, 1);
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
        maxPos.x += objsMaxMin[i].offSet.x;
        maxPos.y += objsMaxMin[i].offSet.y;
        maxPos.z += objsMaxMin[i].offSet.z;

        minPos.x += objsMaxMin[i].offSet.x;
        minPos.y += objsMaxMin[i].offSet.y;
        minPos.z += objsMaxMin[i].offSet.z;

        if ((cameraPos.x > maxPos.x || cameraPos.x < minPos.x) || (cameraPos.y > maxPos.y || cameraPos.y < minPos.y) || (cameraPos.z > maxPos.z || cameraPos.z < minPos.z))
        {
            objsMaxMin[i].canMove = true;
        }
        else
        {
            objsMaxMin[i].canMove = true;
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
        camera5.position.x, camera5.position.y, camera5.position.z,
        camera5.target.x, camera5.target.y, camera5.target.z,
        camera5.up.x, camera5.up.y, camera5.up.z
        );

    modelStack.LoadIdentity();

    Mtx44 MVP;

    if (light[0].type == Light::LIGHT_DIRECTIONAL)
    {
        Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
        Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
    }
    else if (light[0].type == Light::LIGHT_SPOT)
    {
        Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
        Vector3 spotDirection_camerspace = viewStack.Top() * light[0].spotDirection;
        glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_camerspace.x);
    }
    else
    {
        Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

    }



    //AXES
    //RenderMesh(meshList[GEO_AXES], false, toggleLight);

    //modelStack.PushMatrix();
    //modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    //RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
    //modelStack.PopMatrix();


    //modelStack.PushMatrix();
    //modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
    //RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
    //modelStack.PopMatrix();

	//RENDER HANDS
	modelStack.PushMatrix();
	modelStack.Translate(camera5.position.x, camera5.position.y - 1, camera5.position.z);
	RenderHandInfronOfScreen();
	modelStack.PopMatrix();

	//RENDER SKYBOX
    RenderSkybox();

    modelStack.PushMatrix();
    modelStack.Scale(1000, 1000, 1000);
    RenderMesh(meshList[GEO_QUAD], false, toggleLight);
    modelStack.PopMatrix();

    std::ostringstream ss;

    //ss.str("");
    //ss << " X:" << camera3.position.x << "|| Y:" << camera3.position.y << "|| Z:" << camera3.position.z;
    //RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 2, 3, 4);

}

void SP2::Exit()
{
    // Cleanup VBO here
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
