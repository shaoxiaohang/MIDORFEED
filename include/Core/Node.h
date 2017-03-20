#pragma once
#include<string>
#include<vector>
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
	protected:
		Node* myParent;
		DrawableList myDrawables;
		ChildrenList myChildren;
		std::string myName;
	};
}