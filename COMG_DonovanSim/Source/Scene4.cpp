#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
    // Init VBO here

    // Set background color to dark blue
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //Enable depth buffer and depth testing
    glEnable(GL_DEPTH_TEST);

    //Enable back face culling
    glEnable(GL_CULL_FACE);

    //Default to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //Load vertex and fragment shaders
    m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
    // Use our shader
    glUseProgram(m_programID);
    // Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

    //variable to rotate geometry
    rotateAngle = 0;
    planet1RevAngle = planet1RotAngle = moon1RotAngle = 0;
    venusRevAngle = venusRotAngle = 360;
    earthRevAngle = earthRotAngle = moonRevAngle = 0;
    marsRevAngle = marsRotAngle = 0;
    jupiterRevAngle = jupiterRotAngle = 0;
    saturnRevAngle = saturnRotAngle = 0;
    uranusRevAngle = uranusRotAngle = 0;
    neptuneRevAngle = neptuneRotAngle = 0;

    //Initialize camera settings
    camera.Init(Vector3(60, 40, 40), Vector3(0, 0, 0), Vector3(0, 1, 0));

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
    meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0));
    //meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1);
    //meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", 1, 1);

    meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 0), 0.3f, 4);
    meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0, 1), 36);
    meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 10, 36);

    meshList[GEO_PLANET1] = MeshBuilder::GenerateSphere("Planet1", Color(1, 0, 0), 10, 36);
    meshList[GEO_MOON1] = MeshBuilder::GenerateSphere("Moon1", Color(1, 0, 1), 10, 36);
    meshList[GEO_RING1] = MeshBuilder::GenerateRing("Ring1", Color(1, 1, 1), 0.8f, 36);

    //Solar system
    meshList[GEO_SUN] = MeshBuilder::GenerateSphere("Sun", Color(1, 1, 0), 10, 36);
    meshList[GEO_MERCURY] = MeshBuilder::GenerateSphere("Mercury", Color(0.545, 0.270, 0.074), 10, 36);
    meshList[GEO_VENUS] = MeshBuilder::GenerateSphere("Venus", Color(0.823, 0.411, 0.117), 10, 36);
    meshList[GEO_EARTH] = MeshBuilder::GenerateSphere("Earth", Color(0, 1, 0), 10, 36);
    meshList[GEO_MOON] = MeshBuilder::GenerateSphere("Moon", Color(0.596, 0.596, 0.596), 10, 36);
    meshList[GEO_MARS] = MeshBuilder::GenerateSphere("Mars", Color(0.647, 0.164, 0.164), 10, 36);
    meshList[GEO_JUPITER] = MeshBuilder::GenerateSphere("Jupiter", Color(0.960, 0.870, 0.701), 10, 36);
    meshList[GEO_SATURN] = MeshBuilder::GenerateSphere("Saturn", Color(0.960, 0.870, 0.701), 10, 36);
    meshList[GEO_SATURNRING] = MeshBuilder::GenerateRing("Saturn Ring", Color(0.960, 0.870, 0.701), 0.95f, 36);
    meshList[GEO_URANUS] = MeshBuilder::GenerateSphere("Uranus", Color(0, 0, 1), 10, 36);
    meshList[GEO_NEPTUNE] = MeshBuilder::GenerateSphere("NEPTUNE", Color(0.5, 0.5, 1), 10, 36);

    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
    projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Scene4::Update(double dt)
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

    rotateAngle += (float)(15 * dt);

    planet1RevAngle += (float)(10 * dt);
    planet1RotAngle += (float)(8 * dt);
    moon1RotAngle += (float)(80 * dt);

    venusRevAngle -= (float)(10 * dt);
    venusRotAngle -= (float)(8 * dt);

    earthRevAngle += (float)(12 * dt);
    earthRotAngle += (float)(4 * dt);
    moonRevAngle += (float)(80 * dt);

    marsRevAngle += (float)(15 * dt);
    marsRotAngle += (float)(6 * dt);

    jupiterRevAngle += (float)(13 * dt);
    jupiterRotAngle += (float)(3 * dt);

    saturnRevAngle += (float)(20 * dt);
    saturnRotAngle += (float)(10 * dt);

    uranusRevAngle += (float)(22 * dt);
    uranusRotAngle += (float)(10 * dt);

    neptuneRevAngle += (float)(20 * dt);
    neptuneRotAngle += (float)(8 * dt);
}

