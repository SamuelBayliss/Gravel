#include <boost/test/unit_test.hpp>

#include <potholes/codegen/Generator.h>
#include <potholes/codegen/GraphUtilities.h>
#include <gravel/Context.h>

#include <cloog/cloog.h>

#include <utility>
namespace PG =  Potholes::Generator;

BOOST_AUTO_TEST_SUITE ( CodegenTest ) 

BOOST_AUTO_TEST_CASE( codegen_constructor_test)
{
    PG::Generator gen("/Users/sb1708/Work/shared-tools/Gravel/test/input/mmm.scop");


}

BOOST_AUTO_TEST_CASE( codegen_print_code )
{
    PG::Generator gen("/Users/sb1708/Work/shared-tools/Gravel/test/input/mmm.scop");

    gen.generate(PG::C);
    gen.emit(PG::C);
}

BOOST_AUTO_TEST_CASE( codegen_print_verilog )
{
    PG::Generator gen("/Users/sb1708/Work/shared-tools/Gravel/test/input/mmm.scop");

    gen.generate(PG::Verilog);
    gen.emit(PG::Verilog);
}

BOOST_AUTO_TEST_CASE( codegen_walk_ranges_i )
{
    PG::Generator gen("/Users/sb1708/Work/shared-tools/Gravel/test/input/mmm.scop");
    gen.generate(PG::Verilog);
    // walk the output ranges
    PG::interval range = gen.find_output_range_for_iterator("x1");

    
    //cloog_int_print(stdout, range.first);
    
   
    
   // BOOST_CHECK(range.first);
   // BOOST_CHECK(range.second == 49);
}

BOOST_AUTO_TEST_CASE( codegen_walk_ranges_j )
{
    PG::Generator gen("/Users/sb1708/Work/shared-tools/Gravel/test/input/mmm.scop");
    gen.generate(PG::Verilog);
    // walk the output ranges
    PG::interval range = gen.find_output_range_for_iterator("x2");
   /* std::pair<long, long> range = gen.calculate_output_range(stmt);
    BOOST_CHECK(range.first == 0);
    BOOST_CHECK(range.second == 49);
    * */
}

BOOST_AUTO_TEST_CASE( codegen_walk_ranges_k )
{
    PG::Generator gen("/Users/sb1708/Work/shared-tools/Gravel/test/input/mmm.scop");
    gen.generate(PG::Verilog);
    // walk the output ranges
    PG::interval range = gen.find_output_range_for_iterator("x3");
    /*
    std::pair<long, long> range = gen.calculate_output_range(stmt);
    BOOST_CHECK(range.first == 0);
    BOOST_CHECK(range.second == 49);
     */
}

BOOST_AUTO_TEST_CASE ( test_disjoint_sets ) {
  // test our ability to create disjoint sets
 
    std::multimap<int,int> edges;
    
    typedef std::pair<int, int> Edge;
    
    edges.insert(Edge(1,2));
    edges.insert(Edge(4,5));
    edges.insert(Edge(5,6));
    edges.insert(Edge(2,3));
    
    std::set< std::set < int > > disjoint_sets = find_disjoint_sets(edges);

    BOOST_CHECK(disjoint_sets.size() == 2);
    
    
}

BOOST_AUTO_TEST_CASE ( test_disjoint_sets_2 ) {
  // test our ability to create disjoint sets
 
    std::multimap<int,int> edges;
    
    typedef std::pair<int, int> Edge;
    
    edges.insert(Edge(1,2));
    edges.insert(Edge(3,4));
  
    BOOST_CHECK(find_disjoint_sets(edges).size() == 2);
    
    
}

BOOST_AUTO_TEST_CASE ( test_disjoint_sets_3 ) {
  // test our ability to create disjoint sets
 
    std::multimap<int,int> edges;
    
    typedef std::pair<int, int> Edge;
    
    edges.insert(Edge(1,2));
    edges.insert(Edge(2,3));
    edges.insert(Edge(3,4));
  
    BOOST_CHECK(find_disjoint_sets(edges).size() == 1);
    
    
}

BOOST_AUTO_TEST_CASE ( test_disjoint_sets_4 ) {
  // test our ability to create disjoint sets
 
    std::multimap<int,int> edges;
    
    typedef std::pair<int, int> Edge;
    
    edges.insert(Edge(1,2));
    edges.insert(Edge(4,5));
    edges.insert(Edge(3,4));
    edges.insert(Edge(5,6));
    edges.insert(Edge(2,3));
    BOOST_CHECK(find_disjoint_sets(edges).size() == 1);
    
    
}


BOOST_AUTO_TEST_SUITE_END()
        
