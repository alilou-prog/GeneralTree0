#ifndef GENERAL_TREE_NODE_H
#define GENERAL_TREE_NODE_H

#include <vector>

// forward declaration
template <typename NODETYPE> class GeneralTree;

template <typename NODETYPE>
class GeneralTreeNode {
    
    friend class GeneralTree <NODETYPE>;

    public:
    // initialize m_data
    GeneralTreeNode(const NODETYPE &data)
        : m_data {data}
    {}

    NODETYPE getNodeData() const
    {
        return m_data;
    }

    private:
    NODETYPE m_data;
    std::vector< GeneralTreeNode<NODETYPE> *> m_children;
};

#endif
