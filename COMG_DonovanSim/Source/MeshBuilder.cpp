#include "MeshBuilder.h"
#include "GL\glew.h"
#include <vector>
#include "vertex.h"
#include "Mtx44.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;

    Vertex v;

    v.pos.Set(-lengthX, 0, 0);  v.color.Set(1, 0, 0);   vertex_buffer_data.push_back(v);
    v.pos.Set(lengthX, 0, 0);   v.color.Set(1, 0, 0);   vertex_buffer_data.push_back(v);
    v.pos.Set(0, -lengthY, 0);  v.color.Set(0, 1, 0);   vertex_buffer_data.push_back(v);
    v.pos.Set(0, lengthY, 0);   v.color.Set(0, 1, 0);   vertex_buffer_data.push_back(v);
    v.pos.Set(0, 0, -lengthZ);  v.color.Set(0, 0, 1);   vertex_buffer_data.push_back(v);
    v.pos.Set(0, 0, lengthZ);   v.color.Set(0, 0, 1);   vertex_buffer_data.push_back(v);

    index_buffer_data.push_back(0);
    index_buffer_data.push_back(1);
    index_buffer_data.push_back(2);
    index_buffer_data.push_back(3);
    index_buffer_data.push_back(4);
    index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = 6;
    mesh->mode = Mesh::DRAW_LINES;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, std::vector<Node>&objsMaxMin)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    //top
    v.pos.Set(0.5f, 0.f, 0.5f);	    v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0);    vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(1, 1);    vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.f, 0.5f);	    v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(1, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 1);    vertex_buffer_data.push_back(v);

    for (unsigned i = 0; i < 6; ++i)
    {
        index_buffer_data.push_back(i);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLES;

    return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;
    //left
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
    //back
    v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
    //bottom
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
    //front
    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
    //right
    v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
    //top
    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

    for (unsigned i = 0; i < 36; ++i)
    {
        index_buffer_data.push_back(i);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLES;

    return mesh;
}

//Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, float lengthX, float lengthY)
//{
//    std::vector<Vertex> sphere_vertex_buffer_data;
//    std::vector<GLuint> sphere_index_buffer_data;
//
//    Vertex sphere;
//
//    float sphere_x;
//    float sphere_y;
//    float sphere_z;
//
//    for (double angle = 0; angle <= 2 * Math::PI;)
//    {
//        sphere_x = cos(angle) * 1;
//        sphere_y = sin(angle) * 1;
//        sphere_z = 0;
//
//        sphere.pos.Set(sphere_x, sphere_y, sphere_z);  sphere.color.Set(0.583f, 0.771f, 0.014f);   sphere_vertex_buffer_data.push_back(sphere);
//
//        sphere_z += 1;
//        angle += (2 * Math::PI / 36);
//    }
//
//    for (int i = 0; i < 36; ++i)
//    {
//        sphere_index_buffer_data.push_back(i);
//    }
//
//    Mesh *mesh = new Mesh(meshName);
//
//    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sphere_vertex_buffer_data.size() * sizeof(Vertex), &sphere_vertex_buffer_data[0], GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sphere_index_buffer_data.size() * sizeof(GLuint), &sphere_index_buffer_data[0], GL_STATIC_DRAW);
//
//    mesh->indexSize = 36;
//    mesh->mode = Mesh::DRAW_TRIANGLE_FAN;
//    return mesh;
//}



float CircleX(float theta)
{
    return cos(Math::DegreeToRadian(theta));
}

float CircleZ(float theta)
{
    return sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, unsigned numSlices)
{
    std::vector<Vertex> Circle_vertex_buffer_data;
    std::vector<GLuint> Circle_index_buffer_data;

    Vertex v;

    float anglePerSlice = 360.f / numSlices;
    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        float theta = slice * anglePerSlice;
        v.pos.Set(CircleX(theta), 0 ,CircleZ(theta));
        v.color = color;
        v.normal.Set(0, 1, 0);
        Circle_vertex_buffer_data.push_back(v);
    }

    v.pos.Set(0, 1, 0);
    v.color = color;
    v.normal.Set(0, 1, 0);
    Circle_vertex_buffer_data.push_back(v);

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        Circle_index_buffer_data.push_back(slice);
        Circle_index_buffer_data.push_back(numSlices + 1);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, Circle_vertex_buffer_data.size() * sizeof(Vertex), &Circle_vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, Circle_index_buffer_data.size() * sizeof(GLuint), &Circle_index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = Circle_index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
    return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, float innerRadius, unsigned numSlices)
{
    std::vector<Vertex> ring_vertex_buffer_data;
    std::vector<GLuint> ring_index_buffer_data;

    Vertex ring;

    float anglePerSlice = 360.f / numSlices;
    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        float theta = slice * anglePerSlice;
        ring.pos.Set(CircleX(theta), 0, CircleZ(theta));
        ring.color = color;
        ring.normal.Set(0, 1, 0);
        ring_vertex_buffer_data.push_back(ring);

        ring.pos.Set(innerRadius * CircleX(theta), 0, innerRadius * CircleZ(theta));
        ring.color = color;
        ring.normal.Set(0, 1, 0);
        ring_vertex_buffer_data.push_back(ring);
    }

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        ring_index_buffer_data.push_back(2 * slice);
        ring_index_buffer_data.push_back(2 * slice + 1);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, ring_vertex_buffer_data.size() * sizeof(Vertex), &ring_vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, ring_index_buffer_data.size() * sizeof(GLuint), &ring_index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = ring_index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
    return mesh;
}


