// driver for the template class GeneralTree

#include <iostream>
#include "GeneralTree.h"
#include "ProcessInfo/ProcessInfo.h"

#include <vector>
#include <stdlib.h>

using namespace std;

/* the following commented code is used to test GeneralTree*/
/*
enum REQUESTS
{
    QUIT = 0,
    INSERT,
    PRE_ORDER_TRAVERSE,
    PRINT_FOREST,
    MAX
};

void instructions()
{
    cout << "\nTesting General Tree.Choose one of the following operations"
         << "\n0-Quit Processing the tree."
         << "\n1-Insert a node in the tree."
         << "\n2-Pre Order traverse"
         << "\n3-Print Forest\n";
}

template <typename NODETYPE>
void testGeneralTree(GeneralTree<NODETYPE> &tree, const string &typeName)
{
    int choice;
    NODETYPE parentData;
    NODETYPE newData;

    do
    {
        // display instructions
        instructions();

        do
        {
            cout << "\n? ";
            cin >> choice;
        } while (choice < 0 && choice > REQUESTS::MAX);

        switch (choice)
        {
        case REQUESTS::INSERT:
            try
            {
                tree.preOrderTraverse();
                cout << "Enter the parent data:\t";
                cin >> parentData;
                cout << "Enter the new data:\t";
                cin >> newData;
                tree.insert(newData, parentData);
            }
            catch (const invalid_argument &e)
            {
                cerr << e.what() << endl;
            }
            tree.preOrderTraverse();
            break;

        case REQUESTS::PRE_ORDER_TRAVERSE:
            tree.preOrderTraverse();
            break;
        
        case REQUESTS::PRINT_FOREST:
            tree.printForestH();
            break;
            
        case QUIT:
            cout << "Processing the Tree is finished ...\n";
            break;
        }
    } while (choice != QUIT);
}

void insertRandomly(GeneralTree<int> &intTree)
{
    const int NODES_NUM = 100;
    int data, parentData;
    // store parents data in a vector
    vector<int> parentDataVector;

    intTree.insert(1); // root is 1
    parentDataVector.push_back(1);

    for(int i{0}; i < NODES_NUM; ++i)
    {
        data = rand() % 100;
        parentData = parentDataVector [rand() % parentDataVector.size()];

        try{
        intTree.insert(data,parentData);
        // store new element as a possible parent
        parentDataVector.push_back(data);
        }
        catch(const invalid_argument &e)
        {
            cerr << e.what() << "\nParentData = " << parentData;
        }
    }

}
*/

int main()
{
    ProcessInfo top;
    top.displayForest();
}
