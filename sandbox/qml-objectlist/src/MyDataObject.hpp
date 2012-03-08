#ifndef _MyDataObject_HPP_
#define _MyDataObject_HPP_

#include <QtCore/QObject>
#include <QtCore/QString>


class MyDataObject : public QObject
{
public:
	Q_OBJECT
    Q_PROPERTY( QString a READ a NOTIFY aChanged )
    Q_PROPERTY( QString b READ b NOTIFY bChanged )
    Q_PROPERTY( int bSize READ bSize NOTIFY bSizeChanged )
	
public:
	MyDataObject()
	: m_a( "a" )
	, m_b( "b" )
	{}
	MyDataObject( const QString& a, const QString& b )
	: m_a( a )
	, m_b( b )
	{}

	MyDataObject( const MyDataObject& other )
	: m_a( other.m_a )
	, m_b( other.m_b )
	{}

	QString a() const { return m_a; }
	QString b() const { return m_b; }
	std::size_t bSize( ) const { return m_b.size(); }

Q_SIGNALS:
	void aChanged();
	void bChanged();
	void bSizeChanged();
	
private:
	QString m_a;
	QString m_b;
};

#endif
