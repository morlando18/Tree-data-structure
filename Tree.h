
#ifndef TREE_H
#define TREE_H
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

template<class T>
class TreeNode{

private:
    T info;
    vector<TreeNode*> siblings;


public:
    int globalIndex = 0;

    TreeNode<T>() : info(T())
    //Constructor for TreeNode. It stores a default-constructed info value and starts with no siblings.
    {
    }

    TreeNode<T>(T element) : info(element)
    //Constructor for TreeNode. It stores element as its info and starts with no siblings.
    {
    }

    ~TreeNode<T>()
    //Destructor for TreeNode. It recursively deletes all siblings.
    {
        deleteChildren();
    }

    T& getData()
    //Returns a reference to the stored info.
    {
        return info;
    }

    size_t getChildCount()
    //Returns the number of siblings this node has.
    {
        return siblings.size();
    }

    vector<TreeNode*> getChildren() const
    {
        return siblings;
    }

    TreeNode<T>* getChild(size_t index)
    //Returns the child node at specified by index.
    {
        globalIndex = index;
        return siblings.at(index);

    }

    void addChild(TreeNode<T>* child)
    //Add the child node to the siblings of this node.
    {
        siblings.push_back(child);
    }

    void removeChild(size_t index)
    //Remove the child node at specified by index.
    {
        siblings.erase(siblings.begin() + index);
    }

    void deleteChildren()
    //Recursively deletes all siblings.
    {
        for (typename std::vector< TreeNode* >::iterator it = siblings.begin() ; it != siblings.end(); ++it)
        {
            delete (*it);
        }
            siblings.clear();
    }


};

template<class T>
void breadthFirstTraverse(TreeNode<T>* root, void (*dataFunction)(T&))
//Breadth-first traversal starting at root. Calls dataFunction on the info element to process it.
{
    queue<TreeNode<T>*> stack;
    stack.push(root);
    while(!stack.empty())
    {
        TreeNode<T>* node = stack.front();
        dataFunction(node->getData());
        stack.pop();
        for(auto& child : node->getChildren())
        {
            stack.push(child);
        }
    }

}

template<class T>
void preOrderTraverse(TreeNode<T>* root, void (*dataFunction)(T&))
//Pre-order traversal starting at root. Calls dataFunction on the info element to process it.
{
    if(!root) return;
    dataFunction(root->getData());
    for(auto& child : root->getChildren())
    {
        preOrderTraverse(child, (*dataFunction));
    }
}

template<class T>
void postOrderTraverse(TreeNode<T>* root, void (*dataFunction)(T&))
//Post-order traversal starting at root. Calls dataFunction on the info element to process it.
{
    if(!root) return;
    for(auto& child : root->getChildren())
    {
        postOrderTraverse(child,(*dataFunction));
    }
    dataFunction(root->getData());

}

#endif