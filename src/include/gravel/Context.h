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
#include <gravel/Expression.h>

#include <set>
#include <map>
#include <vector>

namespace Gravel { 

    class ModuleInstantiation;
    
typedef std::map<Gravel::ModuleInstantiation, Gravel::Module> ModuleInstantiationMap;
typedef std::set<Gravel::Module> ModuleList;
typedef std::set<Gravel::Symbol> SymbolList;
typedef std::set<Gravel::Expression> ExpressionList;

typedef const std::set<Gravel::Module> ConstModuleList;
typedef const std::set<Gravel::Symbol> ConstSymbolList;
typedef const std::set<Gravel::Expression> ConstExpressionList;

// Module : Direction (Key for Multimap)


// Symbol (Value)


typedef std::multimap<SymbolKey, Gravel::Symbol>::iterator SymbolMapIterator;
typedef std::pair<SymbolMapIterator, SymbolMapIterator> SymbolRange;
typedef std::pair<ConstSymbolMapIterator, ConstSymbolMapIterator> ConstSymbolRange;

typedef std::map<Gravel::Expression, Gravel::Module> ExpressionMap;
typedef ExpressionMap::iterator ExpressionMapIterator;
typedef ExpressionMap::const_iterator ConstExpressionMapIterator;


class Context { 
   private : 
    	static Gravel::Context * pInstance;
        ModuleList ml;
        SymbolMap  sm;
        ExpressionMap em;
        Gravel::ModuleInstantiationMap mm;
        unsigned tempIdentifier;
   protected :
	Context(); 
        
   public : 
    	static Context * getInstance();
        void reset(); // should clear all context without memory leaks
        
        void printSymbols(std::ostream&); // does a dump of all symbols
        
        ConstSymbolList getSymbols(const Gravel::Module&) const ;
        ConstSymbolRange getSymbols(Gravel::Module module, Symbol::Direction direction) const;
     
        ConstExpressionList getExpressions(const Gravel::Module&) const ;
        
        std::string getUniqueIdentifier();
        
        ConstModuleList getModules() const;
        
        void insert(const Gravel::Module&, Gravel::ModuleInstantiation);
        
        
        void insert(const Gravel::Module&);
        bool exists(const Gravel::Module&);
       
        void insert(const Gravel::Module&, const Gravel::Symbol, const Gravel::Interface::Symbol::Direction&);
        bool exists(const Gravel::Module&, const Gravel::Symbol,const Gravel::Interface::Symbol::Direction&);
        
        bool isOwned(const Gravel::Symbol&);
        bool isOwned(const Gravel::Expression&);
        
        Gravel::Module owner(const Gravel::Symbol&);
        Gravel::Module owner(const Gravel::Expression&);
        
        void normalize();
        
        Gravel::Module getModule(const std::string&) const;
        void emit(std::ostream& os);
        bool elaborate();
        
};

};

#endif	/* CONTEXT_H */

