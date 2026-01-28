//Initialise libraries
#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include "textLibrary.h" //Custom library for texts
using namespace std;

//Initialise variables
string selectedText;
string typingPortion;
double elapsedSeconds;
double accuracyPercent;
double WPM;
int textIndex;
int totalChars;
int correctChars;
int incorrectChars;

//Welcomes user + states rules/instructions
int welcome() {
    cout << "Welcome to the Typeracing game!" << endl;
    _sleep(1000);
    cout << endl << "Rules/Instructions:" << endl;
    _sleep(1000);
    cout << "1. Choose a text to type, or enter your own custom text." << endl;
    _sleep(1500);
    cout << "2. Type the text exactly as shown, including capitalization and punctuation." << endl;
    _sleep(1500);
    cout << "3. Your speed and accuracy will be measured." << endl;
    _sleep(1500);
    cout << endl;
    return 0;
}

//Previews the text before starting the "run"
int showTexts() {
    cout << "Available texts:" << endl;
    _sleep(1000);
    int count = getTextCount();
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ") " << getTextByIndex(i) << endl;
        //_sleep(1500); //Experimenting with sleep times
    }
    cout << endl;
    _sleep(1000);
    return 0;
}

//Allows the user to select the piece of text that they want to type out
int selectText() {
    int selection;
    int count = getTextCount();
    cout << "Select a text by entering a number between 1 and " << count << ":" << endl;
    cout << "Enter 0 to randomly select a text." << endl;
    cout << "Enter -1 to add your own custom text." << endl;

    while (true) {
        while (!(cin >> selection)) { //Selection is set as an integer, if an integer is not inputted, body runs
            cout << "Invalid input! Please enter a number between 0 and " << count << ":" << endl;
            cin.clear(); //Clears userinput to allow loop to rerun
            cin.ignore(10000, '\n'); //Ignores newline buffer to avoid any errors
        }

        if (selection >= 1 && selection <= count) { //Specific text selection
            textIndex = selection - 1;
            selectedText = getTextByIndex(textIndex);
            cin.ignore(10000, '\n'); //Ignores newline buffer to avoid any errors
            break;
        }
        else if (selection == 0) { //Random text selection
            textIndex = rand() % count;
            selectedText = getTextByIndex(textIndex);
            cin.ignore(10000, '\n'); //Ignores newline buffer to avoid any errors
            break;
        }
        else if (selection == -1) { //Custom text selection
            cin.ignore(10000, '\n'); //Ignores newline buffer to avoid any errors
            cout << endl << "Enter your custom text:" << endl;
            string customText;
            getline(cin, customText);

            addText(customText); //Adds custom text
            textIndex = getTextCount() - 1;
            selectedText = customText;
            break;
        }
        else { //Error handling when number out of range
            cout << "Invalid selection. Please enter a number between 0 and " << count << ":" << endl;
        }
    }

    return 0;
}

//Shows the selected text and waits for the user to be ready
int readyUp() {
    cout << endl << "Previewing text " << textIndex + 1 << ": " << endl;
    cout << "\"" << selectedText << "\"" << endl << endl;
    cout << "Press Enter when you are ready to start...";

    //Error handling incase user spams enter
    if (cin.peek() == '\n') { //Checks for newline buffer
        cin.ignore(1, '\n'); //Clears newline buffer
    }

    //Userinput for if they are ready
    string readyState;
    getline(cin, readyState);

    return 0;
}

//Countdown before starting the "run"
int startCountdown() {
    cout << "Starting in 3..." << endl;
    _sleep(1000);
    cout << "2..." << endl;
    _sleep(1000);
    cout << "1..." << endl;
    _sleep(1000);
    cout << "Go!" << endl << endl;

    return 0;
}

//Allows the user to actually type during the "run"
int getUserInput() {
    cout << "\"" << selectedText << "\"" << endl << endl;

    clock_t startTime = clock();
    getline(cin, typingPortion); //Userinput will be read as a line instead of the first word

    clock_t endTime = clock();
    elapsedSeconds = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

    return 0;
}

//Actually counts each word from each userinput
int countWords(const string& s) {
    bool inWord = false;
    int words = 0;

    for (char c : s) {
        if (isspace(static_cast<unsigned char>(c))) {
            inWord = false; //Any whitespace will end the current word
        } else {
            if (!inWord) {  //Once a new word is started with a non whitespace, "words" count is updated then loops
                inWord = true;
                ++words;
            }
        }
    }
    return words;
}

//Calculates WPM and accuracy
int calculateStats() {
    totalChars = static_cast<int>(selectedText.size());
    correctChars = 0;
    incorrectChars = 0;

    //Compares userinputted characters with character from text
    int maxLen = static_cast<int>(max(selectedText.size(), typingPortion.size()));

    for (int i = 0; i < maxLen; i++) {
        char originalChar = (i < static_cast<int>(selectedText.size())) ? selectedText[i] : '\0';
        char typedChar    = (i < static_cast<int>(typingPortion.size()))    ? typingPortion[i]    : '\0';

        if (originalChar == typedChar && originalChar != '\0') {
            correctChars++;
        }
        else {
            if (originalChar != '\0' || typedChar != '\0') {
                incorrectChars++;
            }
        }
    }

    //Accuracy calculations + Error handling
    if (totalChars == 0) {
        accuracyPercent = 0;
    }
    else {
        accuracyPercent = (static_cast<double>(correctChars) / static_cast<double>(totalChars)) * 100.0;
    }

    //WPM calculations
    double minutes = elapsedSeconds / 60.0;
    int wordsTyped = countWords(typingPortion);
    double accuracyFraction = accuracyPercent / 100.0;

    //Error handling
    if (minutes == 0.0) {
        WPM = 0;
    }
    else {
        WPM = (static_cast<double>(wordsTyped) / minutes) * accuracyFraction;
    }

    return 0;
}

//Prints the results of the "run"
 int showResults() {
    cout << endl << fixed << setprecision(2);
    cout << "Results:" << endl;
    cout << "Time taken: " << elapsedSeconds << " seconds" << endl;
    cout << "Correct characters: " << correctChars << endl;
    cout << "Incorrect characters: " << incorrectChars << endl;
    cout << "Accuracy: " << accuracyPercent << "%" << endl;
    cout << "WPM: " << WPM << endl;

    return 0;
}

//Runs the game
int main() {
    srand(time(NULL));
    welcome();

    char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        showTexts();
        selectText();
        readyUp();
        startCountdown();
        getUserInput();
        calculateStats();
        showResults();
        cout << endl << "Play again? (y/n): " << endl;

        while (true) {
            while (!(cin >> playAgain)) { //playAgain is set as a character, if a character is not inputted, body runs
                cout << "Please enter 'y' or 'n'." << endl;
                cin.clear(); //Clears userinput to allow loop to rerun
                cin.ignore(10000, '\n'); //Ignores newline buffer to avoid any errors
            }

            if (playAgain == 'y' || playAgain == 'Y' || playAgain == 'n' || playAgain == 'N') { //Loops back to play again function
                break;
            }
            cout << "Please enter 'y' or 'n'." << endl;
            cin.clear(); //Clears userinput to allow loop to rerun
            cin.ignore(10000, '\n');  //Ignores newline buffer to avoid any errors
        }
        cout << endl;
    }

    return 0;
}