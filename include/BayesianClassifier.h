//
// Created by Malip on 08.06.2022.
//

#ifndef BAYESIANCLASSIFIER_BAYESIANCLASSIFIER_H
#define BAYESIANCLASSIFIER_BAYESIANCLASSIFIER_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "EmailCsvParser.h"
#include <EditText.h>

using namespace std;

struct SampleType{
    size_t spam;
    size_t ham;
    SampleType(size_t inSpam = 0, size_t inHam = 0) : spam(inSpam), ham(inHam){}
};



class BayesianClassifier {
    float smoothing{1};//Сглаживание Лапласа
    SampleType countWordsInClass;
    map<string, SampleType> trained_sample;
    EditText* editor_text;

    /**
* Метод расчитывает оценку принадлежности сообщения для каждого класса
* @param wordsMessageTesting слова из тестового сообщения
     * @param classifierMessage класс сообщения (SPAM/HAM)
* @return возвращает оценку принадлежности сообщения к классу
*/
    float countOccurrencesWordInClass(set<string> *wordsMessageTesting, type_message classifierMessage);

public:

    /**
* @param dataSet база данных сообщений,
     * @param inEditorText текстовый редактор
     * @param inCountTrainedMessage количество считываемых сообщений для обучения классификатора
*/
    BayesianClassifier(EmailCsvParser* dataSet, EditText* inEditorText, int inCountTrainedMessage = 1);

    /**
* Метод классифиицирует сообщение (SPAM/HAM)
* @param wordsMessageTesting массив слов тестового сообщения
* @return возвращает класс, к которому принадлежит сообщение
*/
    type_message messageClassifier(string* wordsMessageTesting);

    ~BayesianClassifier();
};


#endif //BAYESIANCLASSIFIER_BAYESIANCLASSIFIER_H
