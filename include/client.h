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
    Client(const string& name, int contact,const string& address);

    // Getters
    int getClientId() const;
    const string& getName() const;
    int getContact() const;
    int getAddress() const;

    // Static getter
    static int getNextId();

    // Setters
    void setId(int id);
    void setName(string &name);
    void setContact(int contact);
    void setAddress(string &address);

    // String methods
    string toString() const;
    void fromString();
};
