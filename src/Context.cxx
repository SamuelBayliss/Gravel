#include <stdlib.h>

#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <gravel/Module.h>
#include <gravel/private/Module.h>

#include <gravel/Context.h>


Gravel::Context * Gravel::Context::pInstance = NULL;

Gravel::Context * Gravel::Context::getInstance()
{
  if (Gravel::Context::pInstance == NULL) {
    Gravel::Context::pInstance = new Gravel::Context();
  }
  return pInstance;
}

Gravel::Module Gravel::Context::getPointer(Gravel::ModuleImplementation * impl) {
    Gravel::Context * ctx = Gravel::Context::getInstance();
    return ctx->getModule(impl->getName());
}

Gravel::Module Gravel::Context::getPointer(const Gravel::ModuleImplementation * impl) {
    Gravel::Context * ctx = Gravel::Context::getInstance();
    return ctx->getModule(impl->getName());
}


Gravel::Context::Context() : tempIdentifier(0) { 
    
}
struct name_matches : public std::binary_function<Gravel::Module, std::string, bool> {
        bool operator()(const Gravel::Module& m, const std::string name) const {
           return m.getName() == name; 
        } 
};

Gravel::Module Gravel::Context::getModule(const std::string& name) const { 
    // This should increment module reference counter when return does a copy
    std::binder2nd<name_matches>  match_object(name_matches(), name);
    Gravel::ModuleSet::iterator mlit = std::find_if(ml.begin(), ml.end(), match_object);
    
    if (mlit == ml.end()) { 
        throw Gravel::Exception::ModuleNotFound(name);
    } else { 
      return *mlit;
    }
    
}

void Gravel::Context::insert(const Gravel::Pointer::Module& module) { 
    ml.insert(module);
}

void Gravel::Context::insert(const Gravel::Pointer::Assignment& assignment) {
 //   std::cerr << "Inserted Assignment\n";
    al.insert(assignment);
}

void Gravel::Context::insert(Gravel::Pointer::Module& module, Gravel::Pointer::Symbol symbol, const Gravel::Interface::Symbol::Direction& direction) {
    SymbolKey key(module, symbol);
    sm.insert(std::pair<SymbolKey, Gravel::Interface::Symbol::Direction>(key, direction));
    
    Gravel::Pointer::Actor actor = boost::static_pointer_cast<Gravel::Actor>(symbol);
    
    am.insert(std::pair<Gravel::Pointer::Actor, Gravel::Pointer::Module>(actor, module));
    propagate();
}

struct symbol_matches : public std::binary_function<std::pair<const Gravel::SymbolKey, Gravel::Interface::Symbol::Direction>, Gravel::Interface::Symbol::Direction, bool> {
        bool operator()(const std::pair<const Gravel::SymbolKey, Gravel::Interface::Symbol::Direction> & p,  const Gravel::Interface::Symbol::Direction & direction) const {
           return (p.second) == direction;
        } 
};

bool Gravel::Context::exists(const Gravel::Pointer::Module& module) { 
    return (ml.find(module) != ml.end());
}



bool Gravel::Context::exists(const Gravel::Pointer::Module& module, const Gravel::Pointer::Symbol symbol, const Gravel::Interface::Symbol::Direction& direction) {
    SymbolKey key(module, symbol);
    ConstSymbolRange sr = sm.equal_range(key);  
    
        std::binder2nd<symbol_matches>  match_object((symbol_matches()), direction);
   // Gravel::ModuleList::iterator mlit = std::find_if(ml.begin(), ml.end(), match_object);
    
    return (std::find_if(sr.first, sr.second, match_object) == sr.second);//std::bind2nd<std::equal_to<Gravel::Symbol>, Gravel::Symbol>(eq,symbol)) != sr.second);
}

Gravel::ModuleSet Gravel::Context::getModules() const { 
    return ml;
}

Gravel::SymbolSet Gravel::Context::getSymbols(const Gravel::Pointer::Module& module) const { 
    Gravel::ConstSymbolMapIterator mit;
    
    Gravel::SymbolSet sl;
    
    for (mit = sm.begin() ; mit != sm.end() ; mit++ ) {
        Gravel::SymbolKey sk = mit->first;
    
        if (sk.first == module) {
            sl.insert(Gravel::Symbol(sk.second));
        }
        
    }
    return sl;
}



class find_parent_module : public std::unary_function<Gravel::SymbolSet::iterator,const Gravel::Module> {
public :
    const Gravel::Module operator() (const Gravel::Symbol& symbol) {
    
    
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    Gravel::Module module = symbol.getOwner();
    
    return module;
    
    };
};


