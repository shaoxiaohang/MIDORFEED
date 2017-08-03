#include <Render/Scene.h>
#include <Render/Drawable.h>
#include <Render/Program.h>
#include <Render/Context.h>
#include <Render/ClearState.h>
#include <Render/Camera.h>
#include <Render/DrawState.h>
#include <Render/Light.h>
#include <Render/Material.h>
#include <Render/Texture.h>
#include <Render/Mesh.h>
#include <Render/QtContext.h>
#include <Render/ShaderManager.h>
#include <Render/RenderState.h>
#include <Core/Node.h>
#include <Core/Utility.h>
#include <Core/NodeVisitor.h>
#include <algorithm>
#include <sstream>

#ifdef DrawState
#undef DrawState
#endif // DrawState

#define VRV_MAX_NUM_LIGHTS 4
namespace vrv
{
	Scene* Scene::myInstance = 0;

	RenderInfo::RenderInfo(Drawable* _drawable, Matrix4f _modelMatrix, Material* _material)
		: drawable(_drawable)
		, modelMatrix(_modelMatrix)
		, material(_material)
	{}

	void RenderInfo::update(Program* program)
	{
		if (program)
		{
			program->getUniform("vrv_model_matrix")->set(modelMatrix);
			if (material)
			{
				Texture* diffuse = material->getTexture(Material::Material_Diffuse);
				if (diffuse)
				{
					QtContext::instance().glActiveTexture(GL_TEXTURE0 + Material::Material_Diffuse);
					QtContext::instance().glBindTexture(GL_TEXTURE_2D, diffuse->id());
				}
				Texture* specular = material->getTexture(Material::Material_Specular);
				if (specular)
				{
					QtContext::instance().glActiveTexture(GL_TEXTURE0 + Material::Material_Specular);
					QtContext::instance().glBindTexture(GL_TEXTURE_2D, specular->id());
				}


				if (program->getUniform("vrv_material.hasDiffuse"))
				{
					program->getUniform("vrv_material.hasDiffuse")->set(material->hasDiffuse());
				}
				if (program->getUniform("vrv_material.hasSpecular"))
				{
					program->getUniform("vrv_material.hasSpecular")->set(material->hasSpecular());
				}
				if (program->getUniform("vrv_material.diffuse_tex"))
				{
					program->getUniform("vrv_material.diffuse_tex")->set(Material::Material_Diffuse);
				}
				if (program->getUniform("vrv_material.specular_tex"))
				{
					program->getUniform("vrv_material.specular_tex")->set(Material::Material_Specular);
				}
				if (program->getUniform("vrv_material.ambient"))
				{
					program->getUniform("vrv_material.ambient")->set(material->ambient());
				}
				if (program->getUniform("vrv_material.diffuse"))
				{
					program->getUniform("vrv_material.diffuse")->set(material->diffuse());
				}

				if (program->getUniform("vrv_material.specular"))
				{
					program->getUniform("vrv_material.specular")->set(material->specular());
				}
				if (program->getUniform("vrv_material.shininess"))
				{
					program->getUniform("vrv_material.shininess")->set(material->shininess());
				}
			}
		}
	}

	bool RenderInfo::SortDrawable::operator()(const RenderInfo& left, const RenderInfo& right)
	{
		if (left.drawable->drawState() && right.drawable->drawState())
		{
			return *(left.drawable->drawState()) < *(right.drawable->drawState());
		}
		return true;
	}

	Scene::Scene(Context* context)
		: myContext(context)
		, myRoot(0)
		, myVisualizeDepthBuffer(false)
		, myOptimizeVisualizeDepthBuffer(true)
		, myOutlineObjects(false)
		, myOutlineWidth(1.2)
		, myOutlineRenderState(0)
		, myPhoneLightingRenderState(0)
		, myEnableDepthTest(true)
	{
		myContext->setScene(this);
		myClearState = new ClearState();
		myMasterCamera = new Camera();
		myOutlineRenderState = new RenderState();
		myOutlineRenderState->stencilTest().setStencilRef(1);
		myOutlineRenderState->stencilTest().setStencilFucntion(StencilTest::STENCIL_FUNC_LEQUAL);
		myOutlineRenderState->stencilTest().setStencilWriteMask(0x00);
		myOutlineRenderState->depthTest().setEnabled(false);
		myPhoneLightingRenderState = new RenderState();
	}

	void Scene::setSceneData(Node* root)
	{
		myRoot = root;
	}

	void Scene::cullTraverse()
	{
		myRenderlist.clear();
		std::stack<Node*> DFSStack;
		DFSStack.push(myRoot);
		DFS(DFSStack, myRoot);
	}

	void Scene::DFS(std::stack<Node*>& stack, Node* node)
	{
		addDrawableToRender(node);
		stack.pop();
		for (unsigned int i = 0; i < node->numberOfChildren(); ++i)
		{
			Node* child = node->getChild(i);
			stack.push(child);
			DFS(stack, child);
		}
	}

