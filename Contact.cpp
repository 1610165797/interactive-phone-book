#include "Contact.h"
#include <algorithm>


Email::Email(string type, string email_addr){
    // Already done
    this->type = type;
    this->email_addr = email_addr;
}

void Email::set_contact(){
    // Already done! 
    // We don't need to validate the entered email address.  
	cout << "Enter the type of email address: ";
	getline(cin,this->type);
    cout << "Enter email address: ";
    getline(cin,this->email_addr);
}

string Email::get_contact(bool add){
    // TODO
    // return example: "(Personal) username@gmail.com" 
    string x="";
    if(add==true)
    {
        x="Email: ";
    }
    else
    {
        x="";
    }
    return x+"("+this->type+") "+this->email_addr;
}


void Email::print(){
    // TODO
    // Hint: use get_contact
    cout<<get_contact()<<endl;
}


Phone::Phone(string type, string num){
    // TODO
    // It is possible that the phone number is given with (292-431-9876) or without (2924319876) dashes. 
    // We are sure that all phone numbers have 10 digits. 
    this->type=type;
    if(num.size()==10)
    {
        num=num.substr(0,3)+"-"+num.substr(3,3)+"-"+num.substr(6,4);
    }
    this->num=num;
}


void Phone::set_contact(){
    // TODO
    
    // Use these prompts:    
	cout <<"Enter the type of phone number: ";
	getline(cin,this->type);
	cout << "Enter the phone number: ";
	string temp;
	getline(cin,temp);
	if(temp.size()==10)    
    {
        temp=temp.substr(0,3)+"-"+temp.substr(3,3)+"-"+temp.substr(6,4);
    }
    this->num=temp;
}


string Phone::get_contact(bool add){
    // TODO
    // return example "(Cell) 213-876-0023"
    string x="";
    if(add==true)
    {
        x="Phone: ";
    }
    else
    {
        x="";
    }
    return x+"("+this->type+") "+this->num;
}


void Phone::print(){
    // TODO 
    // Hint: use get_contact
    cout<<get_contact()<<endl;
}

SNAccount::SNAccount(string type,string value)
{
	this->type=type;
	this->value=value;
}

string SNAccount::get_contact(bool add)
{
    string x="";
    if(add==true)
    {
        x="SocialNetwork: ";
    }
    else
    {
        x="";
    }
	return x+"("+this->type+") "+this->value;
}

void SNAccount::print()
{
	cout<<get_contact()<<endl;
}

void SNAccount::set_contact()
{
	cout<<"Enter the type of Social Network Account: ";
	getline(cin,this->type);
	cout<<"Enter the value of Social Network Account: ";
	getline(cin,this->value);
}