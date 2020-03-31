#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>

#define DEBUG

using namespace std;

string valueType;
string sortOrder;
vector<string> words;

vector<int> numbers;


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

//TODO add instructions
//TODO add specific error statements
int validateArgs(int argc, char** argv) {

    if (argc < 4) {
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

    valueType = argv[3];

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
    if (sortOrder == "ascending") {

        if (valueType == "both") {
            sort(numbers.begin(), numbers.end());
            sort(words.begin(), words.end());
        }
        else if (valueType == "alpha") {
            sort(words.begin(), words.end());
        }
        else {
            sort(numbers.begin(), numbers.end());
        }

    }
    else if (sortOrder == "descending") {

        if (valueType == "both") {
            sort(numbers.begin(), numbers.end(), greater<>());
            sort(words.begin(), words.end(),greater<>());
        }
        else if (valueType == "alpha") {
            sort(words.begin(), words.end(), greater<>());
        }
        else {
            sort(numbers.begin(), numbers.end(), greater<>());
        }
    }

#ifdef DEBUG
    printf("Printing strings\n");

    for (const string& str : words) {
        printf("%s\n", str.c_str());
    }


    printf("Sorted numbers\n");
    for (int n: numbers) {
        printf("%d ",n);
    }
    printf("\n");

#endif
    file.close();

    return 0;
}
