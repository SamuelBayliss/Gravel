#include <gravel/Context.h>
#include <boost/bind.hpp>
#include <stdlib.h>

#include <algorithm>
#include <functional>
#include <string>

Gravel::Context * Gravel::Context::pInstance = NULL;

Gravel::Context * Gravel::Context::getInstance()
{
  if (Gravel::Context::pInstance == NULL) {
    Gravel::Context::pInstance = new Gravel::Context();
  }
  return pInstance;
}

Gravel::Context::Context() { 
    
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

void Gravel::Context::insert(const Gravel::Module& module, const Gravel::Symbol symbol, const Gravel::SymbolInterface::Direction& direction) {
    SymbolKey key(module, direction);
    sm.insert(std::pair<SymbolKey, Symbol>(key, symbol));
}

struct symbol_matches : public std::binary_function<std::pair<const Gravel::SymbolKey, Gravel::Symbol>, Gravel::Symbol, bool> {
        bool operator()(const std::pair<const Gravel::SymbolKey, Gravel::Symbol>& p,  const Gravel::Symbol & n) const {
           return (p.second) == n;
        } 
};


bool Gravel::Context::exists(const Gravel::Module& module, const Gravel::Symbol symbol, const Gravel::SymbolInterface::Direction& direction) {
    SymbolKey key(module, direction);
    ConstSymbolRange sr = sm.equal_range(key);  
    
        std::binder2nd<symbol_matches>  match_object((symbol_matches()), symbol);
   // Gravel::ModuleList::iterator mlit = std::find_if(ml.begin(), ml.end(), match_object);
    
    return (std::find_if(sr.first, sr.second, match_object) == sr.second);//std::bind2nd<std::equal_to<Gravel::Symbol>, Gravel::Symbol>(eq,symbol)) != sr.second);
}

Gravel::ConstModuleList Gravel::Context::getModules() const { 
    return ml;
}

Gravel::ConstSymbolRange Gravel::Context::getSymbols(Gravel::Module module, Symbol::Direction direction) const { 
    SymbolKey key(module, direction);
        return sm.equal_range(key);
    
}

void Gravel::Context::emit(std::ostream& os) {
    // emit to file
    
    os << ml.size() << std::endl;
    
}

bool Gravel::Context::elaborate() {
    // create .gravel folder if it doesn't exist
    // emit files to temporary file 
    
    // call iverilog and elaborate design (capturing output)
    // report success / failure and output / error messages
    
    return true;
}