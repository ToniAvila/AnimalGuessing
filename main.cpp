/*
HW5 Animal Guessing Game

Toni Avila (TXA180025), CS 1337.010
4/15/2020

When executed, this program initially outputs a message from the root node guessing
the animal the user is thinking of. If it's correct, the program is finished and the
user can choose to play again with a different animal in mind. If the animal is not in the tree,
a new node will be created using data entered by the user (a question and its respective
answer) and put in either the position of noAnswer or yesAnswer. The user can then run the program again,
answer the questions accordingly, and find that animal that was just inserted into the tree.

Change/Improvement Log:
-Created skeleton of the program through creation of the struct node, and the root struct
as the head of the tree. (4/15/2020)
-Created addToTree function which either finds the animal in mind, or cretaes a new node for
the animal wanted, while also making sure to put it in either the yesAnswer location
or noAnswer location depending on user response. (4/16/2020)
-Added continuePlay function to keep game running while bool returned is true i.e "y"
is entered. (4/16/2020)
-Created getNewAnimalData which gets the name of the new animal, a question to distinguish it, and its
answer, storing all of them for use in other functions. (4/17/2020)
-Made beginTheGame function which essentially starts the game using node given and uses a bit of recursion.
(4/18/2020)

Notes:
-Traverse through the game using only "y" and "n" keys and their
uppercase equivalents, NOT yes or no.
-User must specify they want to play the game again after adding an
animal not yet in the tree.
-New nodes are dynamically created in memory using the "new" function.

For reference:
-https://www.cprogramming.com/tutorial/lesson18.html
(used to learn methods for binary trees and set them up)

*/


#include <iostream>
#include <string>

using namespace std;

// main struct used for entire program
struct AnimalNode
{
    string guess = ""; // default to blank
    string question = ""; // default to blank

    AnimalNode *yesAnswer = nullptr; // default to null
    AnimalNode *noAnswer = nullptr; // default to null
};


// get answer from users
void getAnswerFromUser(string& userAnswer)
{
    cin >> userAnswer;

    while (!(userAnswer == "y" || userAnswer == "n" || userAnswer== "Y" || userAnswer== "n"))
    {
        cout << "You entered an option not specified. Please enter \"y\", \"n\", \"Y\" or \"N\"" << endl;
        cin >> userAnswer;
    }
} // getAnswerFromUser()

void getNewAnimalData(string& temporaryGuess, string& temporaryQuestion, AnimalNode *currentNode, string& answerFromUser)
{
    cout << "What is the name of the animal you had in mind?" << endl;
    cin >> temporaryGuess;
    cin.ignore(); // to clear keyboard buffer, as it would have a remaining key

    // reading in new question
    cout << "Please enter a question that will distinguish a " << temporaryGuess << " from a " << currentNode->guess << "." << endl;
    getline(cin, temporaryQuestion);

    cout << "With respect to the question you entered above, what would be the correct answer for this new animal?" << endl;
    cin >> answerFromUser;

    // input validation
    while (!(answerFromUser == "y" || answerFromUser == "n" || answerFromUser == "Y" || answerFromUser == "N"))
    {
        cout << "Invalid answer. Please enter \"y\" or \"n\"" << endl;
        cin >> answerFromUser;
    }
} // getNewAnimalData()

bool continuePlay()
{
    char replay;

    cout << "Would you like to start the game over, with the new data in the tree? (\"y\" for yes, \"n\" for no)." << endl;
    cin >> replay;

    if (replay == 'y' || replay == 'Y')
        return true;

    return false; // default, will end program
} // continuePlay()

void addToTree(AnimalNode *currNode, string userAnswer)
{
    string temporaryGuess;
    string temporaryQuestion;
    string answerForUserAnimal;

    cout << "Is it a " << currNode->guess << "?" << endl;
    getAnswerFromUser(userAnswer);

    if (userAnswer == "y" || userAnswer =="Y")
        cout << "The tree has guessed your animal." << endl;
    else
    {
        // get the information from a new animal
        getNewAnimalData(temporaryGuess, temporaryQuestion, currNode, answerForUserAnimal);

        AnimalNode *yesNode; // creating node for the yesNode position
        AnimalNode *noNode; // creating node for the noNode position

        if (answerForUserAnimal == "y" || answerForUserAnimal == "Y")
        {
            // if the answer to the new question is yes, a node for the yes option will be created holding the "new" animal
            yesNode = new AnimalNode;
            yesNode->guess = temporaryGuess; // setting user inputted animal to guess field

            noNode = new AnimalNode;
            noNode->guess = currNode->guess; // setting current
        }
        else if (answerForUserAnimal == "n" || answerForUserAnimal == "N")
        {
            // if the answer to the new question is no, a node for the yes option will be created holding the current node's guess
            yesNode = new AnimalNode;
            yesNode->guess = currNode->guess;

            noNode = new AnimalNode;
            noNode->guess = temporaryGuess;
        }

        currNode->guess = ""; // empty
        currNode->question = temporaryQuestion;
        currNode->yesAnswer = yesNode; // rerouting addresses
        currNode->noAnswer = noNode;
    }
} // addToTree()

void beginTheGame(AnimalNode *currNode)
{
    string userAnswer;

    if (!(currNode->question == "")) // if Q isn't blank, ask it then grab the answer
    {
        cout << currNode->question << endl;
        getAnswerFromUser(userAnswer);

        if (userAnswer == "y"|| userAnswer== "Y") // use of recursion to ask the questions in other nodes
            beginTheGame(currNode->yesAnswer);
        else
            beginTheGame(currNode->noAnswer);
    }
    else // no question, then run addToTree Function
        addToTree(currNode, userAnswer);
} // beginGame()


int main()
{
    // initializing head of the tree with lizard as the guess
    // child pointers and question are null
    AnimalNode *root = new AnimalNode;
    root->guess = "lizard";

    cout << "This is the animal guessing game. Traverse through the game with the use of: " << endl
         << "*y or Y for Yes" << endl
         << "*n or N for no" << endl;

    cout << "Press any key and then enter to begin the game." << endl;
    cin.get();

    do
    {
        beginTheGame(root); // game is first ran with lizard as the guess/root/head
    }
    while (continuePlay());

    return 0;
} // main{}
