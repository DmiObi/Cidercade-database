// Dmitrii Obideiko
// ID: DXO200006

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iomanip>

#include "BinTree.h"
#include "Game.h"

using namespace std;

void printNodeInFile(treeNode* node, ostream& file) // fills cidercade.dat file
{
    Game g = node->getGame();
    file << g.getName() << ", "
         << g.getScore() << ", "
         << g.getInitials() << ", "
         << g.getPlays() << ", $"
         << g.getRev() << endl;
}

// Reads the tree level by level
void brFrstTrav(queue<treeNode*>& que, BinTree &tree, ostream& file)
{
    // checks if the tree is not empty
    if (tree.getRoot() != nullptr)
    {
        // we add the first node and its children to q
        cout << endl << endl;
        que.push(tree.getRoot());
        treeNode* curNode = que.front();
        
        while (!que.empty())
        {
            // check if the node has child - if it does we add it to queue
            if (curNode->getLeft() != nullptr) { que.push(curNode->getLeft()); }
            if (curNode->getRight() != nullptr) { que.push(curNode->getRight()); }
            printNodeInFile(curNode, file);
            que.pop();
            curNode = que.front();
        }
    }
}

Game parseDatabaseLine(string &line)
{
    string name;
    int    score;
    string initials;
    int    plays;
    double revenue;
    
    size_t start = 0;
    size_t end = line.find(",");
    name = line.substr(start, end - start);
    
    start = end + 2;
    end = line.find(",", start);
    score = stoi(line.substr(start, end - start));
    
    start = end + 2;
    end = line.find(",", start);
    initials = line.substr(start, end - start);
    
    start = end + 2;
    end = line.find(",", start);
    plays = stoi(line.substr(start, end - start));
    
    start = line.find("$", end + 1) + 1;
    revenue = stod(line.substr(start, line.size() - 1));
    
    return Game(name, score, initials, plays, revenue);
}

void loadDatabaseFile(ifstream &file, BinTree &tree)
{
    while (!file.eof())
    {
        string line;
        getline(file, line);
        
        if (line.size() != 0)
        {
            Game g = parseDatabaseLine(line);
            tree.addRecord(new Node<Game>(g));
        }
    }
}

enum Field
{
    SCORE = 1, INITIALS = 2, PLAYS = 3
};

string getFieldName(int num)
{
    if (num == SCORE) { return "high score"; }
    else if (num == INITIALS) { return "initials"; }
    else if (num == PLAYS) { return "plays"; }
    else { return ""; }
}

void printNodeWoName(treeNode* node)
{
    Game g = node->getGame();
    cout << "High Score: " << g.getScore() << '\n'
         << "Initials: " << g.getInitials() << '\n'
         << "Plays: " << g.getPlays() << '\n'
         << "Revenue: $" << g.getRev() << endl << endl;
}

void execCmdLine(string &line, BinTree &tree)
{
    int cmd = stoi(line.substr(0, 1));
    
    if (cmd == 1) // Add a record
    {
        size_t start = line.find("\"") + 1;
        size_t end = line.find("\"", start + 1);
        string name = line.substr(start, end - start);
        
        start = end + 1;
        end = line.find(" ", start + 1);
        int score = stoi(line.substr(start, end - start));
        
        start = end + 1;
        end = line.find(" ", start + 1);
        string initials = line.substr(start, end - start);
        
        start = end + 1;
        end = line.find(" ", start + 1);
        int plays = stoi(line.substr(start, end - start));
        
        start = line.find('$') + 1;
        end = line.size();
        double revenue = stod(line.substr(start, end - start));
        
        Game g(name, score, initials, plays, revenue);
        tree.addRecord(new Node<Game>(g));
        
        cout << "RECORD ADDED" << '\n' << g << endl;
    }
    else if (cmd == 2) // Search a record
    {
        string name = line.substr(2, line.length() - 2);
        
        treeNode* node = tree.search(tree.getRoot(), name);
        
        if (node != nullptr)
        {
            cout << node->getGame().getName() << " FOUND" << endl;
            
            while (node != nullptr)
            {
                printNodeWoName(node);
                node = tree.search(node, name); // not sure
            }
        }
        else
            cout << name << " NOT FOUND" << endl << endl;
    }
    else if (cmd == 3) // Edit a record
    {
        size_t start = line.find("\"") + 1;
        size_t end = line.find("\"", start + 1);
        string name = line.substr(start, end - start);
        
        treeNode* node = tree.search(tree.getRoot(), name);
        Game& g = node->getGame();
        
        start = end + 2;
        end = line.find(" ", start);
        int field = stoi(line.substr(start, end - start));
        
        start = end + 1;
        end = line.size();
        
        cout << name << " UPDATED" << endl;
        cout << "UPDATE TO " << getFieldName(field) << " - VALUE ";
        
        if (field == SCORE) // Changing score
        {
            int score = stoi(line.substr(start, end - start));
            g.setScore(score);
            cout << score << endl;
        }
        else if (field == INITIALS) // Changing initials
        {
            string initials = line.substr(start, end - start);
            g.setInitials(initials);
            cout << initials << endl;
        }
        else if (field == PLAYS) // Changing plays
        {
            int plays = stoi(line.substr(start, end - start));
            g.setPlays(plays);
            cout << plays << endl;
        }
        
        cout << "High Score: " << g.getScore() << endl;
        cout << "Initials: " << g.getInitials() << endl;
        cout << "Plays: " << g.getPlays() << endl;
        cout << "Revenue: $" << g.getRev() << endl << endl;
        
    }
    else if (cmd == 4) // Deletes a record
    {
        size_t start = 2;
        size_t end = line.size();
        string name = line.substr(start, end - start);
        treeNode* node = tree.search(tree.getRoot(), name);
        treeNode* deletedNode = tree.removeRecord(node);
        
        cout << "RECORD DELETED" << endl;
        cout << deletedNode << endl;
        
    }
    else if (cmd == 5) // sorting in asc/des order
    {
        if (line.find("asc") != string::npos)
        {
            cout << "RECORDS SORTED ASCENDING" << endl;
            tree.displayTreeAsc(tree.getRoot());
            cout << endl;
        }
        else if (line.find("des") != string::npos)
        {
            cout << "RECORDS SORTED DESCENDING" << endl;
            tree.displayTreeDes(tree.getRoot());
            cout << endl;
        }
    }
}

void loadcmdFile(ifstream &file, BinTree &tree)
{
    while (!file.eof())
    {
        string line;
        getline(file, line);
        
        if (line.size() != 0)
            execCmdLine(line, tree);
    }
}

int main()
{
    cout.setf(cout.fixed); // Sets the ouput format to round to n decimal places
    cout.precision(2); // sets the number of digits in the decimal part
    
    string databaseFileName;
    cin >> databaseFileName;
    string cmdFileName;
    cin >> cmdFileName;
    
    ifstream databaseFile = ifstream(databaseFileName);
    ifstream cmdFile = ifstream(cmdFileName);
    
    BinTree tree;
    loadDatabaseFile(databaseFile, tree);
    loadcmdFile(cmdFile, tree);
    
    ofstream file("cidercade.txt");
    file << fixed << setprecision(2) << endl; 
    queue<treeNode*> que;
    brFrstTrav(que, tree, file);
    
    return 0;
}
