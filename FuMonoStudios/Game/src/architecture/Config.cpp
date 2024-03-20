#include "Config.h"

#include <cassert>
#include <memory>

#include "../json/JSON.h"

Config::Config() :
	placesAccessWrapper_(places_, "PlacesTable") {

}

Config::Config(std::string filename) :
			placesAccessWrapper_(places_, "PlacesTable")	{

	loadReasources(filename);

}


void Config::loadReasources(std::string filename) {

	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	// TODO improve syntax error checks below, now we do not check
	//      validity of keys with values as sting or integer

	// load messages
	jValue = root["places"];

	if (jValue != nullptr) {

		if (jValue->IsArray()) {

			places_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing

			//recorrido de los lugares
			for (auto& v : jValue->AsArray()) {

				if (v->IsObject()) {

					//recorrido de la info del lugar
					for (auto& i : v->AsArray()) {

						JSONObject iObj = i->AsObject();

						for (auto& a : iObj["arrows"]->AsArray()) {



						}

					}

					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string txt = vObj["text"]->AsString();
					
					places_.emplace(key, );

				}
				else {

					throw "'messages' array in '" + filename
						+ "' includes and invalid value";

				}
			}
		}
		else {
			throw "'messages' is not an array in '" + filename + "'";
		}
	}



}

void Config::closeInfo() {

	places_.clear();

	
}