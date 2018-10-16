//
//  main.cpp
//  DetectLanguage
//
//  Created by Raphaël Daumas on 16/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#include "main.hpp"
#include <fann.h>
#include <fstream>
#include <iostream>

using namespace std;

const string path = "/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/spanish.txt";

int main()
{
    TrainAnn();
    DetectText();
    
    return 0;
}

void TrainAnn()
{
    // InputLayer --> nb de lettres (26)
    // OutputLayer --> nb de langues possibles (3 anglais, français, espagnol)
    // HiddenLayer --> 13
    struct fann* ann = fann_create_standard(3, 26, 13, 3);

//    remove("/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/lang.net");
    
    fann_train_on_file(ann, "/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/trainingAFE.data", 100000, 10, 0.0001);
    fann_save(ann, "/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/lang.net");
    fann_destroy(ann);
    

}

void DetectText()
{
    struct fann *ann = fann_create_from_file("/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/lang.net");
    
    float nbLettres[26];
    CalculateFrequenc(path, nbLettres);
    
    float *output = fann_run(ann, nbLettres);
    cout << endl << endl << "Anglais: " << output[0] << endl << "Français : " << output[1] << std::endl << "Espagnol : " << output[2] << endl;
}

void CalculateFrequenc(const string& path, float* frequencesLettres)
{
    ifstream text(path);

    // Nombre d'apparition de chaque lettre
    vector<unsigned int> nbPourChaque(26, 0);

    // nombre de lettres au total
    unsigned int nbChar = 0;

    char c;

    // Pour chaque char du fichier
    // si c'est un caractère alphabétique
    // On ajoute 1 lettre au compteur total et au compteur de la lettre
    while(text >> c){
        c = tolower(c);
        if(c >= 'a' && c <= 'z')
        {
            nbPourChaque[c - 'a']++;
            nbChar++;
        }
    }

    // On divise le nombre d'apparition d'une lettre par le nombre total pour avoir une frequence enter 0 et 1
    for(unsigned int i = 0; i != 26; i++){
        frequencesLettres[i] = nbPourChaque[i] / (double)nbChar;
    }
}
