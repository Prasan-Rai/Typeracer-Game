#ifndef GAME_FILES_TEXTLIBRARY_H
#define GAME_FILES_TEXTLIBRARY_H

#include <string>
#include <vector>
using std::string;
using std::vector;
using namespace std;

//Texts to be played
static vector<string> texts = {
    "The quick brown fox jumps over the lazy dog.",
    "Typing games are a fun way to improve your speed and accuracy.",
    "C plus plus gives programmers a lot of control over system resources.",
    "Practice makes perfect when learning how to type quickly and correctly.",
    "Engineering students often write code to automate boring calculations."
};

//Returns text size as an integer
inline int getTextCount() {
    return static_cast<int>(texts.size());
}

//Returns the text to be played
inline string getTextByIndex(int index) {
    return texts.at(index);
}

//Adds the users new text
inline void addText(const string& newText) {
    texts.push_back(newText);
}

#endif //GAME_FILES_TEXTLIBRARY_H