#include <CoreQt/RenderSettingsLogic.h>
#include <CoreQt/RenderSettingsWidget.h>
#include <Render/Scene.h>
#include <boost/bind.hpp>
namespace vrv
{
	RenderSettingsLogic::RenderSettingsLogic(RenderSettingsWidget* widget)
		: myRenderSettingsWidget(widget)
		, myEnableDepthTest(true)
		, myVisualizeDepthBuffer(false)
		, myOptimizeVisualizeDepthBuffer(true)
		, myOutlineObjects(false)
		, myOutlineWidth(1.2f)
	{
		connectSignals();
		sendSettingsToGui();
	}

	void RenderSettingsLogic::connectSignals()
	{
		myRenderSettingsWidget->signal_enableDepthTestCheckBox_valueChanged.
			connect(boost::bind(&RenderSettingsLogic::slot_enableDepthTestCheckBox_valueChanged, this,_1));
		myRenderSettingsWidget->signal_visualizeDepthBufferCheckBox_valueChanged.
			connect(boost::bind(&RenderSettingsLogic::slot_visualizeDepthBufferCheckBox_valueChanged, this, _1));
		myRenderSettingsWidget->signal_optimizeVisualizeDepthBufferCheckBox_valueChanged.
			connect(boost::bind(&RenderSettingsLogic::slot_optimizeVisualizeDepthBufferCheckBox_valueChanged, this, _1));
		myRenderSettingsWidget->signal_outlineObjectsCheckBox_valueChanged.
			connect(boost::bind(&RenderSettingsLogic::slot_outlineObjectsCheckBox_valueChanged, this, _1));
		myRenderSettingsWidget->signal_outlineWidthSpinBox_valueChanged.
			connect(boost::bind(&RenderSettingsLogic::slot_outlineWidthSpinBox_valueChanged, this, _1));
	}

	void RenderSettingsLogic::sendSettingsToGui()
	{
		myRenderSettingsWidget->enableDepthTest(myEnableDepthTest);
		myRenderSettingsWidget->visualizeDepthBuffer(myVisualizeDepthBuffer);
		myRenderSettingsWidget->optimizeVisualizeDepthBuffer(myOptimizeVisualizeDepthBuffer);
		myRenderSettingsWidget->outlineObjects(myOutlineObjects);
		myRenderSettingsWidget->setOutlineWidth(myOutlineWidth);
	}

	void RenderSettingsLogic::slot_enableDepthTestCheckBox_valueChanged(bool value)
	{
		if (myEnableDepthTest != value)
		{
			myEnableDepthTest = value;
			Scene::instance().enableDepthTest(myEnableDepthTest);
		}
	}

	void RenderSettingsLogic::slot_visualizeDepthBufferCheckBox_valueChanged(bool value)
	{
		if (myVisualizeDepthBuffer != value)
		{
			myVisualizeDepthBuffer = value;
			Scene::instance().setVisualizeDepthBuffer(value);
		}
	}

	void RenderSettingsLogic::slot_optimizeVisualizeDepthBufferCheckBox_valueChanged(bool value)
	{
		if (myOptimizeVisualizeDepthBuffer != value)
		{
			myOptimizeVisualizeDepthBuffer = value;
			Scene::instance().setOptimizeVisualizeDepthBuffer(value);
		}
	}

	void RenderSettingsLogic::slot_outlineObjectsCheckBox_valueChanged(bool value)
	{
		if (myOutlineObjects != value)
		{
			myOutlineObjects = value;
			Scene::instance().setOutlineObjects(value);
		}
	}

	void RenderSettingsLogic::slot_outlineWidthSpinBox_valueChanged(double value)
	{
		if (myOutlineWidth != value)
		{
			myOutlineWidth = value;
			Scene::instance().setOutlineWidth(value);
		}
	}
}