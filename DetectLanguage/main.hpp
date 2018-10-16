//
//  main.hpp
//  DetectLanguage
//
//  Created by Raphaël Daumas on 16/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>
#include <fann.h>

using namespace std;

void CalculateFrequenc(const string& path, vector<double>& nbLettres);
void TrainAnn();
void DetectText();
void generate_frequencies(const string& path, float *frequencies);
