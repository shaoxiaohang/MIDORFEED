#pragma once
#include <string>
#include <vector>
namespace vrv
{
	class Texture3D;
	class Geometry;
	class RenderState;
	class DrawState;
	class Program;
	class Skybox
	{
	public:
		Skybox(const std::vector<std::string>& fileName);

		void draw();

		Texture3D* cubeMap();

	protected:
		void initialize();

	protected:
		Geometry* myCube;
		DrawState* myDrawState;
		std::vector<std::string> myFileNames;
		Texture3D* myCubeMap;
	};
}