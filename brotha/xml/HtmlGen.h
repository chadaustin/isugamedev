#ifndef DATA_HTMLGEN_H
#define DATA_HTMLGEN_H

#include <iostream.h>
#include <string>
#include <sstream>
#include <vector>
#include "BrothaData.h"

namespace reports {
   std::string urlBase = "http://hatori42.com/wb/";

   class request {
   public:
      int carD;
      int playerD;
      int gangD;
      bool valid;
      std::string gang;
      std::string player;
      std::string car;

      request(std::string brothaPath) {
         valid = false;
         brothaPath += "/";
         std::string gpath;
         std::string ppath;
         std::string cpath;
         int state = 0;
         std::string tem = "";
         for (unsigned int i = 0; i < brothaPath.size(); i++) {
            if (brothaPath[i] != '/') {
               tem += brothaPath[i];
            }
            else{
               if (state == 0) {
                  if (tem.size() < 2) {
                     break;
                  }
                  gangD = tem[0] - '0';
                  if (tem[0] < 0 || tem[0] > 3) {
                     break;
                  }
                  gang = tem.substr(1,tem.size()-1);
                  state++;
                  tem = "";
               }
               else if (state == 1) {
                  if (tem.size() < 2) {
                     break;
                  }
                  playerD = tem[0] - '0';
                  if (tem[0] < 0 || tem[0] > 3) {
                     break;
                  }
                  player = tem.substr(1,tem.size()-1);
                  state++;
                  tem = "";
               }
               else if (state == 2) {
                  if (tem.size() < 2) {
                     break;
                  }
                  carD = tem[0] - '0';
                  if (tem[0] < 0 || tem[0] > 3) {
                     break;
                  }
                  car = tem.substr(1,tem.size()-1);
                  state++;
                  valid = true;
               }

            }
         } //end for

      }//end constructor
      void print(std::ostream& o) {
         o << "gang   " << gang << " level " << gangD << std::endl;
         o << "player " << player << " level " << playerD << std::endl;
         o << "car    " << car << " level " << carD << std::endl;
      }
   };


   std::string renderPlayerList(data::playerlist, reports::request);
   std::string renderGangList(data::ganglist, reports::request);
   std::string renderStatList(data::statlist);
   std::string renderModList(data::modlist);

   std::string  parseHTTPRequest(std::string in) {
      in = in.substr(0,in.find_first_of('\n'));
      int firstpace = in.find_first_of(' ');
      int lastspace = in.find_last_of(' ');
      std::string url = in.substr(firstpace + 2,lastspace - firstpace - 2);
      return url;
   }


   std::string GenerateReport(std::string query) {
      reports::request r(query);
      if (r.valid) {
         data::ganglist gl = data::b.getGangList();
         return renderGangList(gl,r);
      }
      return "error";

   }

   std::string GenerateReportFromHTTP(std::string httpR) {
      return GenerateReport(parseHTTPRequest(httpR));
   }

   std::string renderCarList(data::carlist cl, request schema) {
      std::ostringstream out;
      if (schema.carD == 1) {
         out << "<table border=1><tr><th>pic</th><th>car type</th><th>#of mods</th></tr>";
      }
      for (unsigned int i = 0; i < cl.size(); i++) {
         data::Car* c = cl[i];
         if (schema.car.find(c->getName()) !=  std::string::npos || schema.car == "*") {
            if (schema.carD == 1) {
               out << "<tr><td><img src=" + urlBase + "car.jpg></td><td>name:" << c->getName() << "</td><td>";
               out << c->getMods().size() << "</td></tr>";
            }
            if (schema.carD == 2) {
               out << "<div class=\"car2\">";
               out << "<font size=+2>" << c->getName() << "<font>";
               out << "<table><tr><td valign=top>";
               out << "<div><img src=" << urlBase << c->getName() << ".jpg></div>";
               out << "</td><td valign=top>";
               out << "<div>" << renderModList(c->getMods()) << "</div>";
               out << "</td></tr></table>";
               out << "</div>";
            }
         }
      }
      if (schema.carD == 1) {
         out << "</table>";
      }
      return out.str();
   }

   std::string renderGangList(data::ganglist gl, reports::request schema) {
      std::ostringstream html;

      for (int i = 0; i < gl.size(); i++) {
         data::Gang* g = gl[i];
         if (schema.gang.find(g->getName())!= std::string::npos || schema.gang == "*") {
            if (schema.gangD == 2) {
               html << "<h1>" + g->getName() + "</h1>";
               html << "<div class=\"ganginfo\">" << g->getInfo() << "</div>";
               html << "<div class=\"gangplayers\"> number of players: " << g->getPlayerList().size() << "</div>";
            }
            if (schema.gangD == 1) {
               html << "<h1>" << g->getName() << "</h1>";

            }
            html << renderPlayerList(g->getPlayerList(), schema);
         }
      }
      return html.str();
   }

   std::string renderCarTypeList(data::cartypelist ctl) {
      std::string html = "";
      for (unsigned int i = 0; i < ctl.size(); i++) {
         data::Cartype* ct = ctl[i];
         html += "<div class=\"cartype\"> <img src=\"" + urlBase + ct->getName() + ".jpg\"><br>" + ct->getName() + "<br><br>";
      }
      return html;
   }

   std::string renderPlayerList(data::playerlist pl, reports::request schema) {
      std::ostringstream html;
      if (schema.playerD == 1) {
         html << "<table><th>Name</th><th># of cars</th>";
      }
      for (unsigned int i = 0; i < pl.size(); i++) {
         data::Player* p = pl[i];
         if (schema.player.find(p->getName())!=  std::string::npos || schema.player == "*") {
            if (schema.playerD == 1) {
               html << "<tr><td>" << p->getName() << "</td><td>" << p->getCars().size() << "</td></tr>";
               html << "<tr><td colspan=2>" << renderCarList(p->getCars(), schema) << "</td></tr>";
            }
            if (schema.playerD == 2) {
               html << "<div class=\"playerinfo\">";
               html << "<table><tr><td valign=top>";
               html << "<img src=\"" << urlBase << p->getName() << ".jpg\"></td>";
               html << "<td><h2>" << p->getName() << "</h2>";
               html << "stats:<br>";
               html << renderStatList(p->getStats());
               html << "cars:<br>";
               html << renderCarList(p->getCars(),schema);
               html << "</td></table></div>";
            }
            if (schema.playerD == 0) {
               html << renderCarList(p->getCars(),schema);
            }
         }
      }
      if (schema.playerD == 1) {
         html << "</table>";
      }
      return html.str();
   }

   std::string renderModList(data::modlist ml) {
      std::ostringstream html;
      html << "<table><tr><th>mod</th><th>level</th></tr>";
      for (unsigned int i = 0; i < ml.size(); i++) {
         data::Mod* m = ml[i];
         html << "<tr><td>" << m->getType() << "</td><td>" << m->getLevel() << "</td></tr>";
      }
      html << "</table>";
      return html.str();
   }

   std::string renderStatList(data::statlist sl) {
      std::ostringstream html;
      html << "<table>";
      for (unsigned int i = 0; i < sl.size(); i++) {
         data::Stat* m = sl[i];
         html << "<tr><td>" << m->getName() << "</td><td>" << m->getVal() << "</td></tr>";
      }
      html << "</table>";
      return html.str();
   }

   std::string inlineStyle() {
      std::string CSS = "<style>";
      CSS += "div.car2{background-color: white;}";
      CSS += "</style>";
      return CSS;
   }

}

#endif
