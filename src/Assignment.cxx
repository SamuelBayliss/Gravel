#include <gravel/Context.h>
#include <gravel/Assignment.h>

#include <gravel/Symbol.h>
#include <gravel/private/Symbol.h>

#include <gravel/Expression.h>
#include <gravel/private/Expression.h>

#include <gravel/Module.h>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <algorithm>
#include <iterator>


#include <gravel/private/Actor.h>

#include <gravel/AssignmentFunctions.h>

        Gravel::Assignment Gravel::Assignment::Create(const Gravel::Symbol& sym, const Gravel::Expression& exp, unsigned delay) {
            
            Gravel::Context * ctx = Gravel::Context::getInstance();
            
            Gravel::Pointer::Symbol sptr = sym.symbol;
            Gravel::Pointer::Expression eptr = exp.ptr;
            
            Gravel::Pointer::Assignment aptr = Gravel::Pointer::Assignment(new Gravel::Implementation::Assignment(sptr, eptr, delay));
            // register assignment;
            
            ctx->insert(aptr);
            ctx->propagate();
           // std::cout << " Created Assignment " << "\n";
            
            return Gravel::Assignment(aptr);
            
        }
        
        void Gravel::Assignment::emit(std::ostream& os){
                assignment->emit(os);
        }
        
    void Gravel::Implementation::Assignment::emit(std::ostream& os){
        Gravel::Assignment::AssignmentMap::iterator amit;
        for (amit = normal.begin() ; amit != normal.end() ; amit++ ) {
           os << Gravel::Expression(amit->second) << "\n";
            if (delay == 0) {
                os << "assign " << Gravel::Symbol(amit->first) << " = " << Gravel::Symbol(amit->second->getSymbol()) << ";" << "\n";
            } else { 
                Gravel::Assignment::AssignmentMap::iterator rit = reset.find(amit->first);
                
                assert(delay == 1); // only supports single delay at the moment
                Gravel::Context * ctx = Gravel::Context::getInstance();  
                Gravel::Symbol registered_symbol = ctx->getRegisteredSymbol(amit->first);
                
                if (rit == reset.end() ) {
                    
                    // get registered_symbol
                       
                    os << "always @" << "(" << "posedge clk" << ") " << "begin" << "\n";
                    os << registered_symbol << " <= " << Gravel::Symbol(amit->second->getSymbol()) << ";" <<"\n";
                    os << "end " << "\n";
                    os << "assign " << Gravel::Symbol(amit->first) << " = " << registered_symbol << ";" << "\n";
                } else { 
                    
                    os << "always @" << "(" << "posedge clk or posedge reset" << ") " << "begin" << "\n";
                    os << "if " << "(" << "reset" << ")" << "begin";
                    os << registered_symbol << " <= " << Gravel::Symbol(rit->second->getSymbol()) << ";" << "\n";
                    os << "end";
                    
                    os << "end " << "\n";
                    
                }
            }
        }
        
        
        }
           
    void Gravel::Assignment::set_delay(unsigned _delay ) {
        assignment->set_delay(_delay);
        
    }
    
    void Gravel::Implementation::Assignment::set_delay(unsigned _delay ) {
         delay = _delay;
    }
    
           Gravel::Pointer::EdgeAnnotation Gravel::Reset( Gravel::Symbol symbol, Gravel::Expression expression) {
           
               Gravel::Edge edge(symbol.getInput(), expression.getOutput());
               
               /* Sets reset value of a symbol */
            //    std::cerr << "Setting Reset Value Annotation" <<"\n";
               // looks for assignment of a symbol in context 
               // if not found, it creates and assignment
               // else and sets the reset value of that symbol
               
                Gravel::Pointer::EdgeAnnotation rst = Gravel::Annotation::Reset::Create(edge);
                return rst;
           }
           Gravel::Pointer::EdgeAnnotation Gravel::Delay( Gravel::Edge edge) {
              /* Sets delay value of an assignment (in clocks) */
               
               // expression has to be a constant
               
               Gravel::Pointer::EdgeAnnotation ca = Gravel::Annotation::ClockedAssignment::Create(edge);
               
               // may create a new symbol
               Gravel::Context * ctx = Gravel::Context::getInstance();
               ctx->propagate();
               
               return ca;
           }
 
           
           
           
           Gravel::Pointer::EdgeAnnotation Gravel::Assign(Gravel::Edge edge) {
               
                 // std::cerr << "Creating Continuous Assignment Annotation" <<"\n";
                  Gravel::Pointer::EdgeAnnotation ca = Gravel::Annotation::ContinuousAssignment::Create(edge);
               
                  Gravel::Context * ctx = Gravel::Context::getInstance();
                  ctx->propagate();
                  return ca;
           }    
           
           
class register_module : public std::binary_function<Gravel::Pointer::Module, Gravel::Pointer::Actor, void> {
public: 
    void operator() (Gravel::Pointer::Module module, Gravel::Pointer::Actor actor) {
         Gravel::Context * ctx = Gravel::Context::getInstance();
         ctx->insert(actor, module);
    }
};
           
class find_parent_module : public std::unary_function<Gravel::Pointer::Actor,const Gravel::Pointer::Module> {
public :
    const Gravel::Pointer::Module operator() (const Gravel::Pointer::Actor& actor) {
    
    
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    Gravel::Pointer::Module module = ctx->owner(actor);
    
    return module;
    
    };
};
  

