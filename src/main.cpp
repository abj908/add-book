#include "address_book.h"
#include <iostream>

// Function to print the main menu
void printMenu() {
    std::cout << "Address Book Menu:\n"
              << "1. Add Contact\n"
              << "2. View Contacts\n"
              << "3. Search Contact\n"
              << "4. Edit Contact\n"
              << "5. Delete Contact\n"
              << "6. Save to File\n"
              << "7. Load from File\n"
              << "0. Exit\n";
}

int main() {
    AddressBook addressBook; // Create an AddressBook object
    int choice;              // Variable to store user input
    do {
        printMenu(); // Display the menu
        std::cout << "Enter your choice: ";
        std::cin >> choice;  // Read user input
        std::cin.ignore();   // Clear newline character from the input buffer

        if (choice == 1) { // Add a new contact
            Contact contact;
            std::cout << "Enter First Name: ";
            std::getline(std::cin, contact.first_name);
            std::cout << "Enter Last Name: ";
            std::getline(std::cin, contact.last_name);
            std::cout << "Enter Phone Number: ";
            std::getline(std::cin, contact.phone_number);
            std::cout << "Enter Email: ";
            std::getline(std::cin, contact.email);
            std::cout << "Enter Address: ";
            std::getline(std::cin, contact.address);
            addressBook.addContact(contact);
        } else if (choice == 2) { // View all contacts
            auto contacts = addressBook.viewContacts();
            for (const auto& [email, contact] : contacts) {
                std::cout << contact.first_name << " " << contact.last_name << "\n"
                          << contact.phone_number << "\n"
                          << contact.email << "\n"
                          << contact.address << "\n\n";
            }
        } else if (choice == 3) { // Search for a contact
            std::string email;
            std::cout << "Enter email to search: ";
            std::getline(std::cin, email);
            auto result = addressBook.searchContact(email);
            if (result) {
                std::cout << result->first_name << " " << result->last_name << "\n"
                          << result->phone_number << "\n"
                          << result->email << "\n"
                          << result->address << "\n";
            } else {
                std::cout << "Contact not found.\n";
            }
        } else if (choice == 4) { // Edit an existing contact
            std::string email;
            std::cout << "Enter email of contact to edit: ";
            std::getline(std::cin, email);
            Contact updatedContact;
            std::cout << "Enter Updated First Name: ";
            std::getline(std::cin, updatedContact.first_name);
            std::cout << "Enter Updated Last Name: ";
            std::getline(std::cin, updatedContact.last_name);
            std::cout << "Enter Updated Phone Number: ";
            std::getline(std::cin, updatedContact.phone_number);
            std::cout << "Enter Updated Email: ";
            std::getline(std::cin, updatedContact.email);
            std::cout << "Enter Updated Address: ";
            std::getline(std::cin, updatedContact.address);
            if (addressBook.editContact(email, updatedContact)) {
                std::cout << "Contact updated successfully.\n";
            } else {
                std::cout << "Contact not found.\n";
            }
        } else if (choice == 5) { // Delete a contact
            std::string email;
            std::cout << "Enter email of contact to delete: ";
            std::getline(std::cin, email);
            if (addressBook.deleteContact(email)) {
                std::cout << "Contact deleted successfully.\n";
            } else {
                std::cout << "Contact not found.\n";
            }
        } else if (choice == 6) { // Save contacts to a file
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);
            if (addressBook.saveToFile(filename)) {
                std::cout << "Data saved successfully.\n";
            } else {
                std::cout << "Error saving data.\n";
            }
        } else if (choice == 7) { // Load contacts from a file
            std::string filename;
            std::cout << "Enter filename to load: ";
            std::getline(std::cin, filename);
            if (addressBook.loadFromFile(filename)) {
                std::cout << "Data loaded successfully.\n";
            } else {
                std::cout << "Error loading data.\n";
            }
        }
    } while (choice != 0); // Exit when user selects 0
    return 0;
}
