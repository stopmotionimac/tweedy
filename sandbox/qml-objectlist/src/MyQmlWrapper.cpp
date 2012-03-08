#include "MyQmlWrapper.hpp"

#include <boost/lexical_cast.hpp>


void MyQmlWrapper::modifyQmlData()
{
	static int i = 0;
	
	getMyModel()->clear();
	for( int j = 0; j <= i; ++j )
	{
		const std::string iStr = boost::lexical_cast<std::string>( i );
		const std::string jStr = boost::lexical_cast<std::string>( j );
		getMyModel()->append( new MyDataObject( ("ZA"+iStr).c_str(), ("ZB"+jStr).c_str() ) );
	}
	++i;
}

