// XMLNode.cpp

#include "XMLNode.h"

namespace metro
{
	XMLNode::XMLNode(std::string pName, std::vector< XMLNodePtr > pChildren, std::vector< std::pair< std::string, std::string > > pAttribs) :
		mName( pName ),
		mChildren( pChildren ),
		mAttribs( pAttribs )
	{}

	std::string const& XMLNode::getName( void )
	{
		return mName;
	}

	std::vector< std::pair< std::string, std::string > > const& XMLNode::getAttribs( void )
	{
		return mAttribs;
	}

	std::vector< std::string > XMLNode::getAttrib( std::string attribName )
	{
		std::vector< std::string > result;
		for ( int i = 0; i < mAttribs.size(); ++i )
			if ( mAttribs[i].first == attribName )
				result.push_back( mAttribs[i].second );
		return result;
	}

	std::vector< XMLNodePtr > const& XMLNode::getChildren( void )
	{
		return mChildren;
	}

	std::vector< XMLNodePtr > XMLNode::getChildren( std::string childName )
	{
		std::vector< XMLNodePtr > result;

		for ( int i = 0; i < mChildren.size(); ++i )
			if ( mChildren[i]->getName() == childName )
				result.push_back( mChildren[i] );
		return result;
	}

	XMLNodePtr XMLNode::getChild( void )
	{
		if ( mChildren.size() == 0 )
			return XMLNodePtr();
		return mChildren[0];
	}
}
