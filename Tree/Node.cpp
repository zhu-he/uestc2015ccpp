#include "Node.h"

Node::Node(int _value)
{
    value = _value;
}

Node::~Node()
{

}

void Node::append(Node *node)
{
    childNodes.push_back(node);
    node->setParent(this);
}

int Node::count()
{
    int rnt = 1;
    for (std::vector<Node*>::iterator i = childNodes.begin(); i != childNodes.end(); ++i)
    {
        rnt += (*i)->count();
    }
    return rnt;
}

int Node::getValue()
{
    return value;
}

Node* Node::getParent()
{
    return parent;
}

void Node::setParent(Node* node)
{
    parent = node;
}
