#pragma once

#include <string>
namespace vrv
{
	class Program;
 	class ProgramFactory
	{
	public:
		ProgramFactory(const std::string& name);
		const std::string name();
		virtual Program* createProgram() = 0;
	protected:
		const std::string myName;
	};

	class PhoneLightingProgramFactory : public ProgramFactory
	{
	public:
		PhoneLightingProgramFactory();
		Program* createProgram();
	};

	class VisualizeDepthBufferProgramFactory : public ProgramFactory
	{
	public:
		VisualizeDepthBufferProgramFactory();
		Program* createProgram();
	};

	class OutlineObjectsProgramFactory : public ProgramFactory
	{
	public:
		OutlineObjectsProgramFactory();
		Program* createProgram();
	};
}