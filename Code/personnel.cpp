#pragma once

#include <iostream>
#include <iomanip>
#include <string.h>
#include "personnel.hpp"

using namespace std;

void personnel::accept() {
    cout << "\n\n" << setw(44) << "Enter code name - ";
    fgets(code_name, 20, stdin);
    int l = strlen(code_name);
    code_name[l - 1] = '\0';
    cout<< "\n\n" << setw(43) << "Enter tag line - ";
    fgets(tagline, 30, stdin);
    l = strlen(tagline);
    tagline[l - 1] = '\0';
}

char* personnel::ret_code() {
    return code_name;
}

char* personnel::ret_tag() {
    return tagline;
}
