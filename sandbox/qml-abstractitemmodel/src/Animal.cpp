#include "Animal.hpp"

Animal::Animal()
{
}

Animal::Animal( const QString &type, const QString &size )
: m_type( type )
, m_size( size )
{
}

Animal::Animal( const Animal& other )
: m_type( other.m_type )
, m_size( other.m_size )
{
}

QString Animal::type( ) const
{
	return m_type;
}

QString Animal::size( ) const
{
	return m_size;
}
