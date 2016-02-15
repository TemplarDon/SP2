#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Utility.h"
#include "LoadTGA.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "timer.h"
#include <sstream>

SceneText::SceneText()
{
}

SceneText::~SceneText()
{
}

void SceneText::Init()
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

    // Get a handle for our "colorTexture" uniform
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Get a handle for our "textColor" uniform
    m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
    m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

    glUseProgram(m_programID);

    // Make sure you pass uniform parameters after glUseProgram()
    glUniform1i(m_parameters[U_NUMLIGHTS], 1);

    light[0].type = Light::LIGHT_SPOT;
    light[0].position.Set(0, 10, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 5;
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
    glUniform1i(m_parameters[U_NUMLIGHTS], 1);

    //variable to rotate geometry
    rotateAngle = 0;
    toggleLight = true;

    // Variables for finding min & max of x, y, z coords for collision
    verticeNum = 0;
    Position maxPos = Position(0, 0, 0); // Vector for max pos
    Position minPos = Position(0, 0, 0); // Vector for min pos

    //Initialize camera settings
    camera3.Init(Vector3(20, 2, 8), Vector3(0, 0, 0), Vector3(0, 1, 0));

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

    meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_QUAD]->textureID = LoadTGA("Image//bird.tga");

    meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_FRONT]->textureID = LoadTGA("Image//newFront.tga");

    meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_BACK]->textureID = LoadTGA("Image//newBack.tga");

    meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_TOP]->textureID = LoadTGA("Image//newTop.tga");

    meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//newBottom.tga");

    meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_LEFT]->textureID = LoadTGA("Image//newLeft.tga");

    meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_RIGHT]->textureID = LoadTGA("Image//newRight.tga");

    meshList[GEO_GROUND] = MeshBuilder::GenerateQuad("model1", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_GROUND]->textureID = LoadTGA("Image//castleGround.tga");

    //meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("model1", "OBJ//V_Art Spaceship.obj", objsMaxMin, MaxMinPos, verticeNum);
    meshList[GEO_MODEL1]->textureID = LoadTGA("Image//airUV.tga");

    //meshList[GEO_MODEL2] = MeshBuilder::GenerateOBJ("model2", "OBJ//V_Art Land.obj", objsMaxMin);
    //meshList[GEO_MODEL2]->textureID = LoadTGA("Image//outUV.tga");

    meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
    meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("LightBall", Color(1, 1, 1), 10, 20);

    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
    projectionStack.LoadMatrix(projection);


}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
//float FramesPerSecond = 0;

void SceneText::Update(double dt)
{
    //FramesPerSecond = 1 / dt;

    if (Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if (Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

    //createBoundBox(objsMaxMin, verticeNum, MaxMinPos);
    //camera3.Update(dt, objsMaxMin, MaxMinPos);

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

void SceneText::RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight)
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

void SceneText::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneText::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneText::RenderSkybox()
{
    // FRONT
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, -495);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Rotate(-90, 0, 1, 0);
    modelStack.Scale(1000, 1000, 1000);
    RenderMesh(meshList[GEO_FRONT], false, toggleLight);
    modelStack.PopMatrix();

    // BACK
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 495);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(1000, 1000, 1000);
    RenderMesh(meshList[GEO_BACK], false, toggleLight);
    modelStack.PopMatrix();

    // LEFT
    modelStack.PushMatrix();
    modelStack.Translate(-495, 0, 0);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Rotate(0, 0, 1, 0);
    modelStack.Scale(1000, 1000, 1000);
    RenderMesh(meshList[GEO_LEFT], false, toggleLight);
    modelStack.PopMatrix();

    // RIGHT
    modelStack.PushMatrix();
    modelStack.Translate(495, 0, 0);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(1000, 1000, 1000);
    RenderMesh(meshList[GEO_RIGHT], false, toggleLight);
    modelStack.PopMatrix();

    // BOTTOM
    modelStack.PushMatrix();
    modelStack.Translate(0, -495, 0);
    modelStack.Scale(1000, 1000, 1000);
    RenderMesh(meshList[GEO_BOTTOM], false, toggleLight);
    modelStack.PopMatrix();

    // TOP
    modelStack.PushMatrix();
    modelStack.Translate(0, 495, 0);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Scale(1000, 1000, 1000);
    RenderMesh(meshList[GEO_TOP], false, toggleLight);
    modelStack.PopMatrix();
}

