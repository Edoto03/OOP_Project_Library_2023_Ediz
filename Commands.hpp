#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "BookAllocator.hpp"
#include "Library.hpp"
#include "User.hpp"

using std::cin;
using std::cout;
using std::string;

/**
 * @class Commands
 * @brief Represents a set of commands and their execution for a library management system.
 */
class Commands
{
private:
    bool isFileOpen;         /**< Flag indicating whether a file is currently open */
    bool isUserLogged;       /**< Flag indicating whether a user is currently logged in */
    std::string libraryFile; /**< Path to the currently open library file */
    std::string userFile;    /**< Path to the file containing user information */
    User userNow;            /**< Currently logged-in user */
    Library lib;             /**< Library object for managing books */
    BookAllocator ba;        /**< BookAllocator object for creating Book instances */

public:
    /**
     * @brief Converts a string to lowercase.
     * @param str The string to convert.
     */
    void toLowercase(std::string &str);

    /**
     * @brief Opens a library file and loads books from it.
     * @param openFile The path to the file to open.
     */
    void open(const std::string &openFile);

    /**
     * @brief Displays the available commands and their descriptions.
     */
    void help();

    /**
     * @brief Executes the given command.
     * @param command The command to execute.
     */
    void commands(const std::string &command);

    /**
     * @brief Sets the file path for storing user data.
     * @param userFile The file path to be set.
     */
    void setUsersFile(const std::string &userFile);
};
