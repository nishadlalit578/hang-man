#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;
const int MAX_TRIES = 5;

void Instruction()
{
    cout << "\nWelcome to HANGMAN :: Save YOUR friend from being hanged.";
    cout << "\n\nINSTUCTION : \n\t(1) Guess a country Name by guessing the letters in the Codeword.";

    cout << "\n\t(2) Each letter is represented by a star.";
    cout << "\n\t(3) You have to type only one letter in one try";
    cout << "\n\t(4) You have " << MAX_TRIES << " tries to try and guess the word.";
    cout << "\n\n______________________________________________________________________________________________________________________________________\n";
}

void printASCII(string &file)
{
    string line = "";
    ifstream inFile;
    inFile.open(file);
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            getline(inFile, line);
            cout << line << endl;
        }
    }
    inFile.close();
}

int LetterFill(char guess, string secretword, string &guessword)
{
    int i;
    int matches = 0;
    int len = secretword.length();
    for (i = 0; i < len; i++)
    {
        // Did we already match this letter in a previous guess?
        if (guess == guessword[i])
        {
            return 0;
        }
        // Is the guess in the secret word?
        if (guess == secretword[i])
        {
            guessword[i] = guess;
            matches++;
        }
    }
    return matches;
}

int main()
{
    char play_again = 'y';
    while (play_again == 'y' || play_again == 'Y')
    {

        // LOGO AND INSTRUCTION OF THE GAME..
        string filename = "LOGO.txt";
        printASCII(filename);
        Instruction();

        char letter; // FOR GUESSING LETTER..
        int num_of_wrong_guesses = 0;
        string word;
        string words[] = // CODEWORDS
            {
                "india",
                "pakistan",
                "nepal",
                "russia",
                "malaysia",
                "philippines",
                "australia",
                "iran",
                "ethiopia",
                "ecuador",
                "oman",
                "indonesia"};

        // choose and copy a word from array of words randomly.
        srand(time(NULL));
        int n = rand() % 12;
        word = words[n];

        // FOR HIDING THE CODEWORD..
        string unknown(word.length(), '*');

        // DRIVER CODE --->
        while (num_of_wrong_guesses < MAX_TRIES)
        {
            cout << "\n"
                 << unknown;
            cout << "\nGuess a letter: ";
            cin >> letter;

            if (LetterFill(letter, word, unknown) == 0)
            {
                cout << "\nWhoops! That letter isn't in there!" << endl;
                num_of_wrong_guesses++;
                switch (num_of_wrong_guesses)
                {
                case 1:
                    filename = "hangman1.txt";
                    break;
                case 2:
                    filename = "hangman2.txt";
                    break;
                case 3:
                    filename = "hangman3.txt";
                    break;
                case 4:
                    filename = "hangman4.txt";
                    break;
                case 5:
                    filename = "hangman5.txt";
                    break;
                default:
                    break;
                }

                printASCII(filename);

                // cout<<num_of_wrong_guesses<<endl;
            }
            else
            {
                cout << "\nYou found a letter! Isn't that exciting!" << endl;
            }

            // Tell user how many guesses has left.
            cout << "You have " << MAX_TRIES - num_of_wrong_guesses;
            cout << " guesses left." << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~\n";

            // Check if user guessed the word.
            if (word == unknown)
            {
                cout << "\n"
                     << word << endl;
                cout << "Yeah! You got it!\n";
                break;
            }
        }
        // IF NO LETTER MATCHES..
        if (num_of_wrong_guesses == MAX_TRIES)
        {
            cout << "\nSorry, you lose...\nYou've been hanged." << endl;
            cout << "\nThe word was : " << word << "\n"
                 << endl;
        }

        cout << "\nDo you want to play again ? (y / n) ";
        cin >> play_again;
    }
    getch();
    return 0;
}
