// XMLParser.h
//
// XMLParser will define the basic rules for parsing XML config files, and load
// everything into a CppDOM-style query tree.

#ifndef _METRO_XML_PARSER_H_
#define _METRO_XML_PARSER_H_

#include <iostream>
#include <fstream>
#include <string>

#include <boost/spirit.hpp>
#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/common.hpp>
#include <boost/spirit/tree/ast.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/function.hpp>

// TODO: remove this
using namespace boost::spirit;

typedef char char_t;
typedef file_iterator< char_t > iterator_t;
typedef scanner< iterator_t > scanner_t;
typedef rule< scanner_t > rule_t;

namespace metro
{
	struct xmlparse : public grammar< xmlparse >
	{
		static const int cdataID = 1;
		static const int attrib_nameID = 2;
		static const int attrib_valueID = 3;
		static const int attributeID = 4;
		static const int tag_nameID = 5;
		static const int unary_tagID = 6;
		static const int binary_tag_openID = 7;
		static const int binary_tag_closeID = 8;
		static const int binary_tagID = 9;
		static const int space_matchID = 10;

		template < typename ScannerT >
		struct definition
		{
			definition( xmlparse const& )
			{
				// set up the XML Parser
				// TODO: should this be somewhere else?

				// spirit is GAY!!! Gee Ay Why GAAAAAAAAAAY!!!!
				// The guy who wrote it can go fornicate himself with a metal pole. Seriously.
				// default spirit space_p is stupid
				space_match = +space_p;
				// cdata is anything but the start of a tag
				// also should probably drop white space on each end ('cause why would you care?)
				// by requiring that any white space be wrapped in non-white space
				cdata = token_node_d[ + ( ~ ch_p('<') ) ];
				// attrib name must start with a alphabetic
				// char, and ends at a space or an = sign
				attrib_name = token_node_d[ lexeme_d[ ( range_p( 'a','z' ) | range_p( 'A', 'Z' ) ) >> * ( ~ ch_p( '=' ) & ~space_p ) ] ];
				// value is any double-quoted string
				attrib_value = token_node_d[ inner_node_d[ ch_p( '"' ) >> * ( ~ ch_p( '"' ) ) >> ch_p( '"' ) ] ];
				// attribute is a name="value" set
				attribute = infix_node_d[ attrib_name >> ch_p( '=' ) >> attrib_value ];
				tag_name = token_node_d[ + ( ~ space_p & ~ ch_p( '>' ) & ~ ch_p( '/' ) ) ];
				unary_tag = discard_node_d[ ch_p( '<' ) ] >> tag_name >> * ( attribute | discard_node_d[ space_match ] ) >> ch_p( '/' ) >> discard_node_d[ ch_p( '>' ) ];
				binary_tag_open = discard_node_d[ ch_p( '<' ) ] >> root_node_d[ tag_name ] >> * ( attribute | discard_node_d[ space_match ] ) >> discard_node_d[ ch_p( '>' ) ];
				binary_tag_close = discard_node_d[ ch_p( '<' ) ] >> ch_p( '/' ) >> tag_name >> discard_node_d[ ch_p( '>' ) ];
				binary_tag = binary_tag_open >> * ( binary_tag | unary_tag | cdata ) >> binary_tag_close;
			}

			rule< ScannerT, parser_context, parser_tag< cdataID > > cdata;
			rule< ScannerT, parser_context, parser_tag< attrib_nameID > > attrib_name;
			rule< ScannerT, parser_context, parser_tag< attrib_valueID > > attrib_value;
			rule< ScannerT, parser_context, parser_tag< attributeID > > attribute;
			rule< ScannerT, parser_context, parser_tag< tag_nameID > > tag_name;
			rule< ScannerT, parser_context, parser_tag< unary_tagID > > unary_tag;
			rule< ScannerT, parser_context, parser_tag< binary_tag_openID > > binary_tag_open;
			rule< ScannerT, parser_context, parser_tag< binary_tag_closeID > > binary_tag_close;
			rule< ScannerT, parser_context, parser_tag< binary_tagID > > binary_tag;
			rule< ScannerT, parser_context, parser_tag< space_matchID > > space_match;

			rule< ScannerT, parser_context, parser_tag< binary_tagID > > const&
			start() const { return binary_tag; }
		};
	};

	class XMLParser
	{
	public:
		XMLParser( void );

		void parse_file( std::string filename );

	private:
	};
}

#endif
