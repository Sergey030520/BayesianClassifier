//
// Created by sergeimakarov on 08.07.22.
//

#ifndef BAYESIANCLASSIFIER_EMAILCSVPARSER_H
#define BAYESIANCLASSIFIER_EMAILCSVPARSER_H

#include <iostream>
#include <list>
#include <set>
#include <vector>
using namespace std;

enum type_message{SPAM, HAM};

struct ClassifierMessage{
     type_message type;
     string* text;
     ClassifierMessage(type_message inType, string* inText): type(inType),
        text(inText){};
     ~ClassifierMessage(){
         delete text;
     }
};

class EmailCsvParser {
    list<ClassifierMessage*> classified_messages;
public:
    EmailCsvParser() = default;

    /**
* Метод загрузки файлов csv
* @param pathToCsvFile путь до файла Csv
     * @param isReadFirstLine определяет необходимо ли считывать первую строку файла
*/
    void loadFileCsv(const string& pathToCsvFile, bool isReadFirstLine = false);

    /**
* Метод разделяющий строку на колонны
* @param line строка из файла
     * @param delimiter знак разделяющий колонки
* @return возвращает пару ключ-значение, где ключ является типом сообщения, а значение сообщением
*/

    pair<string, string>* parseLine(string* line, char delimiter = ',');

    /**
* Метод добавлени строки в таблицу данных
* @param row пара ключ-значение, где ключ является типом сообщения, а значение сообщением
*/

    void addRow(pair<string, string>* row);

    ClassifierMessage* getMessage();

    size_t countMessage();
};


#endif //BAYESIANCLASSIFIER_EMAILCSVPARSER_H
