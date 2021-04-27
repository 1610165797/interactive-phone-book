
#ifndef MISC_H
#define MISC_H

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void printMe(string type);
bool quit(string com);
void sendEmail(string addr, string subject, string content, string attachment="");

#endif
