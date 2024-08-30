#ifndef GENERAL_TREE_H
#define GENERAL_TREE_H

#include "GeneralTreeNode.h"
#include <iostream>
#include <stdexcept>

template <typename NODETYPE>
class GeneralTree
{
public:
    GeneralTree() : root{nullptr} {};
    ~GeneralTree()
    {
        destructorHelper(root);
    }

    void insert(const NODETYPE &newData, const NODETYPE &parentData = {}) noexcept(false)
    {
        // if root does not exist, insert newNode as root
        if (root == nullptr)
        {
            auto newNode = getNewNode(newData);
            root = newNode;
            return;
        }

        // search for the parent using parentData
        GeneralTreeNode<NODETYPE> *parentPtr = search(parentData);
        if (parentPtr != nullptr)
        {
            auto newNode = getNewNode(newData);
            parentPtr->m_children.push_back(newNode);
            return;
        }

        // If no valid parent was found, throw an expection
        throw std::invalid_argument("\nGeneralTree::insert() :\n"
                                    "A node with the given 'parentData' argument "
                                    "was not found\n");
    }

    void preOrderTraverse() const
    {
        std::cout << "Printing the tree (preOrderTraverse)\n";
        preOrderTraverse(root);
        std::cout << "\n\n";
    }

    void printForestH() const
    {
        std::cout << "\n";
        int padding{-5};
        printForestH_Helper(root, padding);
        std::cout << "\n";
    }


private:
    GeneralTreeNode<NODETYPE> *root;

    void destructorHelper(GeneralTreeNode<NODETYPE> *nodePtr)
    {
        if (nodePtr != nullptr)
        {
            // delete children then the node

            for (auto ptr : nodePtr->m_children)
            {
                destructorHelper(ptr);
            }

            delete nodePtr;
        }
    }

    GeneralTreeNode<NODETYPE> *search(const NODETYPE &data)
    {
        return searchHelper(root, data);
    }

    GeneralTreeNode<NODETYPE> *searchHelper(GeneralTreeNode<NODETYPE> *nodePtr,
                                            const NODETYPE &data)
    {
        if (nodePtr != nullptr)
        {
            if (nodePtr->m_data == data)
                return nodePtr;

            // otherwise , search in the children vector
            // store the results in a vector subTreeResults
            // assume no duplication
            std::vector < GeneralTreeNode<NODETYPE> *> subTreesResults;

            for (auto &&ptr : nodePtr->m_children)
            {
                subTreesResults.push_back(searchHelper(ptr, data));
            }

            // check the results
            for (auto &&resultPtr : subTreesResults)
            {
                if(resultPtr != nullptr)
                    return resultPtr;
            }
            // if all subTreeResults elements are nullptr, then
            return nullptr;
            
        }
        return nullptr;
    }

    GeneralTreeNode<NODETYPE> *getNewNode(const NODETYPE &data)
    {
        return new GeneralTreeNode<NODETYPE>(data);
    }

    void preOrderTraverse(GeneralTreeNode<NODETYPE> *nodePtr) const
    {
        if (nodePtr != nullptr)
        {
            for (auto &&childPtr : nodePtr->m_children)
            {
                preOrderTraverse(childPtr);
            }

            std::cout << nodePtr->m_data << ' ';
        }
    }

    void printForestH_Helper(GeneralTreeNode<NODETYPE> *nodePtr,
                           int padding) const
    {
        if(nodePtr != nullptr)
        {
            padding += 5;
            for (auto &&ptr : nodePtr->m_children)
            {
                printForestH_Helper(ptr, padding);
            }

            for(int i{0}; i < padding; ++i)
            {
                std::cout << ' ';
            }
            std::cout << nodePtr->getNodeData() << '\n';
        }
    }

    
};

#endif