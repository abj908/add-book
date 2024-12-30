#include <gtest/gtest.h>
#include "../include/address_book.h"

// Test adding a contact
TEST(AddressBookTest, AddContact) {
    AddressBook addressBook;

    // Create a contact
    Contact contact = {"John", "Doe", "123-456-7890", "john.doe@example.com", "123 Elm Street"};

    // Add the contact
    addressBook.addContact(contact);

    // Verify the contact exists
    auto result = addressBook.searchContact(contact.email);
    ASSERT_TRUE(result.has_value()); // Contact should be found
    EXPECT_EQ(result->first_name, "John");
    EXPECT_EQ(result->last_name, "Doe");
    EXPECT_EQ(result->phone_number, "123-456-7890");
    EXPECT_EQ(result->email, "john.doe@example.com");
    EXPECT_EQ(result->address, "123 Elm Street");
}

// Test viewing contacts
TEST(AddressBookTest, ViewContacts) {
    AddressBook addressBook;

    // Add two contacts
    Contact contact1 = {"John", "Doe", "123-456-7890", "john.doe@example.com", "123 Elm Street"};
    Contact contact2 = {"Jane", "Doe", "987-654-3210", "jane.doe@example.com", "456 Oak Avenue"};

    addressBook.addContact(contact1);
    addressBook.addContact(contact2);

    // Verify all contacts are returned
    auto contacts = addressBook.viewContacts();
    EXPECT_EQ(contacts.size(), 2);
    EXPECT_EQ(contacts["john.doe@example.com"].first_name, "John");
    EXPECT_EQ(contacts["jane.doe@example.com"].first_name, "Jane");
}

// Test searching for a contact
TEST(AddressBookTest, SearchContact) {
    AddressBook addressBook;

    // Add a contact
    Contact contact = {"John", "Doe", "123-456-7890", "john.doe@example.com", "123 Elm Street"};
    addressBook.addContact(contact);

    // Search for the contact
    auto result = addressBook.searchContact(contact.email);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->first_name, "John");

    // Search for a non-existent contact
    auto missingResult = addressBook.searchContact("notfound@example.com");
    EXPECT_FALSE(missingResult.has_value());
}

// Test editing a contact
TEST(AddressBookTest, EditContact) {
    AddressBook addressBook;

    // Add a contact
    Contact contact = {"John", "Doe", "123-456-7890", "john.doe@example.com", "123 Elm Street"};
    addressBook.addContact(contact);

    // Edit the contact
    Contact updatedContact = {"John", "Smith", "111-222-3333", "john.doe@example.com", "789 Pine Road"};
    bool isEdited = addressBook.editContact(contact.email, updatedContact);

    // Verify the contact was updated
    ASSERT_TRUE(isEdited);
    auto result = addressBook.searchContact(contact.email);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->last_name, "Smith");
    EXPECT_EQ(result->phone_number, "111-222-3333");
    EXPECT_EQ(result->address, "789 Pine Road");
}

// Test deleting a contact
TEST(AddressBookTest, DeleteContact) {
    AddressBook addressBook;

    // Add a contact
    Contact contact = {"John", "Doe", "123-456-7890", "john.doe@example.com", "123 Elm Street"};
    addressBook.addContact(contact);

    // Delete the contact
    bool isDeleted = addressBook.deleteContact(contact.email);
    ASSERT_TRUE(isDeleted);

    // Verify the contact is no longer in the address book
    auto result = addressBook.searchContact(contact.email);
    EXPECT_FALSE(result.has_value());
}

// Test saving and loading from file
TEST(AddressBookTest, SaveAndLoad) {
    AddressBook addressBook;

    // Add a contact
    Contact contact = {"John", "Doe", "123-456-7890", "john.doe@example.com", "123 Elm Street"};
    addressBook.addContact(contact);

    // Save to file
    std::string filename = "test_contacts.txt";
    EXPECT_TRUE(addressBook.saveToFile(filename));

    // Create a new AddressBook object and load from file
    AddressBook loadedAddressBook;
    EXPECT_TRUE(loadedAddressBook.loadFromFile(filename));

    // Verify the loaded contact
    auto result = loadedAddressBook.searchContact(contact.email);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->first_name, "John");
}
