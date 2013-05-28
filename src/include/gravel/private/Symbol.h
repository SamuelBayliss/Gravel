/* 
 * File:   Symbol.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 5:18 PM
 */

#ifndef SYMBOLIMPLEMENTATION_H
#define	SYMBOLIMPLEMENTATION_H

#include <gravel/private/Actor.h>

namespace Gravel { 
    
    namespace Implementation { 
   class Symbol : public Gravel::Actor {         
private:
    std::string name;
    
protected:
    Symbol();
    
public:
    Symbol(const std::string&);
     const std::string getName() const;
     Gravel::Interface::Symbol::Type getType() const;
    
};

class Constant : public Gravel::Actor { 

private : 
    unsigned value;
public:
    
    
};

    };
    






};

#endif	/* SYMBOL_H */

