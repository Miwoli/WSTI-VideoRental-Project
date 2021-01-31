#include "Validation.hpp"

bool Validation::isMovieRent(Movie movie) {
    return !movie.getAvailable();
}

bool Validation::isLoginUsed(std::string login) {
    if (DB::getDB().getUser(login)) return true;
    return false;
}

bool Validation::isMovieNameUsed(std::string name) {
    std::vector<Movie> movies = DB::getDB().selectMovies();
    auto it = std::find_if(movies.begin(), movies.end(), [&name](Movie obj) { return obj.getName() == name; });

    if (it == movies.end()) return false;
    return true;
}

bool Validation::isDecimallBetween(double value, double lowerRange, double upperRange) {
    if ((lowerRange <= value) && (value <= upperRange)) return true;
    return false;
}
