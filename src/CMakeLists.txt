cmake_minimum_required(VERSION 3.20)

add_executable(${PROJECT_NAME}  main.cpp
        BayesianClassifier.cpp ${MY_INCLUDE_DIR}/BayesianClassifier.h
        EmailCsvParser.cpp ${MY_INCLUDE_DIR}/EmailCsvParser.h
        EditText.cpp ${MY_INCLUDE_DIR}/EditText.h)

target_include_directories(${PROJECT_NAME}  PUBLIC ${MY_INCLUDE_DIR})