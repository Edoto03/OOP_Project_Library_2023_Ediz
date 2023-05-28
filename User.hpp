#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

using std::ofstream;
using std::string;

/**
 * @class User
 * @brief Represents a user with a username, password, and admin status.
 */
class User
{
private:
    string username; /**< The username of the user. */
    string password; /**< The password of the user. */
    bool isAdmin;    /**< Indicates whether the user is an administrator. */

public:
    /**
     * @brief Default constructor.
     *
     * The default constructor initializes a User object with empty username and password,
     * and sets the isAdmin flag to false.
     */
    User();

    /**
     * @brief Parameterized constructor.
     * @param username The username of the user.
     * @param password The password of the user.
     * @param isAdmin Indicates whether the user is an administrator.
     *
     * The parameterized constructor creates a User object with the provided username, password, and admin status.
     */
    User(const string &username, const string &password, const bool &isAdmin);

    /**
     * @brief Prints the user's information to a file.
     * @param out The output file stream.
     *
     * This function prints the user's username, password, and admin status to the specified output file stream.
     */
    void printUserInFile(ofstream &out);

    /**
     * @brief Sets the username of the user.
     * @param username The username to set.
     *
     * This function sets the username of the user.
     * If the provided username is empty, it throws an invalid_argument exception.
     */
    void setUsername(const string &username);

    /**
     * @brief Sets the password of the user.
     * @param password The password to set.
     *
     * This function sets the password of the user.
     * If the provided password is empty, it throws an invalid_argument exception.
     */
    void setPassword(const string &password);

    /**
     * @brief Sets the admin status of the user.
     * @param isAdmin Indicates whether the user is an administrator.
     *
     * This function sets the admin status of the user.
     */
    void setIsAdmin(const bool isAdmin);

    /**
     * @brief Retrieves the username of the user.
     * @return The username of the user.
     */
    string getUsername() const;

    /**
     * @brief Retrieves the password of the user.
     * @return The password of the user.
     */
    string getPassword() const;

    /**
     * @brief Retrieves the admin status of the user.
     * @return True if the user is an administrator, false otherwise.
     */
    bool getIsAdmin() const;
};