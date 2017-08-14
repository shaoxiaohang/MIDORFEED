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

	struct SortbyCamera
	{
		SortbyCamera(Vector3f camera)
		{
			myCameraPosition = camera;
		}
		bool operator()(RenderInfo const & a, RenderInfo const & b) const
		{
			Vector3f positionA = a.modelMatrix.getTranslation();
			Vector3f positionB = b.modelMatrix.getTranslation();
			float distanceA = positionA.distanceSquare(myCameraPosition);
			float distanceB = positionB.distanceSquare(myCameraPosition);
			return distanceA > distanceB;
		}

		Vector3f myCameraPosition;
	};


	RenderInfo::RenderInfo(Drawable* _drawable, Matrix4f _modelMatrix, Material* _material)
		: drawable(_drawable)
		, modelMatrix(_modelMatrix)
		, material(_material)
	{}

	RenderQueue::RenderQueue()
		: myModifiedRenderState(0)
		, myModifiedProgram(0)
	{}

	void RenderQueue::draw(Context* context, Camera* camera)
	{
		//draw opaque list first 
		//std::sort(myOpaqueList.begin(), myOpaqueList.end(), RenderInfo::SortDrawable());
		RenderList::iterator itor = myOpaqueList.begin();
		RenderList::iterator end = myOpaqueList.end();
		for (; itor != end; ++itor)
		{
			RenderInfo& info = *itor;
			Drawable* drawable = info.drawable;
			if (myModifiedProgram)
			{
				drawable->drawState()->setProgram(myModifiedProgram);
			}
			if (myModifiedRenderState)
			{
				drawable->drawState()->setRenderState(myModifiedRenderState);
			}
			context->draw(*itor);
		}

		//sort the transparent list from back to front
		sortTransparentList(camera);
		//std::sort(myTransparentList.begin(), myTransparentList.end(), RenderInfo::SortDrawable());
		itor = myTransparentList.begin();
		end = myTransparentList.end();
		for (; itor != end; ++itor)
		{
			RenderInfo& info = *itor;
			Drawable* drawable = info.drawable;
			if (myModifiedProgram)
			{
				drawable->drawState()->setProgram(myModifiedProgram);
			}
			if (myModifiedRenderState)
			{
				drawable->drawState()->setRenderState(myModifiedRenderState);
			}
			context->draw(*itor);
		}

	}

	void RenderQueue::sortTransparentList(Camera* camera)
	{
		Vector3f cameraPosition = camera->position();
		SortbyCamera sort(cameraPosition);
		std::sort(myTransparentList.begin(), myTransparentList.end(), sort);
	}

	void RenderQueue::addToOpaqueList(const RenderInfo& info)
	{
		myOpaqueList.push_back(info);
	}

	void RenderQueue::addToTransparentList(const RenderInfo& info)
	{
		myTransparentList.push_back(info);
	}

	void RenderQueue::clear()
	{
		myOpaqueList.clear();
		myTransparentList.clear();
	}

	void RenderQueue::modifyProgram(Program* program)
	{
		myModifiedProgram = program;
	}

	void RenderQueue::modifyRenderState(RenderState* renderState)
	{
		myModifiedRenderState = renderState;
	}

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

				if (program->getUniform("vrv_discardAlpha"))
				{
					program->getUniform("vrv_discardAlpha")->set(material->discardAlpha());
				}

				if (program->getUniform("vrv_discardAlphaThreshold"))
				{
					program->getUniform("vrv_discardAlphaThreshold")->set(material->discardAlphaThreshold());
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
		myRenderQueue.clear();
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
			if (myVisualizeDepthBuffer)
			{
				myRenderQueue.modifyProgram(ShaderManager::instance()
					.getProgram(ShaderManager::VisualizeDepthBuffer));
			}
			else
			{
				myRenderQueue.modifyProgram(ShaderManager::instance()
					.getProgram(ShaderManager::PhoneLighting));
			}
			myRenderQueue.modifyRenderState(myPhoneLightingRenderState);
			myRenderQueue.draw(myContext, myMasterCamera);

			if (myOutlineObjects)
			{
				myRenderQueue.modifyProgram(ShaderManager::instance()
					.getProgram(ShaderManager::NoLighting));
				myRenderQueue.modifyRenderState(myOutlineRenderState);
				myRenderQueue.draw(myContext, myMasterCamera);
			}
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
			if (material && material->isTransParent())
			{
				myRenderQueue.addToTransparentList(RenderInfo(node->getDrawable(i), node->getModelMatrix(), material));
			}
			else
			{
				myRenderQueue.addToOpaqueList(RenderInfo(node->getDrawable(i), node->getModelMatrix(), material));
			}

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