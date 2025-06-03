#pragma once

#include <string>

using namespace std;

class Client
{
private:
    static int nextClientId;

    int clientId;
    string name;
    int contact;
    string address;
public:
    // Constructors
    Client();
    Client(string name, int contact, string address);

    // Getters
    int getClientId();
    string getName();
    int getContact();
    int getAddress();

    // Static getter
    static int getNextId();

    // Setters
    void setId(int id);
    void setName(string name);
    void setContact(int contact);
    void setAddress(string address);

    // String methods
    string toString();
    void fromString();
};