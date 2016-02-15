#ifndef MESH_H
#define MESH_H

#include <string>
#include "Vector3.h"
#include "vertex.h"
#include "Material.h"

/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
        DRAW_TRIANGLE_FAN,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();
    void Render(unsigned offset, unsigned count);


	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned colorBuffer;
	unsigned indexBuffer;
	unsigned indexSize;

    Position pos;
    int count;
    Position maxPos;
    Position minPos;

    Material material;

    unsigned textureID;
};

#endif