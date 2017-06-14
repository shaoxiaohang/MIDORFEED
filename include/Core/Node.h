#pragma once
#include <string>
#include <vector>
#include <Core/Vector3.h>
#include <Core/Vector4.h>
namespace vrv
{
	class Drawable;
	class Node
	{
	public:
		typedef std::vector<Node*> ChildrenList;
		typedef std::vector<Drawable*> DrawableList;
	public:
		Node();
		Node(const std::string& name);
	
		void addChild(Node* child);
		void removeChild(Node* child);
		unsigned int numberOfChildren();
		Node* getChild(unsigned int i);
		Node* parent();
		void setParent(Node* parent);
		void addDrawable(Drawable* drawable);
		unsigned int numberOfDrawable();
		Drawable* getDrawable(unsigned int i);
		void setPosition(Vector3f pos);
		void setColor(Vector4f color);
		Vector3f position();
		Vector4f color();
		bool useColor();
	protected:
		Node* myParent;
		DrawableList myDrawables;
		ChildrenList myChildren;
		std::string myName;
		bool myUseColor;
		Vector3f myPosition;
		Vector4f myColor;
	};
}