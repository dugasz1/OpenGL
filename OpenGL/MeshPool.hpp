#ifndef MESHPOOL_HPP
#define MESHPOOL_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include "mesh.h"
#include "Console.hpp"

class MeshPool
{
private:
	static std::unordered_map<std::string, Mesh*> pool;
public:
	MeshPool();
	~MeshPool();

	static Mesh* GetMesh(std::string path);
	
};

#endif