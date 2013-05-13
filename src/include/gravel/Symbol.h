/* 
 * File:   Symbol.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 4:53 PM
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

#include <gravel/Object.h>
#include <map>
namespace Gravel { 
    
    class SymbolImplementation;
    
    class Module;
    
    class SymbolInterface { 
    public : 
        typedef enum Direction {Input, Output, Local};
        
           virtual const std::string getName() const = 0;
    };
    
    typedef boost::shared_ptr<SymbolImplementation> SymbolPtr;
    
    class Symbol : public SymbolInterface { 
    private : 
        SymbolPtr symbol;
    protected : 
        Symbol();
    public : 
       Symbol(const std::string&);
       const std::string getName() const;
       bool operator==(const Gravel::Symbol&) const;
    };
 
    typedef std::pair<Gravel::Module, Gravel::Symbol::Direction> SymbolKey;
    typedef std::multimap<SymbolKey, Gravel::Symbol> SymbolMap;
    typedef std::multimap<SymbolKey, Gravel::Symbol>::const_iterator ConstSymbolMapIterator;
    std::ostream& operator<< (std::ostream& os, const Gravel::Symbol& s);
    
}

#endif	/* SYMBOL_H */

