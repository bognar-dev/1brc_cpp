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
    CityTemperatureInfo() : count(0), min(0), max(0), sum(0) {}
};

void tokenize
        (std::vector<std::string_view> &result, const std::string_view &s) {
    result.clear();

    std::string_view::size_type from = 0;
    std::string_view::size_type colon = s.find(';');

    while (colon != std::string_view::npos) {
        result.push_back(s.substr(from, colon - from));
        from = colon + 1;
        colon = s.find(';', from);
    }

    result.push_back(s.substr(from));
}

std::unordered_map<std::string, CityTemperatureInfo> mapOfTemp;

void processChunk(Channel<std::string> &channel) {
    for (;;) {
        auto line = channel.recv();
        if (!line){
            channel.close();
            return;
        };
        std::vector<std::string_view> tokens;
        tokenize(tokens, *line);
        auto it = mapOfTemp.find(std::string(tokens[0]));
        if (it == mapOfTemp.end()) {
            CityTemperatureInfo info;
            info.count = 1;
            info.min = std::stof(std::string(tokens[1]));
            info.max = std::stof(std::string(tokens[1]));
            info.sum = std::stof(std::string(tokens[1]));
            mapOfTemp[std::string(tokens[0])] = info;
            delete &info;
        } else {
            it->second.count++;
            it->second.min = std::min(it->second.min, std::stof(std::string(tokens[1])));
            it->second.max = std::max(it->second.max, std::stof(std::string(tokens[1])));
            it->second.sum += std::stof(std::string(tokens[1]));
        }
    }
}

void read(Channel<std::string> &sender,std::string filepath) {
    std::ifstream file(filepath);
    if (file.fail()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }
    std::string line;
    // Determine the total number of lines in the file
    size_t totalLines = 1000000000;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            sender.send(line);
        }
    }
    sender.close();

}

void readFile(std::string filepath) {

    auto [sender, receiver] = make_channel<std::string>();
    std::thread worker(read, std::ref(sender), std::move(filepath));
    processChunk(receiver);
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
                  << "/" << round(item.second.max) << "\n";
    }
}