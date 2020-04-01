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

vector<string> strings;
vector<string> quotedStrings;
vector<string> unquotedStrings;
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

/* combines the quoted and unquoted strings into one vector */
vector<string> combineVectors(vector<string> vector1, vector<string> vector2) {
        int index1 = 0;
        int index2 = 0;
        vector<string> ret;
        if (ascending) {
            while (!vector1.empty() && !vector2.empty()) {
                if (vector1[0] <= vector2[0]) {
#ifdef DEBUG
                    printf("vector1[0] < vector2[0]. Adding %s instead of %s\n", vector1[0].c_str(), vector2[0].c_str());
#endif
                    ret.push_back(vector1[0]);
                    vector1.erase(vector1.begin());
                } else {
#ifdef DEBUG
                    printf("vector1[0] > vector2[0]. Adding %s instead of %s\n", vector2[0].c_str(), vector1[0].c_str());
#endif
                    ret.push_back("\'" + vector2[0] + "\'");
                    vector2.erase(vector2.begin());
                }
            }

            if (vector1.empty()) {

#ifdef DEBUG
                printf("Dumping vector2 into ret\n");
#endif

                for (const string &str : vector2) {
                    ret.push_back('\'' + str + '\'');
#ifdef DEBUG
                    printf("adding %s\n", str.c_str());
#endif
                }
            } else if (vector2.empty()) {
#ifdef DEBUG
                printf("Dumping vector1 into ret\n");
#endif
                for (const string &str : vector1) {
                    ret.push_back(str);
#ifdef DEBUG
                    printf("adding %s\n", str.c_str());
#endif
                }
            }
        }
        else if (descending) {

            while (!vector1.empty() && !vector2.empty()) {
                if (vector1[0] > vector2[0]) {
#ifdef DEBUG
                    printf("vector1[0] < vector2[0]. Adding %s instead of %s\n", vector1[0].c_str(), vector2[0].c_str());
#endif
                    ret.push_back(vector1[0]);
                    vector1.erase(vector1.begin());
                } else {
#ifdef DEBUG
                    printf("vector1[0] >= vector2[0]. Adding %s instead of %s\n", vector2[0].c_str(), vector1[0].c_str());
#endif
                    ret.push_back("\'" + vector2[0] + "\'");
                    vector2.erase(vector2.begin());
                }
            }

            if (vector1.empty()) {

#ifdef DEBUG
                printf("Dumping vector2 into ret\n");
#endif

                for (const string &str : vector2) {
                    ret.push_back('\'' + str + '\'');
#ifdef DEBUG
                    printf("adding %s\n", str.c_str());
#endif
                }
            } else if (vector2.empty()) {
#ifdef DEBUG
                printf("Dumping vector1 into ret\n");
#endif
                for (const string &str : vector1) {
                    ret.push_back(str);
#ifdef DEBUG
                    printf("adding %s\n", str.c_str());
#endif
                }
            }
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
            /* if string has quotes, remove them before adding to vector */
            if ((value[0] == '\'' || value[0] == '\"') && (value.back() == '\'' || value.back() == '\"')) {
                quotedStrings.push_back(value.substr(1, value.size() - 2));
            }
            else {
                unquotedStrings.push_back(value);
            }
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

        if (alpha) {
            sort(strings.begin(), strings.end());
            sort(quotedStrings.begin(), quotedStrings.end());
#ifdef DEBUG
            cout << "quoted strings";
        for (string str : quotedStrings) {
            cout << str << " ";
        }
        cout << endl;
#endif
            strings = combineVectors(unquotedStrings, quotedStrings);
        }
        if (numeric) {
            sort(numbers.begin(), numbers.end());
        }

    }
    else if (descending) {

        if (alpha) {
            sort(strings.begin(), strings.end(), greater<>());
            sort(quotedStrings.begin(), quotedStrings.end(), greater<>());

#ifdef DEBUG
            cout << "quoted strings";
            for (string str : quotedStrings) {
                cout << str << " ";
            }
            cout << endl;
#endif

            strings = combineVectors(unquotedStrings, quotedStrings);
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
        for (const string& str : strings) {
            cout << str << " ";
        }
    }
    cout << endl;

    file.close();

    return 0;
}
