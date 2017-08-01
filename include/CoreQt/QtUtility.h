#pragma once

#include<QObject>

namespace vrv
{
	class BlockQtSignal
	{
	public:
		BlockQtSignal(QObject* qtObject)
			: myTarget(qtObject)
		{
			myTarget->blockSignals(true);
		}
		~BlockQtSignal()
		{
			myTarget->blockSignals(false);
		}
	protected:
		QObject* myTarget;
	};
}