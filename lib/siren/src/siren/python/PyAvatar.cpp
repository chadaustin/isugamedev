/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PyAvatar.cpp,v $
 * Date modified: $Date: 2003-02-23 04:19:55 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include <boost/python.hpp>
#include <siren/siren.h>

using namespace boost::python;
using namespace siren;

void exportAvatar()
{
   // Avatar
   class_<Avatar, bases<>, boost::noncopyable>("Avatar", no_init)
      .def("triggerAnimation", (bool(Avatar::*)(int))&Avatar::triggerAnimation)
      .def("triggerAnimation", (bool(Avatar::*)(const std::string&))&Avatar::triggerAnimation)
      .def("triggerAnimationCycle", (bool(Avatar::*)(int))&Avatar::triggerAnimationCycle)
      .def("triggerAnimationCycle", (bool(Avatar::*)(const std::string&))&Avatar::triggerAnimationCycle)
      .def("stopAnimation", (bool(Avatar::*)(int))&Avatar::stopAnimation)
      .def("stopAnimation", (bool(Avatar::*)(const std::string&))&Avatar::stopAnimation)
      .def("checkAnimation", (bool(Avatar::*)(int))&Avatar::checkAnimation)
      .def("checkAnimation", (bool(Avatar::*)(const std::string&))&Avatar::checkAnimation)
      .def("stopAllAnimations", &Avatar::stopAllAnimations)
      .def("moveTo", &Avatar::moveTo)
      .def("isMoving", &Avatar::isMoving)
      .def("update", &Avatar::update)
      .def("updateAnimations", &Avatar::updateAnimations)
      .def("updateMesh", &Avatar::updateMesh)
      .def("updateMove", &Avatar::updateMove)
//      .def("render", (bool(Avatar::*)(Avatar::DrawMode))&Avatar::render)
      .def("render", (bool(Avatar::*)())&Avatar::render)
      .def("renderMesh", &Avatar::renderMesh)
      .def("renderSkeleton", &Avatar::renderSkeleton)
      .def("setTexture", &Avatar::setTexture)
      .def("setDrawMode", &Avatar::setDrawMode)
      .def("setLOD", &Avatar::setLOD)
      .def("setShadowColor", &Avatar::setShadowColor)
//      .def("getBone", &Avatar::getBone)
      .def("getAnimID", &Avatar::getAnimID)
//      .add_property("pos", &Avatar::getPos, &Avatar::setPos)
//      .add_property("rot", &Avatar::getRotXYZ, (void(Avatar::*)(const gmtl::EulerAngleXYZf&))&Avatar::setRot)
//      .add_property("rotQuat", &Avatar::getRotQuat, (void(Avatar::*)(const gmtl::Quatf&))&Avatar::setRot)
//      .add_property("scale", &Avatar::getScale, &Avatar::setScale)
//      .add_property("wcs", &Avatar::getWCS)
//      .add_property("model", &Avatar::model)
   ;

   def("Avatar", &Avatar::create, return_value_policy<reference_existing_object>());
}
