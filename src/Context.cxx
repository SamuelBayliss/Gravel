#include <gravel/Context.h>
#include <boost/bind.hpp>
#include <stdlib.h>

#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
Gravel::Context * Gravel::Context::pInstance = NULL;

Gravel::Context * Gravel::Context::getInstance()
{
  if (Gravel::Context::pInstance == NULL) {
    Gravel::Context::pInstance = new Gravel::Context();
  }
  return pInstance;
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
    Gravel::ModuleList::iterator mlit = std::find_if(ml.begin(), ml.end(), match_object);
    
    if (mlit == ml.end()) { 
        throw Gravel::ModuleNotFound(name);
    } else { 
      return *mlit;
    }
    
}

void Gravel::Context::insert(const Gravel::Module& module) { 
    ml.insert(module);
}

bool Gravel::Context::exists(const Gravel::Module& module) { 
    // lookup in module
    return (ml.find(module) != ml.end());

}

void Gravel::Context::insert(const Gravel::Module& module, const Gravel::Symbol symbol, const Gravel::Interface::Symbol::Direction& direction) {
    SymbolKey key(module, direction);
    sm.insert(std::pair<SymbolKey, Symbol>(key, symbol));
}

struct symbol_matches : public std::binary_function<std::pair<const Gravel::SymbolKey, Gravel::Symbol>, Gravel::Symbol, bool> {
        bool operator()(const std::pair<const Gravel::SymbolKey, Gravel::Symbol>& p,  const Gravel::Symbol & n) const {
           return (p.second) == n;
        } 
};


bool Gravel::Context::exists(const Gravel::Module& module, const Gravel::Symbol symbol, const Gravel::Interface::Symbol::Direction& direction) {
    SymbolKey key(module, direction);
    ConstSymbolRange sr = sm.equal_range(key);  
    
        std::binder2nd<symbol_matches>  match_object((symbol_matches()), symbol);
   // Gravel::ModuleList::iterator mlit = std::find_if(ml.begin(), ml.end(), match_object);
    
    return (std::find_if(sr.first, sr.second, match_object) == sr.second);//std::bind2nd<std::equal_to<Gravel::Symbol>, Gravel::Symbol>(eq,symbol)) != sr.second);
}

Gravel::ConstModuleList Gravel::Context::getModules() const { 
    return ml;
}

Gravel::ConstSymbolList Gravel::Context::getSymbols(const Gravel::Module& module) const { 
    Gravel::ConstSymbolMapIterator mit;
    
    Gravel::SymbolList sl;
    
    for (mit = sm.begin() ; mit != sm.end() ; mit++ ) {
        Gravel::SymbolKey sk = mit->first;
    
        if (sk.first == module) {
            sl.insert(mit->second);
        }
        
    }
    return sl;
}

Gravel::ConstExpressionList Gravel::Context::getExpressions(const Gravel::Module& module) const {
     Gravel::ConstExpressionMapIterator mit;
     
     Gravel::ExpressionList el;
     
    for (mit = em.begin() ; mit != em.end() ; mit++ ) {
        if (mit->second == module) {
            el.insert(mit->first);
        }
    }
     return el;
}

Gravel::ConstSymbolRange Gravel::Context::getSymbols(Gravel::Module module, Symbol::Direction direction) const { 
    SymbolKey key(module, direction);
        return sm.equal_range(key);
    
}

void Gravel::Context::emit(std::ostream& os) {
    // emit to file
    
    os << ml.size() << std::endl;
    
}

void Gravel::Context::printSymbols(std::ostream& os) { 
    Gravel::SymbolMapIterator sit;
    for (sit = sm.begin() ; sit != sm.end() ; sit++) {
        Gravel::SymbolKey key = sit->first;
        Gravel::Symbol symbol = sit->second; 
        os << symbol << "\n";
    }
  
}

bool Gravel::Context::isOwned(const Gravel::Symbol& symbol) {
    normalize();
    
    Gravel::ConstSymbolMapIterator mit;
    for (mit = sm.begin() ; mit != sm.end() ; mit++ ) {
        if (mit->second == symbol) {
            return true;
        }
    }
    return false;
}

bool Gravel::Context::isOwned(const Gravel::Expression& expression) {
    normalize();
    
    Gravel::ConstExpressionMapIterator mit;
    for (mit = em.begin() ; mit != em.end() ; mit++ ) {
        if (mit->first == expression) { 
            return true;
        }
    }
    return false;
}


Gravel::Module Gravel::Context::owner(const Gravel::Symbol&) {
   
}

Gravel::Module Gravel::Context::owner(const Gravel::Expression&) {
    
}
        

void find_edges(const Gravel::Module& module, const Gravel::Symbol& symbol) { 
  
    // register symbol with module
    
    // add all the inputs and outputs for this symbol to symbol and expression lists(registering them with module)
    
    
    
}
void find_edges(const Gravel::Module& module, const Gravel::Expression& expression) { 
    // register symbol with module
    
    // add all the inputs and outputs for this expression to symbol and expression lists(registering them with module)
}

unsigned add_edges(const Gravel::Module& module) {
    
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    Gravel::ConstSymbolList sl = ctx->getSymbols(module);
    Gravel::ConstExpressionList el = ctx->getExpressions(module);
    
    unsigned size = sl.size() + el.size();
    
    for (Gravel::ConstSymbolList::iterator cslit = sl.begin() ; cslit != sl.end() ; cslit++) {
        find_edges(module, *cslit);
    }
      for (Gravel::ConstExpressionList::iterator celit = el.begin() ; celit != el.end() ; celit++) {
        find_edges(module, *celit);
    }
    
    return sl.size() + el.size() - size;
}

std::string Gravel::Context::getUniqueIdentifier() {
    std::stringstream ss;
    ss << "tmp_" << tempIdentifier++ ;
    
    return ss.str();
    
}

void Gravel::Context::normalize() {
    
    Gravel::ModuleList::iterator mlit;
    
    for(mlit = ml.begin() ; mlit != ml.end() ; mlit++) {
      
        while ( add_edges(*mlit) != 0) {;}
    
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