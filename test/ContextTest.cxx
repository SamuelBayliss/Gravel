

#include <boost/test/unit_test.hpp>

#include <gravel/Context.h>

BOOST_AUTO_TEST_SUITE ( ContextTest ) 

BOOST_AUTO_TEST_CASE( context_constructor_test)
{
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    BOOST_CHECK ( ctx != NULL);
}

BOOST_AUTO_TEST_SUITE_END()
        