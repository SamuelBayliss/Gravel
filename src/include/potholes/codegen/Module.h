/* 
 * File:   CodegenModule.h
 * Author: sb1708
 *
 * Created on April 30, 2013, 12:06 PM
 */

#ifndef CODEGENMODULE_H
#define	CODEGENMODULE_H

#include <gravel/Module.h>
#include <gravel/private/Module.h>


#include <cloog/cloog.h>

namespace Potholes { 
    

    
    namespace Generator { 
           
        
        class Module : public Gravel::ModuleImplementation { 
        public:
            Module(clast_stmt *);
            virtual void register_symbols();
            virtual void build_chain();
        
        };

        typedef boost::shared_ptr<Potholes::Generator::Module> CodegenModulePtr;
        
    }

};

#include <potholes/codegen/AssignmentModule.h>
#include <potholes/codegen/ForModule.h>
#include <potholes/codegen/GuardModule.h>
#include <potholes/codegen/SequentialModule.h>


#endif	/* CODEGENMODULE_H */

