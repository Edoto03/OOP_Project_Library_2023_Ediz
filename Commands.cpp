#include "Commands.hpp"

void Commands::toLowercase(string &str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] - 'A' + 'a';
    }
}

void Commands::open(const string &openFile)
{
    if (this->isFileOpen)
    {
        cout << "A file is already opened" << std ::endl;
        return;
    }

    else
    {
        std ::ifstream in(openFile);
        if (!in.is_open())
        {
            cout << "Problem with opening the file!" << std ::endl;
            return;
        }

        this->isFileOpen = true;
        this->libraryFile = openFile;

        // Get the current position
        size_t currentPosition = in.tellg();

        // Move to the end of the file
        in.seekg(0, std::ios::end);

        // Get the end position
        size_t endPosition = in.tellg();

        // Check if the file is empty
        bool isEmpty = (currentPosition == endPosition);

        if (!isEmpty)
        {
            string line;

            string author;
            string title;
            string genre;
            string description;
            unsigned year;
            vector<string> tags;
            double rating;
            unsigned ID;

            in.clear();                 // Clear any error flags
            in.seekg(0, std::ios::beg); // Move to the beginning of the file
            while (!in.eof())
            {
                std::getline(in, line);
                std::istringstream iss(line); // Create an input string stream for each line
                std::string tagsString;
                tags.clear();

                // Extract book information from the line
                if (std::getline(iss, author, '|') &&
                    std::getline(iss, title, '|') &&
                    std::getline(iss, genre, '|') &&
                    std::getline(iss, description, '|') &&
                    (iss >> year) &&
                    (iss.ignore(1, '|')) && // Ignore the delimiter '|' after year
                    std::getline(iss, tagsString, '|') &&
                    (iss >> rating) &&
                    (iss.ignore(1, '|')) && // Ignore the delimiter '|' after rating
                    (iss >> ID))
                {
                    // Parse the tagsString to populate the tags vector
                    std::istringstream tagsStream(tagsString);
                    string tag;
                    while (std::getline(tagsStream, tag, ','))
                    {
                        tags.push_back(tag);
                    }

                    Book *book = nullptr;
                    try
                    {
                        book = this->ba.allocate(author, title, genre, description, year, tags, rating, ID);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        cout << e.what() << std ::endl;
                        book = nullptr;
                    }
                    this->lib.addBook(*book);
                }
            }
            in.close();
            cout << "Successfully read books from file." << std ::endl;
            return;
        }
        in.close();

        if (isEmpty)
        {
            cout << "The file you opened is empty, do you want to autogenerate books in it?" << std ::endl;
            cout << "Eneter 1 if the answer is YES, or 0 if the aswer is NO: ";
            int answer;
            cin >> answer;
            cin.ignore();
            if (answer == 1)
            {
                Book *book1 = this->ba.allocate("Suzanne Collins", "The Hunger Games", "Fiction", "Dystopian", 2008, {"suffering", "games", "battle"}, 10, 21);
                Book *book2 = this->ba.allocate("J. K. Rowling", "Harry Potter and the Philosopher's Stone", "Fiction", "Magic", 1997, {"magic", "secrets", "adventures"}, 6.7, 9);
                Book *book3 = this->ba.allocate("Jay Asher", "13 Reasons Why", "Young adult novel", "School abuse", 2017, {"suicide", "drama", "secrets"}, 8.6, 43);
                Book *book4 = this->ba.allocate("Miguel de Cervantes", "Don Quixote", "Novel", "Adventures", 1605, {"adventures", "horse"}, 4.3, 18);
                Book *book5 = this->ba.allocate("James Dashner", "The Maze Runner", "Fiction", "Dystopian", 2009, {"maze", "battle", "survival"}, 9.5, 108);

                this->lib.addBook(*book1);
                this->lib.addBook(*book2);
                this->lib.addBook(*book3);
                this->lib.addBook(*book4);
                this->lib.addBook(*book5);

                std::ofstream out(this->libraryFile);
                if (!out.is_open())
                {
                    cout << "Problem with opening the file!" << std ::endl;
                    return;
                }

                this->lib.printLibraryInFile(out);
                out.close();

                cout << "5 books were autogenerated." << std ::endl;
            }
        }
    }
}

