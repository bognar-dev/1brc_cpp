//
// Created by Niklas on 20/03/2024.
//



#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>



std::map<std::string, std::vector<float>> readFile() {
    //read the csv file from data folder
    std::ifstream file("../data/measurements.txt");
    //check for errors
    if (!file.is_open()) {
        std::cerr << "Error: file not found" << std::endl;
        return {};
    }
    std::cout << "File opened successfully" << std::endl;
    std::string line;

    std::map<std::string, std::vector<float>> data;

    while (std::getline(file, line)) {
        std::string station;
        std::string temperature;
        std::stringstream ss(line);
        std::getline(ss, station, ';');
        std::getline(ss, temperature, ';');
        data[station].push_back(std::stof(temperature));
    }
    std::cout << "Data read successfully" << std::endl;
    file.close();
    return data;
}

void calcAvr(std::map<std::string, std::vector<float>> data) {
    for (const auto &station: data) {
        std::string stationName = station.first;
        std::vector<float> stationData = station.second;
        float minTemp = stationData[0];
        float maxTemp = stationData[0];
        float avgTemp = 0;
        for (int i = 0; i < stationData.size(); i++) {
            if (stationData[i] < minTemp) {
                minTemp = stationData[i];
            }
            if (stationData[i] > maxTemp) {
                maxTemp = stationData[i];
            }
            avgTemp += stationData[i];
        }
        avgTemp /= stationData.size() - 1;
        std::cout << "Station: " << stationName << " Min: " << minTemp << " Max: " << maxTemp << " Avg: " << avgTemp
                  << std::endl;
    }
}
