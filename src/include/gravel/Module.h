/* 
 * File:   Module.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 11:43 AM
 */

#ifndef MODULE_H
#define	MODULE_H

#include <gravel/Object.h>

#include <gravel/Module.h>
#include <gravel/Symbol.h>

#include "private/Symbol.h"
#include "Context.h"

#include <vector>
#include <iterator>
namespace Gravel {

class ModuleImplementation;
    
class ModuleInterface { 
   virtual const std::string getName() const = 0;
   virtual std::ostream& emit(std::ostream& os) const = 0;
};


typedef boost::shared_ptr<ModuleImplementation> ModulePtr;

class Module : public Gravel::ModuleInterface {

    typedef std::vector<Gravel::SymbolImplementation> SymbolList;

protected :  
    Module();
    ModulePtr module;
public : 
    Module(const std::string& name);
    const std::string getName() const;
    std::ostream& emit(std::ostream& os) const;
   // SymbolList getSymbols(Gravel::Symbol::Direction);
    void operator>>(Gravel::Symbol& gs);
    void operator<<(Gravel::Symbol& gs);
    bool operator<(const Module &) const;
    
};

class ModuleNotFound : public std::exception { 
public:
    ModuleNotFound(std::string = "");
    const char * what() const throw();
    ~ModuleNotFound() throw();
private:
    std::string name;
};

struct MixedSeparatorException : public std::exception {};
   

 typedef struct { } Comma;
   typedef struct { } Semicolon;
   
   template <class T>
   class Separator_Traits {
       public : 
       static const std::string Separator()  { 
           return " ";
       }
   };
   
   template<>
   class Separator_Traits<Comma> { 
       public : 
           static const std::string Separator() {
               return ",";
           }
   };
  
   template<>
   class Separator_Traits<Semicolon> { 
       public : 
           static const std::string Separator()  {
               return ";";
           }
   };
   
   template < class T, class S > 
   class FormattedListObj { 
   public:
       typedef Separator_Traits<S> Traits;
       FormattedListObj(T be, T en) : be(be), en(en) {}
           
           static const std::string getSeparator() { 
               return Traits::Separator();
           }
           T be;
           T en;
       
   };
   
   template <class S, class T>
   FormattedListObj<T,S> FormattedList(T bs, T be) {
       return FormattedListObj<T,S>(bs, be);
   }


   class SeparatorInterface {
   public:
        virtual const std::string getSeparator()= 0;
   };

     
   template <class Sep, class It, class charT, class Traits = std::char_traits<charT> >
   class FormattedStream : public std::basic_ostream<charT, Traits>, public SeparatorInterface {
       
       public : 
           FormattedStream(std::basic_ostream<charT, Traits> & ostr) : std::basic_ostream<charT, Traits>(ostr.rdbuf()), empty(true) {
               
           }
            bool isEmpty() const {
                return empty;
            }
            
            const std::string getSeparator() { 
                return traits.Separator();
            }
            
            
            static void emit(FormattedStream & fs, FormattedListObj<Sep, It> fv) {
             

              Gravel::ConstSymbolMapIterator it;
              
              for (it = fv.be ; it != fv.en ; it++) {
                  
                  if (!fs.empty) {
                      fs << fs.getSeparator();
                  } 
                  fs.empty = false;
 
                  fs << it->second;
              }
              
              //  std::ostream_iterator<std::pair<Gravel::SymbolKey, Gravel::Symbol> > out_it (fs,fv.getSeparator().c_str());
              //  std::copy ( fv.be, fv.en, out_it );
              }
            
           bool empty;
          
           private : 
               Separator_Traits<Sep> traits;
               FormattedStream(const FormattedStream&) {};
               
           };
   
 
   template <class T, class S, class P, class Q> 
   FormattedStream<T, S, P,Q>& operator<<(FormattedStream<T, S, P,Q>& fs, const FormattedListObj<T,S> & fv) {
      
       FormattedStream<T,S,P,Q>::emit(fs, fv);
       return fs;
      
   }
   
   
   
   template <class T, class S>
   FormattedStream<T, S, std::ostream::char_type>& operator<<(std::ostream& sink, const FormattedListObj<T, S>& fv) {
       
       FormattedStream<T, S, std::ostream::char_type> * fs;
       
       try {
           SeparatorInterface& si = dynamic_cast<SeparatorInterface&>(sink);
           if (si.getSeparator() != fv.getSeparator()) { 
               throw Gravel::MixedSeparatorException();
           }
           fs = dynamic_cast< FormattedStream <T, S, std::ostream::char_type, std::ostream::traits_type> * >(&sink);
           FormattedStream<T,S,typename std::ostream::char_type>::emit(*fs,fv);
    
           
       } catch(std::bad_cast& ) { 
               fs  = new FormattedStream<T, S, typename std::ostream::char_type>(sink);
       }
       
       return *fs;
   }
   
   
};

#endif	/* MODULE_H */

