#pragma once

#include "../utils/Singleton.h"
#include "../utils/Vector2D.h"

#include <SDL.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <exception>


class Config : public Singleton<Config> {

	friend Singleton<Config>; // needed to give access to private constructors

public:

	struct Arrows {

		Vector2D pos;

		std::string destination_;

		double scale_;

		bool directionRight_;

		Arrows(double x, double y, std::string destination, double scale, bool directionRight) : pos(x, y), destination_(destination),
			scale_(scale), directionRight_(directionRight){}


	};

	struct Characters {

		Vector2D pos;

		std::string name_;

		double scale_;

		bool directionRight_;

		Characters(double x, double y, std::string name, double scale, bool directionRight) : pos(x, y), name_(name),
			scale_(scale), directionRight_(directionRight) {}


	};

	struct Places {

		std::vector<Arrows> myArrows;

		std::vector<Characters> myCharacters;

		Places(std::vector<Arrows> arrows, std::vector<Characters> characters) : myArrows(arrows), myCharacters(characters){

		}

	};


	template<typename T>
	using sdl_resource_table = std::unordered_map<std::string, T>;

	template<typename T>
	class map_access_wrapper {
		sdl_resource_table<T>& map_;
		std::string desc_;
	public:
		map_access_wrapper(sdl_resource_table<T>& map, std::string desc) :
			map_(map), desc_(desc) {
		}

		inline T& at(const std::string& key) {
	
			try {
				return map_.at(key);
			}
			catch (std::out_of_range& e) {
				throw "Key '" + key + "' does not exists in '" + desc_ + "'";
			}
			catch (std::exception& e) {
				throw "Error when accessing key '" + key + "' of '" + //
					desc_ + "'. Original error was: " + e.what();
			}
			catch (...) {
				throw "Unknown error when accessing key '" + key + "' of '" + //
					desc_ + "'";
			}
		
		}

		inline T& operator[](const std::string& key) {
			return at(key);
		}
	};



	
	// All resource maps can be modified from outside, this way you can store
// your own dynamically. Be careful when modifying them!

// fonts map
	inline auto& places() {
		return placesAccessWrapper_;
	}

private:

	Config();
	Config(std::string filename);

	void closeInfo(); // free resources the
	void loadReasources(std::string filename); // load resources from the json file


	sdl_resource_table<Places> places_; // fonts map (string -> font)


	map_access_wrapper<Places> placesAccessWrapper_;

};

inline Config& config() {
	return *Config::instance();
}

