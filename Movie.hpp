#pragma once
#include <string>
#include <vector>

class Movie {
	int id;
	std::string name;
	std::string genre;
	std::string director;
	int length;
	std::string description;
	float rating;
	std::vector<std::string> cast;
	bool available;

public:
	Movie();
	int getId();
	std::string getName();
	std::string getDirector();
	int getLength();
	std::string getDescription();
	float getRating();
	std::vector<std::string> getCast();
	bool getAvailable();

	void setId(int newId);
	void setName(std::string newName);
	void setGenre(std::string newGenre);
	void setDirector(std::string newDirector);
	void setLength(int newLength);
	void setDescription(std::string newDescription);
	void setRating(float newRating);
	void setCast(std::vector<std::string> newCast);
	void setAvailable(bool newAvailable);
};

