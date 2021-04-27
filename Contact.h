
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;


class ContactInfo{
protected: //TODO: should type be private or protected?	Think about it.
	string type;
public:
	virtual void print() = 0;
    virtual string get_contact(bool add=false) = 0;
	virtual void set_contact() = 0;
};


// Complete the Email declaraction from scratch here 

// Complete the phone declaration from scratch
class Email:public ContactInfo{
private:
	string email_addr;
	string get_contact(bool add=false);
public:
	Email();
	Email(string type, string email_addr);
	void print();
	void set_contact();
};

class Phone:public ContactInfo{
private:
	string num;
	string get_contact(bool add=false);
public:
	Phone();
	Phone(string type, string num);
	void print();
	void set_contact();
};

class SNAccount:public ContactInfo{
private:
	string value;
	string get_contact(bool add=false);
public:
	SNAccount();
	SNAccount(string type,string value);
	void print();
	void set_contact();
};

#endif
