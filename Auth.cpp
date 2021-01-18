#include "Auth.hpp"


std::string Auth::sha256(std::string str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string Auth::generateSalt(int length) {
    static const char alphanum[] =
        "0123456789"
        "!@#$%^&*"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    int stringLength = sizeof(alphanum) - 1;

    std::string result;

    std::random_device r;
    std::uniform_int_distribution<int> uniform_dist(0, stringLength);

    for (unsigned int i = 0; i < length; ++i) {
        result += alphanum[uniform_dist(r)];
    }

    return result;
}

std::string Auth::generateHash(std::string password, std::string salt) {
    return sha256(password + salt);
}

bool Auth::registerUser(User newUser, std::string password) {
    if (DB::getDB().getUser(newUser.getLogin())) return false; //TODO: Move validation if user exist to Validator class

    std::string salt = generateSalt(32);
    std::string hash = generateHash(password, salt);

    try {
        DB::getDB().createUser(newUser, hash, salt);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }


    return true;
}
