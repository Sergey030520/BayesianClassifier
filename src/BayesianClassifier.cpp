//
// Created by Malip on 08.06.2022.
//

#include "BayesianClassifier.h"
#include "EditText.h"
#include <future>
#include <cmath>


BayesianClassifier::BayesianClassifier(EmailCsvParser* dataSet, EditText* inEditorText,
                                       int countTrainedMessage) : editor_text(inEditorText) {
    for (size_t numbMessageEmail = 0; numbMessageEmail < countTrainedMessage; ++numbMessageEmail) {
        auto message = dataSet->getMessage();
        auto words = editor_text->removeStopWords(EditText::splitLine(*message->text));
        for (const auto& word : *words) {
            if(trained_sample.count(word) > 0){
                (message->type == SPAM ? trained_sample[word].spam++ : trained_sample[word].ham++);
            }else{
                trained_sample.emplace(make_pair(word,
                                                 (message->type == SPAM ? SampleType(1, 0) :
                                                 SampleType(0, 1))));
            }
            (message->type == SPAM ? countWordsInClass.spam++ : countWordsInClass.ham++);
        }
    }
}

float BayesianClassifier::countOccurrencesWordInClass(set<string> *wordsMessageTesting,
                                                     type_message classifierMessage) {
    float rate;
    for (const auto& word : *wordsMessageTesting) {
        int numbWordsInClass, numberWordIncludeClass;
        if(classifierMessage == SPAM){
            numbWordsInClass = countWordsInClass.spam;
            numberWordIncludeClass = (trained_sample.count(word) > 0 ? trained_sample[word].spam : 0);
        }else{
            numbWordsInClass = countWordsInClass.ham;
            numberWordIncludeClass = (trained_sample.count(word) > 0 ? trained_sample[word].ham : 0);
        }
        rate += log(((smoothing + numberWordIncludeClass)/(numbWordsInClass + trained_sample.size())));

    }
    return rate;
}

type_message BayesianClassifier::messageClassifier(string* message){
    auto wordsMessageTesting = editor_text->removeStopWords(
            EditText::splitLine(*message));
    future<float> threads[]{
            async(&BayesianClassifier::countOccurrencesWordInClass, this, wordsMessageTesting, SPAM),
            async(&BayesianClassifier::countOccurrencesWordInClass, this, wordsMessageTesting, HAM),
    };
    float rateClass[]{threads[0].get(), threads[1].get()};
    return (rateClass[0] > rateClass[1] ? SPAM : HAM);
}

BayesianClassifier::~BayesianClassifier() {
    delete editor_text;
}



