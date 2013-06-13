
#include <potholes/codegen/Generator.h>
#include <potholes/codegen/GraphUtilities.h>

#include <cloog/cloog.h>
#include <cloog/state.h>

#include <gravel/Context.h>

#include <set>
#include <map>

#include <sstream>

#include <boost/scoped_ptr.hpp>

namespace PG =  Potholes::Generator;



PG::Generator::Generator(std::string openscop): input_file(openscop), state(boost::shared_ptr<CloogState>(cloog_state_malloc())), top(Gravel::Module("top")) {
  
    std::cerr << openscop << std::endl;
    
    FILE * openscop_file = fopen(openscop.c_str(), "r");
    
    
    
    if (!openscop_file) {
                throw std::exception();
    }
    osl_scop_p scop = osl_scop_read(openscop_file);
    
  // input = boost::shared_ptr<CloogInput>(cloog_input_from_osl_scop(state.get(), scop));
    input = cloog_input_from_osl_scop(state.get(), scop);
}

void PG::Generator::generate(Target_t target) {
    options = boost::shared_ptr<CloogOptions>(cloog_options_malloc(state.get()));
    
     root = boost::shared_ptr<clast_stmt>(cloog_clast_create_from_input(input, options.get()));
    
    switch (target) {
        case PG::Verilog : {
          
          register_modules();
          register_symbols();
          build_chains();
          
        } break;
        default : { 
          
        }
    }
   
}

void PG::Generator::emit(Target_t target, std::ostream& os) { 
     switch (target) {
     case PG::Verilog : {
         Gravel::Context::getInstance()->emit(os);
     } break;
     case PG::C : { 
       
         clast_pprint(stdout, root.get(),0, options.get());
     } break;
      
     }
}



template <class T>
class identify_seq_edges {
    public : 
        void operator()(clast_stmt * parent, clast_stmt * child, T& data) { 
         if (parent->next == child) {
                // found a sequential edge
             
         } 
        }
};
template <class T>
class identify_all_edges {
    public : 
        void operator()(clast_stmt * parent, clast_stmt * child, T& data) { 
       
        }
};
template <>
class identify_all_edges <std::multimap<clast_stmt *, clast_stmt *> > {
    public : 
        void operator()(clast_stmt * parent, clast_stmt * child, std::multimap<clast_stmt *, clast_stmt *> & data) { 
        
                // found a sequential edge
             data.insert(std::pair<clast_stmt *, clast_stmt *>(parent, child));
         
        }
};

template <>
class identify_seq_edges <std::multimap<clast_stmt *, clast_stmt *> > {
    public : 
        void operator()(clast_stmt * parent, clast_stmt * child, std::multimap<clast_stmt *, clast_stmt *> & data) { 
         if ((parent->next == child) && 
                 ((PG::find_type(parent) != PG::stmt_root_t) ||
                 ((PG::find_type(parent) == PG::stmt_ass_t) && (PG::find_type(child) == PG::stmt_ass_t)))
                 ) {
                // found a sequential edge
             data.insert(std::pair<clast_stmt *, clast_stmt *>(parent, child));
         } 
        }
};

template <class T>
class identify_for_nodes {
    public : 
        void operator()(clast_stmt * node, T& usr) {
          
}

};

template <>
class identify_for_nodes<Potholes::Generator::Generator::StatementSet> {
    public : 
        void operator()(clast_stmt * node, Potholes::Generator::Generator::StatementSet& ss) {
            if (PG::find_type(node) == PG::stmt_for_t) {
             ss.insert(node);   
            }
}

};

template <class T>
class identify_guard_nodes {
    public:
        void operator()(clast_stmt * node, T& usr) const { 
    
        }
};

template <>
class identify_guard_nodes<Potholes::Generator::Generator::StatementSet>  {
    public:
        void operator()(clast_stmt * node, Potholes::Generator::Generator::StatementSet& ss) const { 
      if (PG::find_type(node) == PG::stmt_guard_t) {
                    ss.insert(node);   
            }
        }
};

