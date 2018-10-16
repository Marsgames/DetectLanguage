//
//  main.cpp
//  DetectLanguage
//
//  Created by Raphaël Daumas on 16/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include "main.hpp"
#include <iostream>
#include <fann.h>
//#include <vector>
#include <fstream>
//#include <ctype.h>

using namespace std;

const string path = "/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/spanish.txt";

int main()
{
//    TrainAnn();
    DetectText();
    
    return 0;
}

void TrainAnn()
{
    // InputLayer --> nb de lettres (26)
    // OutputLayer --> nb de langues possibles (3 anglais, français, espagnol)
    // HiddenLayer --> 13
    struct fann* ann = fann_create_standard(3, 26, 13, 3);

    fann_train_on_file(ann, "/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/trainingAFE.data", 100000, 10, 0.0001);
    fann_save(ann, "/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/lang.net");
    fann_destroy(ann);
    

}

void DetectText()
{
    struct fann *ann = fann_create_from_file("/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/lang.net");
    
//    CalculateFrequenc(path, nbLettres);
    
    float nbLettres[26];
    generate_frequencies(path, nbLettres);
    
//    vector<double> output = fann_run(ann, nbLettres);
    float *output = fann_run(ann, nbLettres);
    cout << "English: " << output[0] << endl << "French : " << output[1] << std::endl << "Espagnol : " << output[2] << endl; 
}

void generate_frequencies(const string& path, float* frequencies)
{
    ifstream infile(path);
//    if(!infile) error("Cannot open input file", filename);
    
    vector<unsigned int> letter_count(26, 0);
    unsigned int num_characters = 0;
    char c;
    while(infile.get(c)){
        c = tolower(c);
        if(c >= 'a' && c <= 'z'){
            letter_count[c - 'a']++;
            num_characters++;
        }
    }
    
//    if(!infile.eof()) error("Something strange happened");
    for(unsigned int i = 0; i != 26; i++){
        frequencies[i] = letter_count[i]/(double)num_characters;
    }
}

void CalculateFrequenc(const string& path, float* nbLettres)
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
