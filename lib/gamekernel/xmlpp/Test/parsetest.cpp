// Parse test application
// Based upon: parsetest.cpp from xmlpp

// needed includes
#include <fstream>
#include <iostream>
#include <ctime>
#include <xmlpp/xmlpp.h>

// namespace includes
using namespace xmlpp;
using namespace std;


// dumps the node
void dump_node( xmlnode &node, int level = 0 )
{
   xmlstring name = node.name();
   xmlnodetype type = node.get_type();

   for(int i=0;i<level;i++) cout << " ";

   char c = ' ';
   switch(type)
   {
   case xml_nt_node:
      c = '+';
      break;
   case xml_nt_leaf:
      c = '-';
      break;
   case xml_nt_document:
      c = '\\';
      break;
   case xml_nt_cdata:
      c = '#';
      name = node.get_cdata();
      break;
   }

   cout << c << name.c_str() << endl;
   xmlattributes attr = node.get_attrmap();

   // guru: added output of attributes
   for (xmlattributes::iterator j = attr.begin(); j!=attr.end(); j++)
   {
      for (int i=0; i<level; i++) cout << " ";
      cout << "   ";
      cout << j->first << ": " << j->second << endl;
   }

   xmlnodelist& nlist = node.children();

   xmlnodelist::const_iterator iter, stop;
   iter = nlist.begin();
   stop = nlist.end();

   while (iter != stop)
   {
      xmlnodeptr node = *iter;

      dump_node ( *node, level+1 );

      ++iter;
   }
};

void process_xml( std::string filename )
{
   cout << "processing [" << filename << "] ..." << endl;

   xmlcontextptr context( new xmlcontext );
   xmldocument node( context );
   ifstream istr( filename.c_str() );

   // Verify that file opened
   if(!istr)
   {
      std::cerr << "Bad file: " << filename << std::endl;
      return;
   }

   try
   {
      clock_t tstart = ::clock();

      node.load( istr, context );

      clock_t tstop = ::clock();
      cout << " needed " <<
         (tstop-tstart)/static_cast<float>(CLOCKS_PER_SEC)
         << " seconds." << endl;

      dump_node( node );

      ofstream ostr( "parsetest.xml" );
      node.save( ostr );
      ostr.close();

   }
   catch (xmlerror e)
   {
      xmllocation where( context->get_location() );
      xmlstring errmsg;
      e.get_strerror(errmsg);

      // print out where the error occured
      cout << filename << ":" << where.get_line() << " ";
      cout << "at position " << where.get_pos();
      cout << ": error: " << errmsg.c_str();
      cout << endl;

      // print out line where the error occured
      ifstream errfile( filename.c_str() );
      int linenr = where.get_line();
      char linebuffer[1024];
      for(int i=0;i<linenr&&!errfile.eof();i++)
         errfile.getline(linebuffer,1024);

      int pos = where.get_pos();
      if (pos>=80) pos%=80;

      std::string line( linebuffer + (where.get_pos()-pos) );
      if (line.length()>=79) line.erase(79);
      cout << line.c_str() << endl;
      for(int j=2;j<pos;j++)
         cout << ' ';
      cout << '^' << endl;
   }
}

int main(int argc, char* argv[])
{
   for(int i=1;i<argc;i++)
   {
      process_xml( std::string(argv[i]) );
   }

   return 0;
}
