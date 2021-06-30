#include <iostream>
#include <iomanip>
#include <conio.h>
#include <dos.h>
#include <fstream>
#include <process.h>
#include <string.h>
#include <stdio.h>
#include <cstdio>
#include <chrono>
#include <thread>
#include <sys/stat.h>
#include "staff.hpp"
#include "personnel.hpp"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

int ca = 0, cs = 0, cc = 0;

void display_diamond();
void homepage();
void form();
void perlogin();
void personneld(personnel P);
void complaint(staff &S);
void staff_login();
void apply(personnel P);
void comp(personnel P);
void view_staff_login(personnel P);
void view_staff(staff S,personnel P);
void staffd(staff S);
void delete_record(staff S, const char* file);
void update_record(staff S, const char* file);
void count_staff();
void count_apply();
void count_complaint();

int main() {
    system("cls");
    count_staff();
    count_apply();
    count_complaint();
    struct stat buf;
    if(stat("../DataFiles/personnel.dat", &buf) == -1) {
        personnel P;
        ofstream fout("../DataFiles/personnel.dat", ios::binary | ios::app);
        if(!fout) {
            cout<<"Unable to open ";
            exit(0);
        }
        else {
            P.accept();
            fout.write((char*)&P, sizeof(P));
            P.accept();
            fout.write((char*)&P, sizeof(P));
        }
        fout.close();
    }
    display_diamond();
    return 0;
}

void display_diamond() {
    system("cls");
    cout << setw(45) << "DIAMOND DOGS" << endl;
    cout << "	  	      __________________________________               \n";
    cout << "		    /                                    \\            \n";
    cout << "		  /                                        \\          \n";
    cout << "	        /                                            \\        \n";
    cout << "	      /             ||======\\  ||======\\               \\    \n";
    cout << "	    /               ||      |  ||      |                 \\   \n";
    cout << "	  <                 ||      |  ||      |                  >   \n";
    cout << "	    \\               ||      |  ||      |                /     \n";
    cout << "	      \\             ||      |  ||      |              /       \n";
    cout << "	        \\           ||      |  ||      |            /         \n";
    cout << "		  \\         ||      |  ||      |          /           \n";
    cout << "		    \\       ||======/  ||======/        /             \n";
    cout << "		      \\                               /               \n";
    cout << "		        \\                           /                 \n";
    cout << "			  \\                       /                   \n";
    cout << "			    \\                   /                     \n";
    cout << "			      \\               /                       \n";
    cout << "			        \\           /                         \n";
    cout << "				  \\       /                           \n";
    cout << "				    \\   /                             \n";
    cout << "				      \\/                               \n";
    cout << setw(49) << "> HOME OF THE ELITE <" << endl;
    cout << "Press any key to continue - ";
    getch();
    homepage();
}

void homepage() {
    system("cls");
    int opt;
    cout << setw(46) << "DIAMOND DOGS" << "\n\n\n";
    cout << "This is the portal page of the private mercenary organization - " << "DIAMOND DOGS." <<endl;
    cout << "The page provides access to various facilities depending upon position in DD. " << endl;
    cout << "\n\n\nIf you are a staff member, press 1 to login to your DD account.\n\n";
    cout << "If you are a part of the authorized personnel, press 2 to login and manage the base statistics and staff.\n\n";
    cout << "Not a dog already? If you want to be one and you have what it takes to become  one! Apply today!!" << endl;
    cout << "Press 3 to fill the application form\n\n";
    cout << "If you want to go back to the first screen, press 4\n\n";
    cout << "Or press 5 if you want to terminate the program right now.\n\n\n";
    cout << "Enter your option - ";
    cin >> ws >> opt;
    char buff[3];
    fgets(buff, 3, stdin);
    switch(opt) {
    case 1:
        staff_login();
        break;
    case 2:
        perlogin();
        break;
    case 3:
        form();
        break;
    case 4:
        display_diamond();
        break;
    case 5:
        cout << endl << "The program is terminated" << endl;
        exit(0);
        break;
    default:
        system("cls");
        cout << "\nIncorrect option passed. Enter a number from 1 to 5." <<endl;
        cout << "Reloading screen in 5 seconds.....";
        sleep_for(5s);
        homepage();
    }
}

