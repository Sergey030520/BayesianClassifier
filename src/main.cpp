#include <iostream>
#include "EmailCsvParser.h"
#include "BayesianClassifier.h"
#include <vector>
#include <future>
using namespace std;


int percentOfNumber(int sizeEl, float percent){
    return (sizeEl*percent)/100;
}


int main(int argc, char **argv) {
    EmailCsvParser emailParser;
    emailParser.loadFileCsv("");

    size_t countAllMessage = emailParser.countMessage(),
            countTrainedMessage = percentOfNumber(countAllMessage, 80),
            countTestMessage = countAllMessage - countTrainedMessage;

    const string pathToFileStopWord = "";

    BayesianClassifier bayesianClassifier(&emailParser, new EditText(pathToFileStopWord),
                                          countTrainedMessage);

    vector<future<type_message>> thr_message_processing;
    vector<type_message> message_type_approved;

    int classifier_accuracy = 0;
    for (size_t numbMessage = 0; numbMessage < countTestMessage; ++numbMessage) {
        auto message = emailParser.getMessage();
        thr_message_processing.push_back(
                async(&BayesianClassifier::messageClassifier, &bayesianClassifier, message->text));
        message_type_approved.push_back(message->type);
    }
    for (int numbThread = 0; numbThread < thr_message_processing.size(); ++numbThread) {
        classifier_accuracy += (thr_message_processing[numbThread].get() == message_type_approved[numbThread]
                ? 1 : 0);
    }

    cout << "classifier accuracy: " << (float)(classifier_accuracy)/(float)countTestMessage << endl;
}