// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DB.hpp"
#include "Movie.hpp"
#include "Show.hpp"

int main() {

    Movie newMovie (
        4,
        "TestName",
        "Action",
        "Lorem Ipsum",
        75,
        "Lorem ipsum dolor sit amet",
        4.6,
        std::vector<std::string>{
            std::string("George Clooney"),
            std::string("Brad Pitt"),
            std::string("Angelina Jolie")},
        "20-05-2015",
        false
        );
    DB::getDB().createMovie(newMovie);
    Show::mainMenu();

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
