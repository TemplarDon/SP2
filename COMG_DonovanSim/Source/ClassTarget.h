/*************************************************************************************************/
/*!
\file   ClassTarget.h
\author Gary Goh
\brief
Defines a target to get/set a variable.
*/
/*************************************************************************************************/
#ifndef _CLASSTARGET_H_
#define _CLASSTARGET_H_

template <class T> class ClassTarget
{
private:
	T *target;

public:
	ClassTarget(T *target = 0) : target(target)
	{

	}

	void setTargetLocation(T *target)
	{
		this->target = target;
	}

	void setTargetValue(T value)
	{
		*target = value;
	}
};

#endif