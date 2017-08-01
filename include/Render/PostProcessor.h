#pragma once

#include <string>

namespace vrv
{
	class Node;

	class PostProcessor
	{
	public:
		PostProcessor(std::string name);
		virtual void run(Node* root) = 0;
	protected:
		std::string myName;
	};

	class OutlinePostProcessor : PostProcessor
	{
	public:
		OutlinePostProcessor();
		void run(Node* root);
	};
}