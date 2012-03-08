#ifndef _ANIMAL_HPP_
#define _ANIMAL_HPP_

#include <QtCore/QObject>
#include <QtCore/QString>


class Animal : public QObject
{
public:
	Q_OBJECT
public:
	Animal();
	Animal( const QString &type, const QString &size );
	Animal( const Animal& other );
	Animal& operator=( const Animal& other )
	{
		m_type = other.m_type;
		m_size = other.m_size;
	}

	QString type( ) const;
	QString size( ) const;

	std::size_t realSize( ) const
	{
		return m_type.size( );
	}

private:
	QString m_type;
	QString m_size;
};

#endif
