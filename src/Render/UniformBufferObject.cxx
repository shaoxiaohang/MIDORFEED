#include <Render/UniformBufferObject.h>
#include <Render/QtContext.h>
#include <Render/Uniform.h>
namespace vrv
{
	UniformBufferObject::UniformBufferObject()
		: BufferObject(BufferObject::UNIFORM_BUFFER)
	{}

	void UniformBufferObject::bindToPoint(int point)
	{
		bind();
		QtContext::instance().glBindBufferBase(myGLType, point, myID);
		unbind();
	}

	void UniformBufferObject::addAutomaticUniform(AutomaticUniform* uniform)
	{
		myUniforms.push_back(uniform);
	}

	void UniformBufferObject::build()
	{
		int totalSize = 0;
		for (int i = 0; i < myUniforms.size(); ++i)
		{
			totalSize += myUniforms[i]->uniform()->size();
		}

		bind();
		bufferData(totalSize, 0);
		unbind();
	}

	void UniformBufferObject::update()
	{
		bind();
		int offset = 0;
		for (int i = 0; i < myUniforms.size(); ++i)
		{
			AutomaticUniform* automaticUniform = myUniforms[i];
			automaticUniform->update();
			Uniform* uniform = automaticUniform->uniform();
			bufferSubData(offset, uniform->size(), uniform->dataPointer());
			offset += uniform->size();
		}
		unbind();
	}
}