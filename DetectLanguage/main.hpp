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

void CalculateFrequenc(ifstream& text, float* frequencesLettres);
void TrainAnn();
void DetectText();
ifstream GetTextFilePath();
