#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#include <string>
#include <unordered_map>
#include <optional>

// Struct to represent a contact
struct Contact {
    std::string first_name;   // First name of the contact
    std::string last_name;    // Last name of the contact
    std::string phone_number; // Phone number
    std::string email;        // Email (used as unique key)
    std::string address;      // Physical address
};

// Class to manage the address book
class AddressBook {
public:
    // Adds a new contact or updates an existing one
    void addContact(const Contact& contact);

    // Returns all contacts as an unordered map
    std::unordered_map<std::string, Contact> viewContacts() const;

    // Searches for a contact by email
    std::optional<Contact> searchContact(const std::string& email) const;

    // Edits an existing contact by email
    bool editContact(const std::string& email, const Contact& updatedContact);

    // Deletes a contact by email
    bool deleteContact(const std::string& email);

    // Saves contacts to a file
    bool saveToFile(const std::string& filename) const;

    // Loads contacts from a file
    bool loadFromFile(const std::string& filename);

private:
    // Hash map to store contacts, using email as the key
    std::unordered_map<std::string, Contact> contacts;
};

#endif // ADDRESS_BOOK_H
