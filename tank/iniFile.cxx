
#include <iostream>
#include "regexx.hh"
#include "iniFile.h"

void iniFile::load( const char* const filename )
{
   regexx::Regexx sectionMatcher, sectionNameMatcher;
   regexx::Regexx commentSubst;
   regexx::Regexx keyMatcher;
   std::string inifiletext;

   std::ifstream dataFile;
   dataFile.open( filename, std::ios::in );
   iniUtil::getAll( dataFile, inifiletext );
   dataFile.close();
   int num_of_matches;

   // remove comments...
   std::string nocomments;
   nocomments.reserve( inifiletext.size() );

   // remove all /* comments */
   nocomments = commentSubst.replace( inifiletext, "/[\\*]+[^{\\*/}]*[\\*]+/", "", regexx::Regexx::global);
   inifiletext = nocomments;
    
   // remove all // comments.
   nocomments = commentSubst.replace( inifiletext, "//[^\n]*", "", regexx::Regexx::global);
   inifiletext = nocomments;
    
   try
   {
      // divide the inifile into individual sections, each match should look like this:
      // [section]
      // key1 = value1
      // ...
      // keyn = valuen
      num_of_matches = sectionMatcher.exec( inifiletext,"\\[[^\\[]*", regexx::Regexx::global);

       for (int section = 0; section < sectionMatcher.match.size();  ++section)
       {
         std::string sectiontext = sectionMatcher.match[section];

         // extract the [sectionname] from the section.  
         // The match should be the name without the []
         // NOTE: couldn't figure out the stingy regex, 
         //       but the greedy one should work since there should only be one [] pair, 
         //       by definition of sectionMatcher regex.
         num_of_matches = sectionNameMatcher.exec( sectiontext, "\\[(.*)\\]", regexx::Regexx::global);
         std::string sectionname;
         if (num_of_matches != 0)
         { 
            sectionname = sectionNameMatcher.match[0].atom[0]; 
         } 
         else 
         { 
            sectionname = "--- not found: possible regex error?";
         }
         //         std::cout<<"Group: " << sectionname<<"\n"<<std::flush;

         // make sure that iniFile contains the section, 
         // NOTE: only useful if there are no keys, otherwise redundant.
         this->putSection( sectionname, iniSection() );
         
         // extract all the keys within the section
         // stips any whitespace before keyname, before and after =, and after the value.
         // i.e.     key name      =      value   string  
         //      becomes "key name" and "value   string"
         num_of_matches = keyMatcher.exec( sectiontext,"[ ]*([^=^\n]*[^=^ ^\n])[ ]*=+[ ]*([^\n]*[^ ^\n]?)[\n]*", regexx::Regexx::global);
         //       std::cout << "Found " << num_of_matches <<" entries:"<< endl;

         for (int key = 0; key < keyMatcher.match.size();  ++key)
         {
            const int keyStringIndex = 0, valueStringIndex = 1;
            //        std::cout << keyMatcher.match[entry].atom[key] << " = " << keyMatcher.match[entry].atom[value] << "\n"<<std::flush;

            std::string name = keyMatcher.match[key].atom[keyStringIndex];
            std::string data = keyMatcher.match[key].atom[valueStringIndex];
            this->putKey( sectionname, name, data );
         }
       }
   } // end of try
   catch(regexx::Regexx::CompileException &e) 
   {
       std::cerr << e.message().c_str() << std::endl;
   }
}