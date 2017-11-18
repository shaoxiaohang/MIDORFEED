#include <CoreQt/RenderSettingsWidget.h>
#include <CoreQt/RenderSettingsLogic.h>
#include <CoreQt/QtUtility.h>
#include <QGridLayout>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QComboBox>

namespace vrv
{
	RenderSettingsWidget::RenderSettingsWidget()
		: myLogic(0)
		, myEnableDepthTestCheckBox(0)
		, myOutlineObjectsCheckBox(0)
		, myOutlineWidthSpinBox(0)
	{
		setupGui();
	}

	void RenderSettingsWidget::setupGui()
	{
		setMinimumWidth(200);
		setMinimumHeight(200);
		QGridLayout* mainLayout = new QGridLayout(this);
		{
			myEnableDepthTestCheckBox = new QCheckBox(this);
			myEnableDepthTestCheckBox->setText(tr("Enable Depth Test"));
			mainLayout->addWidget(myEnableDepthTestCheckBox, 0, 0);
			connect(myEnableDepthTestCheckBox, SIGNAL(stateChanged(int)), SLOT(on_enableDepthTestCheckBox_valueChanged(int)));
		}
		{
			myVisualizeDepthBufferCheckBox = new QCheckBox(this);
			myVisualizeDepthBufferCheckBox->setText(tr("Visualize Depth Buffer"));
			mainLayout->addWidget(myVisualizeDepthBufferCheckBox, 1, 0);
			connect(myVisualizeDepthBufferCheckBox, SIGNAL(stateChanged(int)),
				SLOT(on_visualizeDepthBufferCheckBox_valueChanged(int)));
		}
		{
			myOptimizeVisualizeDepthBufferCheckBox = new QCheckBox(this);
			myOptimizeVisualizeDepthBufferCheckBox->setText(tr("Optimize Visualization"));
			mainLayout->addWidget(myOptimizeVisualizeDepthBufferCheckBox, 1, 1);
			connect(myOptimizeVisualizeDepthBufferCheckBox, SIGNAL(stateChanged(int)),
			SLOT(on_optimizeVisualizeDepthBufferCheckBox_valueChanged(int)));
		}
		{
			myOutlineObjectsCheckBox = new QCheckBox(this);
			myOutlineObjectsCheckBox->setText(tr("Outline Objects"));
			mainLayout->addWidget(myOutlineObjectsCheckBox, 2, 0);
			connect(myOutlineObjectsCheckBox, SIGNAL(stateChanged(int)),
			SLOT(on_outlineObjectsCheckBox_valueChanged(int)));
		}
		{
			myOutlineWidthLabel = new QLabel(this);
			myOutlineWidthLabel->setText(tr("Outline Width"));
			mainLayout->addWidget(myOutlineWidthLabel, 2, 1);

			myOutlineWidthSpinBox = new QDoubleSpinBox(this);
			myOutlineWidthSpinBox->setSingleStep(0.1);
			mainLayout->addWidget(myOutlineWidthSpinBox, 2, 2);
			connect(myOutlineWidthSpinBox, SIGNAL(valueChanged(double)),
				SLOT(on_outlineWidthSpinBox_valueChanged(double)));
		}

		{
			myPostEffectComboBox = new QComboBox(this);
			myPostEffectComboBox->insertItem(0, tr("default"));
			myPostEffectComboBox->insertItem(1, tr("Inversion"));
			myPostEffectComboBox->insertItem(2, tr("grayscale"));
			myPostEffectComboBox->insertItem(3, tr("kernel effect"));
			myPostEffectComboBox->insertItem(4, tr("blur"));
			myPostEffectComboBox->insertItem(5, tr("edge detection"));
			mainLayout->addWidget(myPostEffectComboBox,3, 0);
			connect(myPostEffectComboBox, SIGNAL(currentIndexChanged(int)),
				SLOT(onPostEffectComboBoxCurrentIndexChanged(int)));
		}
	}

	void RenderSettingsWidget::showEvent(QShowEvent* e)
	{
		myLogic = new RenderSettingsLogic(this);
	}

	void RenderSettingsWidget::on_enableDepthTestCheckBox_valueChanged(int value)
	{
		signal_enableDepthTestCheckBox_valueChanged((bool)value);
	}

	void RenderSettingsWidget::on_visualizeDepthBufferCheckBox_valueChanged(int value)
	{
		signal_visualizeDepthBufferCheckBox_valueChanged((bool)value);
	}

	void RenderSettingsWidget::on_optimizeVisualizeDepthBufferCheckBox_valueChanged(int value)
	{
		signal_optimizeVisualizeDepthBufferCheckBox_valueChanged((bool)value);
	}

	void RenderSettingsWidget::on_outlineObjectsCheckBox_valueChanged(int value)
	{
		signal_outlineObjectsCheckBox_valueChanged((bool)value);
	}

	void RenderSettingsWidget::on_outlineWidthSpinBox_valueChanged(double value)
	{
		signal_outlineWidthSpinBox_valueChanged(value);
	}

	void RenderSettingsWidget::onPostEffectComboBoxCurrentIndexChanged(int index)
	{
		signal_postEffectComboBoxCurrentIndexChanged(index);
	}

	void RenderSettingsWidget::closeEvent(QCloseEvent* e)
	{
		delete myLogic;
		myLogic = 0;
	}

	void RenderSettingsWidget::enableDepthTest(bool value)
	{
		BlockQtSignal block(myEnableDepthTestCheckBox);
		myEnableDepthTestCheckBox->setChecked(value);
	}

	void RenderSettingsWidget::visualizeDepthBuffer(bool value)
	{
		BlockQtSignal block(myVisualizeDepthBufferCheckBox);
		myVisualizeDepthBufferCheckBox->setChecked(value);
	}

	void RenderSettingsWidget::optimizeVisualizeDepthBuffer(bool value)
	{
		BlockQtSignal block(myOptimizeVisualizeDepthBufferCheckBox);
		myOptimizeVisualizeDepthBufferCheckBox->setChecked(value);
	}

	void RenderSettingsWidget::outlineObjects(bool value)
	{
		BlockQtSignal block(myOutlineObjectsCheckBox);
		myOutlineObjectsCheckBox->setChecked(value);
	}

	void RenderSettingsWidget::setOutlineWidth(double value)
	{
		BlockQtSignal block(myOutlineWidthSpinBox);
		myOutlineWidthSpinBox->setValue(value);
	}
}