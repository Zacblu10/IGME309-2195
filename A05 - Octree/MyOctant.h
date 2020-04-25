#pragma once
#ifndef __MYOCTANT_H_
#define __MYOCTANT_H_

#include "MyEntityManager.h"

namespace Simplex
{
class MyOctant
{
	static int currentDimension;
	int dimension = 0; //what dimension this octant represents

	//position variables
	vector3 center = vector3(0.0f); 
	vector3 max = vector3(0.0f);	//(centerX+sze, centerY+size,centerZ+size)
	vector3 min = vector3(0.0f);	//(centerX-size, centerY-size,centerZ-size)
	float size = 0.0f; //halfwidth of the octant

	//tree variables
	MyOctant* parent = nullptr; //pointer to the parent
	MyOctant* children[8]; //pointer to the array of children

	//manager references
	MyEntityManager* entityManager = nullptr; //entity manager singleton
	MeshManager* meshManager = nullptr; //mesh manager singleton

	//objects in the octree
	std::vector<uint> entityList;
	uint entityCount; 

public: 
	/*USAGE: Constructs entire tree
	ARGUMENTS:
		int _levels -> how many tiers the tree will have
		vector3 _center -> center point for the tree
		float _size -> halfwidth of the square
	OUTPUT: Class Object*/
	MyOctant(int _levels, vector3 _center, float _size); 

	/*USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance*/
	MyOctant(MyOctant const& other);
	
	/*USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---*/
	MyOctant& operator=(MyOctant const& other);

	/*USAGE: Destructor 
	ARGUMENTS: ---
	OUTPUT: --- */
	~MyOctant(void);

	/*USAGE:Draw the current tree to the screen
	ARGUMENTS: ---
	OUTPUT: - */
	void Display();


	/*USAGE:Fills the tree with the objects in the scene for collision detection
	ARGUMENTS:
	OUTPUT:*/
	void fillTree();

	/*USAGE: Checks collisions for all objects in the octant
	ARGUMENTS:
	OUTPUT:*/
	void CheckCollisions();
};

}

#endif //__MYOCTANT_H_


/*USAGE:
ARGUMENTS:
OUTPUT:*/