template <class T>
class identify_assignment_nodes{
public : 
    void operator()(clast_stmt * node, T& usr) { 
    
        }
};

template <>
class identify_assignment_nodes<Potholes::Generator::Generator::StatementSet>{
public : 
    void operator()(clast_stmt * node, Potholes::Generator::Generator::StatementSet& ss) { 
      if (PG::find_type(node) == PG::stmt_ass_t) {
          ss.insert(node);
            }
        }
};
    




std::ostream& operator<<(std::ostream& os, PG::clast_stmt_type t) { 
    
    switch(t) {
        case PG::stmt_ass_t : {
            os << "stmt_ass_t";
        }; break;
        case PG::stmt_for_t :{
              os << "stmt_ass_t";
        }; break;
        case PG::stmt_root_t :{
              os << "stmt_ass_t";
        }; break;
        case PG::stmt_guard_t :{
              os << "stmt_ass_t";
        }; break;
        case PG::stmt_user_t :{
              os << "stmt_ass_t";
        }; break;
        case PG::stmt_seq_t :{
              os << "stmt_ass_t";
        }; break;
        case PG::stmt_null_t :{
              os << "stmt_ass_t";
        }; break;
        case PG::other_t :     {  
            os << "stmt_ass_t";
        }; break;
        default : { 
            assert(false);
        }
    }
    return os;
    
}

void print(std::ostream& os, const std::multimap<clast_stmt *, clast_stmt *>& mm) { 
    
    std::multimap<clast_stmt *, clast_stmt *>::const_iterator it;
    for (it = mm.begin(); it != mm.end() ; it++) {
        os << PG::find_type(it->first) << " : " << PG::find_type(it->second) << std::endl;
    }
    
}








std::multimap<clast_stmt *, clast_stmt *> find_edge_set(std::set<clast_stmt *> nodes, 
        std::multimap<clast_stmt *, clast_stmt *> all_edges) { 
    
    std::multimap<clast_stmt *, clast_stmt *> some_edges;
    
    /* given a node set, find all the edges that include nodes in that set */
    
    
}

clast_stmt * find_start_node(std::set<clast_stmt *> nodes, std::multimap<clast_stmt *, clast_stmt *> edges) {
    // one of the nodes in the node set has no incoming edges
    
    /* look through the node_set, and all the edges to find a node with no incoming edge */
    
    return NULL;
}

void PG::Generator::create_and_append_nodes(StatementSet ss, ModuleSet& ms) { 
    /* 1 : 1 mapping of these statement to modules */
    
    StatementSet::iterator ssit;
    
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    for(ssit = ss.begin() ; ssit != ss.end() ; ssit++ ) {
    
          Potholes::Generator::clast_stmt_type type = PG::find_type(*ssit);
          switch(type) {
              case PG::stmt_for_t : {
                  Gravel::Pointer::Module mp = Gravel::Pointer::Module(new PG::ForModule(*ssit));
                    Gravel::Module m = Gravel::Module(mp);
                    ctx->insert(mp);
                  ///  modules.insert(m);
              } break;
              case PG::stmt_guard_t : { 
                  Gravel::Pointer::Module mp = Gravel::Pointer::Module(new PG::GuardModule(*ssit));
                    Gravel::Module m = Gravel::Module(mp);
                      ctx->insert(mp);
                    // modules.insert(Gravel::Module(mp));
              } break;
               case PG::stmt_ass_t : { 
                   Gravel::Pointer::Module mp = Gravel::Pointer::Module(new PG::AssModule(*ssit));
                     Gravel::Module m = Gravel::Module(mp);
                       ctx->insert(mp);
                   //  modules.insert(Gravel::Module(mp));
              } break;
              
          }
          
    
    }
    

    
  
    
}

