/* 
 * File:   ModuleImplementation.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 3:56 PM
 */

#ifndef MODULEIMPLEMENTATION_H
#define	MODULEIMPLEMENTATION_H

#include <string>

namespace Gravel { 

class ModuleImplementation { 
    
private:
    std::string name;
    
protected:
    ModuleImplementation();
public:
    ModuleImplementation(const std::string&);
     const std::string getName();
};


};

#endif	/* MODULEIMPLEMENTATION_H */

