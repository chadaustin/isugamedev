/*************************************************************************/
/*                                                                       */
/*  Regexx - Regular Expressions C++ solution.                           */
/*                                                                       */
/*  http://projects.nn.com.br/                                           */
/*                                                                       */
/*  Copyright (C) 2000 Gustavo Niemeyer <gustavo@nn.com.br>              */
/*                                                                       */
/*  This library is free software; you can redistribute it and/or        */
/*  modify it under the terms of the GNU Library General Public          */
/*  License as published by the Free Software Foundation; either         */
/*  version 2 of the License, or (at your option) any later version.     */
/*                                                                       */
/*  This library is distributed in the hope that it will be useful,      */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    */
/*  Library General Public License for more details.                     */
/*                                                                       */
/*  You should have received a copy of the GNU Library General Public    */
/*  License along with this library; if not, write to the                */
/*  Free Software Foundation, Inc., 59 Temple Place - Suite 330,         */
/*  Boston, MA  02111-1307, USA.                                         */
/*                                                                       */
/*************************************************************************/

// $Revision: 1.1 $
// $Date: 2001-09-19 15:03:08 $

#include "split.hh"

std::vector<std::string>
regexx::split(const std::string& _where, const std::string& _str)
{
  std::vector<std::string> v;
  std::string::size_type lastpos = 0;
  std::string::size_type pos = _str.find(_where);
  while(pos != std::string::npos) {
    v.push_back(_str.substr(lastpos,pos-lastpos));
    lastpos = pos+_where.length();
    pos = _str.find(_where,lastpos);
  }
  v.push_back(_str.substr(lastpos));
  return v;
}

std::vector<std::string>
regexx::splitex(const std::string& _regex, const std::string& _str)
{
  std::vector<std::string> v;
  Regexx rxx;
  rxx.expr(_regex);
  rxx.str(_str);
  v.reserve(rxx.exec());
  std::vector<RegexxMatch>::const_iterator i;
  std::string::size_type lastpos = 0;
  for(i = rxx.match.begin(); i != rxx.match.end(); i++) {
    v.push_back(_str.substr(lastpos,i->start()-lastpos));
    lastpos = i->start()+i->length();
  }
  v.push_back(_str.substr(lastpos,i->start()));
  return v;
}
