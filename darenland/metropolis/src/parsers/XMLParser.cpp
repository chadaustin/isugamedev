// XMLParser.cpp

#include "XMLParser.h"
#include "XMLNode.h"

namespace metro
{
	XMLParser::XMLParser( void )
	{
	}

	// Here's some typedefs to simplify things
	typedef char const*                              iterator_t;
	typedef tree_match<iterator_t>                   parse_tree_match_t;
	typedef parse_tree_match_t::const_tree_iterator  iter_t;
	XMLNodePtr eval_expression(iter_t const& i);

	// TODO delete this
	void printTree( const XMLNodePtr root, int tab = 0 )
	{
		std::cout << "[TREE]";

		for ( int i = 0; i < tab; ++i )
			std::cout << "   ";

		std::cout << root->getName();

		for ( std::vector< std::pair< std::string, std::string > >::const_iterator itr = root->getAttribs().begin(); itr < root->getAttribs().end(); ++itr )
			std::cout << " > " << itr->first << "=:" << itr->second << ":";
		std::cout << std::endl;

		for ( std::vector< XMLNodePtr >::const_iterator itr = root->getChildren().begin(); itr < root->getChildren().end(); ++itr )
			printTree( *itr, tab + 1 );

		return;
	}

	std::string trim(std::string s)
	{
		int start = 0;
		int end = s.size() - 1;
		std::string result;

		while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
			++start;
		while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
			--end;

		for ( int i = start; i <= end; ++i )
			result += s[i];

		return result;
	}

	void XMLParser::parse_file( std::string filename )
	{
		//iterator_t start( filename.c_str() );
		//iterator_t end( start.make_end() );
		//tree_parse_info<> info = ast_parse( start, end, *anychar_p );

		xmlparse x;
		std::string s = "";

		std::ifstream in( filename.c_str() );
		while ( !in.eof() )
			s += in.get();

		in.close();

		tree_parse_info<> info = ast_parse(s.c_str(), x);

		XMLNodePtr root = eval_expression( info.trees.begin() );
		printTree( root );

		XMLNodePtr bod = (root->getChildren("body"))[0];
		printTree( bod );
		
		std::cout << "bgcolor is: " << bod->getAttrib("bgcolor")[0] << std::endl;
	}

	std::string valtos(std::vector<char>::const_iterator i1, std::vector<char>::const_iterator i2)
	{
		std::string str = "";
		while ( i1 < i2 )
		{
			str += *i1;
			++i1;
		}
		return str;
	}

	XMLNodePtr eval_expression(iter_t const& i)
	{
		std::string myName;
		std::vector< XMLNodePtr > myKids;
		std::vector< std::pair< std::string, std::string > > myAttribs;

		if ( i->value.id() == xmlparse::cdataID )
		{
			std::string val = trim( valtos( i->value.begin(), i->value.end() ) );
			if ( val == "" )
				myName = "null";
			else
				myName = "cdata";
			myAttribs.push_back( std::make_pair( "text", val ) );
		}
		else if ( i->value.id() == xmlparse::attrib_nameID )
			; // handled by attribute
		else if ( i->value.id() == xmlparse::attrib_valueID )
			; // handled by attribute
		else if ( i->value.id() == xmlparse::attributeID )
		{
			iter_t chilluns = i->children.begin();
			std::string attr = valtos( chilluns->value.begin(), (chilluns++)->value.end() );
			std::string val = valtos( chilluns->value.begin(), chilluns->value.end() );
			myAttribs.push_back( std::make_pair( attr, val ) );
		}
		else if ( i->value.id() == xmlparse::tag_nameID )
		{
			// we're a name, so try to pull attribs (which should be our only kids)
			// and set our name
			myName = valtos( i->value.begin(), i->value.end() );

			iter_t chilluns = i->children.begin();
			while ( chilluns < i->children.end() )
			{
				XMLNodePtr temp = eval_expression( chilluns++ );
				myAttribs.push_back( temp->getAttribs()[0] );
			}
		}
		else if ( i->value.id() == xmlparse::unary_tagID )
		{
			// children will be name followed by attribs
			iter_t chilluns = i->children.begin();

			myName = valtos( chilluns->value.begin(), (chilluns++)->value.end() );
			while ( chilluns < i->children.end() - 1 )
			{
				XMLNodePtr temp = eval_expression( chilluns++ );
				myAttribs.push_back( temp->getAttribs()[0] );
			}
		}
		else if ( i->value.id() == xmlparse::binary_tag_openID )
			; // this gets discarded because the tag_name steals its children
		else if ( i->value.id() == xmlparse::binary_tag_closeID )
		{
			// the children will be ['/', "name"] because spirit is so special
			iter_t chilluns = i->children.begin() + 1;
			myName = valtos( chilluns->value.begin(), chilluns->value.end() );
		}
		else if ( i->value.id() == xmlparse::binary_tagID )
		{
			// have we closed the tag successfully?
			bool tagClosed = false;

			iter_t chilluns = i->children.begin();

			// evaluate the first child, which will have our name and attribs
			XMLNodePtr me = eval_expression( chilluns++ );
			// pull the tag name, which should be the first child value
			myName = me->getName();
			// the name evaluated its children as attribs, so copy them out
			for ( int at = 0; at < me->getAttribs().size(); ++at )
				myAttribs.push_back( me->getAttribs()[ at ] );

			// now the rest of our children should evaluate as either other tags,
			// or cdata (which will return a node same as a tag would) so add them
			// to our node children, return, and we're done!
			// (oh, but check for null nodes since spirit is retarded about white space)
			while ( chilluns < i->children.end() )
			{
				XMLNodePtr temp = eval_expression( chilluns++ );
				if ( temp->getName() == myName )
					tagClosed = true;
				else if ( temp->getName() != "null" )
					myKids.push_back( temp );
			}

			if ( !tagClosed )
			 std::cout << "!!!!![XMLParser] Tag <" << myName << "> not closed properly" << std::endl;
		}

		return XMLNodePtr( new XMLNode( myName, myKids, myAttribs ) );
	}
}
