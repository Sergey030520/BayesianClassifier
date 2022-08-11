//
// Created by sergeimakarov on 09.08.22.
//

#ifndef BAYESIANCLASSIFIER_EDITTEXT_H
#define BAYESIANCLASSIFIER_EDITTEXT_H

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class EditText {
private:
    set<string> stop_words;
    set<string>* loadStopWords(const string& path);
public:
    /**
* @param path в конструктор класса передаётся адресс на пермеyнную,
     * которая хранит путь до фалйа с стоп словами
*/
    EditText(const string& path);

    /**
* Метод переводит символы из верхнего регистра в нижний
* @param word слово, для обработки
* @return возвращает слово, где все буквы в нижнем регистре
*/
    static string lower(string& word);

    /**
* Метод удаляет из динамического массива стоп слова
* @param words массив слов
* @return возвращает контейнер set, в котором отсутсвуют стоп слова
*/
    set<string>* removeStopWords(vector<string>* words);

    /**
* Метод делит строку на слова и удаляет знаки препинаяния
* @param line строка которую необходимо разделить
* @return динамический массив слов
*/
    static vector<string>* splitLine(const string& line);
};


#endif //BAYESIANCLASSIFIER_EDITTEXT_H