void Commands::help()
{
    cout << std::endl;
    cout << "The following commands are supported: " << std::endl;
    cout << ">open <filename> - opens file, contatining information about library's books." << std::endl;
    cout << ">close - closes the currently opened file." << std::endl;
    cout << ">save - saves the changes made in the file opened." << std::endl;
    cout << ">saveas <filename> - saves the changes made in the file given." << std::endl;
    cout << ">help - shows available commands and what they do." << std ::endl;
    cout << ">exit - exits the system. " << std::endl;
    cout << std::endl;
    cout << ">login <username> <password> - logs user into the system, if username and password are valid." << std::endl;
    cout << ">logout - logs out the currently logged in user." << std::endl;
    cout << ">books_all - shows brief information, about all books, currently loaded." << std::endl;
    cout << ">books_info <isbn_value> -  shows detailed info about book with id <isbn_value>." << std::endl;
    cout << ">books_find <option> <option_string> - filters all books in system, by option and value given." << std::endl;
    cout << ">books_sort <option> [asc | desc] - sorts all books by <option> which could be {title, author, year or rating}." << std::endl;
    cout << ">books_add - adds a new book to the library." << std ::endl;
    cout << ">books_remove <title> - removes a book from the library." << std ::endl;
    cout << ">user_add <user> <password> - adds new user to the system. " << std::endl;
    cout << ">user_remove <user> - removes user from the system." << std::endl;
}

