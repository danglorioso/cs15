/*
 * Filename: DirNode.h
 * Contains: Interface of the DirNode class
 *           Each DirNode will be a folder (and contain info of files
 *           inside that directory.
 * Part of: Project 2 assignment "Grep" for Comp 15 Fall 2018
 *
 */

#ifndef REFERENCE_DIRNODE_H
#define REFERENCE_DIRNODE_H

#include <string>
#include <vector>

// This are the nodes that make up our N-ery file tree
class DirNode {
public:
        // Default constructor. Creates empty dirNode.
        DirNode();

        // Constructor: given the path to explore fully explores that path
        DirNode(std::string newName);

        // Copy Constructor
        DirNode(const DirNode &other);

        // assignment overload. Will seg fault if copied onto itself.
        DirNode &operator=(const DirNode &other);

        // Adds a file with the name "newName" to the current node
        void addFile(std::string newName);

        // adds a sub directory (newDir) to the current node
        void addSubDirectory(DirNode *newDir);

        // returns true if there are sub directories in the current node
        bool hasSubDir();

        // returns true if there are files in the current node
        bool hasFiles();

        // returns true if there are no files or sub directories
        bool isEmpty();

        // returns the number of sub directories
        int numSubDirs();

        // returns the number of files in the current node
        int numFiles();

        // sets the name of the current node
        void setName(std::string newName);

        // returns the name of the current directory
        std::string getName();

        // returns the nth subdirectory
        DirNode *getSubDir(int n);

        // returns nth file name
        std::string getFile(int n);

        // get parent directory node
        DirNode *getParent();

        // set parent directory node
        void setParent(DirNode *newParent);

private:
        // list of all of the sub directories in the
        // current directories
        std::vector<DirNode *> directories;

        // list of all the fileNames in the current directory
        std::vector<std::string> fileNames;

        // current directory name
        std::string name;

        // pointer to parent directory
        DirNode *parent;
};

#endif  // REFERENCE_DIRNODE_H
