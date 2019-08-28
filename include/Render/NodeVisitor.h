#pragma once
#include <stack>
namespace vrv
{
	class Node;
	class NodeVisitor
	{
	public:
		void run(Node*);
	protected:
		virtual void doSomething(Node*) = 0;
	};

   class ApplyRotationNodeVisitor : public NodeVisitor
   {
   public :
      ApplyRotationNodeVisitor();

      void setXRotation(float x);
      void setYRotation(float y);

   protected:
      virtual void doSomething(Node*);

      float myXRotation;
      float myYRotation;
   };
}