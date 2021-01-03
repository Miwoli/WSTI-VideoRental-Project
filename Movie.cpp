#include "Movie.hpp"

Movie::Movie(
    int newId,
    std::string newName,
    std::string newGenre,
    std::string newDirector,
    int newLength,
    std::string newDescription,
    float newRating,
    std::vector<std::string> newCast,
    std::string addDate,
    bool newAvailable
) {
    setId(newId);
    setName(newName);
    setGenre(newGenre);
    setDirector(newDirector);
    setLength(newLength);
    setDescription(newDescription);
    setRating(newRating);
    setCast(newCast);
    setAddDate(addDate);
    setAvailable(newAvailable);
}

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
std::string Movie::getGenre() {
    return genre;
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

std::string Movie::getAddDate() {
    return addDate;
}

bool Movie::getAvailable() {
    return available;
}

Movie Movie::vectorOfStringsToModel(std::vector<std::string> data) {
    return Movie(
        std::stoi(data[0]),         // ID
        data[1],                    // Name
        data[2],                    // Genre
        data[3],                    // Director
        std::stoi(data[4]),         // Length
        data[5],                    // Description
        std::stof(data[6]),         // Rating
        Utils::split(data[7], ","), // Cast
        data[8],                    // Date
        Utils::strToBool(data[9])   // Available
    );
}

std::string Movie::modelToString() {
    return std::to_string(getId()) + ';'
        + getName() + ';'
        + getGenre() + ';'
        + getDirector() + ';'
        + std::to_string(getLength()) + ';'
        + getDescription() + ';'
        + std::to_string(getRating()) + ';'
        + Utils::implode(getCast(), ',') + ';'
        + getAddDate() + ';'
        + Utils::boolToStr(getAvailable());
}

void Movie::setId(int newId) {
    id = newId;
}

void Movie::setName(std::string newName) {
    name = newName;
}

void Movie::setGenre(std::string newGenre) {
    genre = newGenre;
}

void Movie::setDirector(std::string newDirector) {
    director = newDirector;
}

void Movie::setLength(int newLength) {
    length = newLength;
}

void Movie::setDescription(std::string newDescription) {
    description = newDescription;
}

void Movie::setRating(float newRating) {
    rating = newRating;
}

void Movie::setCast(std::vector<std::string> newCast) {
    cast = newCast;
}

void Movie::setAddDate(std::string newAddDate) {
    addDate = newAddDate;
}

void Movie::setAvailable(bool newAvailable) {
    available = newAvailable;
}