void Scene4::Render()
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

    //AXES
    modelStack.PushMatrix();
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_AXES]->Render();
    modelStack.PopMatrix();

    //SUN
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 0);//Bring to origin
    modelStack.Rotate(15, 0, 0, 1);//Tilt the sun4
    modelStack.Rotate(rotateAngle, 0, 1, 0);//Rotate the sun on an axis
    modelStack.Scale(3, 3, 3);
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_SUN]->Render();
    modelStack.PopMatrix();

    //Mercury
    modelStack.PushMatrix();
    modelStack.Rotate(rotateAngle, 0, 0, 1); //revolution
    modelStack.Rotate(rotateAngle, 0, 1, 0); //rotate on axis
    modelStack.Translate(6, 2, 0); //offset from centre
    modelStack.Scale(0.3, 0.3, 0.3); //Size
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_MERCURY]->Render();
    modelStack.PopMatrix();

    //Venus
    modelStack.PushMatrix();
    modelStack.Rotate(venusRevAngle, 0, 1, 0); //revolution
    modelStack.Rotate(venusRotAngle, 0, 1, 0); //rotate on axis
    modelStack.Translate(8, 1, 0); //offset from centre
    modelStack.Scale(0.45, 0.45, 0.45); //Size
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_VENUS]->Render();
    modelStack.PopMatrix();


    //Earth System
    modelStack.PushMatrix();
    modelStack.Rotate(earthRevAngle, 0, 0.5, 0);
    modelStack.Translate(10, 2, 0); //offset from centre

    //Moon (Earth System)
    modelStack.PushMatrix();
    modelStack.Rotate(moonRevAngle, 1, 0, 0); //Revolve around Earth
    modelStack.Translate(0, 2, 0);
    modelStack.Scale(0.2, 0.2, 0.2);
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_MOON]->Render();
    modelStack.PopMatrix();

    //Earth itself
    modelStack.PushMatrix();
    modelStack.Rotate(earthRotAngle, 0, 1, 0); //rotate on its own axis
    modelStack.Scale(0.8, 0.8, 0.8); //planet size
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_EARTH]->Render();
    modelStack.PopMatrix();

    modelStack.PopMatrix();


    //Mars
    modelStack.PushMatrix();
    modelStack.Rotate(marsRevAngle, 0, 1, 0); //revolution
    modelStack.Rotate(marsRotAngle, 0, 1, 0); //rotate on axis
    modelStack.Translate(12, 1, 0); //offset from centre
    modelStack.Scale(0.75, 0.75, 0.75); //Size
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_MARS]->Render();
    modelStack.PopMatrix();

    //Jupiter
    modelStack.PushMatrix();
    modelStack.Rotate(jupiterRevAngle, 0, 1, 1); //revolution
    modelStack.Rotate(jupiterRotAngle, 0, 1, 0); //rotate on axis
    modelStack.Translate(25, 1, 1); //offset from centre
    modelStack.Scale(2.5, 2.5, 2.5); //Size
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_JUPITER]->Render();
    modelStack.PopMatrix();


    //Saturn System
    modelStack.PushMatrix();
    modelStack.Rotate(saturnRevAngle, 1, 1, 0);
    modelStack.Translate(32, 2, 0); //offset from centre

    //Saturn Itself
    modelStack.PushMatrix();
    modelStack.Rotate(saturnRotAngle, 0, 1, 0); //rotate on its own axis

    modelStack.PushMatrix(); 
    modelStack.Scale(2, 2, 2); //planet size
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_SATURN]->Render();
    modelStack.PopMatrix();

    //Saturn Ring
    modelStack.PushMatrix();
    modelStack.Scale(3, 3, 3);
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_SATURNRING]->Render();
    modelStack.PopMatrix();

    modelStack.PopMatrix();
    modelStack.PopMatrix();

    //Uranus
    modelStack.PushMatrix();
    modelStack.Rotate(uranusRevAngle, 0, 1, 1); //revolution
    modelStack.Rotate(uranusRotAngle, 0, 1, 0); //rotate on axis
    modelStack.Translate(38, 1, 1); //offset from centre
    modelStack.Scale(0.8, 0.8, 0.8); //Size
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_URANUS]->Render();
    modelStack.PopMatrix();

    //Neptune
    modelStack.PushMatrix();
    modelStack.Rotate(neptuneRevAngle, 0, 1, 1); //revolution
    modelStack.Rotate(neptuneRotAngle, 0, 1, 0); //rotate on axis
    modelStack.Translate(42, 5, 1); //offset from centre
    modelStack.Scale(0.65, 0.65, 0.65); //Size
    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_NEPTUNE]->Render();
    modelStack.PopMatrix();

    
}

void Scene4::Exit()
{
    // Cleanup VBO here
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
