#include "LuaScript.hpp"

//std::vector<Model> LuaScript::spawned;
Renderer* LuaScript::renderer;

LuaScriptLoadException::LuaScriptLoadException() {
}

LuaScriptLoadException::LuaScriptLoadException(const std::string &_msg) {
	this->msg = _msg;
}

LuaScript::LuaScript() {}

LuaScript::LuaScript(const std::string &_path) {
	this->root_path = _path;
	this->meta_path = _path;
	this->meta_path.append("meta.xml");
	this->L = luaL_newstate();
	luaL_openlibs(this->L);
	//Register functions
	lua_register(this->L, "avarage", average2);
	lua_register(this->L, "spawnModel", LuaScript::SpawnModel);
	lua_register(this->L, "setModelPosition", LuaScript::SetModelPosition);
	//Define global variables
	/*lua_pushinteger(L, GL_DECAL);
	lua_setglobal(L, "GL_DECAL");
	lua_pushinteger(L, GL_MODULATE);
	lua_setglobal(L, "GL_MODULATE");*/

	try {
		this->meta_file = new rapidxml::file<>(this->meta_path.c_str());
	}
	catch (const std::runtime_error* e) {
		throw new LuaScriptLoadException("A meta file nem talalhato.\n");
	}
	this->xmldoc.parse<0>(this->meta_file->data());
	rapidxml::xml_node<>* root_node = this->xmldoc.first_node();
	if (strcmp(root_node->name(), "meta")) {
		throw new LuaScriptLoadException("A meta root node nem talalhato a fileben.\n");
		return;
	}

	std::vector<rapidxml::xml_node<>*> script_nodes = rxmlp::GetNodesByName(root_node, "script");
	Console::Write("Script: ", Color::light_magenta);
	std::cout << "Loaded. Contains " << script_nodes.size() << " script node (" << _path << ")" << std::endl;
	for (std::vector<rapidxml::xml_node<>*>::iterator script_node = script_nodes.begin(); script_node != script_nodes.end(); script_node = ++script_node) {
		std::vector<rapidxml::xml_attribute<>*> attributes = rxmlp::GetAttributesByName((*script_node), "src");

		int index = (script_node - script_nodes.begin()) + 1;

		if (attributes.size() > 1) {
			printf("\tSKIPPING... Too much src attributes in %d. script node\n", index);
			continue;
		}
		if (attributes.size() == 0) {
			printf("\tSKIPPING... There is no src attrubute in %d. script node\n", index);
			continue;
		}
		std::string realPath(this->root_path);
		realPath.append(attributes[0]->value());
		//printf("asd:%s\n\n", realPath.c_str());
		std::ifstream f(realPath);
		if (f.fail()) {
			printf("\tSKIPPING... %s file not found in %d. script node\n", attributes[0]->value(), index);
			f.close();
			continue;
		}
		f.close();

		//printf("Script: LOADING... %s file\n", attributes[0]->value());
		luaL_dofile(this->L, realPath.c_str());
	}

}

LuaScript::~LuaScript() {}


int LuaScript::average2(lua_State *L)
{
	// get number of arguments
	int n = lua_gettop(L);
	double sum = 0;
	int i;
	// loop through each argument
	for (i = 1; i <= n; i++)
	{
		// total the arguments 
		sum += lua_tonumber(L, i);
	}
	// push the average 
	lua_pushnumber(L, sum / n);
	// push the sum 
	lua_pushnumber(L, sum);

	// return the number of results 
	return 2;
}

int LuaScript::SpawnModel(lua_State *L) {
	
	Object* o = new Object("objs/house2.obj", "textures/house2.png");
	LuaScript::renderer->AddToQueue(o);
	lua_pushlightuserdata(L, (void*)o);

	return 1;
}

int LuaScript::SetModelPosition(lua_State *L) {
	Object* o = (Object*)lua_touserdata(L, 1);
	o->position.y = 10;

	return 0;
}