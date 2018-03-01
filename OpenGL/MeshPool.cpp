#include "MeshPool.hpp"

std::unordered_map<std::string, Mesh*> MeshPool::pool;

MeshPool::MeshPool(){}

MeshPool::~MeshPool(){}

Mesh* MeshPool::GetMesh(std::string path) {
	Mesh* m;
	try {
		m = MeshPool::pool.at(path);
		Console::Write("Mesh: ", Color::light_blue);
		printf("Founded, pointer returned \n");
	}
	catch (const std::exception&) {
		Console::Write("Mesh: ", Color::light_blue);
		printf("Not founded, generating... \n");

		m = new Mesh(path);
		std::pair<std::string, Mesh*> pair(path, m);
		MeshPool::pool.insert(pair);
		
	}
	return m;
}