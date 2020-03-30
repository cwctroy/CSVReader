#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#define DEBUG

using namespace std;

string filename;
string valueType;
string sortOrder;
vector<string> words;

vector<int> numbers;

/* compares the first character of a string, if it is a quote mark, returns true */
int isString(string str) {
    int ret = 0;

    if (str[0] == '\'' || str[0] == '\"') {
        ret = 1;
    }
    return ret;
}

/* compares the first digit  */
int isNumber(string str) {
    int ret = 0;
    if( str[0] == '1' ||
        str[0] == '2' ||
        str[0] == '3' ||
        str[0] == '4' ||
        str[0] == '5' ||
        str[0] == '6' ||
        str[0] == '7' ||
        str[0] == '8' ||
        str[0] == '9' ||
        str[0] == '0'
            ) {
        ret = 1;
    }
    return ret;
}

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
    return 1;
}

int main(int argc, char** argv) {

    //TODO add more info to output
    if (!validateArgs(argc, argv)) {
        printf("Invalid args\n");
        return -1;
    }

    fstream file;

    filename = argv[1];
    valueType = argv[2];
    sortOrder = argv[3];

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
        else if(isNumber(value)) {
            int num = stringToNum(value);
            numbers.push_back(num);
        }
        //TODO add error?
    }

#ifdef DEBUG
    printf("Printing strings\n");

    for (string str : words) {
        printf("%s\n", str.c_str());
    }

    for (string str : words) {
        printf("%s\n", str.c_str());
    }

#endif
    file.close();

    return 0;
}

