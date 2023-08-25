#include "Json.h"
#include "FileIO.h"
#include "Logger.h"

#include <iostream>
#include <fstream>
#include <sstream>

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

	bool Json::Read(const rapidjson::Value& value, const std::string name, float& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetFloat();
		return false;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string name, bool& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetBool();
		return false;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string name, std::string& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetString();
		return false;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string name, vec2& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}

			data[i] = array[i].GetFloat();
		}

		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string name, Color& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}

			data[i] = array[i].GetFloat();
		}

		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string name, Rect& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}

			data[i] = array[i].GetInt();
		}

		return true;
	}
}