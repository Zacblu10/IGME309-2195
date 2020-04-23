#include "MyOctant.h"

Simplex::MyOctant::MyOctant(int _levels, vector3 _center, float _size)
{
	//set the identifier for the Octant
	//dimension = currentDimension; 
	//currentDimension++; 

	//set variable 
	center = _center; 
	size = _size; 

	//set the bound of the Octant
	max = vector3(center.x + size, center.y + size, center.z + size);
	min = vector3(center.x - size, center.y - size, center.z - size);

	//get a reference to the entity manager
	entityManager = MyEntityManager::GetInstance();
	//get a reference to the mesh manager
	meshManager = MeshManager::GetInstance();

	if (_levels == 1)//base case no more subdivisions
	{
		for (int i = 0; i < 8; i++)
		{
			children[i] = nullptr; 
		}
		return;
	}
	//recursively create children
	float halfWidth = _size / 2; 
	children[0] = new MyOctant(_levels - 1, vector3(center.x + halfWidth, center.y + halfWidth, center.z + halfWidth), halfWidth);
	children[1] = new MyOctant(_levels - 1, vector3(center.x + halfWidth, center.y + halfWidth, center.z - halfWidth), halfWidth);
	children[2] = new MyOctant(_levels - 1, vector3(center.x + halfWidth, center.y - halfWidth, center.z + halfWidth), halfWidth);
	children[3] = new MyOctant(_levels - 1, vector3(center.x + halfWidth, center.y - halfWidth, center.z - halfWidth), halfWidth);
	children[4] = new MyOctant(_levels - 1, vector3(center.x - halfWidth, center.y + halfWidth, center.z + halfWidth), halfWidth);
	children[5] = new MyOctant(_levels - 1, vector3(center.x - halfWidth, center.y + halfWidth, center.z - halfWidth), halfWidth);
	children[6] = new MyOctant(_levels - 1, vector3(center.x - halfWidth, center.y - halfWidth, center.z + halfWidth), halfWidth);
	children[7] = new MyOctant(_levels - 1, vector3(center.x - halfWidth, center.y - halfWidth, center.z - halfWidth), halfWidth);

	//set parents
	for (int i = 0; i < 8; i++) {
		children[i]->parent = this; 
	}
}

Simplex::MyOctant::~MyOctant(void)
{
	//delete all children objects
	if (children[0] != nullptr) {
		for (int i = 0; i < 8; i++) {
			delete children[i]; 
			children[i] = nullptr; 
		}
	}
}

void Simplex::MyOctant::Display()
{
	meshManager->AddWireCubeToRenderList(glm::translate(center) * glm::scale(vector3(size*2)), C_BLUE);

	if (children[0] != nullptr) {//only attempt to display children if they exist
		for (int i = 0; i < 8; i++) {
			children[i]->Display();
		}
	}
}



