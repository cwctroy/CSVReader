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
vector<int> numbers;

bool ascending = false;
bool descending = false;
bool alpha = false;
bool numeric = false;

fstream file;

/* compares the first digit  */
int isNumber(char c) {
    int ret = 0;
    if(c == '1' ||
       c == '2' ||
       c == '3' ||
       c == '4' ||
       c == '5' ||
       c == '6' ||
       c == '7' ||
       c == '8' ||
       c == '9' ||
       c == '0'
            ) {
        ret = 1;
    }
    return ret;
}

int isString(string str) {
    int ret = 0;

    if (!isNumber(str[0])) {
        ret = 1;
    }
    return ret;
}

//TODO handle decimal values
int stringToNum(const string& str) {
    int ret = 0;
    for(char i : str) {
        ret *= 10;
        ret += i - 48;
    }
    return ret;
}

//TODO add specific error statements
int validateArgs(int argc, char** argv) {
    if (argc < 4) {
        printf(R"(improper number of params specified. Expected: "filepath" "sortOrder" "valueType" )");
        return -1;
    }

    return 1;
}

int main(int argc, char** argv) {

    //TODO add more info to output
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
        //TODO add handing of scientific notation
        else if(isNumber(value[0])) {
            int num = stringToNum(value);
#ifdef DEBUG
            printf("Number %d added\n", num);
#endif
            numbers.push_back(num);
        }
        //TODO add error?
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
        for (int n : numbers) {
            cout << n << " ";
        }
    }
    if (alpha) {
        for (string str : words) {
            cout << str << " ";
        }
    }
    cout << endl;

    file.close();

    return 0;
}
