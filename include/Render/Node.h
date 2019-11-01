#pragma once
#include <string>
#include <vector>
#include <map>
#include <Core/Matrix4f.h>
#include <Core/Bound.h>
namespace vrv
{
	class Drawable;
   class Camera;
	class Node
	{
	public:
      typedef std::vector<Drawable*> DrawableList;
		typedef std::vector<Node*> ChildrenList;

	public:
		Node();

		Node(const std::string& name);

      virtual ~Node();

      void addDrawable(Drawable* drawable);

      int numberOfDrawable();

      Drawable* getDrawable(int i);

		void addChild(Node* child);

		void removeChild(Node* child);

		int numberOfChildren();

		Node* getChild(int i);

		Node* parent();

		void setParent(Node* parent);

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

      Bound bound();

      bool isCameraNode();
   protected:

      void calculateBound();

	protected:
		Node* myParent;
		ChildrenList myChildren;
      DrawableList myDrawables;
		std::string myName;
		Vector3f myPosition;
		Vector3f myScale;
		Matrix4f myRotation;
		bool myIsInstanced;
		bool myIsLightPoint;
		bool myIsEllipsoid;
      Bound myBound;
	};
}