class lacks_parent_module : public std::unary_function<Gravel::Pointer::Actor,  bool> {
public:
    bool operator() (const Gravel::Pointer::Actor& actor) { 
        Gravel::Context * ctx = Gravel::Context::getInstance();
        return !(ctx->isOwned(actor));
    };
}; 

               void Gravel::Implementation::Assignment::propagate() {
                  // std::cerr << "Calling Propagator" << "\n";
                   Gravel::Collection::Actor actors;
                   Gravel::Context * ctx = Gravel::Context::getInstance();
                     std::transform(normal.begin(), normal.end(),
                        std::inserter(actors, actors.begin()),
                        boost::bind(&std::map<Gravel::Pointer::Symbol, Gravel::Pointer::Expression>::value_type::first, _1));
                       
                     std::transform(normal.begin(), normal.end(),
                        std::inserter(actors, actors.begin()),
                        boost::bind(&std::map<Gravel::Pointer::Symbol, Gravel::Pointer::Expression>::value_type::second, _1));
                       
                      std::transform(reset.begin(), reset.end(),
                        std::inserter(actors, actors.begin()),
                        boost::bind(&std::map<Gravel::Pointer::Symbol, Gravel::Pointer::Expression>::value_type::first, _1));
                       
                     std::transform(reset.begin(), reset.end(),
                        std::inserter(actors, actors.begin()),
                        boost::bind(&std::map<Gravel::Pointer::Symbol, Gravel::Pointer::Expression>::value_type::second, _1));
                       
                    // std::cout << "Calling Propagate" << "\n";
                     if (delay > 0) {
                         
                         Gravel::Assignment::AssignmentMap::iterator ait;
                         // add all the 'reg' nodes associated with 'normal' assignments
                         for (ait = normal.begin() ; ait != normal.end() ; ait++ ) {
                             Gravel::Pointer::Symbol symbol = ctx->getRegisteredSymbol(ait->first);
                             actors.insert(symbol);
                             std::cout << "Added " << symbol->getName() << "\n";
                         }
                         
                         
                     }
                     
                   // std::cerr << "There are " << actors.size() << "\n";
                   // Make a list of Actor Pointers from all the expressions and symbols
              
                   Gravel::Collection::Actor registered_actors;
                   
                   std::insert_iterator<Gravel::Collection::Actor > rait = std::inserter(registered_actors,registered_actors.begin());
                   std::remove_copy_if(actors.begin(), actors.end(), rait, lacks_parent_module() );
                   
                   
                  std::set<Gravel::Pointer::Module> modules;
                  std::insert_iterator<std::set<Gravel::Pointer::Module> > mit = std::inserter(modules,modules.begin());
                  std::transform(registered_actors.begin(), registered_actors.end(), mit, find_parent_module());
                    
                  //std::cerr << "There is " << modules.size() << " registered modules" << "\n";
                  Gravel::Pointer::Module module = *(modules.begin());
                  
                  boost::function<void (Gravel::Pointer::Actor) > register_function = boost::bind(register_module(), module, _1);
                  
                  std::for_each(actors.begin(), actors.end(), register_function );
                   if (delay > 0) {
                         
                         Gravel::Assignment::AssignmentMap::iterator ait;
                         // add all the 'reg' nodes associated with 'normal' assignments
                         for (ait = normal.begin() ; ait != normal.end() ; ait++ ) {
                             Gravel::Pointer::Symbol symbol = ctx->getRegisteredSymbol(ait->first);
                          // Registered Symbols are always local
                             ctx->insert(symbol, module);

                        
                             if (! ctx->exists(module, "clk")) {
                                Gravel::Pointer::Symbol clk = Gravel::Symbol::Create("clk");
                                
                                Gravel::Symbol cs(clk); 
                                Gravel::Module(module) << cs;
                           
                             }
                             
                             if (! ctx->exists(module, "reset")) {
                                Gravel::Pointer::Symbol reset = Gravel::Symbol::Create("reset");
                                Gravel::Symbol rs(reset); 
                                Gravel::Module(module) <<  rs;      
                             }
                           
                         }
                         
                         
                     }
                  
              
                
               }
           
           
             bool Gravel::Assignment::operator<(const Gravel::Assignment& cmp) const {
                 return assignment.get() < cmp.assignment.get();
             }
           
             
             
           Gravel::Assignment::Assignment(Gravel::Pointer::Assignment assignment) : assignment(assignment) { 
              
           }
                   Gravel::Implementation::Assignment::Assignment(Gravel::Pointer::Symbol& sym, Gravel::Pointer::Expression& exp, unsigned delay) :
                   delay(delay)
                   {
                       normal.insert(Gravel::Assignment::AssignmentPair(sym, exp));
                   }
                   
                   Gravel::Collection::Symbol Gravel::Assignment::get_assigned_symbols() const {
                       return assignment->get_assigned_symbols();
                   }
                   
                   Gravel::Collection::Symbol Gravel::Implementation::Assignment::get_assigned_symbols() const { 
                       Gravel::Collection::Symbol keys;
                       
                       std::transform(normal.begin(), normal.end(),
                        std::inserter(keys, keys.begin()),
                        boost::bind(&std::map<Gravel::Pointer::Symbol, Gravel::Pointer::Expression>::value_type::first, _1));
                       
                       return keys;
                   }