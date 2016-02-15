#ifndef NODE_H
#define NODE_H

#include "vertex.h"
#include <vector>

struct Node
{
public:
    Node(Position maxPosPtr, Position minPosPtr, Position offSet, int scaleOffSet, float rotateAngle, Vector3 rotateAxis, std::string name) { this->maxPos = maxPosPtr; this->minPos = minPosPtr; this->offSet = offSet; this->scaleOffSet = scaleOffSet; this->rotateAngle = rotateAngle; this->rotateAxis.x = rotateAxis.x; this->rotateAxis.y = rotateAxis.y; this->rotateAxis.z = rotateAxis.z; this->name = name; };
    ~Node() {};
    Position maxPos;
    Position minPos;
    Position offSet;

    float rotateAngle;
    Vector3 rotateAxis;

    std::string name;

    int scaleOffSet;
    bool canMove;
};

#endif