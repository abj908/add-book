#include "address_book.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Adds a new contact to the address book or updates an existing one
void AddressBook::addContact(const Contact& contact) {
    contacts[contact.email] = contact; // Insert or update the contact in the hash map
}

// Returns all contacts stored in the address book
std::unordered_map<std::string, Contact> AddressBook::viewContacts() const {
    return contacts;
}

// Searches for a contact by email
std::optional<Contact> AddressBook::searchContact(const std::string& email) const {
    auto it = contacts.find(email); // Find contact in the hash map
    if (it != contacts.end()) {
        return it->second; // Return the contact if found
    }
    return std::nullopt; // Return nullopt if not found
}

// Edits an existing contact
bool AddressBook::editContact(const std::string& email, const Contact& updatedContact) {
    auto it = contacts.find(email); // Find the contact in the hash map
    if (it != contacts.end()) {
        it->second = updatedContact; // Update the contact details
        return true;
    }
    return false; // Return false if the contact was not found
}

// Deletes a contact by email
bool AddressBook::deleteContact(const std::string& email) {
    return contacts.erase(email) > 0; // Erase contact and return true if successful
}

// Saves all contacts to a file in CSV format
bool AddressBook::saveToFile(const std::string& filename) const {
    std::ofstream file(filename); // Open the file for writing
    if (!file) return false;      // Return false if file cannot be opened
    for (const auto& [email, contact] : contacts) {
        file << contact.first_name << "," << contact.last_name << ","
             << contact.phone_number << "," << contact.email << ","
             << contact.address << "\n"; // Write each contact to the file
    }
    return true;
}

// Loads contacts from a file
bool AddressBook::loadFromFile(const std::string& filename) {
    std::ifstream file(filename); // Open the file for reading
    if (!file) return false;      // Return false if file cannot be opened
    contacts.clear();             // Clear existing contacts
    std::string line, token;
    while (std::getline(file, line)) { // Read each line from the file
        std::stringstream ss(line);
        Contact contact;
        std::getline(ss, contact.first_name, ',');
        std::getline(ss, contact.last_name, ',');
        std::getline(ss, contact.phone_number, ',');
        std::getline(ss, contact.email, ',');
        std::getline(ss, contact.address, ',');
        contacts[contact.email] = contact; // Add the contact to the hash map
    }
    return true;
}
