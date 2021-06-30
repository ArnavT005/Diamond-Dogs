#pragma once

#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <thread>
#include <chrono>
#include "staff.hpp"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

staff::staff() {
    strcpy(comp,"NULL");
    strcpy(name,"NULL");
    strcpy(code_name,"NULL");
    age = 0;
    unit = 0;
    skill = 0;
    gender = '\0';
    com = 0;
    fired = 0;
 }

void staff::accept() {
    cout << "Enter name - ";
    fgets(name, 20, stdin);
    int l = strlen(name);
    name[l - 1] = '\0';
    cout << "\nEnter your code name -";
    fgets(code_name, 20, stdin);
    l = strlen(code_name);
    code_name[l - 1] = '\0';
    cout << "\nEnter age - ";
    cin >> age;
    cout << "\nEnter gender (M/F) -";
    cin >> gender;
    system("cls");
    cout << setw(50) << "APPLICATION FORM" << "\n\n\n";
    cout << "\nChoose the unit you want to be in - " << endl;
    cout << "Press 1 to apply for Base development unit " << endl;
    cout << "Press 2 to apply for Combat unit " << endl;
    cout << "Press 3 to apply for Medical Team " << endl;
    cin >> unit;
    cout << "\n\nEnter your skill in the applied field (on a scale of 1 to 10) - ";
    cin >> skill;
    char buff[3];
    fgets(buff, 3, stdin);
    staff S;
    ifstream fin("../DataFiles/staff.dat", ios::binary);
    if(!fin) {
        cout << "Something went wrong. Program terminated!!";
        exit(0);
    }
    bool flag = false;
    while(!fin.eof()) {
        fin.read((char*)&S, sizeof(S));
        if(!strcmpi(code_name, S.ret_code())) {
            flag = true;
            break;
        }
    }
    fin.close();
    ifstream fin2("../DataFiles/apply.dat", ios::binary);
    if(!fin2) {
        cout << "Something went wrong. Program terminated!!";
        exit(0);
    }
    while(!fin2.eof()) {
        fin2.read((char*)&S, sizeof(S));
        if(!strcmpi(code_name, S.ret_code())) {
            flag = true;
            break;
        }
    }
    fin2.close();
    if(flag) {
        cout << "Sorry, the code name \"" << code_name << "\" is already in use. Please pick a new name.\n";
        cout << "Reloading form in 3 seconds...";
        sleep_for(3s);
        system("cls");
        cout << setw(50) << "APPLICATION FORM\n\n\n";
        accept();
    }
}

void staff::display() {
    system("cls");
    cout<<endl<<endl<<endl;
    cout<<"Name of mercenary - ";
    puts(name);
    cout<<"\n\nCode name of the mercenary - ";
    puts(code_name);
    cout<<"\n\nAge of the mercenary - "<<age;
    cout<<"\n\nGender - "<<gender;
    cout<<"\n\nUnit - ";
    switch(unit) {
    case 1:
        cout << "\tBase Development Unit";
        break;
    case 2:
        cout << "\tCombat Unit";
        break;
    case 3:
        cout << "\tMedical Team";
        break;
    }
    cout << "\n\nSkill in the unit - " << skill << "\n\n";
}

void staff::write_comp() {
    cout << "Write your complaint against the organisation - ";
    cout << endl << "(Note that irrelevant complaints, allegations can get you fired from the \norganisation)";
    cout << endl;
    fgets(this->comp, 75, stdin);
    int l = strlen(this->comp);
    this->comp[l - 1] = '\0';
    cout << "\nYour complaint has been successfully saved. You will be notified asap.\n\n";
}

int staff::ret_unit() {
    return unit;
}

char* staff::ret_code() {
    return code_name;
}

char* staff::ret_comp() {
    return comp;
}

char* staff::ret_name() {
    return name;
}