void staff_login() {
    system("cls");
    staff S;
    char codename[20];
    int unit, flag = 0;
    ifstream fin("../DataFiles/staff.dat", ios::binary);
    if(!fin) {
        cout << "Something went wrong. Program terminated!!";
        exit(0);
    }
    cout << endl << setw(45) << "STAFF LOGIN\n\n\n\n\n";
    cout << setw(38) << "Code Name: ";
    fgets(codename, 20, stdin);
    int l = strlen(codename);
    codename[l - 1] = '\0';
    cout << setw(38) << "Unit : ";
    cin >> ws >> unit;
    char buff[3];
    fgets(buff, 3, stdin);
    while(!fin.eof()) {
        fin.read((char*)&S,sizeof(S));
        if((!strcmpi(codename, S.ret_code())) && (unit == S.ret_unit())) {
            if(S.fired==1) {
                system("cls");
                fin.close();
                cout << "\nSorry, but you have been fired and your account is deleted from DD's database!!";
                cout << "\nProgram terminated!!";
                exit(0);
            }
            else {
                flag=1;
                break;
            }
        }
    }
    fin.close();
    if(!flag) {
        cout << "\n\n\nUnauthorised accesss detected." << endl;
        cout << "Program terminated!!";
        exit(0);
    }
    else {
        cout << "Opening dashboard in 2 seconds.....";
        sleep_for(2s);
        staffd(S);
    }
}

void staffd(staff S) {
    system("cls");
    int opt;
    cout << setw(48) << "STAFF DASHBOARD\n\n\n\n\n";
    cout << " 1. Display Details\n";
    cout << " 2. File Complaints\n";
    cout << " 3. Log out and return to portal page\n";
    cout << " 4. Terminate the program\n";
    cout << "Press corresponding option key to continue: ";
    cin >> ws >> opt;
    char buff[3];
    fgets(buff, 3, stdin);
    switch(opt) {
    case 1:
        system("cls");
        cout << setw(48) << "STAFF DASHBOARD\n\n";
        S.display();
        cout << "Press any key to go back - ";
        getch();
        sleep_for(2s);
        staffd(S);
        break;
    case 2:
        complaint(S);
        break;
    case 3:
        homepage();
        break;
    case 4:
        cout<<"\nThe program has been terminated!!";
        exit(0);
    default:
        cout << "Incorrect option entered.Enter a number between from 1 to 4." << endl;
	    cout << "Reloading page in 3 second ";
	    sleep_for(3s);
	    staffd(S);
   }
}

void complaint(staff &S) {
    system("cls");
    staff st;
    ifstream fin("../DataFiles/complaint.dat", ios::binary);
    if(!fin) {
        cout << "Something went wrong. Program terminated!!";
        exit(0);
    }
    bool flag = false;
    while(!fin.eof()) {
        fin.read((char*)&st, sizeof(st));
        if(!strcmpi(S.ret_code(), st.ret_code())) {
            flag = true;
            break;
        }
    }
    fin.close();
    if(flag) {
        cout << "\nYour previous complaint has not been resolved yet. Wait for Boss' verdict before filing another complaint.\n";
        cout << "Redirecting to your dashboard in 5 seconds....\n";
        sleep_for(5s);
        staffd(S);
    }
    else {
        cout << setw(50) << "STAFF COMPLAINTS\n\n\n\n\n";
        ofstream fout("../DataFiles/complaint.dat", ios::binary | ios::app);
        int opt;
        if(!fout) {
            cout << "Something went wrong. Program terminated!";
            exit(0);
        }
        if(S.com == 1) {
            cout << "\nYour previous complaint was taken care of by the organisation.\nThanks for the feedback!" << endl;
            S.com = 0;
        }
        S.write_comp();
        fout.write((char*)&S,sizeof(S));
        fout.close();
        cc++;
        update_record(S, "../DataFiles/staff.dat");
        cout << "Press 1 to go back to dashboard or press 2 to terminate the program - ";
        cin >> ws >> opt;
        char buff[3];
        fgets(buff, 3, stdin);
        switch(opt) {
        case 1:
            staffd(S);
            break;
        case 2:
            cout << "\nThe program is terminated!!";
            exit(0);
            break;
        default:
            cout<<"\nIncorrect option entered. Redirecting to dashboard in 2 seconds.. ";
            sleep_for(2s);
            staffd(S);
        }
    }
}

