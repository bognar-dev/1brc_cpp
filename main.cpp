#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

int main() {
    //read the csv file from data folder
    std::ifstream file("../data/measurements.txt");
    //check for errors
    if (!file.is_open()) {
        std::cerr << "Error: file not found" << std::endl;
        return 1;
    }
    std::cout<< "File opened successfully" << std::endl;
    //read the file line by line
    std::string line;

    std::map<std::string, std::vector<std::string>> data;

    while (std::getline(file, line)) {
        std::string station;
        std::string temperature;
        std::stringstream ss(line);
        std::getline(ss, station, ';');
        std::getline(ss, temperature, ';');
        data[station].push_back(temperature);
    }
    std::cout << "Data read successfully" << std::endl;
    file.close();

    // find min max and average temperature for each station and print it
    for (const auto &station : data) {
        std::string stationName = station.first;
        std::vector<std::string> stationData = station.second;
        float minTemp = std::stof(stationData.at(1));
        float maxTemp = std::stof(stationData.at(1));
        float avgTemp = 0;
        for (int i = 1; i < stationData.size(); i++) {
            float temp = std::stof(stationData[i]);
            if (temp < minTemp) {
                minTemp = temp;
            }
            if (temp > maxTemp) {
                maxTemp = temp;
            }
            avgTemp += temp;
        }
        avgTemp /= stationData.size() - 1;
        std::cout << "Station: " << stationName << " Min: " << minTemp << " Max: " << maxTemp << " Avg: " << avgTemp
                  << std::endl;
    }



    return 0;
}