Gravel::AssignmentSet Gravel::Context::getAssignments(const Gravel::Module& module) const {
    Gravel::AssignmentSet::iterator it;
    
    Gravel::AssignmentSet module_assignments;
    

    for (it = al.begin() ; it != al.end() ; it++) {
        Gravel::Pointer::Assignment assignment = *it;
       Gravel::Collection::Symbol s = assignment->get_assigned_symbols();
       std::set<Gravel::Module> m;
       
       // if all symbols in module, add this assignment to module_assignments
       
       std::insert_iterator<std::set<Gravel::Module> > sit = std::inserter(m, m.begin());
  
       std::transform(s.begin(), s.end(), sit, find_parent_module());
     
       // do some magic binding to a predicate here
       if (m.size() > 1) {
           assert(false); // should throw exception
       }
       if (m.find(module) != m.end()) module_assignments.insert(*it);
       
    }
    
    return module_assignments;
}

Gravel::SymbolSet Gravel::Context::getSymbols(Gravel::Pointer::Module module, Symbol::Direction direction) const { 
    
    Gravel::SymbolMap::const_iterator sit;
    
    Gravel::SymbolSet ss;
    
    for (sit = sm.begin() ; sit != sm.end() ; sit++) {
        
        
        Gravel::SymbolKey key = sit->first;
        
        if (key.first == module && sit->second == direction) {
            ss.insert(Gravel::Symbol(key.second));
        }
        
      
    }
     
    return ss;
    
}

void Gravel::Context::emit(std::ostream& os) {
    // emit to file
    ModuleSet::iterator mlit;
    os << "//" << ml.size() << " Modules" << std::endl;
    for (mlit = ml.begin() ; mlit != ml.end() ; mlit++ ) {
        Gravel::Pointer::Module mptr = *mlit;
        Gravel::Module(mptr).emit(os);
    }
    
    
    
}

void Gravel::Context::printSymbols(std::ostream& os) { 
    Gravel::SymbolMap::iterator sit;
    for (sit = sm.begin() ; sit != sm.end() ; sit++) {
        Gravel::SymbolKey key = sit->first;
        Gravel::Symbol symbol = Gravel::Symbol(key.second);
        os << symbol << "\n";
    }
  
}

bool Gravel::Context::isOwned(const Gravel::Pointer::Actor& actor) {
 
    Gravel::ActorMap::iterator amit = am.find(actor);
 
    return (amit != am.end());
}


Gravel::SymbolVector Gravel::Context::getDelayedSymbols(const Gravel::Symbol&) {
    return Gravel::SymbolVector();
}

Gravel::Symbol Gravel::Context::getRegisteredSymbol(const Gravel::Symbol&) {
    
}

void Gravel::Context::insert(Gravel::Pointer::Actor actor, Gravel::Pointer::Module module) { 
        am.insert(std::pair<Gravel::Pointer::Actor, Gravel::Pointer::Module>(actor, module));     
}

void Gravel::Context::insert(Gravel::Pointer::Actor actor) { 
    as.insert(actor);
}
    
    
    //Gravel::Pointer::GraphNode output = actor->getOutput();
    
    
    
    //Gravel::GraphNode::ConstNodeRange inputs = actor->getInputs();
    
  //  boost::function<void (std::pair<Gravel::GraphEdgeDirection, Gravel::Pointer::GraphNode>) > my_func = boost::bind(insert_parent_function(), actor,  _1);

   // for_each(inputs.first, inputs.second,  my_func );
  


/*void Gravel::Context::insert(Gravel::Pointer::Actor actor, Gravel::Pointer::GraphNode node) { 
    
   // typedef std::map<Gravel::Pointer::GraphNode, Gravel::Pointer::Actor> ActorMap;
    
    am.insert(std::pair<Gravel::Pointer::GraphNode, Gravel::Pointer::Actor>(node, actor));
}*/


struct insert_parent_function : public std::binary_function<const Gravel::Pointer::Actor&, std::pair<Gravel::GraphEdgeDirection, Gravel::Pointer::GraphNode>, void> {
void operator()(const Gravel::Pointer::Actor& actor, std::pair<Gravel::GraphEdgeDirection, Gravel::Pointer::GraphNode> gn) {
    // get gravel context
    Gravel::Context * ctx = Gravel::Context::getInstance();
    Gravel::Pointer::GraphNode node = gn.second;
   
  //  ctx->insert(actor, node);
    
}
};

   Gravel::Pointer::Actor Gravel::Context::getParent(Gravel::Pointer::GraphNode candidate) {
 
       
       Gravel::ActorSet::iterator amit;
       
       
       for (amit = as.begin() ; amit != as.end() ; amit++ ) {
           
          Gravel::Pointer::Actor actor = *amit;
          Gravel::Pointer::GraphNode output = actor->getOutput();

          if (output == candidate) {
             
              return actor;
          }
          
          Gravel::GraphNode::ConstNodeRange inputs = actor->getInputs();
          Gravel::GraphNode::ConstNodeIterator cit;
          for (cit = inputs.first ; cit != inputs.second ; cit++) {
               Gravel::Pointer::GraphNode input = cit->second;
               if (input == candidate) {
                   return actor;
               }
          }

       }
 
       throw Gravel::Exception::ActorNotFound();
       
   }