void form() {
    system("cls");
    int opt;
    staff S;
    ofstream fout("../DataFiles/apply.dat", ios::binary | ios::app);
    if(!fout) {
        cout<<"\nUnable to open the form currently. Try again later...";
        exit(0);
    }
    cout << setw(50) << "APPLICATION FORM\n\n\n";
    S.accept();
    fout.write((char*)&S, sizeof(S));
    fout.close();
    ca++;
    system("cls");
    cout << setw(50) << "APPLICATION FORM\n\n\n";
    cout << "Your details have been registered successfully!! ";
    cout << "The results will be provided to you asap." << endl;
    cout << "You will be able to log in to your staff account upon confirmation with the same codename and unit number.\n\n";
    cout << "To return to the portal page press 0." << endl;
    cout << "Enter any other number to terminate the program" << endl;
    cin>>opt;
    char buff[3];
    fgets(buff, 3, stdin);
    if(!opt)
        homepage();
    else  {
        cout << endl << "The program is terminated!";
        exit(0);
    }
}

void perlogin() {
    system("cls");
    personnel P, check;
    ifstream fin("../DataFiles/personnel.dat", ios::binary);
    int flag=0;
    if(!fin) {
        cout << "\nUnable to login in currently, please try again later...";
        exit(0);
    }
    cout << setw(53) << "AUTHORIZED PERSONNEL LOGIN\n\n\n\n\n";
    P.accept();
    while(!fin.eof()) {
        fin.read((char*)&check, sizeof(check));
        if(!strcmpi(P.ret_code(), check.ret_code())) {
            if(!strcmp(P.ret_tag(), check.ret_tag())) {
                flag=1;
                break;
            }
        }
    }
    fin.close();
    if(!flag) {
        cout << "\n\n\n\n\n\nUnauthorized access detected. Program terminating!!!";
        exit(0);
    }
    else {
        cout << "\n\nOpening personal dashboard.....";
        sleep_for(2s);
        personneld(P);
    }
}

void personneld(personnel P) {
    system("cls");
    int choice;
    if(strcmpi(P.ret_code(), "Snake"))
        cout << setw(50) << "KAZUHIRA'S DASHBOARD\n\n\n";
    else
        cout << setw(47) << "SNAKE'S DASHBOARD\n\n\n";
    cout << "\nWelcome BOSS! What do you want to do today?\n\n";
    cout << "\nNumber of applications currently pending - " << ca;
    cout << "\n\nNumber of complaints currently pending - " << cc;
    cout << "\n\nNumber of dogs currently recruited - " << cs;
    if(ca)
        cout << "\n\nPress 1 to view applications.";
    if(cc)
        cout << "\n\nPress 2 to view complaints.";
    if(cs)
        cout << "\n\nPress 3 to view staff details and manage them.";
    cout << "\n\nPress 4 to logout and go back to the portal page,\n\n";
    cout << "Or press 5 to terminate the program.\n";
    cout << "Enter your choice - ";
    cin >> ws >> choice;
    char buff[3];
    fgets(buff, 3, stdin);
    switch(choice) {
    case 1:
        apply(P);
        break;
    case 2:
        comp(P);
        break;
    case 3:
        view_staff_login(P);
        break;
    case 4:
        homepage();
        break;
    case 5:
        cout << endl << "The program is terminated";
        exit(0);
        break;
    default:
        system("cls");
        cout << "\nIncorrect option passed. Enter a number from 1 to 5." <<endl;
        cout << "Reloading screen in 5 seconds.....";
        sleep_for(5s);
        personneld(P);
    }
}

