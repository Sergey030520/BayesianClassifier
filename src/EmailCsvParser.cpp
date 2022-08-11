//
// Created by sergeimakarov on 08.07.22.
//

#include "EmailCsvParser.h"
#include <fstream>
#include <iterator>
#include <algorithm>

void EmailCsvParser::loadFileCsv(const string &pathToCsvFile,  bool isReadFirstLine) {
    ifstream fileToCsv(pathToCsvFile);
    if (fileToCsv.is_open()) {
        for (string lineFileCsv; getline(fileToCsv, lineFileCsv);) {
            if (!isReadFirstLine) {
                isReadFirstLine = true;
                continue;
            } else {
                addRow(parseLine(&lineFileCsv));
            }
        }
    } else {
        throw errc::file_exists;
    }
}

pair<string, string>* EmailCsvParser::parseLine(string *line, char delimiter) {
    vector<string> columns;
    bool isActiveSeparator = true;
    string column;
    char preSymbol;
    for (char symbol : *line) {
        if(symbol == delimiter && isActiveSeparator && columns.size() < 2){
            columns.emplace_back(column);
            column.clear();
            continue;
        }else if(symbol == '"' && !(isActiveSeparator && preSymbol == symbol)){
            isActiveSeparator = !isActiveSeparator;
        }
        preSymbol = symbol;
        column += symbol;
    }
    return new pair<string, string>(make_pair(columns[0], (columns.size() == 1 ? column : columns[1])));
}

void EmailCsvParser::addRow(pair<string, string>* row) {
    type_message type = (row->first == "spam" ? SPAM : HAM);
    classified_messages.emplace_front(new ClassifierMessage(type, &row->second));
}

ClassifierMessage *EmailCsvParser::getMessage() {
    if(!classified_messages.empty()){
        ClassifierMessage* save_message = classified_messages.front();
        classified_messages.pop_front();
        classified_messages.emplace_back(save_message);
        return save_message;
    }
    return nullptr;
}

size_t EmailCsvParser::countMessage() {
    return classified_messages.size();
}

