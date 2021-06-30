#pragma once

class staff {
    private:
        char name[20], code_name[20], gender, comp[75];
        int age, unit, skill;

    public:
        int fired, com;
        staff();
        void accept();
        void display();
        void write_comp();
        int ret_unit();
        char* ret_code();
        char* ret_comp();
        char* ret_name();
};
