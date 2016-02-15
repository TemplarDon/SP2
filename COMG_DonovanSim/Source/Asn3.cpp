#include "Asn3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Utility.h"
#include "LoadTGA.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "timer.h"
#include <sstream>

Asn3::Asn3()
{
}

Asn3::~Asn3()
{

}

void Asn3::Init()
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

    // Variables for finding min & max of x, y, z coords for collision
    verticeNum = 0;

    Position maxPos = Position(0, 0, 0); // Vector for max pos
    Position minPos = Position(0, 0, 0); // Vector for min pos

    maxPtr = 0;
    minPtr = 0;

    // Variables for interaction
    // Gate Opening
    gateOffSet = 0.f;
    gateMsg = false;

    thwumpOffset = 0;
    thwump3Drop = 0;
    thwump4Drop = 0;
    thwump3Dropping = false;
    thwump4Dropping = false;
    reachedDest = false;

    gateOpened = false;
    gateLocked = false;
    gateLockedMsg = false;
    gateUnlockMsg = false;

    peachMsg = false;
    peachTaken = false;

    keyTaken = false;
    keyMsg = false;

    doorEnterMsg = false;
    doorErrorMsg = false;

    pipeMsg = false;
    completedMsg = false;

    //Initialize camera settings
    camera3.Init(Vector3(-20, 3, -8/*300,3,300*/), Vector3(0, 0, 0), Vector3(0, 1, 0));

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

    meshList[GEO_GROUND] = MeshBuilder::GenerateQuad("ground", Color(1, 1, 1), objsMaxMin);
    meshList[GEO_GROUND]->textureID = LoadTGA("Image//castleFloor.tga");

    meshList[GEO_GROUND]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_GROUND]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_GROUND]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_GROUND]->material.kShininess = 10;


    // ------------------------------------------------------------------------- WALLS ---------------------------------------------------------------------------------------//
    meshList[GEO_WALL] = MeshBuilder::GenerateOBJ("wall", "OBJ//castleWall.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_WALL]->textureID = LoadTGA("Image//wallUV.tga");

    meshList[GEO_WALL]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_WALL]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_WALL]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_WALL]->material.kShininess = 10;

    // Left & Right
    Node wall_1 = Node(meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(0, 0, -50), 10, 0, Vector3(0, 0, 0), "rm1_wall_1");
    Node wall_2 = Node(meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(0, 0, 50), 10, 0, Vector3(0, 0, 0), "rm1_wall_2");

    // Room2 Left & Right
    Node rm2_wall_1 = Node(meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(120, 0, -50), 10, 0, Vector3(0, 0, 0), "rm2_wall_1"); 
    Node rm2_wall_2 = Node(meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(120, 0, 50), 10, 0, Vector3(0, 0, 0), "rm2_wall_2");
    Node rm2_wall_3 = Node(meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(220, 0, -50), 10, 0, Vector3(0, 0, 0), "rm2_wall_3");
    Node rm2_wall_4 = Node(meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(220, 0, 50), 10, 0, Vector3(0, 0, 0), "rm2_wall_4");

    objsMaxMin.push_back(wall_1);
    objsMaxMin.push_back(wall_2);

    objsMaxMin.push_back(rm2_wall_1);
    objsMaxMin.push_back(rm2_wall_2);
    objsMaxMin.push_back(rm2_wall_3);
    objsMaxMin.push_back(rm2_wall_4);
    // ------------------------------------------------------------------------- WALLS ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- WALLS 2 ---------------------------------------------------------------------------------------//
    meshList[GEO_WALL2] = MeshBuilder::GenerateOBJ("wall", "OBJ//castleWall2.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_WALL2]->textureID = LoadTGA("Image//wallUV.tga");

    meshList[GEO_WALL2]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_WALL2]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_WALL2]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_WALL2]->material.kShininess = 10;

    // Front w/ Gate
    Node wall_3 = Node(meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(50, 0, -85), 10, 0, Vector3(0, 0, 0), "rm1_wall_3");
    Node wall_4 = Node(meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(50, 0, 85), 10, 0, Vector3(0, 0, 0), "rm1_wall_4");
    //Back
    Node wall_5 = Node(meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(-50, 0, 0), 10, 0, Vector3(0, 0, 0), "rm1_back_wall");

    // Throne Room Back Wall
    Node wall_6 = Node(meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(250, 0, 0), 10, 0, Vector3(0, 0, 0), "rm2_back_wall");

    objsMaxMin.push_back(wall_3);
    objsMaxMin.push_back(wall_4);
    objsMaxMin.push_back(wall_5);
    objsMaxMin.push_back(wall_6);

    // ------------------------------------------------------------------------- WALLS 2 ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- GATE TOP ---------------------------------------------------------------------------------------//
    meshList[GEO_GATETOP] = MeshBuilder::GenerateOBJ("wall", "OBJ//gateTop.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_GATETOP]->textureID = LoadTGA("Image//gateTopUV.tga");
    meshList[GEO_GATETOP]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_GATETOP]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_GATETOP]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_GATETOP]->material.kShininess = 10;

    Node gateTop = Node(meshList[GEO_GATETOP]->maxPos, meshList[GEO_GATETOP]->minPos, Position(45, -2, 0), 6, 90, Vector3(0, 1, 0), "gatetop");
    objsMaxMin.push_back(gateTop);
    // ------------------------------------------------------------------------- GATE TOP ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- GATE ---------------------------------------------------------------------------------------//
    meshList[GEO_GATE] = MeshBuilder::GenerateOBJ("wall", "OBJ//gate.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_GATE]->textureID = LoadTGA("Image//gateUV.tga");
    meshList[GEO_GATE]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_GATE]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_GATE]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_GATE]->material.kShininess = 10;

    Node gate = Node(meshList[GEO_GATE]->maxPos, meshList[GEO_GATE]->minPos, Position(45, 0, 1), 10, 0, Vector3(0, 0, 0), "gate");
    objsMaxMin.push_back(gate);
    // ------------------------------------------------------------------------- GATE ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- SWITCH ---------------------------------------------------------------------------------------//
    meshList[GEO_SWITCH] = MeshBuilder::GenerateOBJ("wall", "OBJ//switch.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_SWITCH]->textureID = LoadTGA("Image//switchUV.tga");
    meshList[GEO_SWITCH]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_SWITCH]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_SWITCH]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_SWITCH]->material.kShininess = 10;

    Node switch1 = Node(meshList[GEO_SWITCH]->maxPos, meshList[GEO_SWITCH]->minPos, Position(45, 8, 15), 6, 0, Vector3(0, 0, 0), "switch");
    objsMaxMin.push_back(switch1);
    // ------------------------------------------------------------------------- SWITCH ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- THWUMP ---------------------------------------------------------------------------------------//
    meshList[GEO_THWUMP] = MeshBuilder::GenerateOBJ("wall", "OBJ//thwump.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_THWUMP]->textureID = LoadTGA("Image//thwumpUV.tga");
    meshList[GEO_THWUMP]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_THWUMP]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_THWUMP]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_THWUMP]->material.kShininess = 10;

    Node thwump1 = Node(meshList[GEO_THWUMP]->maxPos, meshList[GEO_THWUMP]->minPos, Position(70, -10, 30), 6, 0, Vector3(0, 0, 0), "thwump1");
    Node thwump2 = Node(meshList[GEO_THWUMP]->maxPos, meshList[GEO_THWUMP]->minPos, Position(100, -10, -30), 6, 0, Vector3(0, 0, 0), "thwump2");
    Node thwump3 = Node(meshList[GEO_THWUMP]->maxPos, meshList[GEO_THWUMP]->minPos, Position(130, 5, 30), 6, 0, Vector3(0, 0, 0), "thwump3");
    Node thwump4 = Node(meshList[GEO_THWUMP]->maxPos, meshList[GEO_THWUMP]->minPos, Position(160, 5, -30), 6, 0, Vector3(0, 0, 0), "thwump4");
    objsMaxMin.push_back(thwump1);
    objsMaxMin.push_back(thwump2);
    objsMaxMin.push_back(thwump3);
    objsMaxMin.push_back(thwump4);
    // ------------------------------------------------------------------------- THWUMP ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- THRONE ---------------------------------------------------------------------------------------//
    meshList[GEO_THRONE] = MeshBuilder::GenerateOBJ("wall", "OBJ//throne.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_THRONE]->textureID = LoadTGA("Image//wallUV.tga");
    meshList[GEO_THRONE]->material.kSpecular.Set(0.5,0.5,0.5);
    meshList[GEO_THRONE]->material.kShininess = 12.f; 

    Node throne = Node(meshList[GEO_THRONE]->maxPos, meshList[GEO_THRONE]->minPos, Position(230, -2, 0), 2, 0, Vector3(0, 0, 0), "throne");
    objsMaxMin.push_back(throne);
    // ------------------------------------------------------------------------- THRONE ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- PEDESTAL ---------------------------------------------------------------------------------------//
    meshList[GEO_PEDESTAL] = MeshBuilder::GenerateOBJ("wall", "OBJ//pedastal.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_PEDESTAL]->textureID = LoadTGA("Image//pedestalUV.tga");
    meshList[GEO_PEDESTAL]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_PEDESTAL]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_PEDESTAL]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_PEDESTAL]->material.kShininess = 10;

    Node pedastal1 = Node(meshList[GEO_PEDESTAL]->maxPos, meshList[GEO_PEDESTAL]->minPos, Position(230, -2, -25), 5, 0, Vector3(0, 0, 0), "pedestal1");
    objsMaxMin.push_back(pedastal1);

    Node pedastal2 = Node(meshList[GEO_PEDESTAL]->maxPos, meshList[GEO_PEDESTAL]->minPos, Position(230, -2, 25), 5, 0, Vector3(0, 0, 0), "pedestal2");
    objsMaxMin.push_back(pedastal2);
    // ------------------------------------------------------------------------- PEDESTAL ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- PILLAR ---------------------------------------------------------------------------------------//
    meshList[GEO_PILLAR] = MeshBuilder::GenerateOBJ("wall", "OBJ//pillar.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_PILLAR]->textureID = LoadTGA("Image//pillarUV.tga");
    meshList[GEO_PILLAR]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_PILLAR]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_PILLAR]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_PILLAR]->material.kShininess = 10;

    Node pillar1 = Node(meshList[GEO_PILLAR]->maxPos, meshList[GEO_PILLAR]->minPos, Position(40, -2, 40), 5, 0, Vector3(0, 0, 0), "pillar1");
    objsMaxMin.push_back(pillar1);

    Node pillar2 = Node(meshList[GEO_PILLAR]->maxPos, meshList[GEO_PILLAR]->minPos, Position(40, -2, -40), 5, 0, Vector3(0, 0, 0), "pillar2");
    objsMaxMin.push_back(pillar2);

    Node pillar3 = Node(meshList[GEO_PILLAR]->maxPos, meshList[GEO_PILLAR]->minPos, Position(-40, -2, 40), 5, 0, Vector3(0, 0, 0), "pillar3");
    objsMaxMin.push_back(pillar3);

    Node pillar4 = Node(meshList[GEO_PILLAR]->maxPos, meshList[GEO_PILLAR]->minPos, Position(-40, -2, -40), 5, 0, Vector3(0, 0, 0), "pillar4");
    objsMaxMin.push_back(pillar4);

    // ------------------------------------------------------------------------- PILLAR ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- LAVA ---------------------------------------------------------------------------------------//
    //meshList[GEO_LAVA] = MeshBuilder::GenerateOBJ("wall", "OBJ//lavaPool.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    //meshList[GEO_LAVA]->textureID = LoadTGA("Image//lavapoolUV.tga");

    //Node lava = Node(meshList[GEO_LAVA]->maxPos, meshList[GEO_LAVA]->minPos, Position(150, -2, 0), 1.5, 0, Vector3(0, 0, 0), "lavapool");
    //objsMaxMin.push_back(lava);
    // ------------------------------------------------------------------------- LAVA ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- PEACH ---------------------------------------------------------------------------------------//
    meshList[GEO_PEACH] = MeshBuilder::GenerateOBJ("peach", "OBJ//peach.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_PEACH]->textureID = LoadTGA("Image//peachUV.tga");
    // ------------------------------------------------------------------------- PEACH ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- KEY ---------------------------------------------------------------------------------------//
    meshList[GEO_KEY] = MeshBuilder::GenerateOBJ("key", "OBJ//key.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_KEY]->textureID = LoadTGA("Image//keyUV.tga");
    // ------------------------------------------------------------------------- KEY ---------------------------------------------------------------------------------------//

    // ------------------------------------------------------------------------- DOOR ---------------------------------------------------------------------------------------//
    meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("door", "OBJ//door.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_DOOR]->textureID = LoadTGA("Image//doorUV.tga");

    Node door = Node(meshList[GEO_DOOR]->maxPos, meshList[GEO_DOOR]->minPos, Position(-45, 0, 0), 10, 0, Vector3(0, 0, 0), "door");
    objsMaxMin.push_back(door);
    // ------------------------------------------------------------------------- DOOR ---------------------------------------------------------------------------------------//


    // ------------------------------------------------------------------------- PIPE ---------------------------------------------------------------------------------------//
    meshList[GEO_PIPE] = MeshBuilder::GenerateOBJ("pipe", "OBJ//pipe.obj", objsMaxMin, MaxMinPos, verticeNum, maxPtr, minPtr);
    meshList[GEO_PIPE]->textureID = LoadTGA("Image//pipeUV.tga");

    Node pipe = Node(meshList[GEO_PIPE]->maxPos, meshList[GEO_PIPE]->minPos, Position(335, -2, 300), 5, 0, Vector3(0, 0, 0), "pipe");
    objsMaxMin.push_back(pipe);
    // ------------------------------------------------------------------------- PIPE ---------------------------------------------------------------------------------------//

    meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
    meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("LightBall", Color(1, 0, 0), 10, 20);

    

    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
    projectionStack.LoadMatrix(projection);

}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
float FramesPerSecond = 0;



void Asn3::Update(double dt)
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


    ifDead(dt);
    createBoundBox(objsMaxMin, verticeNum, MaxMinPos, offSets);

    gateInteractions(dt);
    thwumpMovement(dt);
    peachInteractions(dt);
    keyInteractions(dt);
    doorInteractions(dt);
    pipeInteractions(dt);

    camera3.Update(dt, objsMaxMin);
    ifDead(dt);
    


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

void Asn3::gateInteractions(double dt)
{
    int i = 0;
    while (i < objsMaxMin.size())
    {
        if (objsMaxMin[i].name == "gate")
        {
            break;
        }
        ++i;
    }

    if (gateLocked == false)
    {
        // Button Input
        if (camera3.position.x <= 60 && camera3.position.x >= 15 && camera3.position.z <= 25 && camera3.position.z >= -25)
        {
            gateMsg = true;
            if (Application::IsKeyPressed('E'))
            {
                gateOpened = true;
            }
        }
        else
        {
            gateMsg = false;
            gateOpened = false;
        }



        // Movinig Gate
        if (gateOpened == true)
        {
            if (gateOffSet <= 3)
            {
                gateOffSet += (float)(dt);
                objsMaxMin[i].offSet.y += gateOffSet;
            }

        }
        else
        {
            if (gateOffSet > 0)
            {
                gateOffSet -= (float)(dt);
                objsMaxMin[i].offSet.y -= gateOffSet;
            }
        }
    }
    else
    {
        // Button Input
        if (camera3.position.x <= 60 && camera3.position.x >= 15 && camera3.position.z <= 25 && camera3.position.z >= -25)
        {
            if (keyTaken == true)
            {
                gateUnlockMsg = true;
            }

            if (Application::IsKeyPressed('E') && keyTaken == true)
            {
                gateOpened = true;
                gateLockedMsg = false;
                gateLocked = false;
                gateUnlockMsg = false;
            }
            else
            {
                gateLockedMsg = true;
            }



            // Moving gate
            if (gateOpened == true)
            {
                if (gateOffSet <= 3)
                {
                    gateOffSet += (float)(dt);
                    objsMaxMin[i].offSet.y += gateOffSet;
                }

            }
            else
            {
                if (gateOffSet > 0)
                {
                    gateOffSet -= (float)(dt);
                    objsMaxMin[i].offSet.y -= gateOffSet;
                }
            }
        }
    }



}

void Asn3::thwumpMovement(double dt)
{
    float thwumpSpeed = 0.01f;
    if (thwumpOffset <= 60 && reachedDest == false)
    {

        for (int i = 0; i < objsMaxMin.size(); ++i)
        {
            if (objsMaxMin[i].name == "thwump1") // - 
            {
                objsMaxMin[i].offSet.z -= (float)(5.5 * dt);
            }

            if (objsMaxMin[i].name == "thwump2") // +
            {
                objsMaxMin[i].offSet.z += (float)(5.5 * dt);
            }

            if (objsMaxMin[i].name == "thwump3") // -
            {
                objsMaxMin[i].offSet.z -= (float)(5.5 * dt);
                if ((camera3.position.x <= objsMaxMin[i].maxPos.x + objsMaxMin[i].offSet.x + 3 && camera3.position.x >= objsMaxMin[i].minPos.x + objsMaxMin[i].offSet.x - 3) && (camera3.position.z <= objsMaxMin[i].maxPos.z + objsMaxMin[i].offSet.z + 3 && camera3.position.z >= objsMaxMin[i].minPos.z + objsMaxMin[i].offSet.z - 3))
                {
                    thwump3Dropping = true;
                    if (thwump3Drop <= 5 && thwump3Dropping == true)
                    {
                        objsMaxMin[i].offSet.y -= (float)(10 * dt);
                        thwump3Drop += (float)(10 * dt);

                        if (thwump3Drop == 5)
                        {
                            thwump3Dropping = false;
                        }
                    }

                }
                else
                {
                    thwump3Dropping = false;
                }

                if (thwump3Drop >= 0 && thwump3Dropping == false)
                {
                    objsMaxMin[i].offSet.y += (float)(5.5 * dt);
                    thwump3Drop -= (float)(5.5 * dt);
                }
            }

            if (objsMaxMin[i].name == "thwump4") // +
            {
                objsMaxMin[i].offSet.z += (float)(5.5 * dt);
                if ((camera3.position.x <= objsMaxMin[i].maxPos.x + objsMaxMin[i].offSet.x + 3 && camera3.position.x >= objsMaxMin[i].minPos.x + objsMaxMin[i].offSet.x - 3) && (camera3.position.z <= objsMaxMin[i].maxPos.z + objsMaxMin[i].offSet.z + 3 && camera3.position.z >= objsMaxMin[i].minPos.z + objsMaxMin[i].offSet.z - 3))
                {
                    thwump4Dropping = true;
                    if (thwump4Drop <= 5 && thwump4Dropping == true)
                    {
                        objsMaxMin[i].offSet.y -= (float)(10 * dt);
                        thwump4Drop += (float)(10 * dt);

                        if (thwump4Drop == 5)
                        {
                            thwump4Dropping = false;
                        }
                    }

                }
                else
                {
                    thwump4Dropping = false;
                }

                if (thwump4Drop >= 0 && thwump4Dropping == false)
                {
                    objsMaxMin[i].offSet.y += (float)(5.5 * dt);
                    thwump4Drop -= (float)(5.5 * dt);
                }
            }
        }

        thwumpOffset += (float)(5.5 * dt);

        if (thwumpOffset >= 60)
        {
            reachedDest = true;
        }
    }
    if (reachedDest == true)
    {

        for (int i = 0; i < objsMaxMin.size(); ++i)
        {
            if (objsMaxMin[i].name == "thwump1")
            {
                objsMaxMin[i].offSet.z += (float)(5.5 * dt);
            }

            if (objsMaxMin[i].name == "thwump2")
            {
                objsMaxMin[i].offSet.z -= (float)(5.5 * dt);
            }

            if (objsMaxMin[i].name == "thwump3")
            {
                objsMaxMin[i].offSet.z += (float)(5.5 * dt);
                if ((camera3.position.x <= objsMaxMin[i].maxPos.x + objsMaxMin[i].offSet.x + 3 && camera3.position.x >= objsMaxMin[i].minPos.x + objsMaxMin[i].offSet.x - 3) && (camera3.position.z <= objsMaxMin[i].maxPos.z + objsMaxMin[i].offSet.z + 3 && camera3.position.z >= objsMaxMin[i].minPos.z + objsMaxMin[i].offSet.z - 3))
                {
                    thwump3Dropping = true;
                    if (thwump3Drop <= 5 && thwump3Dropping == true)
                    {
                        objsMaxMin[i].offSet.y -= (float)(10 * dt);
                        thwump3Drop += (float)(10 * dt);

                        if (thwump3Drop == 5)
                        {
                            thwump3Dropping = false;
                        }
                    }

                }
                else
                {
                    thwump3Dropping = false;
                }


                if (thwump3Drop >= 0 && thwump3Dropping == false)
                {
                    objsMaxMin[i].offSet.y += (float)(5.5 * dt);
                    thwump3Drop -= (float)(5.5 * dt);
                }
            }

            if (objsMaxMin[i].name == "thwump4")
            {
                objsMaxMin[i].offSet.z -= (float)(5.5 * dt);
                if ((camera3.position.x <= objsMaxMin[i].maxPos.x + objsMaxMin[i].offSet.x + 3 && camera3.position.x >= objsMaxMin[i].minPos.x + objsMaxMin[i].offSet.x - 3) && (camera3.position.z <= objsMaxMin[i].maxPos.z + objsMaxMin[i].offSet.z + 3 && camera3.position.z >= objsMaxMin[i].minPos.z + objsMaxMin[i].offSet.z - 3))
                {
                    thwump4Dropping = true;
                    if (thwump4Drop <= 5 && thwump4Dropping == true)
                    {
                        objsMaxMin[i].offSet.y -= (float)(10 * dt);
                        thwump4Drop += (float)(10 * dt);

                        if (thwump4Drop == 5)
                        {
                            thwump4Dropping = false;
                        }
                    }

                }
                else
                {
                    thwump4Dropping = false;
                }

                if (thwump4Drop >= 0 && thwump4Dropping == false)
                {
                    objsMaxMin[i].offSet.y += (float)(5.5 * dt);
                    thwump4Drop -= (float)(5.5 * dt);
                }
            }
        }

        thwumpOffset -= (float)(5.5 * dt);

        if (thwumpOffset <= 0)
        {
            reachedDest = false;
        }
    }

}

void Asn3::peachInteractions(double dt)
{
    // 230, -2, -25
    if ((camera3.position.x <= 245 && camera3.position.x >= 215) && (camera3.position.z <= -20 && camera3.position.z >= -30) && peachTaken == false)
    {
        peachMsg = true;
        if (Application::IsKeyPressed('E'))
        {
            peachTaken = true;
            peachMsg = false;
            gateLocked = true;
        }
    }
    else
    {
        peachMsg = false;
    }
}

void Asn3::ifDead(double dt)
{
    Vector3 view = (camera3.target - camera3.position).Normalized();
    for (int i = 0; i < objsMaxMin.size(); ++i)
    {
        if (objsMaxMin[i].name == "thwump1" || objsMaxMin[i].name == "thwump2")
        {
            if ((camera3.position.x <= objsMaxMin[i].maxPos.x + objsMaxMin[i].offSet.x + 3 && camera3.position.x >= objsMaxMin[i].minPos.x + objsMaxMin[i].offSet.x - 3) && (camera3.position.z <= objsMaxMin[i].maxPos.z + objsMaxMin[i].offSet.z + 3 && camera3.position.z >= objsMaxMin[i].minPos.z + objsMaxMin[i].offSet.z - 3))
            {
                camera3.Reset();
                gateOffSet = 0.f;
                gateMsg = false;

                gateOpened = false;
                gateLocked = false;

                peachTaken = false;

                keyTaken = false;
                keyMsg = false;

                completedMsg = false;
            }
        }
        else if (objsMaxMin[i].name == "thwump3" || objsMaxMin[i].name == "thwump4")
        {
            if ((camera3.position.x <= objsMaxMin[i].maxPos.x + objsMaxMin[i].offSet.x + 3 && camera3.position.x >= objsMaxMin[i].minPos.x + objsMaxMin[i].offSet.x - 3) && (camera3.position.z <= objsMaxMin[i].maxPos.z + objsMaxMin[i].offSet.z + 3 && camera3.position.z >= objsMaxMin[i].minPos.z + objsMaxMin[i].offSet.z - 3) && (camera3.position.y <= objsMaxMin[i].maxPos.y + objsMaxMin[i].offSet.y && camera3.position.y >= objsMaxMin[i].minPos.y + objsMaxMin[i].offSet.y))
            {
                camera3.Reset();
 
                gateOpened = false;
                gateLocked = false;

                peachTaken = false;

                keyTaken = false;
                keyMsg = false;

                completedMsg = false;
            }
        }
    }
}

void Asn3::keyInteractions(double dt)
{
    if ((camera3.position.x <= 245 && camera3.position.x >= 215) && (camera3.position.z <= 30 && camera3.position.z >= 20) && keyTaken == false)
    {
        keyMsg = true;
        if (Application::IsKeyPressed('E'))
        {
            keyTaken = true;
            keyMsg = false;
        }
    }
    else
    {
        keyMsg = false;
    }
}

void Asn3::doorInteractions(double dt)
{
    if (camera3.position.x <= -25 && camera3.position.x >= -35 && camera3.position.z <= 10 && camera3.position.z >= -10)
    {
        doorEnterMsg = true;
        if (peachTaken == true && Application::IsKeyPressed('E'))
        {
            camera3.position.Set(300, 3, 300);
            camera3.target.Set(315, 3, 315);
        }
        else if (Application::IsKeyPressed('E'))
        {
            doorErrorMsg = true;
        }
    }
    else
    {
        doorEnterMsg = false;
        doorErrorMsg = false;
    }

}

void Asn3::pipeInteractions(double dt)
{
    //335, -2, 300
    if (camera3.position.x <= 345 && camera3.position.x >= 325 && camera3.position.z <= 310 && camera3.position.z >= 290)
    {
        pipeMsg = true;
        if (Application::IsKeyPressed('E'))
        {
            camera3.Reset();
            completedMsg = true;
            peachTaken = false;
            keyTaken = false;
        }
    }
    else
    {
        pipeMsg = false;
    }
}

void Asn3::RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight)
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

void Asn3::RenderText(Mesh* mesh, std::string text, Color color)
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

void Asn3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void Asn3::RenderSkybox()
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

void Asn3::createBoundBox(std::vector<Node>&objsMaxMin, std::vector<Position>* verticeNum, std::vector<Position>& MaxMinPos, std::vector<Position>& offSets)
{

    Vector3 view = (camera3.target - camera3.position).Normalized();
    Position maxPos;
    Position minPos;

    Position cameraPos;

    for (int i = 0; i < objsMaxMin.size(); ++i)
    {
            cameraPos.x = camera3.position.x + view.x;
            cameraPos.y = camera3.position.y + view.y;
            cameraPos.z = camera3.position.z + view.z;

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
                objsMaxMin[i].canMove = false;
            }
        
    }


}
void Asn3::Render()
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
    //RenderMesh(meshList[GEO_AXES], false, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
    modelStack.PopMatrix();


    modelStack.PushMatrix();
    modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
    RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
    modelStack.PopMatrix();


    RenderSkybox();

    // GROUND
    modelStack.PushMatrix();
    modelStack.Translate(0, -2, 0);
    modelStack.Scale(100, 100, 100);
    RenderMesh(meshList[GEO_GROUND], false, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(1, 0, 0);
    RenderMesh(meshList[GEO_GROUND], false, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(1, 0, 0);
    RenderMesh(meshList[GEO_GROUND], false, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PopMatrix();


    // CEILIING
    modelStack.PushMatrix();
    modelStack.Translate(0, 35, 0);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Scale(100, 100, 100);
    RenderMesh(meshList[GEO_GROUND], false, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(1, 0, 0);
    RenderMesh(meshList[GEO_GROUND], false, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(1, 0, 0);
    RenderMesh(meshList[GEO_GROUND], false, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PopMatrix();



    // WAllS

    // Left
    modelStack.PushMatrix();

    modelStack.Translate(5, 0, -50);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();
            
    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(150, 0, -50);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(290, 0, -50);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();


    // Right
    modelStack.PushMatrix();

    modelStack.Translate(5, 0, 50);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(150, 0, 50);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(290, 0, 50);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();



    // ------------------------- WALL W/ GATE ----------------------------//
    modelStack.PushMatrix();

    modelStack.Translate(50, 0, -85);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(50, 0, 85);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();
// ------------------------- WALL W/ GATE ----------------------------//
    modelStack.PushMatrix();

    modelStack.Translate(-50, 0, 0);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 1);
    modelStack.Scale(1, 3, 1);
    RenderMesh(meshList[GEO_DOOR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(250, 0, 0);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // GATE TOP
    modelStack.PushMatrix();
    modelStack.Translate(45, -2 , 0);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(5, 8, 5);
    RenderMesh(meshList[GEO_GATETOP], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 2 + gateOffSet, 1);
    modelStack.Rotate(-90, 0, 1, 0);
    RenderMesh(meshList[GEO_GATE], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // SWITCH
    modelStack.PushMatrix();
    modelStack.Translate(45, 8, 15);
    modelStack.Rotate(-90, 0, 1, 0);
    modelStack.Scale(6, 6, 6);
    RenderMesh(meshList[GEO_SWITCH], true, toggleLight);
    modelStack.PopMatrix();
    
    //THWUMP
    modelStack.PushMatrix();
    modelStack.Translate(70, -10, 30 - thwumpOffset);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(7, 7, 7);
    RenderMesh(meshList[GEO_THWUMP], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(100, -10, -30 + thwumpOffset);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(7, 7, 7);
    RenderMesh(meshList[GEO_THWUMP], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(130, 5 - thwump3Drop, 30 - thwumpOffset);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(7, 7, 7);
    RenderMesh(meshList[GEO_THWUMP], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(160, 5 - thwump4Drop, -30 + thwumpOffset);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(7, 7, 7);
    RenderMesh(meshList[GEO_THWUMP], true, toggleLight);
    modelStack.PopMatrix();


    //THRONE
    modelStack.PushMatrix();
    modelStack.Translate(230, -2, 0);
    modelStack.Rotate(-90, 0, 1, 0);
    modelStack.Scale(2, 2, 2);
    RenderMesh(meshList[GEO_THRONE], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(-13, 15, 0);
    modelStack.Scale(2, 2, 2);
    RenderText(meshList[GEO_TEXT], "Bawser's Throne", Color(1, 1, 0));
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    //Pedestal (Peach)
    modelStack.PushMatrix();
    modelStack.Translate(230, -2, -25);
    modelStack.Scale(5, 8, 5);
    RenderMesh(meshList[GEO_PEDESTAL], true, toggleLight);

    if (peachTaken == false)
    {
        modelStack.PushMatrix();

        modelStack.Translate(0, 1.5, 0);
        modelStack.Scale(1, 1, 1);
        RenderMesh(meshList[GEO_PEACH], false, toggleLight);

        modelStack.PushMatrix();
        modelStack.Translate(0, 1, -2.5);
        modelStack.Rotate(-90, 0, 1, 0);
        modelStack.Scale(0.4, 0.4, 0.4);
        RenderText(meshList[GEO_TEXT], "Princess 'Peach'", Color(1, 1, 0));
        modelStack.PopMatrix();

        modelStack.PopMatrix();
    }

    modelStack.PopMatrix();

    //Pedestal (Key)
    modelStack.PushMatrix();
    modelStack.Translate(230, -2, 25); 
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(5, 8, 5);
    RenderMesh(meshList[GEO_PEDESTAL], true, toggleLight);


    if (keyTaken == false)
    {
        modelStack.PushMatrix();

        modelStack.Translate(-0.75, 1.5, 0);
        modelStack.Scale(0.8, 0.8, 0.8);
        RenderMesh(meshList[GEO_KEY], true, toggleLight);

        modelStack.PushMatrix();
        modelStack.Translate(1, 1, 0);
        modelStack.Rotate(180, 0, 1, 0);
        modelStack.Scale(0.4, 0.4, 0.4);
        RenderText(meshList[GEO_TEXT], "Key", Color(1, 1, 0));
        modelStack.PopMatrix();

        modelStack.PopMatrix();
    }

    modelStack.PopMatrix();

    //Lava
    //modelStack.PushMatrix();
    //modelStack.Translate(150, -2, 0);
    //modelStack.Scale(2, 2, 2);
    //RenderMesh(meshList[GEO_LAVA], true, toggleLight);
    //modelStack.PopMatrix();

    //Pillar
    modelStack.PushMatrix();
    modelStack.Translate(40, -2, 40);
    modelStack.Scale(5, 6.5, 5);
    RenderMesh(meshList[GEO_PILLAR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(40, -2, -40);
    modelStack.Scale(5, 6.5, 5);
    RenderMesh(meshList[GEO_PILLAR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-40, -2, 40);
    modelStack.Scale(5, 6.5, 5);
    RenderMesh(meshList[GEO_PILLAR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-40, -2, -40);
    modelStack.Scale(5, 6.5, 5);
    RenderMesh(meshList[GEO_PILLAR], true, toggleLight);
    modelStack.PopMatrix();

    // On screen text
    ////std::ostringstream target;
    //std::ostringstream position;
    ////ss << "FPS: " << FramesPerSecond;
    ////target << "Camera Target: " << (int)camera3.target.x << " " << (int)camera3.target.y << " " << (int)camera3.target.z;
    //Vector3 boundsCheck = camera3.position + (camera3.target - camera3.position).Normalized();
    //position << "Position: " << (int)camera3.position.x << " " << (int)camera3.position.y << " " << (int)camera3.position.z;
    ////position << "Bounds: " << (int)boundsCheck.x << " " << (int)boundsCheck.y << " " << (int)boundsCheck.z;
    ////RenderTextOnScreen(meshList[GEO_TEXT], target.str(), Color(0, 1, 0), 3, 0, 2);
    //RenderTextOnScreen(meshList[GEO_TEXT], position.str(), Color(0, 1, 0), 3, 0, 3);

    //std::stringstream thwump;
    //std::stringstream thwump1;
    //std::stringstream thwump2;
    //for (int i = 0; i < objsMaxMin.size(); ++i)
    //{
    //    if (objsMaxMin[i].name == "thwump3")
    //    {
    //        //thwump << "Bounds: " << (float)objsMaxMin[i].maxPos.z << " " << (float)objsMaxMin[i].minPos.z;
    //        thwump << "Bounds(z): " << (int)(objsMaxMin[i].maxPos.z + objsMaxMin[i].offSet.z + 3) << " " << (int)(objsMaxMin[i].minPos.z + objsMaxMin[i].offSet.z - 3);
    //        thwump1 << "Bounds(x): " << (int)(objsMaxMin[i].maxPos.x + objsMaxMin[i].offSet.x + 3) << " " << (int)(objsMaxMin[i].minPos.x + objsMaxMin[i].offSet.x - 3);
    //        thwump2 << "Bounds(y): " << (int)(objsMaxMin[i].maxPos.y + objsMaxMin[i].offSet.y) << " " << (int)(objsMaxMin[i].minPos.y + objsMaxMin[i].offSet.y);
    //    }
    //}
    //RenderTextOnScreen(meshList[GEO_TEXT], thwump.str(), Color(0, 1, 0), 3, 0, 8);
    //RenderTextOnScreen(meshList[GEO_TEXT], thwump1.str(), Color(0, 1, 0), 3, 0, 7);
    //RenderTextOnScreen(meshList[GEO_TEXT], thwump2.str(), Color(0, 1, 0), 3, 0, 6);

    std::stringstream ss;
    ss << "FPS: " << FramesPerSecond;
    RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 2, 28, 28);

    if (gateMsg == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Message: Press 'E' to open gate", Color(0, 1, 0), 2, 0, 2);
    }

    if (gateLockedMsg == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Message: Gate is locked!", Color(0, 1, 0), 3, 0, 5);
    }

    if (gateUnlockMsg == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Message: Press 'E' to unlock gate", Color(0, 1, 0), 2, 0, 2);
    }

    if (peachMsg == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Message: Press 'E' to save 'Peach'", Color(0, 1, 0), 2, 0, 2);
    }

    if (peachTaken == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Message: Get 'Peach' out!", Color(0, 1, 0), 2, 0, 3);
    }

    if (keyMsg == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Message: Press 'E' get a Key", Color(0, 1, 0), 2, 0, 2);
    }

    if (doorEnterMsg == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Message: Press 'E' to escape!", Color(0, 1, 0), 2, 0, 2);
    }

    if (doorErrorMsg == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Get 'Peach' first!", Color(0, 1, 0), 2, 0, 3);
    }

    // ADD HTHWUMP COLLSION

    // ------------------------------------------------------------ ESCAPE ROOM ------------------------------------------------------------ //
    // Floor
    modelStack.PushMatrix();
    modelStack.Translate(300, -2, 300);
    modelStack.Scale(100, 100, 100);
    RenderMesh(meshList[GEO_GROUND], true, toggleLight);
    modelStack.PopMatrix();

    // Ceiling
    modelStack.PushMatrix();
    modelStack.Translate(300, 35, 300);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Scale(100, 100, 100);
    RenderMesh(meshList[GEO_GROUND], true, toggleLight);
    modelStack.PopMatrix();

    // Left
    modelStack.PushMatrix();

    modelStack.Translate(300, 0, 250);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // Right
    modelStack.PushMatrix();

    modelStack.Translate(300, 0, 350);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();
 
    // Front
    modelStack.PushMatrix();

    modelStack.Translate(350, 0, 300);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // Back
    modelStack.PushMatrix();

    modelStack.Translate(250, 0, 300);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(10, 5, 10);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 1);
    modelStack.Scale(1, 3, 1);
    RenderMesh(meshList[GEO_DOOR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 6, 0);
    RenderMesh(meshList[GEO_WALL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(335, -2, 300);

    modelStack.PushMatrix();
    modelStack.Translate(0, 10, -3);
    modelStack.Rotate(-90, 0, 1, 0);
    RenderText(meshList[GEO_TEXT], "ESCAPE", Color(1, 1, 0));
    modelStack.PopMatrix();

    modelStack.Scale(5, 5, 5);
    RenderMesh(meshList[GEO_PIPE], true, toggleLight);
    modelStack.PopMatrix();

    if (pipeMsg == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "Message: Press 'E' to escape!", Color(0, 1, 0), 2, 0, 2);
    }

    if (completedMsg == true)
    {
        RenderTextOnScreen(meshList[GEO_TEXT], "COMPLETED", Color(0, 1, 0), 3, 0, 5);
    }
    // ------------------------------------------------------------ ESCAPE ROOM ------------------------------------------------------------ //
}

void Asn3::Exit()
{
    // Cleanup VBO here
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
