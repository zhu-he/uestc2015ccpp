#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

class Node
{
    public:
        Node(int _value);
        virtual ~Node();
        void append(Node *node);
        int count();
        int getValue();
        Node* getParent();
        void setParent(Node* node);
    protected:
    private:
        int value;
        Node* parent;
        std::vector<Node*> childNodes;
};

#include "Node.cpp"

#endif
