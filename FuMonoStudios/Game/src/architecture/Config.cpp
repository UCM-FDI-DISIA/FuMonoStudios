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

					JSONObject vObj = v->AsObject();

					std::string key = vObj["id"]->AsString();

					std::vector<Arrows> placeArrows;

					std::vector<Characters> placeCharacters;

					//recorrido de la info del lugar
					for (auto& i : vObj["data"]->AsArray()) {

						JSONObject iObj = i->AsObject();

						

						for (auto& a : iObj["arrows"]->AsArray()) {

							JSONObject aObj = a->AsObject();

							double x = aObj["x"]->AsNumber();

							double y = aObj["y"]->AsNumber();

							std::string dest = aObj["dest"]->AsString();

							double scale = aObj["scale"]->AsNumber();

							bool dir = aObj["dir"]->AsBool();

							Arrows arrow{ x, y, dest, scale, dir };

							placeArrows.push_back(arrow);

						}


						

					}

					//recorrido de la info del lugar
					for (auto& o : vObj["dataChar"]->AsArray()) {

						JSONObject oObj = o->AsObject();


						for (auto& c : oObj["character"]->AsArray()) {

							JSONObject cObj = c->AsObject();

							double x = cObj["x"]->AsNumber();

							double y = cObj["y"]->AsNumber();

							std::string dest = cObj["name"]->AsString();

							double scale = cObj["scale"]->AsNumber();

							bool dir = cObj["dir"]->AsBool();

							Characters character{ x, y, dest, scale, dir };

							placeCharacters.push_back(character);

						}

					}

					Places pl{ placeArrows, placeCharacters };

					places_.emplace(key, pl);
					
					

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