#pragma once
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Config {

	public:

		Config(std::string fileName);
		~Config();
		
		void Read();

		const std::string GetPathBackground() {return bg_path;};
		const std::string GetPathImage() {return img_path;};
		const std::string GetPathTarget() {return target_path;};
		const double GetPixelMM() {return scaler;};

	private:

	std::string bg_path;
	std::string img_path;
	std::string target_path;
	double scaler;
};