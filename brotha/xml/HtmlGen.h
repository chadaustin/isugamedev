#ifndef HTMLG_H
#define HTMLG_H

#include <iostream.h>
#include <string>
#include <sstream>
#include <vector>
#include "brothadata.h"

namespace reports{

	class request;

	std::string renderPlayerList(dataxml::playerlist, reports::request);
	std::string renderGangList(dataxml::ganglist, reports::request);
	std::string renderStatList(dataxml::statlist);

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
			for(unsigned int i = 0; i < brothaPath.size(); i++){
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
		reports::request r(query);
		dataxml::ganglist gl = dataxml::b.getGangList();
		return renderGangList(gl,r);
	}

	std::string renderCarList(dataxml::carlist cl, request schema){
	  std::ostringstream out;
      out << "<table><tr><th>pic</th><th>car type</th><th>#of mods</th></tr>";
		for(unsigned int i = 0; i < cl.size(); i++){
			dataxml::Car* c = cl[i];
			out << "<tr><td><img src=car.jpg></td><td>" << c->getName() << "</td><td>"
             << c->getMods().size() << "</td></tr>";
		}
		out << "</table>";
		return out.str();
	}

	std::string renderGangList(dataxml::ganglist gl, reports::request schema){
		std::ostringstream html;
		for(int i = 0; i < gl.size(); i++){
			dataxml::Gang* g = gl[i];
			if(schema.gang.find(g->getName())!= -1 || schema.gang == "*"){
				if(schema.gangD == 2){
					 "<h1>" + g->getName() + "</h1>";
					html << "<div class=\"ganginfo\">" << g->getInfo() << "</div>";
					html << "<div class=\"gangplayers\"> number of players: " << g->getPlayerList().size() << "</div>";
				}
				if(schema.gangD == 1){
					html << "<h1>" << g->getName() << "</h1>";
				}
				html << renderPlayerList(g->getPlayerList(), schema);
			}
		}
		return html.str();
	}

	std::string renderCarTypeList(dataxml::cartypelist ctl){
		std::string html = "";
		for(unsigned int i = 0; i < ctl.size(); i++){
			dataxml::Cartype* ct = ctl[i];
			html += "<div class=\"cartype\"> <img src=\""+ ct->getName() + ".jpg\"><br>" + ct->getName() + "<br><br>";
		}
		return html;
	}

	std::string renderPlayerList(dataxml::playerlist pl, reports::request schema){
		std::ostringstream html;
		if(schema.playerD == 1)
			html << "<table><th>Name</th><th># of cars</th>";
		for(unsigned int i = 0; i < pl.size(); i++){
			dataxml::Player* p = pl[i];
			if(schema.player.find(p->getName())!= -1 || schema.player == "*"){
				if(schema.playerD == 1){
			        html << "<tr><td>" << p->getName() << "</td><td>" << p->getCars().size() << "</td></tr>";
					html << "<tr><td colspan=2>" << renderCarList(p->getCars(), schema) << "</td></tr>";
				}
				if(schema.playerD == 2){
					html << "<div class=\"playerinfo\">";
					html << "<table><tr><td valign=top>";
					html << "<img src=\"" << p->getName() << ".jpg\"></td>";
					html << "<td><h2>" << p->getName() << "</h2>";
					html << renderStatList(p->getStats());
					html << renderCarList(p->getCars(),schema);
					html << "</td></table></div>";
				}
			}
		}
		if(schema.playerD == 1)
			html << "</table>";
		return html.str();
	}

	std::string renderModList(dataxml::modlist ml){
		std::string html = "";
		html += "<table>tr><th>mod</th><th>level</th></tr>";
		for(unsigned int i = 0; i < ml.size(); i++){
			dataxml::Mod* m = ml[i];
			html += "<tr><td>" + m->getType() + "</td><td>" + std::string(itoa(m->getLevel(),new char[30],30)) + "</td></tr>";
		}
		html +="</table>";
		return html;
	}

	std::string renderStatList(dataxml::statlist sl){
		std::string html = "";
		html += "<table>";
		for(unsigned int i = 0; i < sl.size(); i++){
			dataxml::Stat* m = sl[i];
			html += "<tr><td>" + m->getName()+ "</td><td>" + m->getVal() + "</td></tr>";
		}
		html +="</table>";
		return html;
	}

}

#endif
