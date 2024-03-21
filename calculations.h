//
// Created by Niklas on 20/03/2024.
//
#pragma once


#include <string>
#include <vector>
#include <map>

void processChunk(int start, int end, std::map<std::string, std::vector<float>>& data);
void calcAvr(std::map<std::string, std::vector<float>> data);
std::map<std::string, std::vector<float>> readFile();