void apply(personnel P) {
    char ch[3];
    staff S;
    int opt;
    while(ca) {
        system("cls");
        ifstream fin("../DataFiles/apply.dat", ios::binary);
        ofstream fout("../DataFiles/staff.dat", ios::binary | ios::app);
        if(!fin || !fout) {
            cout << "Something went wrong. Program terminated!!";
            exit(0);
        }
        cout << setw(50) << "PENDING APPLICATIONS\n\n\n\n";
        cout << "Do you want to load application (Yes/No) - ";
        fgets(ch, 5, stdin);
        int l = strlen(ch);
        ch[l - 1] = '\0';
        if(strcmpi(ch, "No")) {
            fin.read((char*)&S, sizeof(S));
            S.display();
            cout << "\n\nDo you want to recruit the applicant in the desired unit?(Yes/No) ";
            fgets(ch, 5, stdin);
            ch[l - 1] = '\0';
            if(!strcmpi(ch, "Yes")) {
                fout.write((char*)&S, sizeof(S));
                cs++;
            }
            fin.close();
            fout.close();
            delete_record(S, "../DataFiles/apply.dat");
            ca --;
        }
        else {
            fin.close();
            fout.close();
            cout << "\nDo you want to go back to dashboard or logout and terminate the program?";
            cout << "\nPress 1 to go back to dashboard";
            cout << "\nPress 2 to logout and terminate the program" << endl;
            cin >> ws >> opt;
            char buff[3];
            fgets(buff, 3, stdin);
            switch(opt) {
            case 1:
                personneld(P);
                break;
            case 2:
                cout << "\nProgram is terminated";
                exit(0);
            default:
                cout << "\nIncorrect option entered.\nReloading in 3 seconds...";
                sleep_for(3s);
                apply(P);
            }
        }
    }

    if(!ca) {
        system("cls");
        cout << setw(50) << "PENDING APPLICATIONS\n\n\n";
        cout << "All applications have been reviewed!!";
        cout << "\nPress 1 to go back to dashboard";
        cout << "\nPress 2 to logout and terminate the program" << endl;
        cin >> ws >> opt;
        char buff[3];
        fgets(buff, 3, stdin);
        switch(opt) {
        case 1:
            personneld(P);
            break;
        case 2:
            cout << "\nProgram is terminated";
            exit(0);
        default:
            cout << "\nIncorrect option entered.\nReloading in 3 seconds...";
            sleep_for(3s);
            apply(P);
        }
    }
}

