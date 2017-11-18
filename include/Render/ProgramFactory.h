#pragma once

#include <string>
namespace vrv
{
	class Program;
 	class ProgramFactory
	{
	public:
		ProgramFactory(int);
		int type();
		virtual Program* createProgram() = 0;
	protected:
		int myType;
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

	class DefaultQuadProgramFactory : public ProgramFactory
	{
	public:
		DefaultQuadProgramFactory();
		Program* createProgram();
	};

	class ConfigurablePostEffectProgramFactory : public ProgramFactory
	{
	public:
		ConfigurablePostEffectProgramFactory();
		Program* createProgram();
	};
}