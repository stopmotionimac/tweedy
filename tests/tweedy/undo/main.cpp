#include <tweedy/core/truc.hpp>

#include <iostream>

#define BOOST_TEST_MODULE tweedy_undo
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( tweedy_undo_suite01 )

BOOST_AUTO_TEST_CASE( undo_integers )
{
	// simple example to manipulate a stack of undo/redo commands
	// with basic commands to manipulate integer, strings, ...

	BOOST_CHECK_EQUAL( 4.0/2.0, 6.0/3.0 );
}


BOOST_AUTO_TEST_SUITE_END()