void comp(personnel P) {
    system("cls");
    char ch[6];
    int opt;
    char *cha;
    staff S;
    while(cc) {
        system("cls");
        ifstream fin("../DataFiles/complaint.dat", ios::binary);
        if(!fin) {
            cout << "\nUnable to open";
            exit(0);
        }
        cout << setw(49) << "PENDING COMPLAINTS\n\n\n\n";
        cout << "\nDo you want to load complaint (Yes/No)? ";
        fgets(ch, 5, stdin);
        int l = strlen(ch);
        ch[l - 1] = '\0';
        if(!strcmpi(ch, "yes")) {
            fin.read((char*)&S, sizeof(S));
            cout << "\nName of the dog - ";
            puts(S.ret_name());
            cout << "\nComplaint of the dog - " << endl;
            cha = S.ret_comp();
            puts(cha);
            cout << endl << endl;
            cout << "\nDo you want to take necessary actions or reject the complaint and" << endl << "fire the dog (Yes/Fire)? ";
            fgets(ch, 6, stdin);
            l = strlen(ch);
            ch[l - 1] = '\0';
            fin.close();
            if(!strcmpi(ch, "yes")) {
                S.com = 1;
                delete_record(S, "../DataFiles/complaint.dat");
                update_record(S, "../DataFiles/staff.dat");
                cc--;
            }
            else {
                S.fired=1;
                update_record(S, "../DataFiles/staff.dat");
                delete_record(S, "../DataFiles/complaint.dat");
                cc--;
                cs--;
            }
        }
        else {
            fin.close();
            cout << "\nDo you want to go back to dashboard or logout and terminate the program?";
            cout << "\nPress 1 to go back to dashboard";
            cout << "\nPress 2 to logout and terminate the program" << endl;
            cin >> ws >> opt;
            char buff[3];
            fgets(buff, 3, stdin);
            switch(opt) {
            case 1:
                personneld(P);
                break;
            case 2:
                cout << "\nProgram is terminated";
                exit(0);
            default:
                cout << "\nIncorrect option entered.\nReloading in 3 seconds...";
                sleep_for(3s);
                comp(P);
            }
        }
    }
    if(!cc) {
        system("cls");
        cout << setw(49) << "PENDING COMPLAINTS\n\n\n";
        cout << "All complains have been reviewed!!";
        cout << "\nPress 1 to go back to dashboard";
        cout << "\nPress 2 to logout and terminate the program"<<endl;
        cin >> ws >> opt;
        char buff[3];
        fgets(buff, 3, stdin);
        switch(opt) {
        case 1:
            personneld(P);
            break;
        case 2:
            cout<<"\nProgram is terminated";
            exit(0);
        default:
            cout<<"\nIncorrect option entered.\nReloading in 3 seconds...";
            sleep_for(3s);
            comp(P);
        }
    }
}

void view_staff_login(personnel P) {
    system("cls");
    char code[10];
    int flag = 0;
    staff S, nw;
    cout << setw(47) << "STAFF MANAGEMENT\n\n\n\n\n";
    cout << setw(45) << "Enter staff codename - ";
    fgets(code, 20, stdin);
    int l = strlen(code);
    code[l - 1] = '\0';
    ifstream fin("../DataFiles/staff.dat", ios::binary);
    if(!fin) {
        cout << "Something went wrong. Program terminated!!";
        exit(0);
    }
    while(!fin.eof()) {
        fin.read((char*)&S, sizeof(S));
        if(!strcmpi(code, S.ret_code()) && S.fired == 0) {
            flag = 1;
            nw = S;
            break;
        }
    }
    fin.close();
    if(!cs) {
        cout << "\n\n\nNo staff currently recruited. Redirecting to personal dashboard....";
        sleep_for(3s);
        personneld(P);
    }
    else if(!flag) {
        cout << "\n\nNo record found";
        cout << "\nPage reloading.....";
        sleep_for(3s);
        view_staff_login(P);
    }
    else
        view_staff(nw,P);
}

void view_staff(staff S,personnel P) {
    system("cls");
    int opt;
    cout << setw(47) << S.ret_code() << "'s STATISTICS \n\n\n\n";
    cout << "Welcome BOSS!!" << endl;
    cout << "What do you want to do with the following dog - ";
    cout << endl << "Press 1 to view dog's details" << endl << "Press 2 to fire the dog";
    cout << endl << "Press 3 to go back to staff management section" << endl;
    cout << endl << "Press 4 to go back to personal dashboard";
    cout << endl << "Press 5 to logout and terminate the program" << endl;
    cin >> ws >> opt;
    char buff[3];
    fgets(buff, 3, stdin);
    switch(opt) {
    case 1:
        system("cls");
        cout << setw(47) << S.ret_code() << "'s STATISTICS \n\n\n\n";
        S.display();
        cout << "\nPress any key to go back - ";
        getch();
        view_staff(S, P);
        break;
    case 2:
        S.fired = 1;
        system("cls");
        delete_record(S, "../DataFiles/complaint.dat");
        update_record(S, "../DataFiles/staff.dat");
        cs --;
        cc = 0;
        count_complaint();
        cout << "\nThe dog has been fired (hot dog) successfully";
        cout << "\nWhat do you want to do now -";
        if(cs!=0)
            cout << "\nPress 1 to go back to staff management section";
        cout << "\nPress 2 to go back to personal dashboard ";
        cout << "\nPress 3 to logout and terminate the program ";
        cout << endl;
        cin >> ws >> opt;
        char buff[3];
        fgets(buff, 3, stdin);
        switch(opt) {
        case 1:
            view_staff_login(P);
            break;
        case 2:
            personneld(P);
            break;
        case 3:
            cout << "\nProgram terminated";
            exit(0);
            break;
        default:
            cout << "\nSomething went wrong....Program terminated";
            exit(0);
        }
        break;
    case 3:
        view_staff_login(P);
        break;
    case 4:
        personneld(P);
        break;
    case 5:
        cout<<"\nProgram terminated";exit(0);
        break;
    default:
        cout<<"\nSomething went wrong....Program terminated !!";
        exit(0);
    }
}

