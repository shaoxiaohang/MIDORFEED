#pragma once

namespace vrv
{
	class RenderSettingsWidget;
	class RenderSettingsLogic
	{
	public:
		RenderSettingsLogic(RenderSettingsWidget* widget);
	protected:
		void connectSignals();
		void sendSettingsToGui();

		void slot_enableDepthTestCheckBox_valueChanged(bool);
		void slot_visualizeDepthBufferCheckBox_valueChanged(bool);
		void slot_optimizeVisualizeDepthBufferCheckBox_valueChanged(bool);
		void slot_outlineObjectsCheckBox_valueChanged(bool);
		void slot_outlineWidthSpinBox_valueChanged(double);
		void slot_postEffectComboBoxCurrentIndexChanged(int);
	protected:
		RenderSettingsWidget* myRenderSettingsWidget;
		bool myEnableDepthTest;
		bool myVisualizeDepthBuffer;
		bool myOptimizeVisualizeDepthBuffer;
		bool myOutlineObjects;
		double myOutlineWidth;
		int myPostEffectType;
	};
}