#include "Json.h"
#include "FileIO.h"
#include "Core/Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "rapidjson/include/rapidjson/istreamwrapper.h"

namespace kiko
{
	bool Json::Load(const std::string& filename, rapidjson::Document& document)
	{
		std::string buffer;
		if (!readFile(filename, buffer))
		{
			WARNING_LOG("Cannot open file: " << filename);
			return false;
		}

		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);

		document.ParseStream(istream);
		if (!document.IsObject())
		{
			WARNING_LOG("Json file cannot be parsed: " << filename);
			return false;
		}


		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string name, int& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetInt();

		return false;
	}
}