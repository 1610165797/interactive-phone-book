
#ifndef PERSON_H
#define PERSON_H

#include "Date.h"
#include "Contact.h"
#include "misc.h"
#include "fstream"
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
class Person{
    friend class Network;
private:
    float p;
    float receive;
    vector<ContactInfo*> contacts;
	string f_name;  // can have space 
	string l_name;  // can have space
	Date *birthdate;
    Person *next;
    Person *prev; 
    string filename;
    vector<string> avoid;
public: 
    Person();
    Person(string f_name, string l_name, string bdate);
    ~Person();
	void print_person(bool add=false);
	void set_person();
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
    void add_contact(bool add=false);
    void remove_contact();
    void write_to_file(ofstream& outfile);
    bool read_from_file(ifstream& infile);
    void modify();
    string get_email();
    string get_all_emails();
    void send_ad(map <string,int> ad); 
    string choose_ad(map <string,int> ad);
};


#endif
