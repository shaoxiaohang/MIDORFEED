#include <Core/Node.h>

namespace vrv
{
	Node::Node()
		: myParent(0)
	{

	}

	Node::Node(const std::string& name)
		: myName(name)
	{

	}

	void Node::addDrawable(Drawable* drawable)
	{
		myDrawables.push_back(drawable);
	}

	void Node::addChild(Node* child)
	{
		child->setParent(this);
		myChildren.push_back(child);
	}

	void Node::removeChild(Node* child)
	{
		ChildrenList::iterator itor = std::find(myChildren.begin(), myChildren.end(), child);
		if (itor != myChildren.end())
		{
			myChildren.erase(itor);
		}
	}

	unsigned int Node::numberOfChildren()
	{
		return myChildren.size();
	}

	Node* Node::getChild(unsigned int i)
	{
		return myChildren[i];
	}

	unsigned int Node::numberOfDrawable()
	{
		return myDrawables.size();
	}

	Drawable* Node::getDrawable(unsigned int i)
	{
		return myDrawables[i];
	}

	Node* Node::parent()
	{
		return myParent;
	}

	void Node::setParent(Node* parent)
	{
		if (myParent)
		{
			myParent->removeChild(this);
		}
		myParent = parent;
	}
}