std::string Potholes::Generator::create_unique_module_name(clast_stmt * stmt) { 

    Gravel::Context * ctx = Gravel::Context::getInstance();
    

      Potholes::Generator::clast_stmt_type type = PG::find_type(stmt);
      
      std::stringstream ss;
      
      switch(type) {
              case PG::stmt_for_t : {
                  ss << "For_";
                  clast_for * for_stmt = (clast_for *)(stmt);
                  ss << for_stmt->iterator;   
              } break;
              case PG::stmt_guard_t : { 
                  ss << "Guard_";
                  ss << stmt ;
              } break;
               case PG::stmt_ass_t : { 
                  ss << "Ass_";
                  ss << stmt ;
              } break;
              
          }
  
      
      return ss.str();
}


void PG::Generator::create_and_append_nodes(EdgeSet edges, ModuleSet & modules ) { 
    /* find set of keys */
    std::set<std::set<clast_stmt *> > sets_of_nodes;
    
    std::set<std::set<clast_stmt *> >::iterator sosit;
    
    typedef clast_stmt * ClastStatementPtr;
    
    sets_of_nodes = find_disjoint_sets(edges);
    
    for(sosit = sets_of_nodes.begin() ; sosit != sets_of_nodes.end() ; sosit++) { 
        std::multimap<clast_stmt *, clast_stmt *> edge_set = find_edge_set(*(sosit), edges);
        clast_stmt * start_node = find_start_node(*(sosit), edge_set);
        
        // create SeqModule initiated with this clast_stmt * 
        Gravel::Pointer::Module mp = Gravel::Pointer::Module(new PG::SequentialModule(start_node));
        modules.insert(Gravel::Module(mp));
        
    }
}

void PG::Generator::connect_edges(PG::Generator::EdgeSet es, PG::Generator::ModuleSet& modules) {
  
    /* every modules should have exactly one parent */
    
    // go through modules
    // if module is in the seq_set, it's parent is a seq module, 
    // go through seq modules, if next chain leads to module statement then the parent of this module is that seq module
    
    // otherwise, the parent is taken from the edge set.
    
    // every parent calls register_child on it's parent module
    
}


template <class T>
class find_output_expression_ranges {
    public : 
        void operator()(clast_stmt * node, T& usr) {
    
}

};

template <>
class find_output_expression_ranges <PG::interval_expressions> {
    public : 
        find_output_expression_ranges(std::string _iterator) : iterator(_iterator), min(NULL), max(NULL) {
            
        }
        clast_expr * get_output_expression_min() { 
            return min;
        }
        clast_expr * get_output_expression_max() { 
            return max;
        }
        
        void operator()(clast_stmt * node, PG::interval_expressions & usr) {
    
            // check if the output is this one
            
      Potholes::Generator::clast_stmt_type type = PG::find_type(node);
  
      switch(type) {
              case PG::stmt_for_t : {
                  clast_for * for_stmt = (clast_for *)(node);
                  
                  std::cerr << std::string(for_stmt->iterator) << "\n";
                  if (std::string(for_stmt->iterator) == iterator) {
                      min = for_stmt->LB;
                      max = for_stmt->UB;
                  };
              
              } break;
           
               case PG::stmt_ass_t : { 
             
                   clast_assignment * ass_stmt = (clast_assignment *)(node);
                        
                   if (std::string(ass_stmt->LHS) == iterator) {
                       min = ass_stmt->RHS;
                       max = ass_stmt->RHS;
                   };
                   
                   
              } break;
              default : { 
            
                }   break;
          }
      
                usr = PG::interval_expressions(min, max);
        }
    private:
        std::string iterator;
        clast_expr * min;
        clast_expr * max;
};

template <class T>
class find_expression_range  {
  public : 
        void operator()(clast_stmt * node, T& usr) {
    
        }       
};



PG::interval binop ( PG::interval, mpz_t val , clast_bin_type) { 
    
    // treat floor and ceil as rounded intervals
    
    // treat mod as taking all values
    
    // treat exact division min(lb / val , ub / val) -> max ( lb / val, ub / val )
   
}

