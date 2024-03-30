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
#include <algorithm>
#include <numeric>
#include <iterator>


std::mutex mtx;

void processChunk(int start, int end, std::map<std::string, std::vector<float>>& data) {
    std::ifstream file("../data/measurements.txt");
    std::string line;
    file.seekg(std::ios::beg);

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
    file.close();
    std::cout << "Thread " << std::this_thread::get_id() << " finished processing chunk." << std::endl;
}



std::map<std::string, std::vector<float>> readFile() {
    std::map<std::string, std::vector<float>> data;
    std::ifstream file("../data/measurements.txt");
    int lines = 1000000000;
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
    std::cout<<"Data size: "<<data.size()<<std::endl;
    for (const auto &station: data) {
        std::string stationName = station.first;
        std::vector<float> stationData = station.second;
        float minTemp = *std::min_element(stationData.begin(), stationData.end());
        float maxTemp = *std::max_element(stationData.begin(), stationData.end());
        float avgTemp = std::accumulate(stationData.begin(), stationData.end(), 0.0) / stationData.size();
        std::cout << "Station: " << stationName << " Min: " << minTemp << " Max: " << maxTemp << " Avg: " << avgTemp
                  << std::endl;
    }
}
