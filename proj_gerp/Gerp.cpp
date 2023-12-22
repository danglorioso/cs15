/*
 *  Gerp.cpp
 *  Authors: Holden Kittelberger & Dan Glorioso (hkittel01 & dglori02)
 *  Date: 11/30/23
 *
 *  CS 15 PROJECT 4: gerp
 *
 *  PURPOSE: Implementation of the Gerp class which creates a tree of the input
 *           directory, traverses the tree, and indexes each file in the tree.
 *           Also runs the query loop and executes commands. Functions include
 *           makeTree, traverseTree, readLines, parseLine, stripNonAlphaNum,
 *           open_or_die, abort, Query, prompt_and_execute, and printLocations.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>

#include "Gerp.h"

using namespace ::std;

/* Gerp()
 *   Purpose: Constructor for the Gerp class that initializes the root, tree,
 *            and hash table
 * Arguments: none
 *   Returns: none
 */
Gerp::Gerp()
{
    root = nullptr;
    tree = nullptr;
    hashTable = new HashTable();
}

/* ~Gerp()
 *   Purpose: Destructor for the Gerp class that deletes the tree, files, and
 *            hash table
 * Arguments: none
 *   Returns: none
 */
Gerp::~Gerp()
{
    delete tree;

    // Delete files
    int size = files.size();
    for (int i = 0; i < size; i++)
    {
        delete files[i];
    }

    delete hashTable;
}

/* Index(string inputDir)
 *   Purpose: Creates a tree of the input directory, traverses the tree, and
 *            indexes each file in the tree
 * Arguments: string - input directory
 *   Returns: None
 */
void Gerp::Index(string &inputDir)
{
    // create tree of input directory
    makeTree(inputDir);

    // traverse tree and index each file
    string path = root->getName() + "/";
    traverseTree(root, path);
}

/* Query(string outputFile)
 *   Purpose: Runs the query loop function that executes commands
 *            from the user and prints the closing message once the
 *            user quits
 * Arguments: string - output file name
 *   Returns: none
 */
void Gerp::Query(string outputFile)
{
    // run query loop
    prompt_and_execute(outputFile);

    // print closing message
    cout << "Goodbye! Thank you and have a nice day." << endl;
}

/* printFiles()
 *   Purpose: Prints the files in the vector of files. This function is used
 *            for testing purposes
 * Arguments: None
 *   Returns: None
 */
void Gerp::printFiles()
{
    // Traverse each file in the vector of files and print its name
    int size = files.size();
    for (int i = 0; i < size; i++)
    {
        cout << files[i]->getFileName() << endl;
    }
}

/* makeTree(string inputDir)
 *   Purpose: Creates a tree of the input directory
 * Arguments: string - input directory
 *   Returns: None
 */
void Gerp::makeTree(string &inputDir)
{
    // Create tree of input directory
    tree = new FSTree(inputDir);
    root = tree->getRoot();
}

/* traverseTree(DirNode *node, string &path)
 *   Purpose: Traverses the tree and indexes each file in the tree
 * Arguments: DirNode - node, string - path
 *   Returns: None
 */
void Gerp::traverseTree(DirNode *node, string &path)
{
    // Traverse each file in the directory
    for (int i = 0; i < node->numFiles(); i++)
    {
        // Create file object for each file
        string fileName = node->getFile(i);
        string filePath = path + fileName;
        File *fileInstance = new File(fileName, filePath);

        // Add file to vector of files
        files.push_back(fileInstance);
        int fileIndex = files.size() - 1;

        // Add each line of file to vector of lines
        readLines(filePath, fileInstance, fileIndex);
    }

    // Store curr path to reset to throughout forloop
    string temp = path;
    // Repeat for each subdirectory within the directory,
    // appending the name of the subdirectory to the path
    for (int i = 0; i < node->numSubDirs(); i++)
    {
        path = temp;
        path += node->getSubDir(i)->getName() + "/";
        traverseTree(node->getSubDir(i), path);
    }
}

/*
 * name:      readLines
 * purpose:   reads each line of a file and adds it to the vector of lines
 * arguments: string - file path, File - file instance, int - file index
 * returns:   none
 * effects:   adds each line of a file to the vector of lines
 */
void Gerp::readLines(string &filePath, File *fileInstance, int fileIndex)
{
    //open the given file
    ifstream fileInput;
    open_or_die(fileInput, filePath);
    int lineNum = 1;
    // Read each line of the file and add it to the vector of lines
    while (not(fileInput.eof()))
    {
        string line;
        getline(fileInput, line);
        fileInstance->addLine(line);
        parseLine(line, lineNum, fileIndex);
        lineNum++;
    }
    //close the file
    fileInput.close();
}

