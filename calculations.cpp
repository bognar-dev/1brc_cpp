#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <vector>
#include <sstream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>
#include "channel.h"

struct CityTemperatureInfo {
    int count;
    float min;
    float max;
    float sum;
};


std::map<std::string, CityTemperatureInfo> mapOfTemp;

void processChunk(Channel<std::string> &channel) {
    for (auto line = channel.recv(); line.has_value(); line = channel.recv()) {
        std::string city;
        float temp;
        std::stringstream ss(*line);
        std::getline(ss, city, ';');
        ss >> temp;
        if (mapOfTemp.find(city) != mapOfTemp.end()) {
            mapOfTemp[city].count++;
            mapOfTemp[city].sum += temp;
            if (temp < mapOfTemp[city].min) {
                mapOfTemp[city].min = temp;
            }
            if (temp > mapOfTemp[city].max) {
                mapOfTemp[city].max = temp;
            }
        } else {
            mapOfTemp[city] = {1, temp, temp, temp};
        }
    }
}


void readFile(std::string filepath) {
    std::ifstream file(filepath);
    if (file.fail()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }
    std::string line;
    auto [sender, receiver] = make_channel<std::string>();
    std::thread worker(processChunk, std::ref(receiver));
    while (std::getline(file, line)) {
        if (!line.empty()) {
            sender.send(line);
        }
    }
    sender.close();
    worker.join();
}

float round(float x) {
    return std::round(x * 10) / 10;
}

void evaluate(std::string input) {
    readFile(std::move(input));
    for (const auto &item: mapOfTemp) {
        std::cout << item.first << "=" << round(item.second.min) << "/"
                  << round(item.second.sum / item.second.count)
                  << "/" << round(item.second.max) << ", ";
    }
}