#include "Movie.hpp"

int Movie::getId() {
    return id;
}

std::string Movie::getName() {
    return name;
}

std::string Movie::getDirector() {
    return director;
}

int Movie::getLength() {
    return length;
}
std::string Movie::getDescription() {
    return description;
}

float Movie::getRating() {
    return rating;
}

std::vector<std::string> Movie::getCast() {
    return cast;
}

bool Movie::getAvailable() {
    return available;
}

void Movie::setId();
void Movie::setName();
void Movie::setGenre();
void Movie::setDirector();
void Movie::setLength();
void Movie::setDescription();
void Movie::setRating();
void Movie::setCast(std::vector<std::string> newCast) {
    cast = newCast;
}

void Movie::setAvailable(bool newAvailable) {
    available = newAvailable;
}