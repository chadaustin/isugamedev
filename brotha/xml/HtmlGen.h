#ifndef DATA_HTMLGEN_H
#define DATA_HTMLGEN_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "BrothaData.h"
#include "Stat.h"

namespace reports {
   std::string urlBase = "http://hatori42.com/wb/";
   std::string inlineStyle();

   class request {
   public:
      int carD;
      int playerD;
      int gangD;
      bool valid;
      std::string gang;
      std::string player;
      std::string car;
      std::string err;

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
                     err = "gang path to short";
                     break;
                  }
                  gangD = tem[0] - '0';
                  if (gangD < 0 || gangD > 3) {
                     err = "invalid level in gang part";
                     break;
                  }
                  gang = tem.substr(1,tem.size()-1);
                  state++;
                  tem = "";
               }
               else if (state == 1) {
                  if (tem.size() < 2) {
                     err = "player path to short";
                     break;
                  }
                  playerD = tem[0] - '0';
                  if (playerD < 0 || playerD > 3) {
                     err = "invalid level on player";
                     break;
                  }
                  player = tem.substr(1,tem.size()-1);
                  state++;
                  tem = "";
               }
               else if (state == 2) {
                  if (tem.size() < 2) {
                     err = "carpath to short";
                     break;
                  }
                  carD = tem[0] - '0';
                  if (carD < 0 || carD > 3) {
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

   inline std::string renderStatList(data::StatList& sl) {
      std::ostringstream html;
      html << "<table>";
      for (unsigned int i = 0; i < sl.size(); i++) {
         data::Stat* m = sl[i];
         html << "<tr><td>" << m->getName() << "</td><td>" << m->getVal() << "</td></tr>";
      }
      html << "</table>";
      return html.str();
   }

   inline std::string renderModList(data::ModList& ml) {
      std::ostringstream html;
      html << "<table><tr><th>mod</th><th>level</th></tr>";
      for (unsigned int i = 0; i < ml.size(); i++) {
         data::Mod* m = ml[i];
         html << "<tr><td>" << m->getName() << "</td><td><center>" << m->getLevel() << "</center></td></tr>";
      }
      html << "</table>";
      return html.str();
   }

   inline std::string renderCarList(data::CarList& cl, request& schema,
                             const std::string& gangname,
                             const std::string& playername)
   {
      std::ostringstream out;
      if (schema.carD == 1) {
         out << "<table width=70%><tr><th>pic</th><th>car type</th><th>#of mods</th></tr>";
      }
      for (unsigned int i = 0; i < cl.size(); i++) {
         data::Car* c = cl[i];
         if (schema.car.find(c->getName()) !=  std::string::npos || schema.car == "*") {
            if (schema.carD == 1) {
               out << "<tr><td><img src=" << urlBase << c->getName() << "_small.jpg>";
               out << "</td><td><center>";
               out << "<a href=\"/0" << gangname << "/2" << playername << "/2" << c->getName() << "\">";
               out << c->getName() << "</a></center></td><td><center>";
               out << c->getMods().size() << "</center></td></tr>";
            }
            if (schema.carD == 2) {
               out << "<div class=\"car2\">";
               out << "<font size=+2>"; 
               out << "<a href=\"/2" << gangname << "/1*/0*\">" << gangname << "</a>/";
               out << "<a href=\"/0" << gangname << "/2" << playername << "/1*\">" << playername << "</a>/";
               out << c->getName() << "<font>";
               if(c->getMods().size() > 0){
                  out << "<table><tr><td valign=top>";
                  out << "<div><img src=" << urlBase << c->getName() << ".jpg></div>";
                  out << "</td><td valign=top>";
                  out << "<div>" << renderModList(c->getMods()) << "</div>";
                  out << "</td></tr></table>";
               }
               else{
                  out << "<br><b>unmodified</b>";
               }
               out << "</div>";
            }
         }
      }
      if (schema.carD == 1) {
         out << "</table>";
      }
      return out.str();
   }

   inline std::string renderPlayerList(data::PlayerList& pl, reports::request& schema,
                                const std::string& gangname)
   {
      std::ostringstream html;
      if (schema.playerD == 1) {
         html << "<table><th>Name</th><th># of cars</th>";
      }

      for (unsigned int i = 0; i < pl.size(); i++) {
         data::Player* p = pl[i];
         if (schema.player.find(p->getName())!=  std::string::npos || schema.player == "*") {
            if (schema.playerD == 1) {
               html << "<tr><td>";
               html << "<a href=\"/0" << gangname << "/2" << p->getName() << "/1*\">";
               html << p->getName() << "</a></td><td><center>" << p->getCars().size() << "</center></td></tr>";
               html << "<tr><td colspan=2>" << renderCarList(p->getCars(), schema, gangname, p->getName()) << "</td></tr>";
            }
            if (schema.playerD == 2) {
               if(schema.gangD == 0){
                  html << "<div class=\"gang2\">";
               }
               html << "<div class=\"playerinfo\">";
               html << "<table width=100%><tr><td valign=top>";
               html << "<img src=\"" << urlBase << p->getName() << ".jpg\"></td>";
               html << "<td width=100%>";
               html << "<h2>";
               html << "<a href=\"/2" << gangname << "/1*/0*\">" << gangname << "</a>/";
               html << p->getName() << "</h2>";
               if(p->getStats().size() > 0){
                  html << "stats:<br>";
                  html << "<div class=\"statlist\">";
                  html << renderStatList(p->getStats());
                  html << "</div>";
               }
               else{
                  html << "no stats available<br>";
               }

               if(schema.carD > 0){
                  html << "cars:<br>";
                  html << "<div class=\"carlist\">";
                  html << renderCarList(p->getCars(),schema, gangname, p->getName());
                  html << "</div>";
               }
               html << "</td></table></div>";
               if(schema.gangD == 0){
                  html << "</div>";
               }
            }
            if (schema.playerD == 0) {
               html << renderCarList(p->getCars(),schema, gangname, p->getName());
            }
         }
      }
      if (schema.playerD == 1) {
         html << "</table>";
      }
      return html.str();
   }

   inline std::string renderGangList(data::GangList& gl, reports::request& schema) {
      std::ostringstream html;

      for (unsigned int i = 0; i < gl.size(); i++) {
         data::Gang* g = gl[i];
         if (schema.gang.find(g->getName())!= std::string::npos || schema.gang == "*") {
            if (schema.gangD == 2) {
               html << "<div class=\"gang2\">";
               html << "<h1>" + g->getName() + "</h1>";
               html << "<div class=\"ganginfo\">" << g->getInfo() << "</div>";
               html << "<div class=\"gangplayers\"> number of players: " << g->getPlayerList().size() << "</div>";
               html << "<div class=\"playerlist\">";
               html << renderPlayerList(g->getPlayerList(), schema, g->getName());
               html << "</div>";
               html << "</div>";
            }
            else if (schema.gangD == 1) {
               html << "<h1>" << g->getName() << "</h1>";
               html << renderPlayerList(g->getPlayerList(), schema, g->getName());
            }
            else {
               html << renderPlayerList(g->getPlayerList(), schema, g->getName());
            }
         }
      }
      return html.str();
   }

   inline std::string renderCarTypeList(data::CarTypeList& ctl) {
      std::string html = "";
      for (unsigned int i = 0; i < ctl.size(); i++) {
         data::CarType* ct = ctl[i];
         html += "<div class=\"cartype\"> <img src=\"" + urlBase + ct->getName() + ".jpg\"><br>" + ct->getName() + "<br><br>";
      }
      return html;
   }

   inline std::string inlineStyle() {
      std::string CSS = "";
      CSS += "<link rel=\"STYLESHEET\" type=\"text/css\" href=\"http://hatori42.com/br.css\" />";
      CSS += "";
      return CSS;
   }

   inline std::string parseHTTPRequest(std::string in) {
      in = in.substr(0,in.find_first_of('\n'));
      int firstpace = in.find_first_of(' ');
      int lastspace = in.find_last_of(' ');
      std::string url = in.substr(firstpace + 2,lastspace - firstpace - 2);
      return url;
   }


   inline std::string GenerateReport(std::string query, data::BrothaData& data) {
      if(query.size() < 3){
        query = "2*/1*/0*";
      }
      reports::request r(query);
      if (r.valid) {
         data::GangList gl = data.getGangList();
         return inlineStyle() + "<a href=\"/\"><h1>Warn-a-brotha report server</h1></a> " +  renderGangList(gl,r);
      }
      return "error";

   }

   inline std::string GenerateReportFromHTTP(std::string httpR, data::BrothaData& data) {
      return GenerateReport(parseHTTPRequest(httpR), data);
   }

}

#endif
