/* 
 * File:   AssignmentModule.h
 * Author: sb1708
 *
 * Created on April 30, 2013, 12:10 PM
 */

#ifndef ASSIGNMENTMODULE_H
#define	ASSIGNMENTMODULE_H

#include <potholes/codegen/Module.h>

namespace Potholes { 
    namespace Generator { 
        class AssModule : public Potholes::Generator::Module { 
        public:
            AssModule(clast_stmt *);
            void register_symbols();
            void build_chain();
        };

    };

};

#endif	/* ASSIGNMENTMODULE_H */