/*Gravel::Module Gravel::Context::owner(const Gravel::Pointer::Actor& actor) {
    
    ActorMap::iterator smit = am.find(actor);
  
    if (smit == am.end()) throw Gravel::Exception::OwnerNotFound();
    
    return Gravel::Module(smit->second);
    
}*/

Gravel::Pointer::Module Gravel::Context::owner(const Gravel::Pointer::Actor& actor) {
    
    ActorMap::iterator smit = am.find(actor);
  
    if (smit == am.end()) throw Gravel::Exception::OwnerNotFound();
    
    return smit->second;
    
}

     
struct add_iterator_to_module : public std::binary_function<const Gravel::Pointer::Module&, std::pair<Gravel::GraphEdgeDirection, Gravel::Pointer::GraphNode>, void> {
void operator()(const Gravel::Pointer::Module& module, std::pair<Gravel::GraphEdgeDirection, Gravel::Pointer::GraphNode> node_pair) {
    Gravel::Context * ctx = Gravel::Context::getInstance();
    Gravel::Pointer::Actor actor = ctx->getParent(node_pair.second);
    
    ctx->insert(actor, module);
    
   };
};

struct add_node_to_module : public std::binary_function<const Gravel::Pointer::Module&, Gravel::Pointer::GraphNode, void> {
void operator()(const Gravel::Pointer::Module& module, Gravel::Pointer::GraphNode node) {
    Gravel::Context * ctx = Gravel::Context::getInstance();
    Gravel::Pointer::Actor actor = ctx->getParent(node);
    
    ctx->insert(actor, module);
    
   };
};

void find_edges(const Gravel::Pointer::Module& module, const Gravel::Pointer::Actor& actor) { 
  
    // add all the inputs and outputs for this symbol to symbol and expression lists(registering them with module)
 
    Gravel::Pointer::GraphNode output = actor->getOutput();
    
    Gravel::GraphNode::ConstNodeRange inputs = actor->getInputs();

    boost::function<void (std::pair<Gravel::GraphEdgeDirection, Gravel::Pointer::GraphNode>) > add_iterator = boost::bind(add_iterator_to_module(),module,  _1);
    boost::function<void (Gravel::Pointer::GraphNode) > add_node = boost::bind(add_node_to_module(),module,  _1);
    add_node(output);
    
    std::for_each(inputs.first, inputs.second, add_iterator);
   
    
}


unsigned Gravel::Context::add_edges(const Gravel::Pointer::Module& module) {
 
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
   //Gravel::ConstSymbolList sl = ctx->getSymbols(module);

   // Find the number of actors with a mapping
   unsigned size = am.size();
 
   ActorMap::const_iterator amit;
   
   AssignmentSet::const_iterator asit;
   
   for (amit = am.begin() ; amit != am.end() ; amit++ ) {
       if (amit->second == module) {
           find_edges(amit->second, amit->first);
           
       }
   }
  // std::cerr << "Looking for assignments\n";
   for (asit = al.begin() ; asit != al.end() ; asit++ ) {
  //     std::cerr << "Found Assignment\n";
       Gravel::Pointer::Assignment assignment = *asit;
       assignment->propagate();
   } 
   
    unsigned edges_added = am.size() - size;

    return edges_added;
}

std::string Gravel::Context::getUniqueIdentifier() {
    std::stringstream ss;
    ss << "tmp_" << tempIdentifier++ ;
    
    return ss.str();
    
}

void Gravel::Context::propagate() {
    
    Gravel::ModuleSet::iterator mlit;
    
    for(mlit = ml.begin() ; mlit != ml.end() ; mlit++) {
        
        unsigned edges = 0;
        do { 
           edges = add_edges(*mlit);
         
        }
        while ( edges != 0);
         
    }
  
    // go through all modules 
    // collect all registered nodes 
    // register all edges from those nodes
    // repeat until number of additional edges is 0. 
    
    
}

void Gravel::Context::reset() {
    // resets the test fixture
    ml.clear();
    sm.clear();
    tempIdentifier = 0;
}

bool Gravel::Context::elaborate() {
    // create .gravel folder if it doesn't exist
    // emit files to temporary file 
    
    // call iverilog and elaborate design (capturing output)
    // report success / failure and output / error messages
    
    return true;
}