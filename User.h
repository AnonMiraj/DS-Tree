#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "Queue.h"
using std::string ;
using std::cout ;

class User {
private:
    string name;
    string phone;
    string handel;
    int age;
    Queue<string>activites; 
    int hashString(string str, int n); // This will Take 2 parameter str --> Handel Name and n --> Table Size 

public:
    User(const string& name, const string& phone,const string & handel, int age);
		User():name("UNKOWN"),phone("UNKOWN"),handel(""),age(0){}
    void displayInfo() const;
    int getHash(string str, int n);
    string getHandel()const;

};

#endif // USER_H
