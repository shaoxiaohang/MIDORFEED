#include <Core/NodeVisitor.h>
#include <Core/Node.h>
namespace vrv
{
	void NodeVisitor::run(Node* root)
	{
		std::stack<Node*> stack;
		stack.push(root);
		DFSSearch(stack, root);
	}

	void NodeVisitor::DFSSearch(std::stack<Node*>& stack, Node* node)
	{
		doSomething(node);
		stack.pop();
		for (size_t i = 0; i < node->numberOfChildren(); ++i)
		{
			Node* child = node->getChild(i);
			stack.push(child);
			DFSSearch(stack, child);
		}
	}
}