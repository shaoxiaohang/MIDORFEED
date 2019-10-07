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
#include <Render/RenderState.h>
#include <Render/FrameBuffer.h>
#include <Render/PostProcessorManager.h>
#include <Render/Primitives.h>
#include <Render/Skybox.h>
#include <Render/Model.h>
#include <Render/Node.h>
#include <Core/Utility.h>
#include <Render/NodeVisitor.h>
#include <Render/ShadowSystem.h>
#include <Render/TextureQuadRender.h>
#include <Render/Map.h>
#include <Render/MainWindow.h>
#include <Render/OpenGLContext.h>
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


	RenderInfo::RenderInfo(Drawable* _drawable, Matrix4f _modelMatrix, bool isLightPoint, bool isEllipsoid)
		: myDrawable(_drawable)
		, myModelMatrix(_modelMatrix)
		, myIsLightPoint(isLightPoint)
		, myIsEllipsoid(isEllipsoid)
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
			updateModelMatrix(*itor, program);
			updateMaterial(*itor, program);
			draw(*itor, drawState);
		}

		//sort the transparent list from back to front
		sortTransparentList(camera);
		itor = myTransparentList.begin();
		end = myTransparentList.end();
		for (; itor != end; ++itor)
		{
			updateModelMatrix(*itor, program);
			updateMaterial(*itor, program);
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
		renderInfo.myDrawable->drawImplementation(drawState);
	}

	void RenderQueue::updateModelMatrix(RenderInfo& renderInfo, Program* program)
	{
		program->set("vrv_model_matrix", renderInfo.myModelMatrix);
		program->set("isLightPoint", renderInfo.myIsLightPoint);
		program->set("isEllipsoid", renderInfo.myIsEllipsoid);
	}

	void RenderQueue::updateMaterial(RenderInfo& renderInfo, Program* program)
	{
		renderInfo.myDrawable->updateProgram(program);
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
		, myPostProcessorManager(0)
		, myMap(0)
	{
		myMasterCamera = new Camera();
		initializeDrawState();
		myPostProcessorManager = new PostProcessorManager(myMainWindow->width(), myMainWindow->height());
		myShadowSystem = new ShadowSystem();
		myShadowSystem->initializeFrameBuffer(window->width(), window->height());
		myTextureQuadRender = new TextureQuadRender();
		myLightNode = new Node();
      myGuiNode = new Node();
	}

	void Scene::setSceneData(Node* root)
	{
		myRoot = root;
		myRoot->addChild(myLightNode);
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
		for (int i = 0; i < node->numberOfChildren(); ++i)
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
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			cullTraverse();

			//myShadowSystem->run(&myRenderQueue);

			//myPostProcessorManager->bind();

			//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			myRenderQueue.draw(this, myPhoneLightingDrawState, myMasterCamera);

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
				for (int i = 0; i < model->numberOfMeshes(); ++i)
				{
					Geometry* mesh = model->getMesh(i);
					mesh->buildGeometryIfNeeded();
					if (isTransParent)
					{
						myRenderQueue.addToTransparentList(RenderInfo(mesh, node->getModelMatrix(),
							node->isLightPoint(), node->isEllipsoid()));
					}
					else
					{
						myRenderQueue.addToOpaqueList(RenderInfo(mesh, node->getModelMatrix(), 
							node->isLightPoint(), node->isEllipsoid()));
					}
				}
			}
			else
			{
				drawable->buildGeometryIfNeeded();
				if (isTransParent)
				{
					myRenderQueue.addToTransparentList(RenderInfo(drawable, node->getModelMatrix()
						, node->isLightPoint(), node->isEllipsoid()));
				}
				else
				{
					myRenderQueue.addToOpaqueList(RenderInfo(node->getDrawable(i), node->getModelMatrix(), 
						node->isLightPoint(), node->isEllipsoid()));
				}
			}

		}
	}

	void Scene::updateSkybox(Program* program)
	{
		if (mySkybox)
		{
			mySkybox->cubeMap()->bindToPoint(6);
			program->set("skybox", 6);
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

				program->set(lightName + "used", true);
				program->set(lightName + "castShadow", light->castShadow());
				program->set(lightName + "type", light->type());
				program->set(lightName + "ambient", light->ambient());
				program->set(lightName + "diffuse", light->diffuse());
				program->set(lightName + "specular", light->specular());

				switch (light->type())
				{
				case Light::DirectionalLight:
					program->set(lightName + "direction", light->direction());
					break;
				case Light::PointLight:
					program->set(lightName + "position", light->position());
					program->set(lightName + "constant", light->constantTerm());
					program->set(lightName + "linear", light->linearTerm());
					program->set(lightName + "quadratic", light->quadraticTerm());
					break;
				case Light::SpotLight:
					program->set(lightName + "position", light->position());
					program->set(lightName + "constant", light->constantTerm());
					program->set(lightName + "linear", light->linearTerm());
					program->set(lightName + "quadratic", light->quadraticTerm());
					program->set(lightName + "fade", Utility::cos(light->fadeAngle()));
					program->set(lightName + "cutoff", Utility::cos(light->cutoffAngle()));
					break;
				default:
					break;
				}

			}
		}

	}

	void Scene::updateShadow(Program* program)
	{
		if (myShadowSystem->shadowCaster())
		{
			program->set("shadow_matrix", myShadowSystem->shadowCaster()->shadowMatrix());
			myShadowSystem->shadowTexture()->bindToPoint(7);
			program->set("shadowMap", 7);
		}
	}

	void Scene::updateGlobe(Program* program)
	{
      if (myMap)
      {
         static std::vector<int> grids = { 0, 1000000, 2000000, 20000000 };
         static std::vector<double> res = { 0.005, 0.01, 0.05, 0.1 };

         double height = myMap->height(myMasterCamera->position());

         int interval = 0;

         for (int i = 0; i < 3; ++i)
         {
            if (height < grids[i + 1])
            {
               interval = i;
               break;
            }
            else
            {
               if (i == 2)
               {
                  interval = 3;
               }
            }
         }

         Vector2f resolution = Vector2f(res[interval], res[interval]);

         program->set("grid_width", Vector2f(1, 1));
         program->set("grid_resolution", resolution);
      }
	}

	void Scene::initializeDrawState()
	{
		myPhoneLightingDrawState = new DrawState(new RenderState(), new Program("../data/shader/phoneLighting.vert",
			"../data/shader/phoneLighting.frag"));
	}

	void Scene::addLight(Light* light)
	{
		if (light != NULL)
		{
			myLights.push_back(light);
			if (light->castShadow())
			{
				myShadowSystem->setShadowCaster(light);
			}
			Node* lightNode = new Node();
			lightNode->setIsLightPoint(true);
			Cube* cube = new Cube();
			Material* material = new Material();
			material->setAmbient(Vector4f(light->ambient(), 1.0f));
			material->setDiffuse(Vector4f(light->diffuse(), 1.0f)); 
			material->setSpecular(Vector4f(light->specular(), 10.f));
			lightNode->setPosition(light->position());
			cube->setMaterial(material);
			lightNode->setScale(Vector3f(0.3f, 0.3f, 0.3f));
			lightNode->addDrawable(cube);
			myLightNode->addChild(lightNode);
		}
	}

	Node* Scene::root()
	{
		return myRoot;
	}

   Node* Scene::guiRoot()
   {
      return myGuiNode;
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
		updateSkybox(program);
		updateLights(program);
		updateShadow(program);
		updateGlobe(program);
	}

	void Scene::setMap(Map* map)
	{
		myMap = map;
	}

	Map* Scene::map()
	{
		return myMap;
	}

   void Scene::acceptNodeVisitor(NodeVisitor* v)
   {
      if (v && myRoot)
         v->run(myRoot);
   }
}