float SphereX(float phi, float theta)
{
    return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}

float SphereY(float phi, float theta)
{
    return sin(Math::DegreeToRadian(phi));
}

float SphereZ(float phi, float theta)
{
    return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));;
}


Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices)
{
    std::vector<Vertex> sphere_vertex_buffer_data;
    std::vector<GLuint> sphere_index_buffer_data;

    Vertex sphere;

    float anglePerStack = 180.f / numStacks;
    float anglePerSlice = 360.f / numSlices;

    for (unsigned stack = 0; stack < numStacks + 1; ++stack)
    {
        float phi = -90.f + stack * anglePerStack;
        for (unsigned slice = 0; slice < numSlices + 1; ++slice)
        {
            float theta = slice * anglePerSlice;
            sphere.pos.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
            sphere.color = color;
            sphere.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
            sphere.normal.Normalize();
            sphere_vertex_buffer_data.push_back(sphere);
        }
    }



    for (unsigned stack = 0; stack < numStacks; ++stack)
    {
        for (unsigned slice = 0; slice < numSlices + 1; ++slice)
        {
            sphere_index_buffer_data.push_back(stack * (numSlices + 1) + slice);
            sphere_index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
        }
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sphere_vertex_buffer_data.size() * sizeof(Vertex), &sphere_vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sphere_index_buffer_data.size() * sizeof(GLuint), &sphere_index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = sphere_index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
    return mesh;
}

Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices)
{
    std::vector<Vertex> hemisphere_vertex_buffer_data;
    std::vector<GLuint> hemisphere_index_buffer_data;

    Vertex hemisphere;

    float anglePerStack = 180.f / numStacks;
    float anglePerSlice = 360.f / numSlices;

    //Hemisphere
    for (unsigned stack = 0; stack < numStacks + 1; ++stack)
    {
        float phi = 0.f + stack * anglePerStack;
        for (unsigned slice = 0; slice < numSlices + 1; ++slice)
        {
            float theta = slice * anglePerSlice;
            hemisphere.pos.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
            hemisphere.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
            hemisphere.color = color;
            hemisphere_vertex_buffer_data.push_back(hemisphere);
            hemisphere.normal.Set(SphereX(phi + 10, theta), SphereY(phi + 10, theta), SphereZ(phi + 10, theta));
        }
    }

    //Bottom
    for (float theta = 0; theta <= 360; theta += 10)
    {
        hemisphere.normal.Set(0, -1, 0);
        hemisphere.pos.Set(0, 0, 0);
        hemisphere.normal.Set(0, -1, 0);
        hemisphere.pos.Set(CircleX(theta), 0, CircleZ(theta));
        hemisphere.color = color;
        hemisphere_vertex_buffer_data.push_back(hemisphere);
    }



    for (unsigned stack = 0; stack < numStacks; ++stack)
    {
        for (unsigned slice = 0; slice < numSlices + 1; ++slice)
        {
            hemisphere_index_buffer_data.push_back(stack * (numSlices + 1) + slice);
            hemisphere_index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
        }
    }


    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        hemisphere_index_buffer_data.push_back(slice);
        hemisphere_index_buffer_data.push_back(numSlices + 1);
    }


    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, hemisphere_vertex_buffer_data.size() * sizeof(Vertex), &hemisphere_vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, hemisphere_index_buffer_data.size() * sizeof(GLuint), &hemisphere_index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = hemisphere_index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
    return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices)
{
    std::vector<Vertex> cylinder_vertex_buffer_data;
    std::vector<GLuint> cylinder_index_buffer_data;

    Vertex cylinder;
    float height = 5.f;
    float stackHeight = height / numStacks;
    float angleperslice = 360.f / numSlices;

    for (unsigned stack = 0; stack < numStacks + 1; ++stack) // stack
    {
        for (unsigned theta = 0; theta <= 360; theta += 10) // slice
        {
            //add_normal(x(theta), 0, z(theta))
            cylinder.normal.Set(CircleX(theta), 0, CircleZ(theta));
            cylinder.pos.Set(CircleX(theta), (-height / 2) + stack * stackHeight, CircleZ(theta));

            cylinder.normal.Set(CircleX(theta), 0, CircleZ(theta));
            cylinder.pos.Set(CircleX(theta), (-height / 2) + (stack + 1) * stackHeight, CircleZ(theta));

            cylinder_vertex_buffer_data.push_back(cylinder);
            cylinder.color = color;
        }
    }

    for (unsigned theta = 0; theta <= 360; theta += 10) // top
    {
        cylinder.normal.Set(0, 1, 0);
        cylinder.pos.Set(0, -height / 2, 0);
        cylinder.normal.Set(0, 1, 0);
        cylinder.pos.Set(CircleX(theta), height / 2, CircleZ(theta));
        cylinder_vertex_buffer_data.push_back(cylinder);

        cylinder.color = color;
    }

    for (unsigned theta = 0; theta <= 360; theta += 10) // bottom
    {
        cylinder.normal.Set(0, -1, 0);
        cylinder.pos.Set(0, -height / 2, 0);
        cylinder.normal.Set(0, -1, 0);
        cylinder.pos.Set(CircleX(theta), -height / 2, CircleZ(theta));
        cylinder_vertex_buffer_data.push_back(cylinder);

        cylinder.color = color;
    }


    for (unsigned stack = 0; stack < numStacks + 1; stack += 1) // stack
    {
        for (unsigned slice = 0; slice * angleperslice <= 360; slice += 1) // slice
        {
            cylinder_index_buffer_data.push_back(stack * (numSlices + 1) + slice); // Note: numslice is used because it represent one 'round'
            cylinder_index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
        }
    }

    for (unsigned slice = numSlices + 1; slice > 0; --slice)
    {
        cylinder_index_buffer_data.push_back(slice);
        cylinder_index_buffer_data.push_back(numSlices + 1);
    }

    for (unsigned slice = numSlices + 1; slice > 0; --slice)
    {
        cylinder_index_buffer_data.push_back(slice);
        cylinder_index_buffer_data.push_back(numSlices + 1);
    }



    //OTHER CODE
    //float anglePerSlice = 360.f / numSlices;

    //for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    //{
    //    float theta = slice * anglePerSlice;
    //    cylinder.pos.Set(CircleX(theta), -0.5f, CircleZ(theta));
    //    cylinder.color = color;
    //    cylinder.normal.Set(CircleX(theta), 0, CircleZ(theta));
    //    cylinder_vertex_buffer_data.push_back(cylinder);

    //    cylinder.pos.Set(CircleX(theta), 0.5f, CircleZ(theta));
    //    cylinder.color = color;
    //    cylinder.normal.Set(CircleX(theta), 0, CircleZ(theta));
    //    cylinder_vertex_buffer_data.push_back(cylinder);
    //}
    //

    //for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    //{
    //    cylinder_index_buffer_data.push_back(2 * slice);
    //    cylinder_index_buffer_data.push_back(2 * slice + 1);
    //}



    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, cylinder_vertex_buffer_data.size() * sizeof(Vertex), &cylinder_vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, cylinder_index_buffer_data.size() * sizeof(GLuint), &cylinder_index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = cylinder_index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
    return mesh;

}

Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, Color color, float innerRadius, float outerRadius, unsigned numStacks, unsigned numSlices)
{
    std::vector<Vertex> torus_vertex_buffer_data;
    std::vector<GLuint> torus_index_buffer_data;

    Vertex torus;

    float angleperstack = 360.f / numStacks;
    float angleperslice = 360.f / numSlices;
    float x1, z1;
    float x2, y2, z2;

    for (unsigned stack = 0; stack < numStacks + 1; ++stack)
    {
        for (unsigned slice = 0; slice < numSlices + 1; ++slice)
        {
            z1 = outerRadius * cos(stack * Math::DegreeToRadian(angleperstack));
            x1 = outerRadius * sin(stack * Math::DegreeToRadian(angleperstack));
            z2 = (outerRadius + innerRadius * cos(slice * Math::DegreeToRadian(angleperslice))) * cos(stack * Math::DegreeToRadian(angleperstack));
            y2 = innerRadius * sin(slice * Math::DegreeToRadian(angleperslice));
            x2 = (outerRadius + innerRadius * cos(slice * Math::DegreeToRadian(angleperslice))) * sin(stack * Math::DegreeToRadian(angleperstack));
            torus.pos.Set(x2, y2, z2);
            //normal goes here
            torus.normal.Set(x2 - x1, y2, z2 - z1);
            torus.normal.Normalize();
            torus_vertex_buffer_data.push_back(torus);
            torus.color = color;
        }
    }

    for (unsigned stack = 0; stack < numStacks; stack++)
    {
        for (unsigned slice = 0; slice < numSlices + 1; slice++)
        {
            torus_index_buffer_data.push_back((numSlices + 1) * stack + slice + 0);
            torus_index_buffer_data.push_back((numSlices + 1) * (stack + 1) + slice + 0);
        }
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, torus_vertex_buffer_data.size() * sizeof(Vertex), &torus_vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, torus_index_buffer_data.size() * sizeof(GLuint), &torus_index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = torus_index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
    return mesh;

}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numSlices)
{
    std::vector<Vertex> cone_vertex_buffer_data;
    std::vector<GLuint> cone_index_buffer_data;

    Vertex cone;

    float anglePerSlice = 360.f / numSlices;
    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        float theta = slice * anglePerSlice;
        cone.pos.Set(CircleX(theta), 0, CircleZ(theta));
        cone.color = color;
        cone.normal.Set(0, 1, 0);
        cone_vertex_buffer_data.push_back(cone);
    }

    cone.pos.Set(0, 1, 0);
    cone.color = color;
    cone.normal.Set(0, 1, 0);
    cone_vertex_buffer_data.push_back(cone);

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        cone_index_buffer_data.push_back(slice);
        cone_index_buffer_data.push_back(numSlices + 1);
    }

    for (unsigned slice = 0; slice < numSlices + 1; ++slice)
    {
        float theta = slice * anglePerSlice;
        cone.pos.Set(CircleX(theta), 0, CircleZ(theta));
        cone.color = color;
        cone.normal.Set(0, -1, 0);
        cone_vertex_buffer_data.push_back(cone);
    }

    for (unsigned slice = numSlices + 1; slice > 0; --slice)
    {
        cone_index_buffer_data.push_back(slice);
        cone_index_buffer_data.push_back(numSlices + 1);
    }

    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, cone_vertex_buffer_data.size() * sizeof(Vertex), &cone_vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, cone_index_buffer_data.size() * sizeof(GLuint), &cone_index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = cone_index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
    return mesh;
}

