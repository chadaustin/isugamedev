#pragma once
#ifndef HTMLG_H
#define HTMLG_H

#include <iostream.h>
#include <string>
#include <vector>
#include "brothadata.h"

namespace reports{



	class request{
	public:
		int carD;
		int playerD;
		int gangD;
		std::string gang;
		std::string player;
		std::string car;

		request(std::string brothaPath){
			brothaPath += "/";
			std::string gpath;
			std::string ppath;
			std::string cpath;
			int state = 0;
			std::string tem = "";
			for(int i = 0; i < brothaPath.size(); i++){
				if(brothaPath[i] != '/')
					tem += brothaPath[i];
				else{
					if(state == 0){
						gangD = tem[0] - '0';
						gang = tem.substr(1,tem.size()-1);
						state++;
						tem = "";
					}
					else if(state == 1){
						playerD = tem[0] - '0';
						player = tem.substr(1,tem.size()-1);
						state++;
						tem = "";
					}
					else if(state == 2){
						carD = tem[0] - '0';
						player = tem.substr(1,tem.size()-1);
						state++;
					}

				}
			} //end for

		}//end constructor
		void print(std::ostream& o){
			o << "gang   " << gang << " level " << gangD << std::endl;
			o << "player " << player << " level " << playerD << std::endl;
			o << "car    " << car << " level " << carD << std::endl;
		}
	};

	std::string GenerateReport(std::string query){
		request r(query);
		dataxml::ganglist gl = dataxml::b.getGangList();
		return "hi";
	}

	std::string renderCarList(dataxml::carlist cl){
		std::string html = "";
		html += "<table><tr><th>pic</th><th>car type</th><th>#of mods</th></tr>";
		for(int i = 0; i < cl.size(); i++){
			dataxml::Car* c = cl[i];
			html += "<tr><td><img src=car.jpg></td><td>" + c->getName() + "</td><td>" + std::string(itoa(c->getMods().size(),new char[30],30)) + "</td></tr>";
		}
		html += "</table>";
		return html;
	}

	std::string renderGangList(dataxml::ganglist gl, reports::request schema){
		std::string html = "";
		for(int i = 0; i < gl.size(); i++){
			if(schema.gangD == 0){
				dataxml::Gang* g = gl[i];
				html += "<h1>" + g->getName() + "</h1>";
				html += "<div class=\"ganginfo\">" + g->getInfo() + "</div>";
				html += "<div class=\"gangplayers\"> number of players: " + std::string(itoa(g->getPlayerList().size(),new char[30],30))+ "</div>";
			}
		}
		return html;
	}

	std::string renderCarTypeList(dataxml::cartypelist ctl){
		std::string html = "";
		for(int i = 0; i < ctl.size(); i++){
			dataxml::Cartype* ct = ctl[i];
			html += "<div class=\"cartype\"> <img src=\""+ ct->getName() + ".jpg\"><br>" + ct->getName() + "<br><br>";
		}
		return html;
	}

	std::string renderPlayerList(dataxml::playerlist pl){
		std::string html = "";
		html += "<table><th>Name</th><th># of cars</th>";
		for(int i = 0; i < pl.size(); i++){
			dataxml::Player* p = pl[i];
			html +="<tr><td>" + p->getName() + "</td><td>" + std::string(itoa(p->getCars().size(),new char[30],30)) + "</td></tr>";
		}
		html += "</table>";
		return html;
	}

	std::string renderModList(dataxml::modlist ml){
		std::string html = "";
		html += "<table>tr><th>mod</th><th>level</th></tr>";
		for(int i = 0; i < ml.size(); i++){
			dataxml::Mod* m = ml[i];
			html += "<tr><td>" + m->getType() + "</td><td>" + std::string(itoa(m->getLevel(),new char[30],30)) + "</td></tr>";
		}
		html +="</table>";
		return html;
	}

	std::string renderStatList(dataxml::statlist sl){
		std::string html = "";
		html += "<table>";
		for(int i = 0; i < sl.size(); i++){
			dataxml::Stat* m = sl[i];
			html += "<tr><td>" + m->getName()+ "</td><td>" + m->getVal() + "</td></tr>";
		}
		html +="</table>";
		return html;
	}

}

#endif