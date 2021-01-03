#pragma once
#include <string>
#include <vector>
#include "Utils.hpp"

enum class MovieParams {
	ID,
	NAME,
	GENRE,
	LENGTH,
	DESCRIPTION,
	RATING,
	CAST,
	ADDDATE,
	AVAILABLE
};

class Movie {
	int id;
	std::string name;
	std::string genre;
	std::string director;
	int length;
	std::string description;
	float rating;
	std::vector<std::string> cast;
	std::string addDate;
	bool available;

public:
	Movie(
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
	);
	void setName(std::string newName);
	void setGenre(std::string newGenre);
	void setDirector(std::string newDirector);
	void setLength(int newLength);
	void setDescription(std::string newDescription);
	void setRating(float newRating);
	void setCast(std::vector<std::string> newCast);
	void setAddDate(std::string newAddDate);
	void setAvailable(bool newAvailable);
	void setId(int newId);
	int getId();
	std::string getName();
	std::string getDirector();
	int getLength();
	std::string getGenre();
	std::string getDescription();
	float getRating();
	std::vector<std::string> getCast();
	std::string getAddDate();
	bool getAvailable();
	Movie static vectorOfStringsToModel(std::vector<std::string>);
	std::string modelToString();
};
