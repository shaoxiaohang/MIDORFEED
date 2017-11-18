#pragma once

#include <QWidget>
#include<boost/signals2.hpp>

class QCheckBox;
class QDoubleSpinBox;
class QLabel;
class QComboBox;

namespace vrv
{
	class RenderSettingsLogic;
	class RenderSettingsWidget : public QWidget
	{
		Q_OBJECT
	public:
		RenderSettingsWidget();
		void enableDepthTest(bool);
		void visualizeDepthBuffer(bool);
		void optimizeVisualizeDepthBuffer(bool);
		void outlineObjects(bool);
		void setOutlineWidth(double);
	protected:
		void setupGui();
		void showEvent(QShowEvent* e);
		void closeEvent(QCloseEvent* e);


	protected slots:
		void on_enableDepthTestCheckBox_valueChanged(int);
		void on_visualizeDepthBufferCheckBox_valueChanged(int);
		void on_optimizeVisualizeDepthBufferCheckBox_valueChanged(int);
		void on_outlineObjectsCheckBox_valueChanged(int);
		void on_outlineWidthSpinBox_valueChanged(double);
		void onPostEffectComboBoxCurrentIndexChanged(int);
	public:
		boost::signals2::signal<void(bool)> signal_enableDepthTestCheckBox_valueChanged;
		boost::signals2::signal<void(bool)> signal_visualizeDepthBufferCheckBox_valueChanged;
		boost::signals2::signal<void(bool)> signal_optimizeVisualizeDepthBufferCheckBox_valueChanged;
		boost::signals2::signal<void(bool)> signal_outlineObjectsCheckBox_valueChanged;
		boost::signals2::signal<void(double)> signal_outlineWidthSpinBox_valueChanged;
		boost::signals2::signal<void(int)> signal_postEffectComboBoxCurrentIndexChanged;
	protected:
		RenderSettingsLogic* myLogic;
		QCheckBox* myEnableDepthTestCheckBox;
		QCheckBox* myVisualizeDepthBufferCheckBox;
		QCheckBox* myOptimizeVisualizeDepthBufferCheckBox;
		QCheckBox* myOutlineObjectsCheckBox;
		QDoubleSpinBox* myOutlineWidthSpinBox;
		QLabel* myOutlineWidthLabel;
		QComboBox* myPostEffectComboBox;
	};
}