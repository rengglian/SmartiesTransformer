#include "config.hpp"

Config::Config(std::string fileName) {
    std::ifstream i(fileName);
    json j;
    i >> j;
    
    bg_path =  j.at("background"); 
    img_path = j.at("image");
    target_path = j.at("target");
    scaler = j.at("pixelmm");   
}

Config::~Config() {

}