#pragma once

#include <string>

using namespace std;

class Client
{
private:
    static int nextId;

    bool isActive;
    int clientId;
    string name;
    int contact;
    string address;
public:
    // Constructors
    Client();
    Client(const string& name, int contact,const string& address, bool active);

    // Getters
    int getClientId() const;
    const string& getName() const;
    int getContact() const;
    const string& getAddress() const;
    bool getActivity() const;

    // Static methods
    static int getNextId();
    static void incrementId();
    static void setNextId(int id);

    // Setters
    void setId(int id);
    void setName(const string &name);
    void setContact(int contact);
    void setAddress(const string &address);
    void setActivity(bool activity);


    // Kill Switch
    void switchActive();

    // String methods
    string toString() const;
    void fromString(const string &line);
};
