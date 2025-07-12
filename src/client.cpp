#include "../include/client.h"

#include <sstream>
#include <iomanip>

// Static Member Initialization
int Client::nextId = 1;

// Default Constructor for Client
Client::Client() : clientId(0), name(""), contact(0), address("") {}

// Construct a Client object with a given name, contact and address
Client::Client(const string &name, int contact, const string &address, bool isActive)
{
    this->clientId = nextId;
    this->name = name;
    this->contact = contact;
    this->address = address;
    this->isActive = true;
}

// Getters
int Client::getClientId() const { return clientId; }
const string &Client::getName() const { return name; }
int Client::getContact() const { return contact; }
const string &Client::getAddress() const { return address; }
bool Client::getActivity() const { return isActive; }

// Setters
void Client::setId(int id) { this->clientId = id; }
void Client::setName(const string &name) { this->name = name; }
void Client::setContact(int contact) { this->contact = contact; }
void Client::setAddress(const string &address) { this->address = address; }
void Client::setActivity(bool activity) { this->isActive = activity; }

// Kill Switch
void Client::switchActive()
{
    isActive = !isActive;
}

// Static methods
int Client::getNextId() { return nextId; }
void Client::incrementId() { ++nextId; }
void Client::setNextId(int Id) { nextId = Id; }

// String methods

// Returns a string representation of the Client object in CSV format.
string Client::toString() const
{
    return to_string(clientId) + ',' + name + ',' + to_string(contact) + ',' + address + ',' + to_string(isActive);
}

// Returns a string representation of the Client object in a table-friendly format
string Client::toDisplay() const
{
    stringstream ss;

    ss << setw(2) << right << clientId << " | "
       << setw(18) << left << name << " | "
       << setw(35) << left << address << " | "
       << setw(12) << left << contact << " | "
       << setw(8) << left << (getActivity() ? "Active" : "Inactive");

    return ss.str();
}

// Parses a comma-separated string to initialize Client attributes: clientId,
// name, contact, and address.
void Client::fromString(const string &line)
{
    stringstream ss(line);
    string field;

    getline(ss, field, ',');
    setId(stoi(field));
    getline(ss, field, ',');
    setName(field);
    getline(ss, field, ',');
    setContact(stoi(field));
    getline(ss, field, ',');
    setAddress(field);
    getline(ss, field);
    setActivity(stoi(field));
}