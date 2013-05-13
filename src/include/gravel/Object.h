/* 
 * File:   Object.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 11:20 AM
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <boost/shared_ptr.hpp>

namespace Gravel { 

        template <class T>
        class ReferenceCountedObject : boost::shared_ptr<T> {

                
    
    
        };
};

#endif	/* OBJECT_H */

