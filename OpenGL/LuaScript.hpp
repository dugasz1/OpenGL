//
//Created by Bozó Dávid - TMN7C4
//
#ifndef LUA_SCRIPT_HPP
#define LUA_SCRIPT_HPP

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include "Lua\lua.hpp"
#include "rapidxml\rapidxml.hpp"
#include "rapidxml\rapidxml_utils.hpp"
#include "rapidxml\rapidxml_utilsplus.hpp"
#include "Object.hpp"
#include "Renderer.hpp"
#include "Console.hpp"

class LuaScriptLoadException : public std::exception {
private:
	std::string msg;
public:
	LuaScriptLoadException();
	LuaScriptLoadException(const std::string &_msg);

	virtual const char* what() const throw() {
		return this->msg.c_str();
	}
};

class LuaScript
{
private:
	std::string root_path;
	std::string meta_path;
	rapidxml::xml_document<> xmldoc;
	rapidxml::file<> *meta_file;
	lua_State* L;
public:
	static Renderer* renderer;
	LuaScript();

	//! The models which are spawned by the script
	//static std::vector<Model> spawned;
	//! THIS IS FOR LUA | DO NOT CALL
	static int LuaScript::average2(lua_State *L);
	static int LuaScript::SpawnModel(lua_State *L);
	static int LuaScript::SetModelPosition(lua_State *L);

	//! Args:
	//! _path: where the meta.xml can be found. Don't forget / at the end;
	LuaScript(const std::string &_path);
	~LuaScript();
};

#endif