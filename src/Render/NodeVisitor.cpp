#include <Render/NodeVisitor.h>
#include <Render/Node.h>
namespace vrv
{
	void NodeVisitor::run(Node* root)
	{
      if (root)
         doSomething(root);

      for (size_t i = 0; i < root->numberOfChildren(); ++i)
      {
         run(root->getChild(i));
      }
	}

   ApplyRotationNodeVisitor::ApplyRotationNodeVisitor()
      : myXRotation(0)
      , myYRotation(0)
   {

   }

   void ApplyRotationNodeVisitor::setXRotation(float x)
   {
      myXRotation = x;
   }

   void ApplyRotationNodeVisitor::setYRotation(float y)
   {
      myYRotation = y;
   }

   void ApplyRotationNodeVisitor::doSomething(Node* node)
   {
      if (node)
      {
         node->setRotation(Matrix4f::makeRotateX(myXRotation)*Matrix4f::makeRotateY(myYRotation)* node->rotation());
      }
   }
}