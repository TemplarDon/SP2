#include "Asn1.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"

#include <iostream>

#include "shader.hpp"
#include "vector"

Asn1::Asn1()
{
}

Asn1::~Asn1()
{
}

void Asn1::Init()
{
    // Init VBO here
    //Set Background to dark blue
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    rotateAngle = 0;
    scaleAll = 0;
    sun_count = 0;
    humanTranslate = -15;
    humanHand = 0;
    firstLap = false;
    fireBreakOff = false;
    translateX = -19.7;
    translateY = -25;
    gateAnimation = 0;
    gateOpen = true;
    cloudTranslate = -30;

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

    //Tower Body/Rectangle
    static const GLfloat vertex_buffer_data[] = {
        0.0f, -0.5f, 0.0f,
        0.0f, 1.5f, 0.0f,
        1.5f, -0.5f, 0.0f,
        1.5f, -0.5f, 0.0f,
        0.0f, 1.5f, 0.0f,
        1.5f, 1.5f, 0.0f
    };

    //Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    //Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data[] = {
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RECTANGLE]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------

    //Battlements------------------------------------------------------------------------------------------------
    static const GLfloat vertex_buffer_data2[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    //Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    //Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data2[] = {
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------

    //Walls------------------------------------------------------------------------------------------------------
    static const GLfloat vertex_buffer_data3[] = {
        0.0f, 0.0f, 0.0f,
        2.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        2.0f, 0.0f, 0.0f,
        2.0f, 1.0f, 0.0f
    };

    //Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_WALLS]);
    //Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data3[] = {
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
        0.125f, 0.125f, 0.125f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WALLS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------

    //Bridge/Road------------------------------------------------------------------------------------------------
    static const GLfloat vertex_buffer_data4[] = {
        0.0f, 0.0f, 0.0f,
        -0.5f, -2.0f, 0.0f,
        0.5f, -2.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, -2.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.5f, -2.0f, 0.0f,
        1.5f, -2.0f, 0.0f
    };

    //Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GE0_BRIDGE]);
    //Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4), vertex_buffer_data4, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data4[] = {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GE0_BRIDGE]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------

    //Gate-------------------------------------------------------------------------------------------------------
    static const GLfloat vertex_buffer_data5[] = {
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.5, 0.0, 0.0,

        0.5, 0.0, 0.0,
        0.5, 1.0, 0.0,
        0.0, 1.0, 0.0,

        0.0, 1.0, 0.0,
        0.5, 1.0, 0.0,
        0.5, 1.5, 0.0,

        0.5, 1.5, 0.0,
        1.5, 1.5, 0.0,
        0.5, 1.0, 0.0,

        0.5, 1.0, 0.0,
        1.5, 1.0, 0.0,
        1.5, 1.5, 0.0,

        1.5, 1.5, 0.0,
        1.5, 1.0, 0.0,
        2.0, 1.0, 0.0,

        2.0, 1.0, 0.0,
        1.5, 1, 0,
        2, 0 , 0,

        2, 0, 0,
        1.5, 1, 0,
        1.5, 0, 0,
    };

    //Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_GATE]);
    //Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data5), vertex_buffer_data5, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data5[] = {
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
        0.545, 0.270, 0.074,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_GATE]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data5), color_buffer_data5, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------

    //Sun--------------------------------------------------------------------------------------------------------
    static GLfloat vertex_buffer_data6[36 * 3] = {};
    static GLfloat color_buffer_data6[36 * 3] = {};

    float circle_x = 0;
    float circle_y = 0;
    std::vector<float>circle;
    std::vector<float>circleColour;

    for (double angle = 0; angle <= 2 * Math::PI;)
    {
        circle_x = cos(angle) * 1;
        circle_y = sin(angle) * 1;
        circle.push_back(circle_x);
        circle.push_back(circle_y);
        circle.push_back(0.0);
        angle += (2 * Math::PI / 36);
        circleColour.push_back(1.0f);
        circleColour.push_back(1.0f);
        circleColour.push_back(1.0f);
    }

    for (int i = 0; i < 36*3; ++i)
    {
        vertex_buffer_data6[i] = circle[i];
        color_buffer_data6[i] = circleColour[i];
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data6), vertex_buffer_data6, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data6), color_buffer_data6, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------

    //Torch-Stand------------------------------------------------------------------------------------------------
    //Triangle
    static const GLfloat vertex_buffer_data7[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
    };
    //Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
    //Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data7), vertex_buffer_data7, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data7[] = {
        1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data7), color_buffer_data7, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------

    //Background-------------------------------------------------------------------------------------------------
    static const GLfloat vertex_buffer_data8[] = {
        -40, -30 , 0,
        -40, -5, 0,
        40, -30, 0,

        40, -30, 0,
        40, -5, 0,
        -40, -5, 0,

        -40, -5, 0,
        -40, 30, 0,
        40, -5, 0,

        40, -5, 0,
        40, 30, 0,
        -40, 30, 0,
    };
    //Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BACKGROUND]);
    //Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data8), vertex_buffer_data8, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data8[] = {
        0.0f, 0.4f, 0.0f,
        0.0f, 0.4f, 0.0f,
        0.0f, 0.4f, 0.0f,
        0.0f, 0.4f, 0.0f,
        0.0f, 0.4f, 0.0f,
        0.0f, 0.4f, 0.0f,

        0.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 0.2f, 
        0.0f, 0.0f, 0.2f, 
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BACKGROUND]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data8), color_buffer_data8, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------

    //Dark Blue--------------------------------------------------------------------------------------------------
    static const GLfloat color_buffer_data9[] = {
        0.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 0.2f,
    };
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DARKBLUE]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data9), color_buffer_data9, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------

    //Red--------------------------------------------------------------------------------------------------------
    static GLfloat color_buffer_data10[36*3] = {};
    circleColour.clear();

    for (int i = 0; i < 36 * 3; ++i)
    {
        circleColour.push_back(1.0);
        circleColour.push_back(0.54);
        circleColour.push_back(0.0);
        color_buffer_data10[i] = circleColour[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RED]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data10), color_buffer_data10, GL_STATIC_DRAW);
    //-----------------------------------------------------------------------------------------------------------
}
void Asn1::Update(double dt)
{
    
    if (humanTranslate >= -30 && firstLap == false)
    {
        humanTranslate -= 0.1;
        humanHand -= 0.5;
        if (humanTranslate < -30)
        {
            firstLap = true;
        }
    }
    if (humanTranslate <= -15 && firstLap == true)
    {
        humanTranslate += 0.1;
        humanHand += 0.5;
        if (humanTranslate > -15)
        {
            firstLap = false;
        }
    }

    if (scaleAll <= 6)
    {
        scaleAll += 0.1;
    }
    else
    {
        scaleAll = 1;
        fireBreakOff = true;
    }

    if (fireBreakOff == true)
    {
        translateY += 0.3;
        translateX += sin(translateX);
        if (translateY > 30)
        {
            fireBreakOff = false;
        }
    }
    else
    {
        translateY = -15;
        translateX = -19.7;
    }

    if (gateAnimation > -6 && gateOpen == true)
    {
        gateAnimation -= 0.1;
        if (gateAnimation < -6)
        {
            gateOpen = false;
        }
    }
    else if (gateOpen == false)
    {
        gateAnimation += 0.1;
        if (gateAnimation > 5)
        {
            gateOpen = true;
        }
    }

    if (cloudTranslate <= 40)
    {
        cloudTranslate += 0.1;
        if (cloudTranslate > 40)
        {
            cloudTranslate = -40;
        }
    }
}

