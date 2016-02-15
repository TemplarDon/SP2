#include "Scene2.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"

#include <iostream>

#include "shader.hpp"

Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
    // Init VBO here
    //Set Background to dark blue
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    rotateAngle = 0;
    translateX = 0;
    scaleAll = 0;

    //Load vertex and fragment shaders
    m_programID = LoadShaders(
        "Shader//TransformVertexShader.vertexshader",
        "Shader//SimpleFragmentShader.fragmentshader"
        );

    //Use our shader
    glUseProgram(m_programID);
    //Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");


    //Generate a default VBO
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //Generate Buffers
    glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

    //Enable Depth Test
    glEnable(GL_DEPTH_TEST);

    static const GLfloat vertex_buffer_data[] = {
        -1.0f, 1.0f, -1.0f, //vertex 0 of triangle
        -1.0f, -1.0f, -1.0f, //vertex 1 of triangle
        0.25f, 0.0f, -1.0f, //vertex 2 of triangle
    };

    //Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
    //Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 3.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

  


}

void Scene2::Update(double dt)
{
    if (Application::IsKeyPressed(VK_SPACE))
    {
        rotateAngle += (float)(10 * dt);
        translateX += (float)(10 * dt);
        if (translateX >= 40)
        {
            translateX = -40;
        }

        scaleAll += (float)(2 * dt);
        if (scaleAll >= 10)
        {
            scaleAll = 0;
        }
    }
    
}

void Scene2::Render()
{
    // Render VBO here
    // Clear color buffer every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
    glEnableVertexAttribArray(1); // 2nd attribute buffer : colours

    //Initilise Matrix
    Mtx44 translate, rotate, scale;
    Mtx44 model;
    Mtx44 view;
    Mtx44 projection;
    Mtx44 MVP;

    translate.SetToIdentity();
    rotate.SetToIdentity();
    scale.SetToIdentity();
    model.SetToIdentity();
    view.SetToIdentity(); //No need for camera, set to world's origin

    projection.SetToOrtho(-40, 40, -30, 30, -10, 10); //World cube boundary set by this


    //1st Triangle-------------------------------------------------
    scale.SetToScale(10, 10, 10);
    rotate.SetToRotation(rotateAngle, 0, 0, 1);
    translate.SetToTranslation(1, 1, 1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,0 );
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the 1st triangle
    glDrawArrays(GL_TRIANGLES, 0, 3); 
    //---------------------------------------------------------------

    //2nd Triangle-------------------------------------------------
    scale.SetToScale(1, 1, 1);
    rotate.SetToRotation(60, 0, 0, 1);
    translate.SetToTranslation(translateX, 20, 1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP


    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the 2nd triangle
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle
    //---------------------------------------------------------------

    //3rd Triangle-------------------------------------------------
    scale.SetToScale(scaleAll, scaleAll, 0);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-20, -20, 1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the 3rd triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //---------------------------------------------------------------

    glDisableVertexAttribArray(1);

    glDisableVertexAttribArray(0);
}

void Scene2::Exit()
{
    // Cleanup VBO here
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);

    glDeleteProgram(m_programID);

}
