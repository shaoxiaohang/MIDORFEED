#include <Core/Node.h>

namespace vrv
{
	Node::Node()
		: myParent(0)
		, myScale(1.0f)
	{}

	Node::Node(const std::string& name)
		: myName(name)
		, myParent(0)
		, myScale(1.0f)
	{}

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

	void Node::setPosition(Vector3f pos)
	{
		myPosition = pos;
	}

	Vector3f Node::position()
	{
		return myPosition;
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

	void Node::setScale(float scale)
	{
		myScale = scale;
	}

	float Node::scale()
	{
		return myScale;
	}

	Matrix4f Node::getModelMatrix()
	{
		return Matrix4f::makeTranslate(myPosition) * Matrix4f::makeScale(myScale,myScale,myScale);
	}
}