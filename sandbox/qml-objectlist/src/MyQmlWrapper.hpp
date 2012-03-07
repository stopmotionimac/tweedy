#ifndef _TWEEDY_MYQMLWRAPPER_HPP_
#define _TWEEDY_MYQMLWRAPPER_HPP_

#include "MyDataObject.hpp"

#include <qobjectlistmodel.h>

#include <QtCore/QObject>

#include <boost/lexical_cast.hpp>

#include <iostream>


class MyQmlWrapper : public QObject
{
	Q_OBJECT
public:
    Q_PROPERTY( QObjectListModel* myModel READ getMyModel NOTIFY myModelChanged )
	
	QObjectListModel* getMyModel() { return &_model; }
	
    Q_INVOKABLE void add()
	{
		static int i = 4;
		const std::string ii = boost::lexical_cast<std::string>(i++);
		_model.append( new MyDataObject( QString::fromStdString("AA"+ii), QString::fromStdString("BB"+ii) ) );
	}
    Q_INVOKABLE void remove( int index )
	{
		std::cout << "MyQmlWrapper::remove item " << index << " on " << _model.size() << " elements." << std::endl;
		_model.removeAt( index );
		std::cout << "MyQmlWrapper::remove removed." << std::endl;
	}
	
Q_SIGNALS:
	void myModelChanged();

public Q_SLOTS:
	void modifyQmlData();
	
private:
	QObjectListModel _model;
};

#endif
