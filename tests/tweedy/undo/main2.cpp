#include <tweedy/core/truc.hpp>

#include <iostream>
#include <queue>

#define BOOST_TEST_MODULE tweedy_undo
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( tweedy_undo_suite01 )

BOOST_AUTO_TEST_CASE( undo_integers )
{
	// simple example to manipulate a stack of undo/redo commands
	// with basic commands to manipulate integer, strings, ...
	std::queue<int> q;
	
	q.push(5);
	q.push(51);
	q.push(52);
	q.push(53);

	BOOST_CHECK_EQUAL( q.front(), 5 );

	q.pop();
	
	BOOST_CHECK_EQUAL( q.size(), 3 );
	BOOST_CHECK_EQUAL( q.front(), 51 );
	BOOST_CHECK_EQUAL( q.back(), 53 );
	
}


BOOST_AUTO_TEST_SUITE_END()