PG::interval binop( PG::interval, PG::interval, clast_red_type) {
    // sum = lb_x + lb_y to ub_x + ub_y
    // min = interval with smallest lb
    // max = interval with largest ub
}

PG::interval mult (PG::interval, mpz_t val) { 
    // min (lb*val, ub*val) -> max (lb * val, ub * val)
}

PG::interval red (PG::interval[] , unsigned size, clast_red_type) { 
    // apply binop reductions to pairs. 
}


template <>
class find_expression_range <PG::interval> {

    
    
   public : 
       
       PG::interval evaluate_expression(clast_expr * expr) {
           
           // look up input ranges
           
           switch (expr->type) {
               
               case clast_expr_name : { 
                   // lookup expression in name table
                   // lookup range in expression table
               } break;
               case clast_expr_term : { 
                   // if var == NULL, then range = val
                   // else 
                   // range = evaluate_expression() mult i;
                   
               } break;
               case clast_expr_bin : { 
                   // lhs = evaluate_expression(LHS) 
                   // range = lhs binop int
               } break;
               case clast_expr_red : { 
                   // evaluate all reduction expressions
                   // apply reduction to ranges
               } break;
           }
               
           // save range for output expression
           

           
       }
       
        void operator()(clast_stmt * node, PG::interval & range) {
    
            // find the outputs for this node and place their ranges in the map
            
         Potholes::Generator::clast_stmt_type type = PG::find_type(node);
   
        switch(type) {
              case PG::stmt_for_t : {
              clast_for * for_stmt = (clast_for *)(node);
              
              PG::interval min = evaluate_expression(for_stmt->LB);
              PG::interval max = evaluate_expression(for_stmt->UB);
              
              // range is bottom of min to top of max
              
              } break;
           
              case PG::stmt_ass_t : { 
                clast_assignment * ass_stmt = (clast_assignment *)(node);
                PG::interval min = evaluate_expression(ass_stmt->RHS);
              } break;
              default : { 
                assert(false);
                }   break;
          }


            
            
        }
        
   find_expression_range(PG::interval_expressions) { 
       
     }

   private: 
       
       typedef std::map<clast_expr *, PG::interval> ExprRangeMap;
       typedef std::map<const char *, clast_expr *> IteratorExprMap;
       
       ExprRangeMap expr_ranges;
       IteratorExprMap iterator_map;
       
   
};


PG::interval PG::Generator::find_output_range_for_iterator(std::string iterator) { 
    PG::interval_expressions range_expressions;
    

    
    find_output_expression_ranges<PG::interval_expressions> find_functor(iterator) ;
    PG::walk_nodes<PG::interval_expressions, find_output_expression_ranges<PG::interval_expressions> >(root.get(), find_functor , range_expressions);
    
    if ((range_expressions.first == NULL ) || (range_expressions.second == NULL)) { 
        throw std::exception(); // update this exception to something useful when I get a chance
    }
    
    PG::interval range;
    PG::init_interval(range);
    find_expression_range<PG::interval> evaluate_functor(range_expressions);
    PG::walk_nodes<PG::interval, find_expression_range<PG::interval> >(root.get(), evaluate_functor, range);
    
    return range;
}


template <class T>
class find_output_range {
    
    private: 
        clast_expr * expr;
    
    public : 
        find_output_range(clast_expr * _expr) : expr(_expr) { 
         
        }
        
        void operator()(clast_stmt * node, T& usr) {
    
}

};


PG::interval PG::Generator::Generator::calculate_output_range(clast_expr * expr) { 
    // if a for statement, range is calculated from the original isl_set, 
     PG::interval range;
     PG::init_interval(range);
     
     PG::interval_expressions range_expressions = PG::interval_expressions(expr, expr);
     find_expression_range<PG::interval> evaluate_functor(range_expressions);
     PG::walk_nodes<PG::interval, find_expression_range<PG::interval> >(root.get(), evaluate_functor, range);
    
 
 return range;   
    
    
}


