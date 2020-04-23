#include "MyOctant.h"

//declaring static variables
int Simplex::MyOctant::currentDimension = 1;

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

	entityCount = 0; 

	if (_levels == 1)//base case no more subdivisions
	{
		dimension = currentDimension; 
		currentDimension++; 
		//set the dimension
		for (int i = 0; i < 8; i++)
		{
			children[i] = nullptr; 
		}
		fillTree();
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

Simplex::MyOctant::MyOctant(MyOctant const& other)
{
	dimension = other.dimension; 
	center = other.center; 
	max = other.max; 
	min = other.min; 
	size = other.size; 
	entityCount = other.entityCount; 
	entityList = other.entityList;

	//get a reference to the entity manager
	entityManager = MyEntityManager::GetInstance();
	//get a reference to the mesh manager
	meshManager = MeshManager::GetInstance();
	
	//only needed if the original one had children 
	if (other.children[0] != nullptr) {
		children[0] = new MyOctant(*other.children[0]);
		children[1] = new MyOctant(*other.children[1]);
		children[2] = new MyOctant(*other.children[2]);
		children[3] = new MyOctant(*other.children[3]);
		children[4] = new MyOctant(*other.children[4]);
		children[5] = new MyOctant(*other.children[5]);
		children[6] = new MyOctant(*other.children[6]);
		children[7] = new MyOctant(*other.children[7]);
		//set parents
		for (int i = 0; i < 8; i++) {
			children[i]->parent = this;
		}
	}


}

Simplex::MyOctant& Simplex::MyOctant::operator=(MyOctant const& other)
{
	dimension = other.dimension;
	center = other.center;
	max = other.max;
	min = other.min;
	size = other.size;
	entityCount = other.entityCount;
	entityList = other.entityList;

	//get a reference to the entity manager
	entityManager = MyEntityManager::GetInstance();
	//get a reference to the mesh manager
	meshManager = MeshManager::GetInstance();

	//only needed if the original one had children 
	if (other.children[0] != nullptr) {
		children[0] = other.children[0];
		children[1] = other.children[1];
		children[2] = other.children[2];
		children[3] = other.children[3];
		children[4] = other.children[4];
		children[5] = other.children[5];
		children[6] = other.children[6];
		children[7] = other.children[7];
		//set parents
		for (int i = 0; i < 8; i++) {
			children[i]->parent = this;
		}
	}
	
	return *this;
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

	//reset static variables
	currentDimension = 0; 
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

void Simplex::MyOctant::fillTree()
{
	//loop through all the entities 
	for (int i = 0; i < entityManager->GetEntityCount(); i++)
	{
		////get the unique ID of the entity
		//String uniqueID = entityManager->GetUniqueID(i); 
		MyEntity* entity = entityManager->GetEntity(i);
		//get the rigidbody of the entity
		MyRigidBody* entityRB = entity->GetRigidBody();

		 //check if the cube is within the quad

		 if (entityRB->GetMaxGlobal().x <min.x) //this to the right of other
			 continue;
		 if (entityRB->GetMinGlobal().x > max.x) //this to the left of other
			 continue;
		 if (entityRB->GetMaxGlobal().y < min.y) //this below of other
			 continue;
		 if (entityRB->GetMinGlobal().y > max.y) //this above of other
			 continue;
		 if (entityRB->GetMaxGlobal().z < min.z) //this behind of other
			 continue;
		 if (entityRB->GetMinGlobal().z > max.z) //this in front of other
			 continue;

		 //add the dimension to the entity 
		 entity->AddDimension(dimension);
		 entityList.push_back(i);
		 entityCount++;
	}

}

void Simplex::MyOctant::CheckCollisions()
{
	//if there are children check collisions of the children's entities
	if (children[0] != nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			children[i]->CheckCollisions();
		}
	}

	//if there are entities in the list, check collisions against other entities in the list. Only leaves should have entities in the list.
	if (entityCount != 0)
	{
		for (uint i = 0; i < entityCount - 1; i++)
		{
			for (uint j = i + 1; j < entityCount; j++)
			{
				entityManager->GetEntity(entityList[i])->IsColliding(entityManager->GetEntity(entityList[j]));
			}
		}
	}
	
}



