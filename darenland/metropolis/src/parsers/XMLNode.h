// XMLNode.h
//
// A node in an XML tree resulting from parsing a file.
// It stores the tag name and attributes and children.

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

#define XMLNodePtr boost::shared_ptr< XMLNode >

namespace metro
{
	class XMLNode
	{
	public:
		XMLNode(std::string pName, std::vector< XMLNodePtr > pChildren, std::vector< std::pair< std::string, std::string > > pAttribs);
		std::string const& getName( void );

		// return all atributes as a vector of key/value pairs
		std::vector< std::pair< std::string, std::string > > const& getAttribs( void );
		// return the values of attributes matching the given key. If none match, the vector will have 0 length
		std::vector< std::string > getAttrib( std::string attribName );

		// return all children in the order they were found in the file
		std::vector< XMLNodePtr > const& getChildren( void );
		// return all children whos names match the given name
		std::vector< XMLNodePtr > getChildren( std::string childName );
		// returns the first child. This should only be used when you are sure there will be exactly
		// one child of the current node.
		XMLNodePtr getChild( void );

	private:
		std::string mName;
		std::vector< XMLNodePtr > mChildren;
		std::vector< std::pair< std::string, std::string > > mAttribs;
	};
}
