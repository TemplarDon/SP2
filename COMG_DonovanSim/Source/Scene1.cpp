#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	// Init VBO here
    //Set Background to dark blue
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //Generate a default VBO
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //Generate Buffers
    glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

    //Enable Depth Test
    glEnable(GL_DEPTH_TEST);

    //1st Triangle-----------------------------------------
    //An array of 3 vectors which represents 3 vertices
    //static const GLfloat vertex_buffer_data[] = {
    //    -1.0f, 1.0f, -1.0f, //vertex 0 of triangle
    //    -1.0f, -1.0f, -1.0f, //vertex 1 of triangle
    //    0.25f, 0.0f, -1.0f, //vertex 2 of triangle
    //};

    static const GLfloat vertex_buffer_data[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.0f, 0.0f,
    };

    //Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
    //Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    // An array of 3 vetors which represents the colors of the 3 vertices
    //static const GLfloat color_buffer_data[] = {
    //    0.255f, 0.0f, 1.0f, //Colour of vertex 0
    //    0.255f, 0.0f, 1.0f, //Colour of vertex 1
    //    0.255f, 0.0f, 1.0f, //Colour of vertex 2
    //};

    static const GLfloat color_buffer_data[] = {
        1.0f, 1.0f, 1.0f,
        2.0f, 2.0f, 3.0f,
        3.0f, 3.0f, 3.0f,
        4.0f, 4.0f, 4.0f,
        5.0f, 5.0f, 5.0f,
        6.0f, 6.0f, 6.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
    //------------------------------------------------------

    //2nd Triangle------------------------------------------
    static const GLfloat vertex_buffer_data2[] = {
        1.0f, 1.0f, 0.0f, //vertex 0 of triangle
        1.0f, -1.0f, 0.0f, //vertex 1 of triangle
        -0.5f, 0.0f, 0.0f, //vertex 2 of triangle
    };

    //Set the current active buffer for 2nd
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
    //Transfer vertices to OpenGL for 2nd
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

    // An array of 3 vetors which represents the colors of the 3 vertices (2nd)
    static const GLfloat color_buffer_data2[] = {
        0.255f, 0.255f, 0.255f, //Colour of vertex 0
        0.255f, 0.255f, 0.255f, //Colour of vertex 1
        0.255f, 0.255f, 0.255f, //Colour of vertex 2
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);
    //--------------------------------------------------------

    //8-Sided Polygon------------------------------------------
    static const GLfloat vertex_buffer_data3[] = {
        0.5f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, -0.5f, 0.0f,
        0.5f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        -1.0f, -0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -1.0f, 0.5f, 0.0f,
        -0.5f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
    };

    //Set the current active buffer for Polygon
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_POLYGON]);
    //Transfer vertices to OpenGL for Polygon
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);

    // An array of 3 vetors which represents the colors of the 3 vertices (2nd)
    static const GLfloat color_buffer_data3[] = {
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_POLYGON]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);
    //--------------------------------------------------------

    //Star----------------------------------------------------
    static const GLfloat vertex_buffer_data4[] = {
        0.0f, 0.75f, 0.0f,//1 top
        0.25f, 0.25f, 0.0f,
        -0.25f, 0.25f, 0.0f,
        0.25f, 0.25f, 0.0f,//2  right
        0.75f, 0.25f, 0.0f,
        0.5f, -0.25f, 0.0f,
        0.5f, -0.25f, 0.0f,//3 btm-right
        0.75f, -0.75f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,//4 btm-left
        -0.75f, -0.75f, 0.0f,
        -0.5f, -0.25f, 0.0f,
        -0.5f, -0.25f, 0.0f,//5 left
        -0.75f, 0.25f, 0.0f,
        -0.25f, 0.25f, 0.0f,
        -0.25f, 0.25f, 0.0f,//6
        -0.5f, -0.25f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.25f, 0.25f, 0.0f,//7
        0.5f, -0.25f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.25f, 0.25f, 0.0f,//8
        0.25f, 0.25f, 0.0f,
        0.0f, -0.5f, 0.0f,
    };

    //Set the current active buffer for Star
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_STAR]);
    //Transfer vertices to OpenGL for Star
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4), vertex_buffer_data4, GL_STATIC_DRAW);

    // An array of 3 vetors which represents the colors of the 3 vertices (2nd)
    static const GLfloat color_buffer_data4[] = {
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_STAR]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);
    //--------------------------------------------------------

    //Castle Tower Test---------------------------------------
    static const GLfloat vertex_buffer_data5[] = {
        0.0f, 0.0f, 0.0f,//Tower Base 1st Half
        0.0f, 0.75f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.75f, 0.0f,//Tower Base 2nd Half
        0.0f, 0.74f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f,//Tower Base Left
        0.0f, 0.3f, 0.5f,
        -0.2f, 0.0f, 0.5f,
    };
    
    //Set the current active buffer for Star
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CASTLE_TEST]);
    //Transfer vertices to OpenGL for Star
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data5), vertex_buffer_data5, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data5[] = {
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
        0.255f, 0.0f, 0.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CASTLE_TEST]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data5), color_buffer_data5, GL_STATIC_DRAW);
    //--------------------------------------------------------
    //Load vertex and fragment shaders
    m_programID = LoadShaders(
        "Shader//SimpleVertexShader.vertexshader",
        "Shader//SimpleFragmentShader.fragmentshader"
        );
    //Use our shader
    glUseProgram(m_programID);
}

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Render VBO here
    // Clear color buffer every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
    glEnableVertexAttribArray(1); // 2nd attribute buffer : colours

    //1st Triangle-------------------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

    glVertexAttribPointer(
        0, // attribute 0. Must match the layout in the shader. Usually 0 is for vertex
        3, // size
        GL_FLOAT, //type
        GL_FALSE, //normalized?
        0, //stride
        0 //array buffer offset
        );

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the 1st triangle
    //glDrawArrays(GL_LINE_STRIP, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle
    //---------------------------------------------------------------

    //2nd Triangle---------------------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);

    glVertexAttribPointer(
        0, // attribute 0. Must match the layout in the shader. Usually 0 is for vertex
        3, // size
        GL_FLOAT, //type
        GL_FALSE, //normalized?
        0, //stride
        0 //array buffer offset
        );

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the 2nd triangle
    //glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle
    //------------------------------------------------------------------

    //Polygon-----------------------------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_POLYGON]);

    glVertexAttribPointer(
        0, // attribute 0. Must match the layout in the shader. Usually 0 is for vertex
        3, // size
        GL_FLOAT, //type
        GL_FALSE, //normalized?
        0, //stride
        0 //array buffer offset
        );

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_POLYGON]);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Polygon
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 13); // Starting from vertex 0; 3 vertices = 1 triangle
    //------------------------------------------------------------------

    //Star--------------------------------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_STAR]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_STAR]);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Star
    glDrawArrays(GL_TRIANGLES, 0, 24); // Starting from vertex 0; 3 vertices = 1 triangle
    //------------------------------------------------------------------

    //Castle_Test--------------------------------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CASTLE_TEST]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CASTLE_TEST]);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Draw the Castle
    //glDrawArrays(GL_TRIANGLES, 0, 9); // Starting from vertex 0; 3 vertices = 1 triangle
    //------------------------------------------------------------------

    glDisableVertexAttribArray(1);

    glDisableVertexAttribArray(0);
}

void Scene1::Exit()
{
	// Cleanup VBO here
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);

    glDeleteProgram(m_programID);

}
