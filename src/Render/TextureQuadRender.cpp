#include <Render/TextureQuadRender.h>
#include <Render/Array.h>
#include <Render/Geometry.h>
#include <Render/RenderState.h>
#include <Render/StateSet.h>
#include <Render/Program.h>
#include <Render/Texture2D.h>

namespace vrv
{
	TextureQuadRender::TextureQuadRender()
	{
		initialize();
	}

	void TextureQuadRender::initialize()
	{
		ArrayVec2* pos = new ArrayVec2();
		pos->add(Vector2f(-1, 1));
		pos->add(Vector2f(-1, -1));
		pos->add(Vector2f(1, -1));
		pos->add(Vector2f(1, 1));

		ArrayVec2* st = new ArrayVec2();
		st->add(Vector2f(0, 1));
		st->add(Vector2f(0, 0));
		st->add(Vector2f(1, 0));
		st->add(Vector2f(1, 1));

		myQuadGeometry = new Geometry();
		myQuadGeometry->setVertex(pos);
		myQuadGeometry->setTextureCoordinate(st);
		myQuadGeometry->addPrimitiveSet(Drawable::QUADS,0, 4);

		myQuadGeometry->buildGeometry();

		RenderState* renderState = new RenderState();
		renderState->depthTest().setEnabled(false);

      myStateSet = new StateSet(renderState, new Program("../data/shader/defaultQuad.vert",
			"../data/shader/defaultQuad.frag"));
	}

	void TextureQuadRender::drawTexture(Texture2D* texture)
	{
		texture->bindToPoint(0);
      myStateSet->program()->set("scene", 0);

		myQuadGeometry->drawImplementation();

	}
}