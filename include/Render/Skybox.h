#pragma once
#include <string>
#include <vector>
namespace vrv
{
	class Texture3D;
	class Geometry;
	class RenderState;
	class Program;
	class SkyBox
	{
	public:
		SkyBox(const std::vector<std::string>& fileName);

	protected:
		void initialize();

	protected:
		Geometry* myCube;
		RenderState* myRenderState;
		Program* myProgram;
		std::vector<std::string> myFileNames;
		Texture3D* myCubeMap;
	};
}