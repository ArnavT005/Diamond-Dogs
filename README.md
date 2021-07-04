# Diamond Dogs

## High School CS Project
---

### Instructions to execute program:

- Change to *Code* directory.
- Run the command `g++ main.cpp personnel.cpp staff.cpp -o main` in the terminal.
- Execute the executable using `./main` or `./main.exe`.

---

### Administrative Privileges:

Admin data is stored in *personnel.dat* file, present in DataFiles folder. There can be only **two** admins at any point of time. By default they are:
 - **Snake**, Tag-line ("Diamonds are forever")
 - **Kazuhira Miller**, Tag-line ("Diamonds are hard")    

It is possible to override the tag-lines and it can be done by deleting the *personnel.dat* file and re-running the program. Changing names however, is not recommended.

---

### Database:

The entire data of the organization is stored in four binary files. These are:
- personnel.dat
- staff.dat
- complaint.dat
- apply.dat

The names are suggestive of the data that they store. Also, person's **Code Name** is used as the *key* in the database.

---
---