void SceneText::createBoundBox(std::vector<Node>&objsMaxMin, std::vector<Position>* verticeNum, std::vector<Position>& MaxMinPos)
{
    // ------------------------------- Finding Min & Max Values (For Collision) -------------------------------------------//
    //std::vector<Position>& vecRef = *verticeNum; // dereference pointer
    //for (int i = 0; i < vecRef.size(); ++i)
    //{
    //    if (vecRef[i].x > maxPos.x)
    //    {
    //        maxPos.x = vecRef[i].x;
    //    }
    //    if (vecRef[i].x < minPos.x)
    //    {
    //        minPos.x = vecRef[i].x;
    //    }

    //    if ((vecRef[i].y > maxPos.y))
    //    {
    //        maxPos.y = vecRef[i].y;
    //    }
    //    if (vecRef[i].y < minPos.y)
    //    {
    //        minPos.y = vecRef[i].y;
    //    }

    //    if (vecRef[i].z > maxPos.z)
    //    {
    //        maxPos.z = vecRef[i].z;
    //    }
    //    if (vecRef[i].z < minPos.z)
    //    {
    //        minPos.z = vecRef[i].z;
    //    }
    //}

    //// Push back a new Node with the maxPos and minPos
    //Node someNode = Node(maxPos, minPos);
    //objsMaxMin.push_back(someNode);
    // ------------------------------- Finding Min & Max Values (For Collision) -------------------------------------------//
}
void SceneText::Render()
{
    // Render VBO here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Set view matrix using camera settings
    viewStack.LoadIdentity();
    viewStack.LookAt(
        camera3.position.x, camera3.position.y, camera3.position.z,
        camera3.target.x, camera3.target.y, camera3.target.z,
        camera3.up.x, camera3.up.y, camera3.up.z
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
    RenderMesh(meshList[GEO_AXES], false, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
    modelStack.PopMatrix();


    RenderSkybox();
   
    modelStack.PushMatrix();
    modelStack.Translate(0, -2, 0);
    modelStack.Scale(100, 100, 100);
    RenderMesh(meshList[GEO_GROUND], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 20, -50);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Scale(100, 100, 100);
    RenderMesh(meshList[GEO_GROUND], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 20, 50);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Scale(100, 100, 100);
    RenderMesh(meshList[GEO_GROUND], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(50, 20, 0);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Scale(100, 100, 100);
    RenderMesh(meshList[GEO_GROUND], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-50, 20, 0);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Scale(100, 100, 100);
    RenderMesh(meshList[GEO_GROUND], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    RenderMesh(meshList[GEO_MODEL1], false, toggleLight);
    modelStack.PopMatrix();

    // Text
    modelStack.PushMatrix();
    modelStack.Scale(15, 15, 15);
    RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
    modelStack.PopMatrix();

    // On screen text
    std::ostringstream target;
    std::ostringstream position;
    //ss << "FPS: " << FramesPerSecond;
    target << "Camera Target: " << (int)camera3.target.x << " " << (int)camera3.target.y << " " << (int)camera3.target.z;
    position << "Camera Position: " << (int)camera3.position.x << " " << (int)camera3.position.y << " " << (int)camera3.position.z;
    RenderTextOnScreen(meshList[GEO_TEXT], target.str(), Color(0, 1, 0), 3, 0, 2);
    RenderTextOnScreen(meshList[GEO_TEXT], position.str(), Color(0, 1, 0), 3, 0, 3);

    RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 0, 1);


}

void SceneText::Exit()
{
    // Cleanup VBO here
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
