#pragma once
#include <rapidjson/include/rapidjson/document.h>
#include <string>

namespace kiko
{
	class Json
	{
	public:
		static bool Load(const std::string& filename, rapidjson::Document& document);

		static bool Read(const rapidjson::Value& value, const std::string name, int& data, bool required  = 0);
	};
}