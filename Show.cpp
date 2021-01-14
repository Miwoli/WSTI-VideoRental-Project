#include "Show.hpp"

bool Show::sortByIdAsc(Movie lhs, Movie rhs) {
		return lhs.getId() < rhs.getId();
}

bool Show::sortByIdDesc(Movie lhs, Movie rhs) {
	return lhs.getId() > rhs.getId();
}

bool Show::sortByNameAsc(Movie lhs, Movie rhs) {
	return lhs.getName() < rhs.getName();
}

bool Show::sortByNameDesc(Movie lhs, Movie rhs) {
	return lhs.getName() > rhs.getName();
}

bool Show::sortByGenreAsc(Movie lhs, Movie rhs) {
	return lhs.getGenre() < rhs.getGenre();
}

bool Show::sortByGenreDesc(Movie lhs, Movie rhs) {
	return lhs.getGenre() > rhs.getGenre();
}

bool Show::sortByLengthAsc(Movie lhs, Movie rhs) {
	return lhs.getLength() < rhs.getLength();
}

bool Show::sortByLengthDesc(Movie lhs, Movie rhs) {
	return lhs.getLength() > rhs.getLength();
}

bool Show::sortByRatingAsc(Movie lhs, Movie rhs) {
	return lhs.getRating() < rhs.getRating();
}

bool Show::sortByRatingDesc(Movie lhs, Movie rhs) {
	return lhs.getRating() > rhs.getRating();
}

bool Show::sortByAddDateAsc(Movie lhs, Movie rhs) {
	std::vector<std::string> lhsVec = Utils::split(lhs.getAddDate(), "-");
	std::vector<std::string> rhsVec = Utils::split(rhs.getAddDate(), "-");

	if (std::stoi(lhsVec[2]) != std::stoi(rhsVec[2])) return std::stoi(lhsVec[2]) < std::stoi(rhsVec[2]);
	if (std::stoi(lhsVec[1]) != std::stoi(rhsVec[1])) return std::stoi(lhsVec[1]) < std::stoi(rhsVec[1]);
	return std::stoi(lhsVec[0]) < std::stoi(rhsVec[0]);
}

bool Show::sortByAddDateDesc(Movie lhs, Movie rhs) {
	std::vector<std::string> lhsVec = Utils::split(lhs.getAddDate(), "-");
	std::vector<std::string> rhsVec = Utils::split(rhs.getAddDate(), "-");

	if (std::stoi(lhsVec[2]) != std::stoi(rhsVec[2])) return std::stoi(lhsVec[2]) > std::stoi(rhsVec[2]);
	if (std::stoi(lhsVec[1]) != std::stoi(rhsVec[1])) return std::stoi(lhsVec[1]) > std::stoi(rhsVec[1]);
	return std::stoi(lhsVec[0]) > std::stoi(rhsVec[0]);
}

bool Show::sortByAvailableAsc(Movie lhs, Movie rhs) {
	return lhs.getAvailable() < rhs.getAvailable();
}

bool Show::sortByAvailableDesc(Movie lhs, Movie rhs) {
	return lhs.getAvailable() > rhs.getAvailable();
}

void Show::mainMenu() {

	int input;

	do {
		std::cout << "----- MOVIE RENTAL MAIN MENU -----" << std::endl << std::endl
			<< "Select option:" << std::endl
			<< "1) Show all movies" << std::endl
			<< "2) Exit" << std::endl;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> input;

		switch (input) {
		case 1:
			char sortInput;

			int orderInput;
			SortOrder sortOrder;

			int paramInput;
			MovieParams sortParam;

			do {
				std::cout << "Do you want to apply sorting? [y/n]" << std::endl;
				std::cin >> sortInput;
			} while (sortInput != 'Y' && sortInput != 'y' && sortInput != 'N' && sortInput != 'n');

			if (sortInput == 'N' || sortInput == 'n') {
				allMovies();
			} else {
				bool correctInput;
				do {
					std::cout << std::endl << std::endl << "Select sort order:" << std::endl
						<< "1) Ascending" << std::endl
						<< "2) Descending" << std::endl;

					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.clear();
					std::cin >> orderInput;
					if (orderInput != 1 && orderInput != 2) {
						correctInput = false;
					} else {
						if (orderInput == 1) sortOrder = SortOrder::ASC;
						if (orderInput == 2) sortOrder = SortOrder::DESC;
						correctInput = true;
					}
				} while (!correctInput && !std::cin);

				do {
					std::cout << std::endl << std::endl << "Select sort param:" << std::endl
						<< "1) ID" << std::endl
						<< "2) Name" << std::endl
						<< "3) Genre" << std::endl
						<< "4) Length" << std::endl
						<< "5) Rating" << std::endl
						<< "6) Add Date" << std::endl
						<< "7) Availibility" << std::endl;
					
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> paramInput;
					correctInput = true;
					
					switch (paramInput) {
					case 1: 
						sortParam = MovieParams::ID;
						break;
					case 2:
						sortParam = MovieParams::NAME;
						break;
					case 3:
						sortParam = MovieParams::GENRE;
						break;
					case 4:
						sortParam = MovieParams::LENGTH;
						break;
					case 5:
						sortParam = MovieParams::RATING;
						break;
					case 6:
						sortParam = MovieParams::ADDDATE;
						break;
					case 7:
						sortParam = MovieParams::AVAILABLE;
						break;
					default:
						correctInput = false;
						break;
					}
				} while (!correctInput || !std::cin);
				allMovies(sortOrder, sortParam);
			}

			break;
		default:
			break;
		}

	} while (input != 2 || !std::cin);
}

