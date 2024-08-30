
#include "ProcessInfo.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <regex>

#include <vector>
#include "../GeneralTree.h"

using namespace std;

// ################ LOCAL FUNCTIONS

// split a string into a vector according to a given delimiter
void split(string& str, vector<string> &tokens, const string delimiter =" ")
{
    size_t pos {0};
    string token;

    while( (pos = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0,pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    // the last token
    tokens.push_back(str);
}

// count the number of indentation for a string and remove it
// here indentation will be two spaces "  "
// this help us to determine hierarchy level
int indentationCount(string& str, const string &indentation)
{
    size_t pos{0};
    int indentationNum{0};

    while( (pos = str.find(indentation)) != string::npos)
    {
        ++indentationNum;
        str.erase(0, pos + indentation.length());
    }

    return indentationNum;
}

// store the splitted output in a GeneralTree
void storeInTree(vector<string> &tokens, GeneralTree<string> &tree)
{
    // indentation is two spaces
    const string indentation = "  ";
    // track the last token (line) because it could be a parent
    //  if we enter a new level of hierarchy
    string lastToken{""};

    // this table is used to store the parents' data
    // the index of each element indicates the level of its children
    //  in the hierachy
    string parentsData[10]{}; // assume 10 level of hierarchy as a max

    // we use these two vars to detect if we enter a new level
    //  of hierarchy
    int currentIndentationCount {0}, newIndentationCount;

    for (auto &&str : tokens)
    {
        // remove indentation and get its count
        newIndentationCount = indentationCount(str, indentation);

        // if we detect that we entered a new higher level of hierarchy
        //  (depth), we set the parentData with the corresponding index
        // index = hierarchy/depth level
        
        if(newIndentationCount > currentIndentationCount) // either + or -
        {
            parentsData[newIndentationCount] = lastToken;
            currentIndentationCount = newIndentationCount; // update
        }

        // insert in the tree
        tree.insert(str,parentsData[currentIndentationCount]);

        // update lastToken
        lastToken = str;
    }
    
}

// ################ LOCAL FUNCTIONS


void ProcessInfo::display(const string& arguments)
{
    if(evaluateArguments(arguments))
    {
        const string command = "ps -eo " + arguments; 
        m_systemAnalyser.RunCommand(command.data());
        cout << m_systemAnalyser.output();
    }
    else
    {
        throw invalid_argument("ProcessInfo::display() :"
        "invalid arguments given to ps");
    }
}

void ProcessInfo::displayForest()
{
    // execute ps specifying comm attribute and --forest option
    const string command = "ps -eo comm -H";
    m_systemAnalyser.RunCommand(command.data());

    // store the output in a local string
    string output {m_systemAnalyser.output()};
    
    // split the output into lines in a vector
    std::vector <string> lines;
    split(output, lines, "\n");

    // now storing in the tree
    GeneralTree <string> tree;
    storeInTree(lines,tree);
    tree.printForestH();
}

string ProcessInfo::help() const 
{
    ostringstream out;
    out << "Usage: ProcessInfo::diplay(arguments)\n"
        << "arguments= PATTERN, PATTERN, ....\n"
        << "PATTERN = (args|cmd|comm|pid|ppid|tty),\n"
        << endl;

    return out.str();
}

// use regulat expression to validate arguments
bool ProcessInfo::evaluateArguments(const string& arguments) const
{
    // each group contains three letter and a comma, except the last one
    regex re("((args|cmd|comm|pid|ppid|tty),)*"
        "((args|cmd|comm|pid|ppid|tty))",
        std::regex_constants::extended); 

    if (regex_match(arguments, re))
        return true;
    else
        return false;
}