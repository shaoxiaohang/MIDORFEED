#include <Render/Node.h>

namespace vrv
{
	Node::Node()
		: myParent(0)
		, myScale(1.0f)
		, myIsLightPoint(false)
		, myIsEllipsoid(false)
	{}

	Node::Node(const std::string& name)
		: myName(name)
		, myParent(0)
		, myScale(1.0f)
		, myIsLightPoint(false)
		, myIsEllipsoid(false)
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

	void Node::setScale(Vector3f scale)
	{
		myScale = scale;
	}

	Vector3f Node::scale()
	{
		return myScale;
	}

	void Node::setRotation(Matrix4f rotation)
	{
		myRotation = rotation;
	}

	Matrix4f Node::rotation()
	{
		return myRotation;
	}

	Matrix4f Node::getModelMatrix()
	{
		return Matrix4f::makeTranslate(myPosition) * myRotation * Matrix4f::makeScale(myScale.x(), myScale.y(), myScale.z());
	}

	void Node::setIsLightPoint(bool val)
	{
		myIsLightPoint = val;
	}

	bool Node::isLightPoint()
	{
		return myIsLightPoint;
	}

	void Node::setIsEllipsoid(bool val)
	{
		myIsEllipsoid = val;
	}

	bool Node::isEllipsoid()
	{
		return myIsEllipsoid;
	}

   void Node::calculateBound()
   {
      float min = FLT_MAX;
      float max = 0;
   }
}