/*


assert(stmt);
      Potholes::Generator::clast_stmt_type type = PG::find_type(stmt);
   
     switch(type) {
              case PG::stmt_for_t : {
              clast_for * for_stmt = (clast_for *)(stmt);
              std::string iterator = std::string(for_stmt->iterator);  
              } break;
           
              case PG::stmt_ass_t : { 
               
              } break;
              default : { 
                assert(false);
                }   break;
          }

*/

void PG::Generator::register_modules() { 

    
    StatementSet guard_nodes;
    StatementSet for_nodes;
    StatementSet assignment_nodes;
    
    EdgeSet seq_edges;
    EdgeSet all_edges;
    
    walk_edges<EdgeSet, identify_seq_edges<EdgeSet> >(root.get(), identify_seq_edges<EdgeSet>(), seq_edges);
    walk_edges<EdgeSet, identify_all_edges<EdgeSet> >(root.get(), identify_all_edges<EdgeSet>(), all_edges);
    
    walk_nodes<StatementSet, identify_guard_nodes<StatementSet> >(root.get(), identify_guard_nodes<StatementSet>(), guard_nodes);
    walk_nodes<StatementSet, identify_for_nodes<StatementSet> >(root.get(), identify_for_nodes<StatementSet>(), for_nodes);
    walk_nodes<StatementSet, identify_assignment_nodes<StatementSet> >(root.get(), identify_assignment_nodes<StatementSet>(), assignment_nodes);
   
    
    
    create_and_append_nodes(guard_nodes, modules);
    create_and_append_nodes(for_nodes,  modules);
    create_and_append_nodes(assignment_nodes, modules);
    create_and_append_nodes(seq_edges, modules);
    
    connect_edges(all_edges, modules);
    
}

     void PG::Generator::register_symbols() {
         
         Gravel::Context * ctx = Gravel::Context::getInstance();
         
        Gravel::ModuleSet cml = ctx->getModules();
        Gravel::ModuleSet::iterator cmlit;
        for (cmlit = cml.begin() ; cmlit != cml.end() ; cmlit++ ) {
            //Gravel::Pointer::Module ptr = cmlit->getPointer();
            
            Potholes::Generator::CodegenModulePtr cgptr = boost::dynamic_pointer_cast<Potholes::Generator::Module>(*cmlit);
            
            if ( cgptr != Potholes::Generator::CodegenModulePtr() ) {
                cgptr->register_symbols();
            }
            
        }
         
     }
     
     
     void PG::Generator::gather_iterator_edges() {
            
                   
        }
     
     
        void PG::Generator::register_iterator_edge_symbols() {
           
        }
        
        void PG::Generator::gather_control_edges() {
            
            
            
        }
        void PG::Generator::insert_control_edge_symbols() {
            
        }
     
     void PG::Generator::build_chains() {
               
         Gravel::Module top("top");
       /* Automatically Registered */
         Gravel::Context * ctx = Gravel::Context::getInstance();
         
         
         
       
        Gravel::Symbol clk("clk");
        top << clk;
        Gravel::Symbol reset("reset");
        top  << reset;
         
        /* create symbols to link together modules at top level */
        
        gather_iterator_edges();
        register_iterator_edge_symbols();
        
       /* create symbols to link together modules at top level */
        
        gather_control_edges();
        insert_control_edge_symbols();
        
     }

     
     

  /*  std::cerr << "Seq edges has " << seq_edges.size() << " edges" << std::endl;
    std::cerr << "For Nodes has " << for_nodes.size() << " nodes" << std::endl;
    std::cerr << "Guard Nodes has " << guard_nodes.size() << " nodes"<< std::endl;
    std::cerr << "Assignment Nodes has " << assignment_nodes.size() << " nodes"<< std::endl;

    print(std::cerr, seq_edges);
   */