	void Scene::renderScene()
	{
		myContext->clear(myClearState);
		if (myRoot)
		{
			updateLights();
			cullTraverse();
			//std::sort(myRenderlist.begin(), myRenderlist.end(), RenderInfo::SortDrawable());
			RenderList::iterator itor = myRenderlist.begin();
			RenderList::iterator end = myRenderlist.end();

			for (; itor != end; ++itor)
			{
				RenderInfo& info = *itor;
				Drawable* drawable = info.drawable;
				if (myVisualizeDepthBuffer)
				{
					drawable->drawState()->setProgram(ShaderManager::instance().getProgram(ShaderManager::VisualizeDepthBuffer));
				}
				else
				{
					drawable->drawState()->setProgram(ShaderManager::instance().getProgram(ShaderManager::PhoneLighting));
				}
				
				drawable->drawState()->setRenderState(myPhoneLightingRenderState);
			}

			draw();
			
			if (myOutlineObjects)
			{
				RenderList::iterator itor = myRenderlist.begin();
				RenderList::iterator end = myRenderlist.end();

				for (; itor != end; ++itor)
				{
					RenderInfo& info = *itor;
					Drawable* drawable = info.drawable;
					drawable->drawState()->setProgram(ShaderManager::instance().getProgram(ShaderManager::NoLighting));
					drawable->drawState()->setRenderState(myOutlineRenderState);
					info.modelMatrix.scale(myOutlineWidth);
				}
				draw();
			}
		}
	}

	void Scene::draw()
	{
		RenderList::iterator itor = myRenderlist.begin();
		RenderList::iterator end = myRenderlist.end();
		for (; itor != end; ++itor)
		{
			myContext->draw(*itor);
		}
	}

	Camera* Scene::masterCamera()
	{
		return myMasterCamera;
	}

	void Scene::addDrawableToRender(Node* node)
	{
		unsigned int numOfDrawables = node->numberOfDrawable();
		for (unsigned int i = 0; i < numOfDrawables; ++i)
		{
			Mesh* mesh = dynamic_cast<Mesh*>(node->getDrawable(i));
			Material* material = 0;
			if (mesh)
			{
				material = mesh->material();
			}
			node->getDrawable(i)->buildGeometryIfNeeded(material);
			myRenderlist.push_back(RenderInfo(node->getDrawable(i), node->getModelMatrix(), material));
		}
	}

	void Scene::updateLights()
	{
		if (myLights.size() > 0)
		{
			int numOfLights = myLights.size();
			for (int i = 0; i < numOfLights; ++i)
			{
				std::stringstream ss;
				ss << "vrv_lights[" << i << "].";
				std::string lightName = ss.str();
				Light* light = myLights[i];
				Program* phoneLighting = ShaderManager::instance().getProgram(ShaderManager::PhoneLighting);
				phoneLighting->getUniform(lightName + "used")->set(true);
				phoneLighting->getUniform(lightName + "type")->set(light->type());
				phoneLighting->getUniform(lightName + "ambient")->set(light->ambient());
				phoneLighting->getUniform(lightName + "diffuse")->set(light->diffuse());
				phoneLighting->getUniform(lightName + "specular")->set(light->specular());
				switch (light->type())
				{
				case Light::DirectionalLight:
					phoneLighting->getUniform(lightName + "direction")->set(light->direction());
					break;
				case Light::PointLight:
					phoneLighting->getUniform(lightName + "position")->set(light->position());
					phoneLighting->getUniform(lightName + "constant")->set(light->constantTerm());
					phoneLighting->getUniform(lightName + "linear")->set(light->linearTerm());
					phoneLighting->getUniform(lightName + "quadratic")->set(light->quadraticTerm());
					break;
				case Light::SpotLight:
					phoneLighting->getUniform(lightName + "position")->set(light->position());
					phoneLighting->getUniform(lightName + "constant")->set(light->constantTerm());
					phoneLighting->getUniform(lightName + "linear")->set(light->linearTerm());
					phoneLighting->getUniform(lightName + "fade")->set(Utility::cos(light->fadeAngle()));
					phoneLighting->getUniform(lightName + "cutoff")->set(Utility::cos(light->cutoffAngle()));
					break;
				default:
					break;
				}

			}
		}

	}

	void Scene::addLight(Light* light)
	{
		if (light != NULL)
		{
			myLights.push_back(light);
		}
	}

	Node* Scene::root()
	{
		return myRoot;
	}

	void Scene::setVisualizeDepthBuffer(bool visualize)
	{
		if (myVisualizeDepthBuffer != visualize)
		{
			myVisualizeDepthBuffer = visualize;
		}

	}

	void Scene::setOptimizeVisualizeDepthBuffer(bool optimize)
	{
		if (ShaderManager::instance().getProgram(ShaderManager::VisualizeDepthBuffer)->
			getUniform("optimizeVisualizeDepth"))
		{
			ShaderManager::instance().getProgram(ShaderManager::VisualizeDepthBuffer)->
				getUniform("optimizeVisualizeDepth")->set(optimize);
		}
	}

	void Scene::setOutlineObjects(bool value)
	{
		myOutlineObjects = value;
	}

	void Scene::setOutlineWidth(double value)
	{
		myOutlineWidth = value;
	}

	void Scene::enableDepthTest(bool value)
	{
		if (myEnableDepthTest != value)
		{
			myEnableDepthTest = value;
			myPhoneLightingRenderState->depthTest().setEnabled(myEnableDepthTest);
		}

	}
}