/* 
 * File:   ModuleImplementation.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 3:56 PM
 */

#ifndef MODULEIMPLEMENTATION_H
#define	MODULEIMPLEMENTATION_H

#include <string>

#include <gravel/Module.h>

namespace Gravel { 


    
class ModuleImplementation : public Gravel::ModuleInterface { 
    
private:
    std::string name;
    
protected:
    ModuleImplementation();
public:
    ModuleImplementation(const std::string&);
     const std::string getName() const;
     bool operator<(const ModuleImplementation &) const;
    // virtual std::ostream& emit(std::ostream& os) const;
};


};

#endif	/* MODULEIMPLEMENTATION_H */

