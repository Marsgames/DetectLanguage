//
//  main.cpp
//  DetectLanguage
//
//  Created by Raphaël Daumas on 16/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include "main.hpp"
#include <iostream>
//#include "fann.h"
//#include <vector>
#include <fstream>
//#include <ctype.h>

using namespace std;

const string path = "/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/frequences.data";

int main()
{
    //    if(argc != 2) error("Remember to specify an input file");
    
    vector<double> nbLettres = vector<double>(26);
    CalculateFrequenc(path, nbLettres);
    
    cout << "nb de A : " << nbLettres[0] << endl;
    
    //    for(unsigned int i = 0; i != 26; i++){
    //        cout << nbLettres[i] << ' ';
    //    }
    //    cout << endl;
    
    return 0;
}

void CalculateFrequenc(const string& path, vector<double>& nbLettres)
{
    ifstream text;
    text.open(path);
    char c;
    
    while (text >> c)
    {
        if (isalpha(c))
        {
            int index = toupper(c) - 'A';
            nbLettres[index]++;
        }
    }
    
}