/* parseLine(string line, int lineNum, int fileIndex)
 *   Purpose: Parses a line of a file and adds each word to the hash table
 *            with its file index and line number
 * Arguments: string - line, int - line number, int - file index
 *   Returns: None
 */
void Gerp::parseLine(string &line, int lineNum, int fileIndex)
{
    string word;
    stringstream ss(line);

    // For each word in the line, strip it and add it to the hash table
    while (ss >> word)
    {
        word = stripNonAlphaNum(word);

        // check if the stripped word was all non-alphanumeric characters
        // and is now empty
        if (not word.empty())
            hashTable->insertWord(word, lineNum, fileIndex);
    }
}

/* stripNonAlphaNum(string &word)
 *   Purpose: strips non-alphanumeric characters from the beginning and end of
 *            a string
 * Arguments: string input to strip
 *    Return: string of stripped string
 *    Effect: Non-alphanumeric characters are removed from the beginning and
 *            end of the string
 */
string Gerp::stripNonAlphaNum(string &word)
{
    int numFront = 0;
    int numBack = 0;
    int length = word.length();

    // Count number of non-alphanumeric characters in front
    int index = 0;
    if (not word.empty())
    {
        while (not(isalnum(word[index]) or index >= length))
        {
            numFront++;
            index++;
        }
    }
    // Count number of non-alphanumeric characters in back
    index = length - 1;
    if (not(numFront >= length))
    {
        while (not(isalnum(word[index])))
        {
            numBack++;
            index--;
        }
    }
    // Strip non-alphanumeric characters from front and back
    return word.substr(numFront, (length - numBack - numFront));
}

/*
 *      name: open_or_die
 *   purpose: attempts to open a file, exits with an error otherwise
 * arguments: streamtype, filename
 *   returns: none
 *   effects: opens a file or exits with an error
 */
template <typename streamtype>
void Gerp::open_or_die(streamtype &stream, string &fileName)
{
    stream.open(fileName);
    if (not stream.is_open())
    {
        string error_message = "Unable to open file " + fileName;
        throw runtime_error(error_message);
    }
}

/* prompt_and_execute(string outputFile)
 *   Purpose: Prompts the user for a query and executes the command
 *            until the user quits. Commands include @i and @insensitive for
 *            case insensitive search, @q and @quit to quit, and @f to change
 *            the output file. A string inputted is search as case sensitive.
 * Arguments: string - output file name
 *   Returns: none
 */
void Gerp::prompt_and_execute(string &outputFile)
{
    // Open the output file
    ofstream output;
    open_or_die(output, outputFile);

    string func, next_func;
    bool asking = true;

    // run until user quits
    while (asking and not cin.eof()) {
        cout << "Query? ";
        cin >> func;

        if (func == "@i" or func == "@insensitive") {
            // run insensitive search
            cin >> next_func;
            searchWord(next_func, false, output);
        }
        else if (func == "@q" or func == "@quit")
            asking = false;
        else if (func == "@f") {
            // run file search
            output.close();
            cin >> next_func;
            open_or_die(output, next_func);
        }
        // run case sensitive search
        else
            searchWord(func, true, output);
    }
    output.close();
}

/*
 * name:      searchWord
 * purpose:   searches for a word in the hash table and prints the locations
 * arguments: string - word to search for, bool - case sensitive, ostream -
 *            output
 * returns:   none
 * effects:   prints the locations of a word
 */
void Gerp::searchWord(string func, bool sensitive, ostream &output)
{
    set<pair<int, int>> *wordLocations;
    // give stipped func
    func = stripNonAlphaNum(func);
    // get word locations from hash
    wordLocations = hashTable->getWordLocation(func, sensitive);
    // print locations
    printLocations(wordLocations, sensitive, func, output);
}

/*
 * name:      printLocations
 * purpose:   prints the locations of a word
 * arguments: set<pair<int, int>> - locations, bool - sensitive, string - word,
 *            ostream - output
 * returns:   none
 * effects:   prints the locations of a word
 */
void Gerp::printLocations(set<pair<int, int>> *locations, bool sensitive,
                          string word, ostream &output)
{
    // print not found in sensitive search
    if (locations == nullptr and sensitive)
        output << word << " Not Found. Try with @insensitive or @i." << endl;
    // print not found in insensitive search
    else if (locations == nullptr and not sensitive)
        output << word << " Not Found." << endl;
    // print locations when found
    else
    {
        for (auto wordLoc = locations->begin(); wordLoc != locations->end();
             wordLoc++)
        {
            File *file = files[wordLoc->second];
            output << file->getPath() << ":" << wordLoc->first << ": ";
            output << file->getLine(wordLoc->first - 1) << endl;
        }
    }
}
