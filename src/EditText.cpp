//
// Created by sergeimakarov on 09.08.22.
//

#include "EditText.h"
#include <algorithm>
#include <regex>
#include <fstream>

EditText::EditText(const string &path) : stop_words(*loadStopWords(path)) {}

string EditText::lower(string& word){
    transform(begin(word), end(word), begin(word),
              [](unsigned char symbol){return tolower(symbol);});
    return word;
}

set<string> *EditText::removeStopWords(vector<string>* words){
    auto setWithoutStopWords = new set<string>;
    for (auto word : *words) {
        if(stop_words.find(lower(word)) == end(stop_words)) {
            setWithoutStopWords->insert(word);
        }
    }
    return setWithoutStopWords;
}

vector<string> *EditText::splitLine(const string& line){
    auto words = new vector<string>;
    regex regex("[a-zA-Z]+");
    for (sregex_token_iterator it(begin(line), end(line), regex), last; it != last; ++it)
        words->push_back(it->str());
    return words;
}

set<string> *EditText::loadStopWords(const string& path){
    auto stopWords = new set<string>;
    try {
        ifstream file(path);
        if (file.is_open()) {
            for (string line; getline(file, line);) {
                for (auto word: *splitLine(line)) {
                    stopWords->insert(lower(word));
                }
            }
        }
    }catch (exception& exception){
        cout << "File stop_words is not find!" << endl;
    }
    return stopWords;
}




