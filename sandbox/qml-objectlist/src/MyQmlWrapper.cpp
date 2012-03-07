#include "MyQmlWrapper.hpp"

#include <boost/lexical_cast.hpp>


void MyQmlWrapper::modifyQmlData()
{
	static int i = 0;
	const std::string iStr = boost::lexical_cast<std::string>( i );
	getMyModel()->append( new MyDataObject( ("ZA"+iStr).c_str(), ("ZB"+iStr).c_str() ) );
}