void Commands::commands(const string &command)
{
    string generalCommand;
    std::istringstream iss(command);
    iss >> generalCommand;

    this->toLowercase(generalCommand);

    if (generalCommand == "open")
    {
        string openfileName;
        iss >> openfileName;
        this->open(openfileName);
    }

    else if (generalCommand == "close")
    {
        if (!this->isFileOpen)
        {
            cout << "There is no open file to close." << std ::endl;
            return;
        }

        this->isFileOpen = false;
        cout << "Successfully closed " << this->libraryFile << std ::endl;
        this->libraryFile = "";
        return;
    }

    else if (generalCommand == "save")
    {
        if (!this->isFileOpen)
        {
            cout << "There is no file given to save to" << std ::endl;
            return;
        }

        std::ofstream out(this->libraryFile);
        if (!out.is_open())
        {
            cout << "Problem with opening the file!" << std ::endl;
            return;
        }
        this->lib.printLibraryInFile(out);
        cout << "Successfully saved to " << this->libraryFile << std ::endl;
        out.close();
    }

    else if (generalCommand == "saveas")
    {
        string newFileName;
        iss >> newFileName;

        std::ofstream outNew(newFileName);
        if (!outNew.is_open())
        {
            cout << "Problem with opening the file!" << std ::endl;
            return;
        }
        this->lib.printLibraryInFile(outNew);
        outNew.close();

        cout << "Library successfully saved in " << newFileName << std ::endl;
    }

    else if (generalCommand == "help")
    {
        this->help();
    }

    else if (generalCommand == "exit")
    {
        cout << "Exiting the program..." << std::endl;
    }

    else if (generalCommand == "login")
    {
        cout << "Username: ";
        string username;
        cin >> username;

        cout << "Password: ";
        string password;
        cin >> password;
        cin.ignore();

        std::ifstream in(this->userFile);
        if (!in.is_open())
        {
            cout << "Problem with opening thee file that stores the users!" << std ::endl;
            return;
        }

        string line;
        vector<string> fileContent;
        while (std::getline(in, line))
        {
            fileContent.push_back(line);
        }

        in.close();

        std::ofstream out(this->userFile, std::ios::app);
        if (!out.is_open())
        {
            cout << "Problem with opening the file that stores the users!" << std ::endl;
            return;
        }

        for (size_t i = 0; i < fileContent.size(); i++)
        {
            string usernameInThisLine, passwordInThisLine, isAdminInThisLine;
            std::istringstream in(fileContent[i]);
            in >> usernameInThisLine >> passwordInThisLine >> isAdminInThisLine;

            if (usernameInThisLine == username && passwordInThisLine == password)
            {
                if (!this->isUserLogged)
                {
                    cout << "Welcome, <" << username << ">!" << std ::endl;
                    this->isUserLogged = true;

                    try
                    {
                        this->userNow.setUsername(username);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        cout << e.what() << std::endl;
                    }

                    try
                    {
                        this->userNow.setPassword(password);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        cout << e.what() << std::endl;
                    }

                    if (isAdminInThisLine == "admin")
                        this->userNow.setIsAdmin(true);
                    else
                        this->userNow.setIsAdmin(false);
                }

                else
                {
                    cout << "You are already logged in." << std ::endl;
                }
                return;
            }
        }

        cout << "Incorrect username or password, try again." << std ::endl;

        out.close();
    }

    else if (generalCommand == "logout")
    {
        if (this->isUserLogged)
        {
            this->isUserLogged = false;
            return;
        }

        cout << "There is no user logged in." << std ::endl;
    }

    else if (generalCommand == "books_all")
    {
        if (this->isUserLogged)
        {
            this->lib.booksAll();
        }

        else
            cout << "There is no user logged in so you can't do this command." << std ::endl;
    }

    else if (generalCommand == "books_info")
    {
        if (this->isUserLogged)
        {
            string isbn;
            iss >> isbn;

            int id = std::stoul(isbn);
            this->lib.booksInfo(id);
        }

        else
            cout << "There is no user logged in so you can't do this command." << std ::endl;
    }

    else if (generalCommand == "books_find")
    {
        if (this->isUserLogged)
        {
            string option, optionOfTheOption;
            iss >> option;

            cout << "Enther the " << option << " you are looking for: ";
            std::getline(cin, optionOfTheOption);

            this->lib.bookFind(option, optionOfTheOption);
        }

        else
            cout << "There is no user logged in so you can't do this command." << std ::endl;
    }

    else if (generalCommand == "books_sort")
    {
        if (this->isUserLogged)
        {
            string word;
            vector<string> words;
            while (iss >> word)
            {
                words.push_back(word);
            }

            if (words.size() == 1)
            {
                this->lib.sort(words[0], true);
            }
            else
            {
                if (words[1] == "asc")
                    this->lib.sort(words[0], true);
                else if (words[1] == "desc")
                    this->lib.sort(words[0], false);
                else
                    cout << "Comмand invalid." << std ::endl;
            }
        }
        else
            cout << "There is no user logged in so you can't do this command." << std ::endl;
    }

    else if (generalCommand == "books_add")
    {
        if (!this->isUserLogged && !this->userNow.getIsAdmin())
        {
            cout << "There is no user logged or the user logged is not an admin so you can't do this command." << std ::endl;
            return;
        }

        string author;
        string title;
        string genre;
        string description;
        unsigned year;
        string inputTags;
        string tag;
        vector<string> tags;
        double rating;
        unsigned ID;

        cout << "Author: ";
        cin >> author;

        cout << "Title: ";
        cin >> title;

        cout << "Genre: ";
        cin >> genre;

        cout << "Description: ";
        cin >> description;

        cout << "Year: ";
        cin >> year;

        cout << "Tags: ";
        cin.ignore();
        std::getline(cin, inputTags);
        std::istringstream inTags(inputTags);
        while (inTags >> tag)
        {
            tags.push_back(tag);
        }

        cout << "Rating: ";
        cin >> rating;

        cout << "ID: ";
        cin >> ID;

        cin.ignore();

        Book *book = nullptr;
        try
        {
            book = this->ba.allocate(author, title, genre, description, year, tags, rating, ID);
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << std ::endl;
            book = nullptr;
        }
        this->lib.addBook(*book);

        cout << "New book successfully added." << std ::endl;
    }

    else if (generalCommand == "books_remove")
    {
        if (this->isUserLogged && this->userNow.getIsAdmin())
        {
            string removeTitle;
            std::getline(iss, removeTitle);
            removeTitle.erase(0, 1);
            lib.removeBook(removeTitle);
        }

        else
            cout << "There is no user logged or the user logged is not an admin so you can't do this command." << std ::endl;
    }

    else if (generalCommand == "user_add")
    {
        if (!this->isUserLogged && !this->userNow.getIsAdmin())
        {
            cout << "There is no user logged or the user logged is not an admin so you can't do this command." << std ::endl;
            return;
        }
        string username, pass;
        iss >> username >> pass;

        User userAdd(username, pass, false);
        try
        {
            User userAdd(username, pass, false);
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << std::endl;
        }

        std::ofstream out(this->userFile, std::ios::app);
        if (!out.is_open())
        {
            cout << "Problem with opening the file that stores the users!" << std ::endl;
            return;
        }

        else
            userAdd.printUserInFile(out);

        out.close();

        cout << "User <" << username << "> successfully added." << std ::endl;
    }

    else if (generalCommand == "user_remove")
    {
        if (!this->isUserLogged && !this->userNow.getIsAdmin())
        {
            cout << "There is no user logged or the user logged is not an admin so you can't do this command." << std ::endl;
            return;
        }

        string removeUsername;
        iss >> removeUsername;

        std::ifstream in(this->userFile);
        if (!in.is_open())
        {
            cout << "Problem with opening the file that stores the users!" << std ::endl;
            return;
        }

        string line;
        vector<string> fileContent;
        while (std::getline(in, line))
        {
            fileContent.push_back(line);
        }

        in.close();

        std::ofstream out(this->userFile);
        if (!out.is_open())
        {
            cout << "Problem with opening the file that stores the users!" << std ::endl;
            return;
        }

        for (size_t i = 0; i < fileContent.size(); i++)
        {
            string usernameInThisLine;
            std::istringstream in(fileContent[i]);
            in >> usernameInThisLine;

            if (usernameInThisLine != removeUsername)
            {
                out << fileContent[i] << std ::endl;
            }
        }

        out.close();

        cout << "User <" << removeUsername << "> successfully removed." << std ::endl;
    }

    else
        cout << "This command isn't supported." << std ::endl;
}

void Commands::setUsersFile(const string &userFile)
{
    this->userFile = userFile;
    std::ofstream out(this->userFile);
    if (!out.is_open())
    {
        cout << "Problem with setting the file" << std::endl;
        return;
    }

    out << "admin i<3c++ admin" << std ::endl;
    out.close();
}