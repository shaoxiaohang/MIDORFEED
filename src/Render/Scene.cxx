#include <Render/Scene.h>
#include <Render/Drawable.h>
#include <Render/Program.h>
#include <Render/ClearState.h>
#include <Render/Camera.h>
#include <Render/DrawState.h>
#include <Render/Light.h>
#include <Render/Material.h>
#include <Render/Texture2D.h>
#include <Render/Texture3D.h>
#include <Render/QtContext.h>
#include <Render/ShaderManager.h>
#include <Render/RenderState.h>
#include <Render/FrameBuffer.h>
#include <Render/PostProcessorManager.h>
#include <Render/Skybox.h>
#include <Render/Model.h>
#include <Core/Node.h>
#include <Core/Utility.h>
#include <Core/NodeVisitor.h>
#include <Render/MainWindow.h>
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
			Vector3f positionA = a.myModelMatrix.getTranslation();
			Vector3f positionB = b.myModelMatrix.getTranslation();
			float distanceA = positionA.distanceSquare(myCameraPosition);
			float distanceB = positionB.distanceSquare(myCameraPosition);
			return distanceA > distanceB;
		}

		Vector3f myCameraPosition;
	};


	RenderInfo::RenderInfo(Drawable* _drawable, Matrix4f _modelMatrix)
		: myDrawable(_drawable)
		, myModelMatrix(_modelMatrix)
	{}

	RenderQueue::RenderQueue()
	{}

	void RenderQueue::draw(Scene* scene, DrawState* drawState, Camera* camera)
	{
		Program* program = drawState->program();
		scene->updateProgram(program);

		//draw opaque list first 
		RenderList::iterator itor = myOpaqueList.begin();
		RenderList::iterator end = myOpaqueList.end();
		for (; itor != end; ++itor)
		{
			draw(*itor, drawState);
		}

		//sort the transparent list from back to front
		sortTransparentList(camera);
		itor = myTransparentList.begin();
		end = myTransparentList.end();
		for (; itor != end; ++itor)
		{
			draw(*itor, drawState);
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

	void RenderQueue::draw(RenderInfo& renderInfo, DrawState* drawState)
	{
		Program* program = drawState->program();
		program->set("vrv_model_matrix", renderInfo.myModelMatrix);
		renderInfo.myDrawable->updateProgram(program);
		renderInfo.myDrawable->drawImplementation(drawState);
	}

	Scene::Scene(MainWindow* window)
		: myRoot(0)
		, myVisualizeDepthBuffer(false)
		, myOptimizeVisualizeDepthBuffer(true)
		, myOutlineObjects(false)
		, myOutlineWidth(1.2)
		, myEnableDepthTest(true)
		, myMainWindow(window)
		, myPostEffectType(0)
		, mySkybox(0)
	{
		myShaderManager = new ShaderManager();
		myMasterCamera = new Camera();
		initializeDrawState();
		myPostProcessorManager = new PostProcessorManager(myMainWindow->width(),myMainWindow->height());
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
		if (myRoot)
		{	
			cullTraverse();

			//myPostProcessorManager->bind();

			QtContext::instance().glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			QtContext::instance().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			myRenderQueue.draw(this, myPhoneLightingDrawState, myMasterCamera);

			//unbind the sky box cube map
			QtContext::instance().glActiveTexture(GL_TEXTURE2);
			QtContext::instance().glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			if (mySkybox)
			{
				mySkybox->draw();
			}

			//myPostProcessorManager->run();
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
			Drawable* drawable = node->getDrawable(i);
			Material* material = drawable->material();
			Model* model = dynamic_cast<Model*>(drawable);
			bool isTransParent = material && material->isTransParent();

			if (model)
			{
				for (int i = 0; i < model->numberOfMeshes(); ++ i)
				{
					Geometry* mesh = model->getMesh(i);
					mesh->buildGeometryIfNeeded();
					if (isTransParent)
					{
						myRenderQueue.addToTransparentList(RenderInfo(mesh, node->getModelMatrix()));
					}
					else
					{
						myRenderQueue.addToOpaqueList(RenderInfo(mesh, node->getModelMatrix()));
					}
				}
			}
			else
			{
				drawable->buildGeometryIfNeeded();
				if (isTransParent)
				{
					myRenderQueue.addToTransparentList(RenderInfo(drawable, node->getModelMatrix()));
				}
				else
				{
					myRenderQueue.addToOpaqueList(RenderInfo(node->getDrawable(i), node->getModelMatrix()));
				}
			}
		
		}
	}

	void Scene::updateLights(Program* program)
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
				if (program->getUniform(lightName + "used"))
				{
					program->getUniform(lightName + "used")->set(true);
				}
				if (program->getUniform(lightName + "type"))
				{
					program->getUniform(lightName + "type")->set(light->type());
				}
				if (program->getUniform(lightName + "ambient"))
				{
					program->getUniform(lightName + "ambient")->set(light->ambient());
				}
				if (program->getUniform(lightName + "diffuse"))
				{
					program->getUniform(lightName + "diffuse")->set(light->diffuse());
				}
				if (program->getUniform(lightName + "specular"))
				{
					program->getUniform(lightName + "specular")->set(light->specular());
				}
				
				switch (light->type())
				{
				case Light::DirectionalLight:
					if (program->getUniform(lightName + "direction"))
					{
						program->getUniform(lightName + "direction")->set(light->direction());
					}				
					break;
				case Light::PointLight:
					if (program->getUniform(lightName + "position"))
					{
						program->getUniform(lightName + "position")->set(light->position());
					}
					if (program->getUniform(lightName + "constant"))
					{
						program->getUniform(lightName + "constant")->set(light->constantTerm());
					}
					if (program->getUniform(lightName + "linear"))
					{
						program->getUniform(lightName + "linear")->set(light->linearTerm());
					}
					
					if (program->getUniform(lightName + "quadratic"))
					{
						program->getUniform(lightName + "quadratic")->set(light->quadraticTerm());
					}
				
					break;
				case Light::SpotLight:
					if (program->getUniform(lightName + "position"))
					{
						program->getUniform(lightName + "position")->set(light->position());
					}
					if (program->getUniform(lightName + "constant"))
					{
						program->getUniform(lightName + "constant")->set(light->constantTerm());
					}
					if (program->getUniform(lightName + "linear"))
					{
						program->getUniform(lightName + "linear")->set(light->linearTerm());
					}
					if (program->getUniform(lightName + "fade"))
					{
						program->getUniform(lightName + "fade")->set(Utility::cos(light->fadeAngle()));
					}
					if (program->getUniform(lightName + "cutoff"))
					{
						program->getUniform(lightName + "cutoff")->set(Utility::cos(light->cutoffAngle()));
					}
					
					break;
				default:
					break;
				}

			}
		}

	}

	void Scene::initializeDrawState()
	{
		myPhoneLightingDrawState = new DrawState(new RenderState(), ShaderManager::instance().
			getProgram(ShaderManager::PhoneLighting));
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
		}
	}

	void Scene::setPostEffectType(int type)
	{
		myPostEffectType = type;
	}

	int Scene::postEffectType()
	{
		return myPostEffectType;
	}

	void Scene::setSkybox(Skybox* skybox)
	{
		mySkybox = skybox;
	}

	Skybox* Scene::skybox()
	{
		return mySkybox;
	}

	void Scene::visualizeNormal(bool b)
	{
		myVisualizeNormal = b;
	}

	void Scene::updateProgram(Program* program)
	{
		if (mySkybox)
		{
			mySkybox->cubeMap()->bindToPoint(2);
			if (program->getUniform("skybox"))
			{
				program->getUniform("skybox")->set(2);
			}
		}
		updateLights(program);
	}
}