void Show::movieDetails(int id) {
	Movie movie = DB::getDB().getMovie(id);
	std::string isAvailable = movie.getAvailable() ? "Available" : "Not available";

	std::cout << movie.getName() << std::endl << std::endl
		<< "Rate: " << movie.getRating() << " | " << movie.getLength() << "min. | " << isAvailable << std::endl << std::endl
		<< "Cast: " << Utils::implode(movie.getCast(), ", ") << std::endl << std::endl
		<< movie.getDescription() << std::endl << std::endl
		<< "Available since: " << movie.getAddDate() << std::endl << std::endl;
}

void Show::addMovie() {
	Movie movie = Movie();

	std::string text;
	int intiger;
	float decimal;

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, text);
	movie.setName(text);
	std::cout << std::endl;

	std::cout << "Genre: ";
	std::getline(std::cin >> std::ws, text);
	movie.setGenre(text);
	std::cout << std::endl;

	std::cout << "Direcotr: ";
	std::getline(std::cin >> std::ws, text);
	movie.setDirector(text);
	std::cout << std::endl;

	std::cout << "Length: ";
	std::cin >> intiger;
	movie.setLength(intiger);
	std::cout << std::endl;

	std::cout << "Description: ";
	std::getline(std::cin >> std::ws, text);
	movie.setDescription(text);
	std::cout << std::endl;

	std::cout << "Rating (1-5, decimals with .): "; // TODO: Create class validator, validate inputs
	std::cin >> decimal;
	movie.setRating(decimal);
	std::cout << std::endl;

	std::cout << "Cast (separated with comma, with no spaces around commas): " << std::endl;
	std::getline(std::cin >> std::ws, text);
	movie.setCast(Utils::split(text, ","));
	std::cout << std::endl;

	movie.setAddDate(Utils::nowAsString());
	movie.setAvailable(true);

	DB::getDB().createMovie(movie);
}

void Show::allMovies(SortOrder order, MovieParams param) {
	std::vector<Movie> movies = DB::getDB().selectMovies();

	switch (param) {
	case MovieParams::ID:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByIdDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByIdAsc);
		}
		break;
	case MovieParams::NAME:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByNameDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByNameAsc);
		}
		break;
	case MovieParams::GENRE:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByGenreDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByGenreAsc);
		}
		break;
	case MovieParams::LENGTH:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByLengthDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByLengthAsc);
		}
		break;
	case MovieParams::RATING:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByRatingDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByRatingAsc);
		}
		break;
	case MovieParams::ADDDATE:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByAddDateDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByAddDateAsc);
		}
		break;
	case MovieParams::AVAILABLE:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByAvailableDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByAvailableAsc);
		}
		break;
	default:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByIdDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByIdAsc);
		}
		break;
	}

	for (auto movie : movies) {
		std::string isAvailable = movie.getAvailable() ? "Available" : "Not available";
		std::cout << movie.getId() << ") "
			<< movie.getName() << " | "
			<< movie.getDirector() << " | "
			<< movie.getLength() << "min. | "
			<< movie.getGenre() << " | "
			<< movie.getRating() << " | "
			<< movie.getAddDate() << " | "
			<< isAvailable
			<< std::endl;
	}

	char seeDetails;
	do {
		std::cout << "Do you want to see more details [y/n]" << std::endl;
		std::cin >> seeDetails;
	} while (seeDetails != 'Y' && seeDetails != 'y' && seeDetails != 'N' && seeDetails != 'n');

	if (seeDetails == 'Y' || seeDetails == 'y') {

		int moviesAmount = movies.size();
		int movieId;

		do {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Type movie ID you wish to see details: ";
			std::cin >> movieId;

			if ((movieId > moviesAmount) || !std::cin) std::cout << "There's no movie with that ID" << std::endl;
		} while ((movieId > moviesAmount) || !std::cin);

		movieDetails(movieId);
	}
}
