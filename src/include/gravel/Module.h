/* 
 * File:   Module.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 11:43 AM
 */

#ifndef MODULE_H
#define	MODULE_H


#include <iostream>
#include <string>
#include <vector>

#include <gravel/Object.h>
#include <gravel/Symbol.h>



namespace Gravel {

    namespace Implementation {
        class Symbol;
    };
    
class ModuleImplementation;
    
class ModuleInterface { 
   virtual const std::string getName() const = 0;
//   virtual std::ostream& emit(std::ostream& os) const = 0;
};


namespace Pointer { 

typedef boost::shared_ptr<ModuleImplementation> Module;

};

class Module : public Gravel::ModuleInterface {

    typedef std::vector<Gravel::Implementation::Symbol> SymbolList;

protected :  
   // Module();
   Gravel::Pointer::Module module;  
public : 

    Module(const std::string& name);
    Module(Gravel::Pointer::Module);
  //  Module(const Module &);
    const std::string getName() const;

    std::ostream& emit(std::ostream& os) const;
   // SymbolList getSymbols(Gravel::Symbol::Direction);
    bool operator==(const Module & ) const;
    void operator>>(Gravel::Symbol& gs);
    void operator<<(Gravel::Symbol& gs);
    bool operator<(const Module &) const;
    bool operator!=(const Module &) const;  
    //Gravel::Module & operator=(const Gravel::Module & rhs);
    
};



class SynthesizableModule { 
    public:
        virtual void synthesize() = 0;
};

 class InstantiatedModule { 
    public:
        typedef std::map<Gravel::Symbol, Gravel::Symbol> SymbolMap;
        InstantiatedModule(const std::string&, const Gravel::Module, const SymbolMap);
    private:
        const std::string name;
        const Gravel::Module module;
        const SymbolMap connections;
    };

 
namespace Exception {  
class ModuleNotFound : public std::exception { 
public:
    ModuleNotFound(std::string = "");
    const char * what() const throw();
    ~ModuleNotFound() throw();
private:
    std::string name;
};
};

struct MixedSeparatorException : public std::exception {};
   

 typedef struct { } Comma;
   typedef struct { } Semicolon;
   
   template <class T>
   class Separator_Traits {
       public : 
       //static const std::string Separator()  { 
       //    return " ";
       //}
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
   
   template < class Sep, class It > 
   class FormattedListObj { 
   public:
       typedef Separator_Traits<Sep> Traits;
       FormattedListObj(It be, It en) : be(be), en(en) {}
           
           static const std::string getSeparator() { 
               return Traits::Separator();
           }
           It be;
           It en;
       
   };
   
   template <class Sep, class It>
   FormattedListObj<Sep,It> FormattedList(It bs, It be) {
       return FormattedListObj<Sep,It>(bs, be);
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
             

              Gravel::SymbolSet::iterator it;
              
              for (it = fv.be ; it != fv.en ; it++) {
                  
                  if (fs.empty == false) {
                      fs << fs.getSeparator();
                  } 
                  
               
                  fs.empty = false;
 
                  fs << *it;
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
               FormattedStream<T,S,typename std::ostream::char_type>::emit(*fs,fv);
       }
       
       return *fs;
   }
   
   
};

#endif	/* MODULE_H */

