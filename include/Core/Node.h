#pragma once
#include <string>
#include <vector>
#include <map>
#include <Core/Matrix4.h>
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

		Vector3f position();

		void setScale(Vector3f scale);

		Vector3f scale();

		void setRotation(Matrix4f rotation);

		Matrix4f rotation();

		Matrix4f getModelMatrix();

		void setIsLightPoint(bool);
		bool isLightPoint();

		void setIsEllipsoid(bool);
		bool isEllipsoid();

	protected:
		Node* myParent;
		DrawableList myDrawables;
		ChildrenList myChildren;
		std::string myName;
		Vector3f myPosition;
		Vector3f myScale;
		Matrix4f myRotation;
		bool myIsInstanced;
		bool myIsLightPoint;
		bool myIsEllipsoid;
	};
}