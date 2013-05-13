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
    
class SymbolImplementation : public Gravel::Actor { 
    
private:
    std::string name;
    
protected:
    SymbolImplementation();
public:
    SymbolImplementation(const std::string&);
     const std::string getName() const;
};


};

#endif	/* SYMBOL_H */