void delete_record(staff S,const char* file) {
    staff st;
    ifstream fin(file, ios::binary);
    ofstream fout("../DataFiles/temp.dat", ios::binary | ios::trunc);
    if(!fin||!fout) {
        cout << "\nSomething went wrong. Program terminated!!";
        exit(0);
    }
    while(!fin.eof()) {
        fin.read((char*)&st, sizeof(st));
        if(strcmpi(st.ret_code(), S.ret_code()))
            fout.write((char*)&st, sizeof(st));
    }
    fin.close();
    fout.close();
    remove(file);
    rename("../DataFiles/temp.dat", file);
}

void update_record(staff S, const char* file) {
    staff st;
    int l;
    fstream fin(file, ios::binary | ios::in | ios::out);
    if(!fin) {
        cout << "\nSomething went wrong. Program terminated!!";
        exit(0);
    }
    while(!fin.eof()) {
        l = fin.tellg();
        fin.read((char*)&st, sizeof(st));
        if(!strcmpi(st.ret_code(), S.ret_code())) {
            fin.seekg(l);
            fin.write((char*)&S, sizeof(S));
            break;
        }
    }
    fin.close();
}

void count_staff() {
    staff S;
    struct stat buf;
    if(stat("../DataFiles/staff.dat", &buf) == -1) {
        ofstream fout("../DataFiles/staff.dat", ios::binary | ios::app);
        if(!fout) {
            cout<<"Unable to open ";
            exit(0);
        }
        fout.close();
    }
    ifstream fin("../DataFiles/staff.dat", ios::binary);
    if(!fin) {
        cout << "Unable to open ";
        exit(0);
    }
    while(fin.read((char*)&S, sizeof(S))) {
        if(!S.fired)
            cs++;
    }
    fin.close();
}

void count_apply() {
    staff S;
    struct stat buf;
    if(stat("../DataFiles/apply.dat", &buf) == -1) {
        ofstream fout("../DataFiles/apply.dat", ios::binary | ios::app);
        if(!fout) {
            cout<<"Unable to open ";
            exit(0);
        }
        fout.close();
    }
    ifstream fin("../DataFiles/apply.dat", ios::binary);
    if(!fin) {
        cout << "Unable to open";
        exit(0);
    }
    fin.seekg(0, ios::end);
    ca = fin.tellg() / sizeof(S);
    fin.close();
}

void count_complaint() {
    staff S;
    struct stat buf;
    if(stat("../DataFiles/complaint.dat", &buf) == -1) {
        ofstream fout("../DataFiles/complaint.dat", ios::binary | ios::app);
        if(!fout) {
            cout<<"Unable to open ";
            exit(0);
        }
        fout.close();
    }
    ifstream fin("../DataFiles/complaint.dat", ios::binary);
    if(!fin) {
        cout << "Unable to open";
        exit(0);
    }
    fin.seekg(0, ios::end);
    cc = fin.tellg() / sizeof(S);
    fin.close();
}

