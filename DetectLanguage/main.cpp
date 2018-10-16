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
    
    
    // Création du réseau de neurones
    // nbLayer, InputLayer, HiddenLayer, OutputLayer
    struct fann* ann = fann_create_standard(3, 26, 13, 4);

    
//    remove("/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/lang.net");
    
    // Entrainement du réseau à partir du fichier trainingAFE.data
    // epochs max : 100000
    // affiche des infos toutes les 10 epochs
    // erreur max désiré : 0.0001
    fann_train_on_file(ann, "/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/trainingAFE.data", 100000, 10, 0.0001);
    
    // Sauvegarde du réseau dans le fichier lang.net pour pouvoir s'en servir dans d'autres programmes
    fann_save(ann, "/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/lang.net");
    fann_destroy(ann);
    

}

void DetectText()
{
    // Création du réseau de neurones à partir des résultats de l'entrainement précedent (sauvegardé dans lang.net
    struct fann *ann = fann_create_from_file("/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/lang.net");
    
    // Séléction du fichier par l'utilisateur
    ifstream textFile = GetTextFilePath();
    
    // Calculs des fréquences de chaques lettres pour le texte donné
    float nbLettres[26];
    CalculateFrequenc(textFile, nbLettres);
    
    // Résultat du réseau de neurones
    float *output = fann_run(ann, nbLettres);
    cout << endl << endl << "Anglais : " << output[0] * 100 << "%" << endl << "Français : " << output[1] * 100 << "%" << std::endl << "Espagnol : " << output[2] * 100 << "%" << endl << "Allemand : " << output[3] * 100 << "%" << endl;// << "Portugais : " << output[4] * 100 << "%" << endl;
}

void CalculateFrequenc(ifstream& text, float* frequencesLettres)
{
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

    // On divise le nombre d'apparition d'une lettre par le nombre total pour avoir une frequence entre 0 et 1
    for(unsigned int i = 0; i != 26; i++){
        frequencesLettres[i] = nbPourChaque[i] / (double)nbChar;
//        cout << (char)(i + 'a') << " : " << frequencesLettres[i] << endl;
    }
}

ifstream GetTextFilePath()
{
        ifstream fileText;
        string path;
        
        do{
            system("CLEAR");
            cout << "francais - anglais - espagnol - allemand" << endl << "---------" << endl << endl;
            cout << "Choisissez la langue que vous voulez ou laissez vide pour français" << endl;
            getline(cin, path);
            if ("" == path){
                path = "francais";
            }
            fileText.open("/Users/Raph/Documents/Gamagora/IA/Cours5/DetectLanguage/" + path + ".txt");
        }while (!fileText);
        
        return fileText;
}
