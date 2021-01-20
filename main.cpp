// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DB.hpp"
#include "Movie.hpp"
#include "Show.hpp"
#include "Utils.hpp"
#include "Auth.hpp"

int main() {

    //Show::addMovie();
    Show::mainMenu();

    /*
    User user1 = User(
        2,
        "user1",
        "User",
        "Userson",
        "123456789",
        "Lorem ipsum street",
        Utils::nowAsString(),
        true
    );

    User user2 = User(
        3,
        "user2",
        "User",
        "Userson",
        "123456789",
        "Lorem ipsum street",
        Utils::nowAsString(),
        false
    );

    User user3 = User(
        4,
        "user1",
        "User",
        "Userson",
        "123456789",
        "Lorem ipsum street",
        Utils::nowAsString(),
        false
    );

    Auth::registerUser(user1, "12345");
    Auth::registerUser(user2, "12345");
    Auth::registerUser(user3, "12345");

    Auth::logout();

    if (Auth::getLoggedUser()) {
        std::cout << Auth::getLoggedUser().value().getFirstName() << std::endl;
    } else {
        std::cout << "No logged user" << std::endl;
    }
    */

    std::cout << "Press any key to exit...";
    std::getchar();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
