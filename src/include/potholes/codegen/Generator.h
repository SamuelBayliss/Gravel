/* 
 * File:   codegenerator.h
 * Author: sb1708
 *
 * Created on April 29, 2013, 12:11 PM
 */

#ifndef CODEGENERATOR_H
#define	CODEGENERATOR_H

#include <string>

#include <cloog/cloog.h>
#include <osl/scop.h>

#include <boost/shared_ptr.hpp>

#include <potholes/codegen/Module.h>
#include <potholes/codegen/Definitions.h>

#include <gravel/Context.h>

#include <set>
#include <map>


namespace Potholes { 

    namespace Generator { 
   

  template <class T, class F> 
  void walk_nodes(clast_stmt * node, F functor,  T& data) { 
    if (node != NULL) {
        functor(node, data);
        clast_stmt_type type = find_type(node);
        
        if ( node->next != NULL) {
            walk_nodes(node->next, functor, data);
        }
        
        switch(type) {
            case stmt_root_t: {
               ;
            } break;
            case stmt_ass_t : { 
               ;
            } break;
            case stmt_for_t : {
                clast_for * for_node = (clast_for *)(node);
              walk_nodes(for_node->body, functor, data);  
            } break;
             case stmt_guard_t : { 
                clast_guard * guard_node = (clast_guard *)(node);
                walk_nodes(guard_node->then, functor, data);
            } break;
           case  stmt_user_t : { 
                ;
            } break;
            
            
        }
    }
}



  
template <class T, class F>
void walk_edges(clast_stmt * parent, clast_stmt * child, F edge_functor, T& data)  { 
    
       if (child != NULL) {
        edge_functor(parent, child, data);
        clast_stmt_type type = find_type(child);
     
        walk_edges(child, child->next, edge_functor, data);
           
        switch(type) {
            case stmt_root_t: {
               ;
            } break;
            case stmt_ass_t : { 
               ;
            } break;
            case stmt_for_t : {
                clast_for * for_node = (clast_for *)(child);
              walk_edges(child, for_node->body, edge_functor, data);  
            } break;
             case stmt_guard_t : { 
                clast_guard * guard_node = (clast_guard *)(child);
                walk_edges(child, guard_node->then, edge_functor, data);
            } break;
            case stmt_user_t : { 
                ;
            } break;
            
            
        }
    }
    
}
template <class T, class F>
  void walk_edges(clast_stmt * node, F edge_functor, T& data) { 
    
    assert(find_type(node) == stmt_root_t);
    walk_edges(node, node->next, edge_functor, data);
}




 std::string create_unique_module_name(clast_stmt *);
  
        class Generator { 
        public:
            
        typedef std::set <Gravel::Module> ModuleSet;
        typedef std::set<clast_stmt *> StatementSet;
        typedef std::multimap<clast_stmt *, clast_stmt *> EdgeSet;
        typedef std::set< std::set<clast_stmt *> >DisjointStatementSets;
   

            
           Generator(std::string openscop = "");
     
           void generate(Target_t);
           void emit(Target_t, std::ostream&);
           
           //void register_signals();
           void register_modules();
           void register_symbols();
           void build_chains();
           
            Potholes::Generator::interval calculate_output_range(clast_expr *);
            Potholes::Generator::interval find_output_range_for_iterator(std::string);
        private:
           std::string input_file;
          // boost::shared_ptr<CloogInput> input;
           CloogInput * input;
           boost::shared_ptr<CloogState> state;
           boost::shared_ptr<clast_stmt> root;
           boost::shared_ptr<CloogOptions> options;
           ModuleSet modules;
           Gravel::Module top;
           
           void connect_edges(EdgeSet, ModuleSet&);
           void create_and_append_nodes(StatementSet, ModuleSet &) ;
           void create_and_append_nodes(EdgeSet, ModuleSet &);
           
           void gather_iterator_edges();
           void register_iterator_edge_symbols();
        
           void gather_control_edges();
           void insert_control_edge_symbols();
           
           
        };
        
        
      

    };

}

#endif	/* CODEGENERATOR_H */

