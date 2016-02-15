#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	// Init VBO here
	
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	//// Generate buffers
	//glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	//glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
 //   glGenBuffers(NUM_GEOMETRY, &m_indexBuffer[0]);

	
	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	
	//// An array of 3 vectors which represents 3 vertices
	//static const GLfloat vertex_buffer_data[] = {
	//	-0.5f,-0.5f,-0.5f,
	//	-0.5f,-0.5f, 0.5f,
	//	-0.5f, 0.5f, 0.5f,
	//	 0.5f, 0.5f,-0.5f,
	//	-0.5f,-0.5f,-0.5f,
	//	-0.5f, 0.5f,-0.5f,
	//	 0.5f,-0.5f, 0.5f,
	//	-0.5f,-0.5f,-0.5f,
	//	 0.5f,-0.5f,-0.5f,
	//	 0.5f, 0.5f,-0.5f,
	//	 0.5f,-0.5f,-0.5f,
	//	-0.5f,-0.5f,-0.5f,
	//	-0.5f,-0.5f,-0.5f,
	//	-0.5f, 0.5f, 0.5f,
	//	-0.5f, 0.5f,-0.5f,
	//	 0.5f,-0.5f, 0.5f,
	//	-0.5f,-0.5f, 0.5f,
	//	-0.5f,-0.5f,-0.5f,
	//	-0.5f, 0.5f, 0.5f,
	//	-0.5f,-0.5f, 0.5f,
	//	 0.5f,-0.5f, 0.5f,
	//	 0.5f, 0.5f, 0.5f,
	//	 0.5f,-0.5f,-0.5f,
	//	 0.5f, 0.5f,-0.5f,
	//	 0.5f,-0.5f,-0.5f,
	//	 0.5f, 0.5f, 0.5f,
	//	 0.5f,-0.5f, 0.5f,
	//	 0.5f, 0.5f, 0.5f,
	//	 0.5f, 0.5f,-0.5f,
	//	-0.5f, 0.5f,-0.5f,
	//	 0.5f, 0.5f, 0.5f,
	//	-0.5f, 0.5f,-0.5f,
	//	-0.5f, 0.5f, 0.5f,
	//	 0.5f, 0.5f, 0.5f,
	//	-0.5f, 0.5f, 0.5f,
	//	 0.5f,-0.5f, 0.5f
	//};
	//
	//// Set the current active buffer
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CUBE]);
	//// Transfer vertices to OpenGL
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	//
	//// An array of 3 vectors which represents the colors of the 3 vertices
	//static const GLfloat color_buffer_data[] = {
	//	0.583f,  0.771f,  0.014f,
	//	0.609f,  0.115f,  0.436f,
	//	0.327f,  0.483f,  0.844f,
	//	0.822f,  0.569f,  0.201f,
	//	0.435f,  0.602f,  0.223f,
	//	0.310f,  0.747f,  0.185f,
	//	0.597f,  0.770f,  0.761f,
	//	0.559f,  0.436f,  0.730f,
	//	0.359f,  0.583f,  0.152f,
	//	0.483f,  0.596f,  0.789f,
	//	0.559f,  0.861f,  0.639f,
	//	0.195f,  0.548f,  0.859f,
	//	0.014f,  0.184f,  0.576f,
	//	0.771f,  0.328f,  0.970f,
	//	0.406f,  0.615f,  0.116f,
	//	0.676f,  0.977f,  0.133f,
	//	0.971f,  0.572f,  0.833f,
	//	0.140f,  0.616f,  0.489f,
	//	0.997f,  0.513f,  0.064f,
	//	0.945f,  0.719f,  0.592f,
	//	0.543f,  0.021f,  0.978f,
	//	0.279f,  0.317f,  0.505f,
	//	0.167f,  0.620f,  0.077f,
	//	0.347f,  0.857f,  0.137f,
	//	0.055f,  0.953f,  0.042f,
	//	0.714f,  0.505f,  0.345f,
	//	0.783f,  0.290f,  0.734f,
	//	0.722f,  0.645f,  0.174f,
	//	0.302f,  0.455f,  0.848f,
	//	0.225f,  0.587f,  0.040f,
	//	0.517f,  0.713f,  0.338f,
	//	0.053f,  0.959f,  0.120f,
	//	0.393f,  0.621f,  0.362f,
	//	0.673f,  0.211f,  0.457f,
	//	0.820f,  0.883f,  0.371f,
	//	0.982f,  0.099f,  0.879f
	//};
	//
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CUBE]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

 //   static const GLuint index_buffer_data[] = { // can use GLushort
 //       0, 1, 2,
 //       3, 4, 5,
 //       6, 7, 8,
 //       9, 10, 11,
 //       12, 13, 14,
 //       15, 16, 17,
 //       18, 19, 20,
 //       21, 22, 23, 
 //       24, 25, 26, 
 //       27, 28, 29,
 //       30, 31, 32,
 //       33, 34, 35,

 //   };

 //   glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer[GEO_CUBE]);
 //   glBufferData(GL_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);

	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
    //meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1);
    //meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", 1, 1);
    
    meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0 ,0), 0.3f , 4);
    meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0 ,1), 36);
    meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 10, 36);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Scene3::Update(double dt)
{
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

    camera.Update(dt);

	rotateAngle += (float)(10 * dt);
}

void Scene3::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 translate, rotate, scale;
	Mtx44 MVP;

	//These will be replaced by matrix stack soon
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;

	//Set all matrices to identity
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();

	//Set view matrix using camera settings
	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
					);

	//Set projection matrix to perspective mode
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near plane, Far plane
	
	//glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	//glEnableVertexAttribArray(1); // 2nd attribute buffer : colors

	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToIdentity();
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	////Render call setup
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CUBE]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CUBE]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	////Actual render call
	////glDrawArrays(GL_TRIANGLES, 0, 36);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer[GEO_CUBE]);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);

    model.SetToIdentity(); //Set to Origin
    MVP = projection * view * model; // Remember, matrix multiplication is the other way around
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
    
    meshList[GEO_AXES]->Render();
    //meshList[GEO_CUBE]->Render();
    //meshList[GEO_QUAD]->Render();
    meshList[GEO_CIRCLE]->Render();
    //meshList[GEO_RING]->Render();
    //meshList[GEO_SPHERE]->Render();
}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
