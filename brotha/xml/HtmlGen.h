#pragma once
#ifndef HTMLG_H
#define HTMLG_H

#include <iostream.h>
#include <string.h>
#include <vector>
#include "brothadata.h"

namespace reports{

	std::string ListEverything(){

	}

	std::string renderCarList(dataxml::carlist cl){
		std::string html = "";
		html += "<table><tr><th>pic</th><th>car type</th><th>#of mods</th></tr>";
		for(int i = 0; i < cl.size(); i++){
			Car* c = cl[i];
			html += "<tr><td><img src=car.jpg></td><td>" + c->name + "</td><td>" + c->getMods().size() + "</td></tr>";
		}
		html += "</table>";
	}
	std::string renderGangList(dataxml::ganglist gl){
		std::string html = "";
		for(int i = 0; i < gl.size(); i++){
		    Gang* g = gl[i];
			html += "<h1>" + g->getName() + "</h1>";
			html += "<div class=\"ganginfo\">" + g->getInfo() + "</div>";
			html += "<div class="\gangplayers\"> number of players: " + g->getPlayerList().size() + "</div>";
		}
	}
}

#endif