#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#define DEBUG

using namespace std;

string valueType;
string sortOrder;

vector<string> words;
vector<double> numbers;

bool ascending = false;
bool descending = false;
bool alpha = false;
bool numeric = false;


/* Returns whether or not the given char is a number */
int isNumber(char c) {
    int ret = 0;
    if(
       c == '1' ||
       c == '2' ||
       c == '3' ||
       c == '4' ||
       c == '5' ||
       c == '6' ||
       c == '7' ||
       c == '8' ||
       c == '9' ||
       c == '0'
       )
    {
        ret = 1;
    }
    return ret;
}

/* Returns whether or not the given string is a string by checking if the first char is a number */
int isString(string str) {
    int ret = 0;

    if (!isNumber(str[0])) {
        ret = 1;
    }
    return ret;
}

/* Ensures that the proper number of args have been passed to the program */
int validateArgs(int argc, char** argv) {
    if (argc < 4) {
        printf(R"(improper number of params specified. Expected: "filepath" "sortOrder" "valueType" )");
        return -1;
    }

    return 1;
}

int main(int argc, char** argv) {

    if (!validateArgs(argc, argv)) {
        printf("Invalid args\n");
        return -1;
    }

    sortOrder = argv[2];
    if (sortOrder == "ascending") {
        ascending = true;
    }
    else if (sortOrder == "descending"){
        descending = true;
    }
    else {
        printf("Invalid sort order. Options: ascending, descending\n");
        return -1;
    }

#ifdef DEBUG
    printf("SortOrder selected:");
    if (ascending) {
        printf("ascending\n");
    }
    else if (descending) {
        printf("descending\n");
    }
    else {
        printf("Error\n");
    }
#endif

    valueType = argv[3];
    if (valueType == "alpha") {
        alpha = true;
    }
    else if (valueType == "numeric") {
        numeric = true;
    }
    else if (valueType == "both") {
        numeric = alpha = true;
    }
    else {
       printf("Invalid value type. Options: alpha, numeric, both\n");
       return -1;
    }

#ifdef DEBUG
    printf("ValueType selected:");
    if (alpha) {
        printf("alpha");
    }
    if (numeric) {
        printf("numeric\n");
    }
    if (!alpha && !numeric){
        printf("Error");
    }
    printf("\n");
#endif

    fstream file;
    file.open(argv[1]);

    string line, value;

    getline(file, line);
    stringstream s(line);

    while (getline(s, value, ',' )) {

        if (isString(value)){
#ifdef DEBUG
            printf("String %s added\n", value.c_str());
#endif
            words.push_back(value);
        }
        else if(isNumber(value[0])) {
            double num = stod(value, nullptr);
#ifdef DEBUG
            printf("Number %f added\n", num);
#endif
            numbers.push_back(num);
        }

    }

    /* Sort relevant vectors*/
    if (ascending) {

        //TODO handle quote marks
        if (alpha) {
            sort(words.begin(), words.end());
        }
        if (numeric) {
            sort(numbers.begin(), numbers.end());
        }

    }
    else if (descending) {

        if (alpha) {
            sort(words.begin(), words.end(), greater<>());
        }
        if (numeric) {
            sort(numbers.begin(), numbers.end(), greater<>());
        }
    }

    /* print relevant vectors */
    if (numeric) {
        for (double n : numbers) {
            cout << n << " ";
        }
    }
    if (alpha) {
        for (const string& str : words) {
            cout << str << " ";
        }
    }
    cout << endl;

    file.close();

    return 0;
}
