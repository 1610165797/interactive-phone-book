
#include <iostream>
#include "Person.h"

int main(){

    Person p1;
    p1.print_person();
    p1.remove_contact();
    cout << "------ done with p1 ----------\n";
    

    Person p2("Alexander Junior", "Montgomery Ford", "0/1/2000");
    p2.print_person();
    cout << "------ done with p2 ----------\n";
  
    Person p3("Trojan", "USC", "10/06/1880");
    Person p4("Trojan", "USC", "10/06/1880");
    Person p5("Trojan", "USC", "10/06/2021");
    cout << (p3==p4) << " " << (p3!=p4) << endl;
    cout << (p5==p4) << " " << (p5!=p4) << endl;
    cout << "------ done with checking equality operator ------\n";

    return 0;
}
