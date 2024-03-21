//
// Created by Niklas on 20/03/2024.
//



#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <limits>
#include <thread>
#include <mutex>


std::mutex mtx;

void processChunk(int start, int end, std::map<std::string, std::vector<float>>& data) {
    std::ifstream file("../data/measurements.txt");
    std::string line;
    file.seekg(std::ios::beg);
    for(int i = 0; i < start; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    for(int i = start; i < end; ++i) {
        if(std::getline(file, line)) {
            std::string station;
            std::string temperature;
            std::stringstream ss(line);
            std::getline(ss, station, ';');
            std::getline(ss, temperature, ';');
            mtx.lock();
            data[station].push_back(std::stof(temperature));
            mtx.unlock();
        }
    }
}

std::map<std::string, std::vector<float>> readFile() {
    std::map<std::string, std::vector<float>> data;
    std::ifstream file("../data/measurements.txt");
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int lines = file.gcount();
    file.clear();
    file.seekg(0, std::ios::beg);
    unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(numThreads);
    int chunkSize = lines / numThreads;
    for(int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? lines : start + chunkSize;
        threads[i] = std::thread(processChunk, start, end, std::ref(data));
    }
    for(auto& thread : threads) {
        thread.join();
    }
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
