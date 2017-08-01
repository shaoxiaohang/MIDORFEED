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
		void DFSSearch(std::stack<Node*>& stack, Node*);
	};
}