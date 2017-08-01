#include <CoreQt/RenderSettingsLogic.h>
#include <CoreQt/RenderSettingsWidget.h>
#include <Core/NodeVisitor.h>
#include <Core/Node.h>
#include <Render/DrawState.h>
#include <Render/RenderState.h>
#include <Render/Drawable.h>
#include <Render/Scene.h>
#include <boost/bind.hpp>

namespace vrv
{
	class DepthTestNodeVisitor : public NodeVisitor
	{
	public:
		void setDepthTestEnabled(bool enabled)
		{
			myDepthEnabled = enabled;
		}
	protected:
		void doSomething(Node* node)
		{
			for (size_t i = 0; i < node->numberOfDrawable(); i++)
			{
				RenderState* renderState = node->getDrawable(i)->drawState()->renderState();
				DepthTest &depth = renderState->depthTest();
				depth.setEnabled(myDepthEnabled);
			}
		}
	protected:
		bool myDepthEnabled;
	};


	RenderSettingsLogic::RenderSettingsLogic(RenderSettingsWidget* widget)
		: myRenderSettingsWidget(widget)
		, myEnableDepthTest(true)
		, myVisualizeDepthBuffer(false)
		, myOptimizeVisualizeDepthBuffer(true)
		, myOutlineObjects(false)
		, myOutlineWidth(1.2)
	{
		connectSignals();
		sendSettingsToGui();
	}

	void RenderSettingsLogic::connectSignals()
	{
		myRenderSettingsWidget->signal_enableDepthTestCheckBox_valueChanged.connect(
			boost::bind(&RenderSettingsLogic::slot_enableDepthTestCheckBox_valueChanged, this, _1));
		myRenderSettingsWidget->signal_visualizeDepthBufferCheckBox_valueChanged.connect(
			boost::bind(&RenderSettingsLogic::slot_visualizeDepthBufferCheckBox_valueChanged, this, _1));
		myRenderSettingsWidget->signal_optimizeVisualizeDepthBufferCheckBox_valueChanged.connect(
			boost::bind(&RenderSettingsLogic::slot_optimizeVisualizeDepthBufferCheckBox_valueChanged, this, _1));
		myRenderSettingsWidget->signal_outlineObjectsCheckBox_valueChanged.connect(
			boost::bind(&RenderSettingsLogic::slot_outlineObjectsCheckBox_valueChanged, this, _1));
		myRenderSettingsWidget->signal_outlineWidthSpinBox_valueChanged.connect(
			boost::bind(&RenderSettingsLogic::slot_outlineWidthSpinBox_valueChanged, this, _1));
	}

	void RenderSettingsLogic::sendSettingsToGui()
	{
		myRenderSettingsWidget->enableDepthTest(myEnableDepthTest);
		myRenderSettingsWidget->visualizeDepthBuffer(myVisualizeDepthBuffer);
		myRenderSettingsWidget->optimizeVisualizeDepthBuffer(myOptimizeVisualizeDepthBuffer);
		myRenderSettingsWidget->setOutlineWidth(myOutlineWidth);
		Scene::instance().setOptimizeVisualizeDepthBuffer(myOptimizeVisualizeDepthBuffer);
		Scene::instance().setOutlineWidth(myOutlineWidth);
	}

	void RenderSettingsLogic::slot_enableDepthTestCheckBox_valueChanged(bool checked)
	{
		static DepthTestNodeVisitor visitor;
		if (myEnableDepthTest != checked)
		{
			myEnableDepthTest = checked;
			visitor.setDepthTestEnabled(checked);
			visitor.run(Scene::instance().root());
		}
	}

	void RenderSettingsLogic::slot_visualizeDepthBufferCheckBox_valueChanged(bool value)
	{
		Scene::instance().setVisualizeDepthBuffer(value);
	}

	void RenderSettingsLogic::slot_optimizeVisualizeDepthBufferCheckBox_valueChanged(bool value)
	{
		Scene::instance().setOptimizeVisualizeDepthBuffer(value);
	}

	void RenderSettingsLogic::slot_outlineObjectsCheckBox_valueChanged(bool value)
	{
		Scene::instance().setOutlineObjects(value);
	}

	void RenderSettingsLogic::slot_outlineWidthSpinBox_valueChanged(double value)
	{
		Scene::instance().setOutlineWidth(value);
	}
}
