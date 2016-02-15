#include "Asn2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Utility.h"

#include "Application.h"
#include "MeshBuilder.h"

Asn2::Asn2()
{
}

Asn2::~Asn2()
{
}

void Asn2::Init()
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
    m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");

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

    glUseProgram(m_programID);

    light[0].position.Set(0, 10, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 2.2;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.001f;

    //Make sure you pass uniform parameters after glUseProgram()
    glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
    glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
    glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
    glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
    glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

    //variable to rotate geometry
    rotateAngle = propellorWingAngle = propellorRotateAngle = 0;

    waveArmAnimation = false;
    armGoingUp = true;
    armWaveAngle = 0;

    mouthRotateAnimation = false;
    mouthOpen = false;
    mouthRotateAngle = 0;

    fireExpand = 1;
    fireExpanding = true;

    cannonFireDistance = 0;
    cannonFiring = false;
    bombExploding = false;
    bombExplosion = 0;
    bombDestroyed = false;

    modelXLocation = modelYLocation = modelZLocation = 0;
    directionAngle = leanAngle =  0;

    toggleLight = true;

    //Initialize camera settings
    camera.Init(Vector3(20, 8, 8), Vector3(0, 0, 0), Vector3(0, 1, 0));

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

    //Light
    meshList[GEO_SHIPBODY] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 10, 36);
    meshList[GEO_SHIPBODY]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
    meshList[GEO_SHIPBODY]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
    meshList[GEO_SHIPBODY]->material.kSpecular.Set(0.4f, 0.4f, 0.4f);
    meshList[GEO_SHIPBODY]->material.kShininess = 10.f;

    meshList[GEO_SHIPTORUS] = MeshBuilder::GenerateTorus("ship torus", Color(0, 1, 0), 0.2f, 0.6f ,10, 36);

    meshList[GEO_SHIPCANNON] = MeshBuilder::GenerateCylinder("cannon body", Color(0, 0, 0), 4, 36);
    meshList[GEO_SHIPCANNON]->material.kSpecular.Set(0.6f, 0.6f, 0.6f);
    meshList[GEO_SHIPCANNON]->material.kShininess = 14.f;

    meshList[GEO_SHIPCANNONTORUS] = MeshBuilder::GenerateTorus("ship cannon torus", Color(0, 0, 0), 0.3f, 0.6f, 10, 36);
    meshList[GEO_SHIPCANNONTORUS]->material.kSpecular.Set(0.6f, 0.6f, 0.6f);
    meshList[GEO_SHIPCANNONTORUS]->material.kShininess = 12.f;

    meshList[GEO_SHIPLIPS] = MeshBuilder::GenerateCube("ship cannon lips", Color(1, 0.647, 0));

    meshList[GEO_SHIPMOUTH] = MeshBuilder::GenerateCube("ship cannon mouth", Color(0, 0, 0));

    meshList[GEO_EYES] = MeshBuilder::GenerateHemisphere("eyes", Color(0, 0, 0), 10, 36);
    meshList[GEO_EYES]->material.kSpecular.Set(0.6f, 0.6f, 0.6f);
    meshList[GEO_EYES]->material.kShininess = 12.f;

    meshList[GEO_EYESSIDES] = MeshBuilder::GenerateHemisphere("eyes side things", Color(1, 0.5, 0), 10, 36);

    meshList[GEO_PROPELLOR] = MeshBuilder::GenerateSphere("propellor", Color(0, 1, 0), 10, 36);

    meshList[GEO_BOWSERBODY] = MeshBuilder::GenerateSphere("Bowser Body", Color(1, 1, 0), 10, 36);

    meshList[GEO_BOWSERBELLY] = MeshBuilder::GenerateSphere("Bowser Belly", Color(0.941, 0.901, 0.549/*1,1,1*/), 10, 36);

    meshList[GEO_BOWSERHEAD] = MeshBuilder::GenerateSphere("Bowser Head", Color(0, 1, 0), 10, 36);

    meshList[GEO_BOWSERHAIR] = MeshBuilder::GenerateHair("Hair", Color(1, 0.270, 0));
    meshList[GEO_BOWSERHAIR]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
    meshList[GEO_BOWSERHAIR]->material.kShininess = 1.f;

    meshList[GEO_BOWSERCHIN] = MeshBuilder::GenerateHemisphere("Bowser Chin", Color(1, 1, 0), 10, 36);

    meshList[GEO_INSIDEMOUTH] = MeshBuilder::GenerateCube("Inner Mouth", Color(1, 0, 0));

    meshList[GEO_OUTERSHELL] = MeshBuilder::GenerateTorus("Outer Shell", Color(1, 1, 1), 0.2f, 0.6f, 10, 36);

    meshList[GEO_INNERSHELL] = MeshBuilder::GenerateHemisphere("Inner Shell", Color(0.1, 1, 0.1), 10, 36);

    meshList[GEO_SPIKECONE] = MeshBuilder::GenerateCone("Cone", Color(1, 0.8, 0.76), 36);

    meshList[GEO_SPIKETORUS] = MeshBuilder::GenerateTorus("Spike Torus", Color(0.545, 0.270, 0.074), 0.2f, 0.6f, 10, 36);

    meshList[GEO_ARM] = MeshBuilder::GenerateCylinder("Arm", Color(1, 1, 0), 6, 36);

    meshList[GEO_ARMCONNECTOR] = MeshBuilder::GenerateSphere("Arm Connector", Color(1, 1, 0), 10, 36);

    meshList[GEO_BOMBBODY] = MeshBuilder::GenerateSphere("Bomb Body", Color(0, 0, 0.2), 10, 36);

    meshList[GEO_BOMBTORUS] = MeshBuilder::GenerateTorus("Bomb Torus", Color(0.854, 0.647, 0.125), 0.2f, 0.6f, 10, 36);

    meshList[GEO_BOMBSTRING] = MeshBuilder::GenerateCylinder("String", Color(1, 1, 1), 6, 36);

    meshList[GEO_BOMBFIRE] = MeshBuilder::GenerateSphere("Bomb Fire", Color(0.886, 0.345, 0.133), 10, 36);

    meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.941, 0.901, 0.549));
    meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(0, 1, 0), 5, 36);
    meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", Color(1, 1, 1), 10, 36);
    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("LightBall", Color(1, 1, 1), 10, 20);

    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
    projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Asn2::Update(double dt)
{
    if (Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if (Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

    camera.Update(dt);

    if (Application::IsKeyPressed('W'))
    {
        /*moveForward += 0.3f;*/
        modelXLocation += (0.5)*(cos(Math::DegreeToRadian(directionAngle)));
        modelZLocation -= (0.5)*(sin(Math::DegreeToRadian(directionAngle)));
        if (leanAngle < 15)
        {
            leanAngle += 1.f;
        }
    }
    if (Application::IsKeyPressed('S'))
    {
        /*moveForward -= 0.3f;*/
        modelXLocation -= (0.5)*(cos(Math::DegreeToRadian(directionAngle)));
        modelZLocation += (0.5)*(sin(Math::DegreeToRadian(directionAngle)));
        if (leanAngle > -5)
        {
            leanAngle -= 1.f;
        }
    }
    if (!Application::IsKeyPressed('W') || !Application::IsKeyPressed('S'))
    {
        if (leanAngle < 0)
        {
            leanAngle += (float)(15 * dt);
        }
        else if (leanAngle > 0)
        {
            leanAngle -= (float)(15 * dt);
        }
    }
    if (Application::IsKeyPressed('A'))
    {
        /*moveLeft += 0.3f;*/
        directionAngle += 1.f;
    }
    if (Application::IsKeyPressed('D'))
    {
        /*moveLeft -= 0.3f;*/
        directionAngle -= 1.f;
    }
    if (Application::IsKeyPressed('Z'))
    {
        modelYLocation += 0.1f;
    }
    if (Application::IsKeyPressed('X'))
    {
        modelYLocation -= 0.1f;
    }

    if (Application::IsKeyPressed('R'))
    {
        armWaveAngle = 0;
        armGoingUp = true;
        waveArmAnimation = false;
        mouthRotateAnimation = false;
        cannonFiring = false;
        modelXLocation = modelYLocation = modelZLocation = 0;
    }

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

    rotateAngle += (float)(15 * dt);

    /*propellorWingAngle += (float)(600 * dt);*/
    propellorRotateAngle += (float)(800 * dt);
    

    if (Application::IsKeyPressed('6'))
    {
        waveArmAnimation = true;
    }
    if (Application::IsKeyPressed('7'))
    {
        waveArmAnimation = false;
    }

    // Wave Hand
    if (waveArmAnimation == true)
    {
        if (armGoingUp == true)
        {
            armWaveAngle += (float)(100 * dt);
            if (armWaveAngle >= 90)
            {
                armGoingUp = false;
            }
        }

        if (armGoingUp == false)
        {
            armWaveAngle -= (float)(100 * dt);
            if (armWaveAngle <= 0)
            {
                armGoingUp = true;
            }
        }
    }

    if (Application::IsKeyPressed('8'))
    {
        mouthRotateAnimation = true;
    }
    if (Application::IsKeyPressed('9'))
    {
        mouthRotateAnimation = false;
    }

    // Mouth Open
    if(mouthRotateAnimation == true)
    {
        if (mouthOpen == true)
        {
            mouthRotateAngle += (float)(50 * dt);
            if (mouthRotateAngle >= 18)
            {
                mouthOpen = false;
            }
        }

        if (mouthOpen == false)
        {
            mouthRotateAngle -= (float)(50 * dt);
            if (mouthRotateAngle <= 0)
            {
                mouthOpen = true;
            }
        }
    }

    // Fire Expansion / Bomb
    if (fireExpanding == true)
    {
        fireExpand += (float)(2 * dt);
        if (fireExpand >= 2)
        {
            fireExpanding = false;
        }
    }
    
    if (fireExpanding == false)
    {
        fireExpand -= (float)(2 * dt);
        if (fireExpand <= 1.2)
        {
            fireExpanding = true;
        }
        
    }

    // Cannon fire
    if (Application::IsKeyPressed('0'))
    {
        cannonFiring = true;
    }
    if (cannonFiring == true)
    {
        cannonFireDistance += (float)(10 * dt);
        if (cannonFireDistance >= 8)
        {
            cannonFiring = false;
            bombExploding = true;
        }
    }
    if (bombExploding == true)
    {
        bombExplosion += (float)(2 * dt);

        if (bombExplosion >= 3)
        {
            bombExploding = false;
            //bombDestroyed = true;
            cannonFireDistance = 0;
        }
    }

    if (bombExploding == false)
    {
        bombExplosion -= (float)(2 * dt);
        if (bombExplosion <= 1.5)
        {
            bombExplosion = 0;
        }
    }
    

}

void Asn2::RenderMesh(Mesh *mesh, bool enableLight, bool toggleLight)
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
    mesh->Render();

}

void Asn2::Render()
{
    // Render VBO here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Set view matrix using camera settings
    viewStack.LoadIdentity();
    viewStack.LookAt(
        camera.position.x, camera.position.y, camera.position.z,
        camera.target.x, camera.target.y, camera.target.z,
        camera.up.x, camera.up.y, camera.up.z
        );

    modelStack.LoadIdentity();

    Mtx44 MVP;

    Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
    glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

    //AXES
    RenderMesh(meshList[GEO_AXES], false, toggleLight);

    //LIGHTBALL
    modelStack.PushMatrix();
    modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
    modelStack.PopMatrix();

    // Start of Environment
    modelStack.PushMatrix();
    modelStack.Translate(0, -25, 0);
    modelStack.Scale(300, 20, 300);
    RenderMesh(meshList[GEO_CUBE], true, toggleLight);
    modelStack.PopMatrix();

    // Pipe
    modelStack.PushMatrix();

    modelStack.Translate(-23, -25, -18);
    modelStack.Scale(5, 6, 5);
    RenderMesh(meshList[GEO_CYLINDER], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 3.5, 0);
    modelStack.Scale(1.5, 1.5, 1.5);
    RenderMesh(meshList[GEO_SHIPTORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 2, 0);
    modelStack.Scale(0.8, 0.7, 0.8);
    RenderMesh(meshList[GEO_BOMBBODY], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // Another Pipe
    modelStack.PushMatrix();

    modelStack.Translate(-25, -25, 25);
    modelStack.Scale(5, 6, 5);
    RenderMesh(meshList[GEO_CYLINDER], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 3.5, 0);
    modelStack.Scale(1.5, 1.5, 1.5);
    RenderMesh(meshList[GEO_SHIPTORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 2, 0);
    modelStack.Scale(0.8, 0.7, 0.8);
    RenderMesh(meshList[GEO_BOMBBODY], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // Another Pipe
    modelStack.PushMatrix();

    modelStack.Translate(26, -25, 19);
    modelStack.Scale(5, 6, 5);
    RenderMesh(meshList[GEO_CYLINDER], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(0, 3.5, 0);
    modelStack.Scale(1.5, 1.5, 1.5);
    RenderMesh(meshList[GEO_SHIPTORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 2, 0);
    modelStack.Scale(0.8, 0.7, 0.8);
    RenderMesh(meshList[GEO_BOMBBODY], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // End of Environment

    // Start of Entire Body
    modelStack.PushMatrix();
    modelStack.Translate(modelXLocation, -15 + modelYLocation, modelZLocation);
    modelStack.Rotate(directionAngle, 0, 1, 0);
    modelStack.Rotate(-leanAngle, 0, 0, 1);
    modelStack.Scale(4, 4, 4);

    // Start of Ship 
    modelStack.PushMatrix();
    //modelStack.Rotate(turnLeft, 0, 1, 0);

    // Body of 'Ship'
    modelStack.PushMatrix();
    modelStack.Translate(0, 2, 0);
    modelStack.Scale(1.3, 1.3, 1.3);
    RenderMesh(meshList[GEO_SHIPBODY], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 2.8, 0);
    modelStack.Scale(1.5, 1, 1.5);
    RenderMesh(meshList[GEO_SHIPTORUS], true, toggleLight);
    modelStack.PopMatrix();

    // Start of Propellor 
    modelStack.PushMatrix();
    modelStack.Rotate(propellorRotateAngle, 0, 1, 0);

    // Middle Bit
    modelStack.PushMatrix();
    modelStack.Translate(0, 0.6, 0);
    modelStack.Scale(0.2, 0.5, 0.2);
    modelStack.Rotate(90, 1, 0, 0);
    RenderMesh(meshList[GEO_SHIPTORUS], true, toggleLight);
    modelStack.PopMatrix();
    
    // Wing
    modelStack.PushMatrix();
    modelStack.Translate(0.55, 0.6, 0);
    modelStack.Rotate(propellorWingAngle, 1, 0, 0);
    modelStack.Rotate(35, 1, 0, 0);
    modelStack.Scale(0.5, 0.01, 0.3);
    RenderMesh(meshList[GEO_PROPELLOR], true, toggleLight);
    modelStack.PopMatrix();

    //Another Wing
    modelStack.PushMatrix();
    modelStack.Translate(-0.55, 0.6, 0);
    modelStack.Rotate(-propellorWingAngle, 1, 0, 0);
    modelStack.Rotate(-35, 1, 0, 0);
    modelStack.Scale(0.5, 0.01, 0.3);
    RenderMesh(meshList[GEO_PROPELLOR], true, toggleLight);
    modelStack.PopMatrix();

    // End of Propellor
    modelStack.PopMatrix();
    
    // Start of Face of 'Ship'
    modelStack.PushMatrix();

    // Start of Eyes
    modelStack.PushMatrix();
    modelStack.Translate(1, 2.5, -0.5);

    //Left eye
    modelStack.PushMatrix();

    //Orange Hemisphere
    modelStack.PushMatrix();
    modelStack.Translate(-0.1, 0, -0.2);
    modelStack.Rotate(270, 0, 0, 1);
    modelStack.Scale(0.1, 0.1, 0.1);
    RenderMesh(meshList[GEO_EYESSIDES], true, toggleLight);
    modelStack.PopMatrix();

    //Black Hemisphere
    modelStack.PushMatrix();
    modelStack.Rotate(270, 0, 0, 1);
    modelStack.Scale(0.15, 0.15, 0.15);
    RenderMesh(meshList[GEO_EYES], true, toggleLight);
    modelStack.PopMatrix();

    //Orange Hemisphere
    modelStack.PushMatrix();
    modelStack.Translate(0.1, 0, 0.2);
    modelStack.Rotate(270, 0, 0, 1);
    modelStack.Scale(0.1, 0.1, 0.1);
    RenderMesh(meshList[GEO_EYESSIDES], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    //Right eye
    modelStack.PushMatrix();

    //Orange Hemisphere
    modelStack.PushMatrix();
    modelStack.Translate(0.1, 0, 0.8);
    modelStack.Rotate(270, 0, 0, 1);
    modelStack.Scale(0.1, 0.1, 0.1);
    RenderMesh(meshList[GEO_EYESSIDES], true, toggleLight);
    modelStack.PopMatrix();

    //Black Hemisphere
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 1);
    modelStack.Rotate(270, 0, 0, 1);
    modelStack.Scale(0.15, 0.15, 0.15);
    RenderMesh(meshList[GEO_EYES], true, toggleLight);
    modelStack.PopMatrix();

    //Orange Hemisphere
    modelStack.PushMatrix();
    modelStack.Translate(-0.1, 0, 1.2);
    modelStack.Rotate(270, 0, 0, 1);
    modelStack.Scale(0.1, 0.1, 0.1);
    RenderMesh(meshList[GEO_EYESSIDES], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    //End of eyes
    modelStack.PopMatrix();
    
    // Start of Cannon
    modelStack.PushMatrix();
    modelStack.Scale(0.8, 1.3, 1.4);

    // 'Lips'
    modelStack.PushMatrix();
    modelStack.Translate(1.6, 1.7, 0);
    modelStack.Scale(0.18, 0.15, 1);
    RenderMesh(meshList[GEO_SHIPLIPS], true, toggleLight);

    modelStack.PushMatrix();
    modelStack.Translate(-1.8, -2.3, 0);
    modelStack.Scale(4.5, 4.5, 1);
    RenderMesh(meshList[GEO_SHIPMOUTH], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.Translate(0, -4.6, 0);
    modelStack.Rotate(-30, 0, 0, 1);
    RenderMesh(meshList[GEO_SHIPLIPS], true, toggleLight);
    modelStack.PopMatrix();

    // Cannon Body
    modelStack.PushMatrix();
    modelStack.Translate(1.8, 1.35, 0);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Scale(0.3, 0.3, 0.3);
    RenderMesh(meshList[GEO_SHIPCANNON], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(2.2, 1.35, 0);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Scale(0.5, 0.5, 0.5);
    RenderMesh(meshList[GEO_SHIPCANNONTORUS], true, toggleLight);
    modelStack.PopMatrix();

    // Start of Bomb
    modelStack.PushMatrix();
    modelStack.Translate(1 + cannonFireDistance, 1.3, 0);
    modelStack.Scale(0.25, 0.15, 0.15);
    if (bombDestroyed == false)
    {
        RenderMesh(meshList[GEO_BOMBBODY], true, toggleLight);
    }
    

    // Start of Ring ontop
    modelStack.PushMatrix();
    modelStack.Translate(0, 0.95, 0);
    modelStack.Scale(0.4, 0.4, 0.4);
    if (bombDestroyed == false)
    {
        RenderMesh(meshList[GEO_SHIPCANNONTORUS], true, toggleLight);
    }
    

    // String
    modelStack.PushMatrix();
    modelStack.Scale(0.5, 0.4, 0.5);
    if (bombDestroyed == false)
    {
        RenderMesh(meshList[GEO_BOMBSTRING], true, toggleLight);
    }
    

    // Fire
    modelStack.PushMatrix();
    modelStack.Translate(0, 3.5, 0);
    modelStack.Scale(1.2, fireExpand + 0.5, 1.2);
    if (bombDestroyed == false)
    {
        RenderMesh(meshList[GEO_BOMBFIRE], true, toggleLight);
    }
    
    modelStack.PopMatrix();

    modelStack.PopMatrix();
    // End of String

    modelStack.PopMatrix();
    // End of Ring

    // Start of Eyes
    // Left Eye
    modelStack.PushMatrix();
    modelStack.Translate(0.9, 0, 0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Scale(0.3, 0.1, 0.1);
    if (bombDestroyed == false)
    {
        RenderMesh(meshList[GEO_SHIPBODY], true, toggleLight);
    }
    
    modelStack.PopMatrix();

    //Right Eye
    modelStack.PushMatrix();
    modelStack.Translate(0.9, 0, -0.4);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Scale(0.3, 0.1, 0.1);
    if (bombDestroyed == false)
    {
        RenderMesh(meshList[GEO_SHIPBODY], true, toggleLight);
    }
   
    modelStack.PopMatrix();
    // End of Eyes 

    // Start of Propellor
    modelStack.PushMatrix();
    modelStack.Translate(-1, 0, 0);
    modelStack.Rotate(propellorRotateAngle, 1, 0, 0);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Scale(0.15, 0.15, 0.15);
    if (bombDestroyed == false)
    {
       RenderMesh(meshList[GEO_ARM], true, toggleLight);
    }

    // Bomb Torus
    modelStack.PushMatrix();
    modelStack.Translate(-1.5, -1.3, 0);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Scale(3, 3, 3);
    if (bombDestroyed == false)
    {
        RenderMesh(meshList[GEO_BOMBTORUS], true, toggleLight);
    }
    modelStack.PopMatrix();

    // Other Torus
    modelStack.PushMatrix();
    modelStack.Translate(1.5, -1.3, 0);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Scale(3, 3, 3);
    if (bombDestroyed == false)
    {
        RenderMesh(meshList[GEO_BOMBTORUS], true, toggleLight);
    }
    modelStack.PopMatrix();

    modelStack.PopMatrix();
    // End of Propeller

    if (bombExploding == true)
    {
        modelStack.Scale(5 + fireExpand, 5 + fireExpand, 5 + fireExpand);
        RenderMesh(meshList[GEO_BOMBFIRE], true, toggleLight);
    }

    modelStack.PopMatrix();
    // End of Bomb

    modelStack.PopMatrix();
    // End of Cannon

    modelStack.PopMatrix();
    // End of Face of 'Ship'

    modelStack.PopMatrix();
    // End of Ship


    

    // Start of Bowser Jr. Body
    modelStack.PushMatrix();

    // Start of Head
    modelStack.PushMatrix();
    modelStack.Translate(0.3, 4, 0); 
    modelStack.Scale(0.5, 0.5, 0.5);
    //modelStack.Translate(0.5, 8, 0);
    RenderMesh(meshList[GEO_BOWSERHEAD], true, toggleLight);

    // Hair
    // Hair Ring
    modelStack.PushMatrix();
    modelStack.Translate(0, 1, 0);
    modelStack.Scale(0.2, 0.2, 0.2);
    modelStack.PushMatrix();
    modelStack.Scale(1.5, 1.5, 1.5);
    RenderMesh(meshList[GEO_SHIPCANNONTORUS], true, toggleLight);
    modelStack.PopMatrix();

    // Hair
    modelStack.PushMatrix();
    modelStack.Translate(0.5, 0, 0.8);
    modelStack.Rotate(100, 0, 0, 1);
    modelStack.Scale(5, 5, 3);
    RenderMesh(meshList[GEO_BOWSERHAIR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0.5, 0, 0);
    modelStack.Rotate(-30, 0, 1, 0);
    modelStack.Rotate(100, 0, 0, 1);
    modelStack.Scale(3, 3, 1.5);
    RenderMesh(meshList[GEO_BOWSERHAIR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0.5, 0, 0.8);
    modelStack.Rotate(30, 0, 1, 0);
    modelStack.Rotate(100, 0, 0, 1);
    modelStack.Scale(3, 3, 1.5);
    RenderMesh(meshList[GEO_BOWSERHAIR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // Eyes
    // Left
    modelStack.PushMatrix();
    modelStack.Translate(0.55, 0.5, 0.65);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Scale(0.12, 0.12, 0.12);
    RenderMesh(meshList[GEO_EYES], true, toggleLight);
    // Eyebrows
    modelStack.PushMatrix();
    modelStack.Translate(-0.5, 1, -2);
    modelStack.Rotate(-150, 0, 0, 1);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Scale(5, 4, 2);
    RenderMesh(meshList[GEO_BOWSERHAIR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // Right
    modelStack.PushMatrix();
    modelStack.Translate(0.55, 0.5, -0.65);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Scale(0.12, 0.12, 0.12);
    RenderMesh(meshList[GEO_EYES], true, toggleLight);

    // Eyebrows
    modelStack.PushMatrix();
    modelStack.Translate(-0.5, 1, 2);
    modelStack.Rotate(-150, 0, 0, 1);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Scale(5, 4, 2);
    RenderMesh(meshList[GEO_BOWSERHAIR], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // Spikes on Head
    //Left
    modelStack.PushMatrix();
    modelStack.Translate(0, 0.8, 0.6);
    modelStack.Rotate(30, 1, 0, 0);
    modelStack.Scale(0.2, 0.2, 0.2);
    RenderMesh(meshList[GEO_SPIKETORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 0.8, 0.6);
    modelStack.Rotate(25, 1, 0, 0);
    modelStack.Scale(0.1, 0.2, 0.1);
    RenderMesh(meshList[GEO_SPIKECONE], true, toggleLight);
    modelStack.PopMatrix();
    
    // Right
    modelStack.PushMatrix();
    modelStack.Translate(0, 0.8, -0.6);
    modelStack.Rotate(-30, 1, 0, 0);
    modelStack.Scale(0.2, 0.2, 0.2);
    RenderMesh(meshList[GEO_SPIKETORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 0.8, -0.6);
    modelStack.Rotate(-30, 1, 0, 0);
    modelStack.Scale(0.1, 0.2, 0.1);
    RenderMesh(meshList[GEO_SPIKECONE], true, toggleLight);
    modelStack.PopMatrix();

    // Start of Nose / Chin
    modelStack.PushMatrix();
    modelStack.Translate(0.3, -0.3, 0);
    modelStack.Scale(1.1, 0.95, 0.9);
    
    modelStack.PushMatrix();
    modelStack.Rotate(180, 0, 1, 0);
    RenderMesh(meshList[GEO_BOWSERCHIN], true, toggleLight);
    modelStack.PopMatrix();

    // Start of Chin / Jaw
    modelStack.PushMatrix();
    modelStack.Translate(-1, -1, 0);
    modelStack.Rotate(-mouthRotateAngle, 0, 0, 1);
    RenderMesh(meshList[GEO_INSIDEMOUTH], true, toggleLight);

    // Lower Jaw
    modelStack.PushMatrix();
    modelStack.Translate(1, 1, 0);
    modelStack.Rotate(180, 1, 0, 0);
    RenderMesh(meshList[GEO_BOWSERCHIN], true, toggleLight);
    //modelStack.Translate(0.05, -0.05, 0);
    modelStack.Scale(1, 0.65, 1.5);
    RenderMesh(meshList[GEO_INSIDEMOUTH], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    // Nostrils
    // Left
    modelStack.PushMatrix();
    modelStack.Translate(0.75, 0.5, 0.3);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Scale(0.05, 0.05, 0.05);
    RenderMesh(meshList[GEO_EYES], true, toggleLight);
    modelStack.PopMatrix();
    // Right
    modelStack.PushMatrix();
    modelStack.Translate(0.75, 0.5, -0.3);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Scale(0.05, 0.05, 0.05);
    RenderMesh(meshList[GEO_EYES], true, toggleLight);
    modelStack.PopMatrix();

    //Right Cheek
    modelStack.PushMatrix();
    modelStack.Translate(-0.2, 0, 0.7);
    modelStack.Scale(0.75, 0.7, 0.75);
    RenderMesh(meshList[GEO_BOWSERBODY], true, toggleLight);
    modelStack.PopMatrix();

    //Left Cheek
    modelStack.PushMatrix();
    modelStack.Translate(-0.2, 0, -0.7);
    modelStack.Scale(0.75, 0.7, 0.75);
    RenderMesh(meshList[GEO_BOWSERBODY], true, toggleLight);
    modelStack.PopMatrix();

    // End of Nose / Chin
    modelStack.PopMatrix();
    

    modelStack.PopMatrix();
    // End of Head

    // Start of Body
    modelStack.PushMatrix();
    modelStack.Scale(0.9, 1, 0.9);
    modelStack.Translate(0, 3, 0);
    RenderMesh(meshList[GEO_BOWSERBODY], true, toggleLight);

    modelStack.Translate(0.6, 0.2, 0);
    modelStack.Rotate(-90, 0, 0, 1);
    modelStack.Scale(0.5, 0.5, 0.7);
    RenderMesh(meshList[GEO_BOWSERBELLY], true, toggleLight);

    modelStack.PopMatrix();
    // End of Body

    // Start of Left Arm
    // Shoulder
    modelStack.PushMatrix();
    modelStack.Translate(0, 3.5, 0.5);
    modelStack.Rotate(110 - armWaveAngle, 1, 0, 0);
    modelStack.Scale(0.3, 0.3, 0.3);
    RenderMesh(meshList[GEO_ARMCONNECTOR], true, toggleLight);
    // Arm
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 0);
    modelStack.Scale(0.7, 0.8, 0.7);
    RenderMesh(meshList[GEO_ARM], true, toggleLight);

    // Hand
    modelStack.PushMatrix();
    modelStack.Translate(0, 3.2, 0);
    modelStack.Scale(1.1, 1.1, 1.1);
    RenderMesh(meshList[GEO_ARMCONNECTOR], true, toggleLight);

    //Arm-Band
    modelStack.PushMatrix();
    modelStack.Translate(0, -0.8, 0);
    modelStack.Scale(1.2, 1.2, 1.2);
    RenderMesh(meshList[GEO_SHIPCANNONTORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PopMatrix();
    // End of Left Arm

    // Start of Right Arm
    // Shoulder
    modelStack.PushMatrix();
    modelStack.Translate(0, 3.5, -0.5);
    modelStack.Rotate(-110 + armWaveAngle, 1, 0, 0);
    modelStack.Scale(0.3, 0.3, 0.3);
    RenderMesh(meshList[GEO_ARMCONNECTOR], true, toggleLight);
    // Arm
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 0);
    modelStack.Scale(0.7, 0.8, 0.7);
    RenderMesh(meshList[GEO_ARM], true, toggleLight);

    // Hand
    modelStack.PushMatrix();
    modelStack.Translate(0, 3.2, 0);
    modelStack.Scale(1.1, 1.1, 1.1);
    RenderMesh(meshList[GEO_ARMCONNECTOR], true, toggleLight);

    //Arm-Band
    modelStack.PushMatrix();
    modelStack.Translate(0, -0.8, 0);
    modelStack.Scale(1.2, 1.2, 1.2);
    RenderMesh(meshList[GEO_SHIPCANNONTORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PopMatrix();

    modelStack.PopMatrix();
    // End of Right Arm

    // Start of Shell
    modelStack.PushMatrix();

    // Shell Body
    modelStack.PushMatrix();
    modelStack.Translate(-0.5, 3.5, 0);
    modelStack.Rotate(45, 0, 0, 1);
    RenderMesh(meshList[GEO_OUTERSHELL], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-0.5, 3.5, 0);
    modelStack.Rotate(45, 0, 0, 1);
    modelStack.Scale(0.65, 0.65, 0.65);
    RenderMesh(meshList[GEO_INNERSHELL], true, toggleLight);
    modelStack.PopMatrix();
    // End of Shell Body

    // Spikes
    // Top-Middle
    modelStack.PushMatrix();
    modelStack.Translate(-0.5, 4.15, 0);
    modelStack.Rotate(0, 0, 0, 1);
    modelStack.Scale(0.2, 0.2, 0.2);
    RenderMesh(meshList[GEO_SPIKETORUS], true, toggleLight);
    modelStack.PopMatrix();
    
    modelStack.PushMatrix();
    modelStack.Translate(-0.5, 4.15, 0);
    modelStack.Rotate(0, 0, 0, 1);
    modelStack.Scale(0.1, 0.2, 0.1);
    RenderMesh(meshList[GEO_SPIKECONE], true, toggleLight);
    modelStack.PopMatrix();

    // Middle-Middle
    modelStack.PushMatrix();
    modelStack.Translate(-0.95, 4, 0);
    modelStack.Rotate(45, 0, 0, 1);
    modelStack.Scale(0.2, 0.2, 0.2);
    RenderMesh(meshList[GEO_SPIKETORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-0.95, 4, 0);
    modelStack.Rotate(45, 0, 0, 1);
    modelStack.Scale(0.1, 0.2, 0.1);
    RenderMesh(meshList[GEO_SPIKECONE], true, toggleLight);
    modelStack.PopMatrix();

    // Middle-Bottom
    modelStack.PushMatrix();
    modelStack.Translate(-1.15, 3.55, 0);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Scale(0.2, 0.2, 0.2);
    RenderMesh(meshList[GEO_SPIKETORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-1.15, 3.55, 0);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Scale(0.1, 0.2, 0.1);
    RenderMesh(meshList[GEO_SPIKECONE], true, toggleLight);
    modelStack.PopMatrix();

    // Left-Top
    modelStack.PushMatrix();
    modelStack.Translate(-0.7, 4, -0.4);
    modelStack.Rotate(-40, 1, 0, 0);
    modelStack.Scale(0.2, 0.2, 0.2);
    RenderMesh(meshList[GEO_SPIKETORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-0.7, 4, -0.4);
    modelStack.Rotate(-40, 1, 0, 0);
    modelStack.Scale(0.1, 0.2, 0.1);
    RenderMesh(meshList[GEO_SPIKECONE], true, toggleLight);
    modelStack.PopMatrix();

    // Right-Top
    modelStack.PushMatrix();
    modelStack.Translate(-0.7, 4, 0.4);
    modelStack.Rotate(40, 1, 0, 0);
    modelStack.Scale(0.2, 0.2, 0.2);
    RenderMesh(meshList[GEO_SPIKETORUS], true, toggleLight);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-0.7, 4, 0.4);
    modelStack.Rotate(40, 1, 0, 0);
    modelStack.Scale(0.1, 0.2, 0.1);
    RenderMesh(meshList[GEO_SPIKECONE], true, toggleLight);
    modelStack.PopMatrix();
    // End of Spikes

    modelStack.PopMatrix();
    // End of Shell

    modelStack.PopMatrix();
    // End of Bower Jr. Body

    modelStack.PopMatrix();
    // End of Entire Body


}

void Asn2::Exit()
{
    // Cleanup VBO here
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
