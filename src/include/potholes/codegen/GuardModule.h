/* 
 * File:   GuardModule.h
 * Author: sb1708
 *
 * Created on April 30, 2013, 12:10 PM
 */

#ifndef GUARDMODULE_H
#define	GUARDMODULE_H

#include <potholes/codegen/Module.h>

namespace Potholes { 
    namespace Generator { 
        class GuardModule : public Potholes::Generator::Module { 
        public:
            GuardModule(clast_stmt *);
            void register_symbols();
            void build_chain();
        };

    }

};

#endif	/* GUARDMODULE_H */