Mesh* MeshBuilder::GenerateHair(const std::string &meshName, Color color)
{
    std::vector<Vertex> hair_vertex_buffer_data;
    std::vector<GLuint> hair_index_buffer_data;

    Vertex hair;

    // Front
    hair.pos.Set(0, 0, 0); hair.color = color; hair.normal.Set(0, 0, 1); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1, 0); hair.color = color; hair.normal.Set(0, 0, 1); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1.2, 0); hair.color = color; hair.normal.Set(0, 0, 1); hair_vertex_buffer_data.push_back(hair);

    hair.pos.Set(0, 0, 0); hair.color = color; hair.normal.Set(0, 0, 1); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(1, 1, 0); hair.color = color; hair.normal.Set(0, 0, 1); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1, 0); hair.color = color; hair.normal.Set(0, 0, 1); hair_vertex_buffer_data.push_back(hair);

    // Top
    hair.pos.Set(0, 0, 0); hair.color = color; hair.normal.Set(0, 1, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1.2, 0); hair.color = color; hair.normal.Set(0, 1, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0, 0, -0.5); hair.color = color; hair.normal.Set(0, 1, 0); hair_vertex_buffer_data.push_back(hair);

    hair.pos.Set(0.8, 1.2, 0); hair.color = color; hair.normal.Set(0, 1, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1.2, -0.5); hair.color = color; hair.normal.Set(0, 1, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0, 0, -0.5); hair.color = color; hair.normal.Set(0, 1, 0); hair_vertex_buffer_data.push_back(hair);

    // Back
    hair.pos.Set(0, 0, -0.5); hair.color = color; hair.normal.Set(0, 0, -1); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1.2, -0.5); hair.color = color; hair.normal.Set(0, 0, -1); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1, -0.5); hair.color = color; hair.normal.Set(0, 0, -1); hair_vertex_buffer_data.push_back(hair);

    hair.pos.Set(0.8, 1, -0.5); hair.color = color; hair.normal.Set(0, 0, -1); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(1, 1, -0.5); hair.color = color; hair.normal.Set(0, 0, -1); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0, 0, -0.5); hair.color = color; hair.normal.Set(0, 0, -1); hair_vertex_buffer_data.push_back(hair);

    // Bottom
    hair.pos.Set(0, 0, 0); hair.color = color; hair.normal.Set(0, -1, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0, 0, -0.5); hair.color = color; hair.normal.Set(0, -1, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(1, 1, -0.5); hair.color = color; hair.normal.Set(0, -1, 0); hair_vertex_buffer_data.push_back(hair);

    hair.pos.Set(0, 0, 0); hair.color = color; hair.normal.Set(0, -1, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(1, 1, -0.5); hair.color = color; hair.normal.Set(0, -1, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(1, 1, 0); hair.color = color; hair.normal.Set(0, -1, 0); hair_vertex_buffer_data.push_back(hair);

    // Pointy bit bottom
    hair.pos.Set(1, 1, 0); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(1, 1, -0.5); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1, -0.5); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);

    hair.pos.Set(0.8, 1, -0.5); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1, 0); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(1, 1, 0); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);

    // Pointy bit top
    hair.pos.Set(0.8, 1, 0); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1, -0.5); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1.2, -0.5); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);

    hair.pos.Set(0.8, 1.2, -0.5); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1.2, 0); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);
    hair.pos.Set(0.8, 1, 0); hair.color = color; hair.normal.Set(1, 0, 0); hair_vertex_buffer_data.push_back(hair);



    for (int i = 0; i < 36; ++i)
    {
        hair_index_buffer_data.push_back(i);
    }


    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, hair_vertex_buffer_data.size() * sizeof(Vertex), &hair_vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, hair_index_buffer_data.size() * sizeof(GLuint), &hair_index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = hair_index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLES;
    return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path)
{
    //Read vertices, texcoords & normals from OBJ
    std::vector<Position> vertices;
    std::vector<TexCoord> uvs;
    std::vector<Vector3> normals;
    bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
    if (!success)
        return NULL;

    //Index the vertices, texcoords & normals properly
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;

    for (int i = 0; i < vertex_buffer_data.size(); ++i)
    {
        index_buffer_data.push_back(i);
    }

    ////verticeNum = &vertices;

    Position maxPos = Position(0, 0, 0); // Vector for max pos
    Position minPos = Position(0, 0, 0); // Vector for min pos

    Position * posPtr1 = 0;

    for (int i = 0; i < vertices.size(); ++i)
    {
        posPtr1 = &vertices[i];
        if (posPtr1->x > maxPos.x)
        {
            maxPos.x = posPtr1->x;
        }
        if (posPtr1->x < minPos.x)
        {
            minPos.x = posPtr1->x;
        }

        if (posPtr1->y > maxPos.y)
        {
            maxPos.y = posPtr1->y;
        }
        if (posPtr1->y < minPos.y)
        {
            minPos.y = posPtr1->y;
        }


        if (posPtr1->z > maxPos.z)
        {
            maxPos.z = posPtr1->z;
        }
        if (posPtr1->z < minPos.z)
        {
            minPos.z = posPtr1->z;
        }

    }


    maxPos.x += 0.1f;
    maxPos.y += 0.1f;
    maxPos.z += 0.1f;

    minPos.x -= 0.1f;
    minPos.y -= 0.1f;
    minPos.z -= 0.1f;

    IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

    //Create the mesh and call glBindBuffer, glBufferData
    //Use triangle list and remember to set index size
    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLES;
    mesh->maxPos = maxPos;
    mesh->minPos = minPos;
    return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float width = 1.f / numCol;
    float height = 1.f / numRow;

    int offset = 0;

    for (unsigned i = 0; i < numRow; ++i)
    {
        for (unsigned j = 0; j < numCol; ++j)
        {
            //Task: Add 4 vertices into vertex_buffer_data
            v.pos.Set(-0.5f, -0.5f, 0);	v.normal.Set(0, 0, 1); v.texCoord.Set(j * width, 1.f - (i + 1) * height);             vertex_buffer_data.push_back(v);
            v.pos.Set(0.5f, -0.5f, 0);	v.normal.Set(0, 0, 1); v.texCoord.Set((j + 1) * width, 1.f - (i + 1) * height);	    vertex_buffer_data.push_back(v);
            v.pos.Set(0.5f, 0.5f, 0);	v.normal.Set(0, 0, 1); v.texCoord.Set((j + 1) * width, 1.f - i * height);	vertex_buffer_data.push_back(v);
            v.pos.Set(-0.5f, 0.5f, 0);	v.normal.Set(0, 0, 1); v.texCoord.Set(j * width, 1.f - i * height);       vertex_buffer_data.push_back(v);

            //Task: Add 6 indices into index_buffer_data
            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 1);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 3);
            offset += 4; // every loop, 4 vertices are created so add 4 vetices
        }
    }


    Mesh *mesh = new Mesh(meshName);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLES;

    return mesh;
}

