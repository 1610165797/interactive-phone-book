
#ifndef NETWORK_H
#define NETWORK_H

#include "Person.h"
#include "Date.h"
#include <stdlib.h>

class Network{

    private:
        Person* head;
        Person* tail;
        int count; 
        Person* search(Person* searchEntry); 
        Person* search(string fname, string lname, string bd);
        map <string,int> ad;
        string fileName; 
    public:
        Network();
        Network(string fileName);
        ~Network();
        void push_front(Person* newEntry);
        void push_back(Person* newEntry);
        bool remove(string fname, string lname, string bd);
        void saveDB(string filename);
        void loadDB(string filename);
        void printDB();
        void showMenu();
        vector<Person*> search(string fname, string lname);
        void loadAD(string filename);
        void printAD(string filename);
};

#endif
