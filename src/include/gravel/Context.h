/* 
 * File:   Context.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 11:19 AM
 */

#ifndef CONTEXT_H
#define	CONTEXT_H

#include <gravel/Symbol.h>
#include <gravel/Module.h>

#include <set>
#include <map>
#include <vector>

namespace Gravel { 

typedef std::set<Gravel::Module> ModuleList;
typedef std::set<Gravel::Symbol> SymbolList;

typedef const std::set<Gravel::Module> ConstModuleList;
typedef const std::set<Gravel::Symbol> ConstSymbolList;


// Module : Direction (Key for Multimap)


// Symbol (Value)


typedef std::multimap<SymbolKey, Gravel::Symbol>::iterator SymbolMapIterator;
typedef std::pair<SymbolMapIterator, SymbolMapIterator> SymbolRange;
typedef std::pair<ConstSymbolMapIterator, ConstSymbolMapIterator> ConstSymbolRange;

class Context { 
   private : 
    	static Gravel::Context * pInstance;
        ModuleList ml;
        SymbolMap  sm;
   protected :
	Context(); 
        
   public : 
    	static Context * getInstance();
        ConstSymbolList getSymbols(const Gravel::Module&) const ;
        ConstSymbolRange getSymbols(Gravel::Module module, Symbol::Direction direction) const;
     
        ConstModuleList getModules() const;
        void insert(const Gravel::Module&);
        bool exists(const Gravel::Module&);
       
        void insert(const Gravel::Module&, const Gravel::Symbol, const Gravel::SymbolInterface::Direction&);
        bool exists(const Gravel::Module&, const Gravel::Symbol,const Gravel::SymbolInterface::Direction&);
        
        Gravel::Module getModule(const std::string&) const;
        void emit(std::ostream& os);
        bool elaborate();
        
};

};

#endif	/* CONTEXT_H */