void Asn1::Render()
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

    //Backgound-------------------------------------------------------------
    scale.SetToScale(1, 1, 1);

    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(0, 0, -9);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BACKGROUND]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BACKGROUND]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Walls
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 12);
    //----------------------------------------------------------------------

    //Castle Body/Rectangle-------------------------------------------------
    scale.SetToScale(10, 10, 10);
    //Left Side
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-30, -5, 0);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Castle Body/Rectangle
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

    //Right Side
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(15, -5, 0);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Castle Body/Rectangle
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    //-----------------------------------------------------------------------

    //Background Castle------------------------------------------------------
    scale.SetToScale(12, 12, 12);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-24, 5, -1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Castle Body/Rectangle
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

    //Battlement
    scale.SetToScale(8, 8, 8);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-28, 20, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    //Battlement
    scale.SetToScale(8, 8, 8);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-22, 20, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    //Battlement
    scale.SetToScale(8, 8, 8);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-16, 20, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    //Battlement
    scale.SetToScale(8, 8, 8);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-10, 20, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    //Battlement
    scale.SetToScale(8, 8, 8);
    rotate.SetToRotation(90, 0, 0, 1);
    translate.SetToTranslation(0, 20, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);


    //-----------------------------------------------------------------------

    //Battlements------------------------------------------------------------
    scale.SetToScale(10, 10, 10);
    
    
    //Left Side Tower
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-35, 10, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Battlement
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-25, 10, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Battlement
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    rotate.SetToRotation(90, 0, 0, 1);
    translate.SetToTranslation(-10, 10, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Battlement
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);



    //Right Side Tower
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(10, 10, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Battlement
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(20, 10, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Battlement
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    rotate.SetToRotation(90, 0, 0, 1);
    translate.SetToTranslation(35, 10, 5);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Battlement
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);
    //-----------------------------------------------------------------------

    //Walls------------------------------------------------------------------
    scale.SetToScale(10, 10, 10);

    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-40, -10, -1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_WALLS]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WALLS]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Walls
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);



    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-25, -10, -1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_WALLS]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WALLS]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Walls
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);



    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(5, -10, -1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_WALLS]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WALLS]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Walls
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);



    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(20, -10, -1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_WALLS]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WALLS]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Walls
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    //-----------------------------------------------------------------------

    //Bridge-----------------------------------------------------------------
    scale.SetToScale(10, 10, 10);

    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-5, -10, 1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GE0_BRIDGE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GE0_BRIDGE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Bridge
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);
    //-----------------------------------------------------------------------

    //Gate-------------------------------------------------------------------
    scale.SetToScale(10, 10, 10);

    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-10, -10, 1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_GATE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_GATE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Gate
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);

    //Gate Closing & Opening
    scale.SetToScale(8, 8, 8);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-6, gateAnimation, -1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Gate
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);

    //Gate Cover-up
    scale.SetToScale(8, 8, 8);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-6, 5.5, 0);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_DARKBLUE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Gate
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    //-----------------------------------------------------------------------

    //Sun--------------------------------------------------------------------
    scale.SetToScale(8, 8, 8);
    rotate.SetToRotation(rotateAngle, 0, 0, 1);
    translate.SetToTranslation(10, 25, 0);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Sun
    glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
    //-----------------------------------------------------------------------


    //Right-Torch-Holder-----------------------------------------------------
    //Torch-Holder Body
    scale.SetToScale(7, 7, 7);
    rotate.SetToRotation(0, 0, 0, 7);
    translate.SetToTranslation(14.5, -25, 9);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Torch-Holder
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

    //Torch-Holder Triangle
    scale.SetToScale(14, 14, 14);
    rotate.SetToRotation(0, 0, 0, 7);
    translate.SetToTranslation(19.7, -25, 1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Torch-Holder
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //Fire Outer
    scale.SetToScale(scaleAll - 2, scaleAll + 2, scaleAll);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(19.7, -15, 7);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Fire
    glDrawArrays(GL_TRIANGLE_FAN, 0, 36*3);

    //Fire Inner
    scale.SetToScale(scaleAll - 3, scaleAll - 1, scaleAll);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(19.7, -15, 8);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RED]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //Draw the Fire
    glDrawArrays(GL_TRIANGLE_FAN, 0, 36 * 3);


    //Fire Breakoff
    scale.SetToScale(1, 2 , 3);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(translateX + 42, translateY, 9);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Torch-Holder
    glDrawArrays(GL_TRIANGLE_FAN, 0, 360 * 3);
    //-----------------------------------------------------------------------

    //Left-Torch-Holder------------------------------------------------------
    //Torch-Holder Body
    scale.SetToScale(7, 7, 7);
    rotate.SetToRotation(0, 0, 0, 7);
    translate.SetToTranslation(-25, -25, 9);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Torch-Holder
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

    //Torch-Holder Triangle
    scale.SetToScale(14, 14, 14);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-19.7, -25, 1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Torch-Holder
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //Outer Fire
    scale.SetToScale(scaleAll - 2, scaleAll + 2, scaleAll);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-19.7, -15, 7);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Fire
    glDrawArrays(GL_TRIANGLE_FAN, 0, 360 * 3);

    //Fire Inner
    scale.SetToScale(scaleAll - 3, scaleAll - 1, scaleAll);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-19.7, -15, 8);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RED]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //Draw the Fire
    glDrawArrays(GL_TRIANGLE_FAN, 0, 36 * 3);


    //Fire Breakoff
    scale.SetToScale(3, 3, 3);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(translateX , translateY, 9);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Torch-Holder
    glDrawArrays(GL_TRIANGLE_FAN, 0, 360 * 3);
    //-----------------------------------------------------------------------

    //Human------------------------------------------------------------------
    scale.SetToScale(2, 2, 2);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(humanTranslate, 22, 10);
    model = translate * rotate * scale; 
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); 

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 36*3);

    scale.SetToScale(8, 6, 6);
    rotate.SetToRotation(180, 0, 0, 1);

    translate.SetToTranslation(humanTranslate, 20, 0);
    model = translate * rotate * scale; 
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); 

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    scale.SetToScale(3, 3, 3);
    rotate.SetToRotation(humanHand, 0, 0, 1);
    translate.SetToTranslation(humanTranslate + 1.5, 17, 0);
    model = translate * rotate * scale;
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //-----------------------------------------------------------------------

    //Flag-------------------------------------------------------------------
    //Left
    //Flag Top
    scale.SetToScale(5, 5, 5);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-26.5, 0, 6);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WALLS]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Flag
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

    //Inner Triangle
    scale.SetToScale(5, 5, 5);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-22.7, 0, 7);
    model = translate * rotate * scale;
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BACKGROUND]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //Outer Circle
    scale.SetToScale(3, 3, 3);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(-22.7, 3, 7);
    model = translate * rotate * scale;
    MVP = projection * view * model;

    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, 360*3);

    //Flag Edge
    scale.SetToScale(5, 5, 5);
    rotate.SetToRotation(180, 0, 0, 1);
    translate.SetToTranslation(-19, -2, 2);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    scale.SetToScale(5, 5, 5);
    rotate.SetToRotation(270, 0, 0, 1);
    translate.SetToTranslation(-26.5, -2, 2);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    //Right
    //Flag Top
    scale.SetToScale(5, 5, 5);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(19, 0, 6);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WALLS]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Flag
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

    //Inner Triangle
    scale.SetToScale(5, 5, 5);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(22.8, 0, 7);
    model = translate * rotate * scale;
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BACKGROUND]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //Outer Circle
    scale.SetToScale(3, 3, 3);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(22.8, 3, 7);
    model = translate * rotate * scale;
    MVP = projection * view * model;

    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, 360 * 3);

    //Flag Edge
    scale.SetToScale(5, 5, 5);
    rotate.SetToRotation(180, 0, 0, 1);
    translate.SetToTranslation(26.5, -2, 2);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    scale.SetToScale(5, 5, 5);
    rotate.SetToRotation(270, 0, 0, 1);
    translate.SetToTranslation(19, -2, 2);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BATTLEMENT]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);
    //-----------------------------------------------------------------------

    //Clouds-----------------------------------------------------------------
    scale.SetToScale(5, 3, 8);
    rotate.SetToRotation(rotateAngle, 0, 0, 1);
    translate.SetToTranslation(cloudTranslate, 28, -1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Clouds
    glDrawArrays(GL_TRIANGLE_FAN, 0, 360);

    scale.SetToScale(5, 3, 8);
    rotate.SetToRotation(90 + rotateAngle, 0, 0, 1);
    translate.SetToTranslation(cloudTranslate, 28, -1);
    model = translate * rotate * scale; //matrix multiplication is opposite way TRS
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update shader with new MVP

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SUN]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SUN]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Clouds
    glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
    //-----------------------------------------------------------------------
    glDisableVertexAttribArray(1);

    glDisableVertexAttribArray(0);
}

void Asn1::Exit()
{
    // Cleanup VBO here
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);

    glDeleteProgram(m_programID);

}
