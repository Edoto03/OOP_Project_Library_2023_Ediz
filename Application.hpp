#pragma once

#include "Commands.hpp"

/**
 * @brief The Application class represents the main application that processes user commands.
 */
class Application
{
private:
    Commands app; /**< The Commands object used for executing user commands. */

    Application(){}; /**< Private constructor to enforce singleton pattern. */

public:
    /**
     * @brief Deleted copy constructor to prevent copying of Application objects.
     */
    Application(const Application &other) = delete;

    /**
     * @brief Deleted assignment operator to prevent copying of Application objects.
     */
    Application &operator=(const Application &other) = delete;

    /**
     * @brief Returns the instance of the Application class.
     *
     * @return The Application instance.
     */
    static Application &getInstance();

    /**
     * @brief Processes the user input and executes corresponding commands.
     */
    void process();
};
