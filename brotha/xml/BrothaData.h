#ifndef BDATA_H
#define BDATA_H

#include <iostream>
#include <string>
#include <vector>



//classes defined in this file:
class Mod;
class Cartype;
class Car;
class Player;
class Gang;
class Bdata;


//this function returns the model for a cartype based on the name
//eventualy, we'll have loaded car files out a directory or XML doc
//to make a map out of it.

std::string fileForCartype(std::string cartype){
  return std::string("car.model"); //we'll worry about it later.
}

typedef vector<Mod*> modlist;
typedef vector<Car*> carlist;
typedef vector<Player*> playerlist;
typedef vector<Gang*> ganglist;
typedef vector<Cartype*> cartypelist;


//modifications to the car.
class Mod {

private:

  std::string type;
  int level;

public:

  Mod(std::string in_type, int in_level){
    type = in_type;
    level = in_level;
  }

  std::string getType(){
    return type;
  }
  
  int getLevel(){
    return level;
  }
  
  void xMLify(ostream& out){
    out <<"        <mod name=\"" << type << "\" level=\"" << level << "\" />" << endl;
  }
};



class Cartype{
private:

  std::string name;
  std::string filename;

public:

  Cartype(){
    name = "none!";
	filename = "car.model";
  }

  Cartype(std::string in_name){
    name = in_name;
    filename = fileForCartype(name);
  }

  std::string getFileName(){
    return filename;
  }

  std::string getName(){
    return name;
  }

  void xMLify(ostream& out){
    out << "  <cartype name=\"" << name << "\" file=\"" << filename<< "\" />" << endl;
  }
};

class Car{
private:
  Cartype name;
  modlist mods;

public:
  Car(std::string iname){
    name = Cartype(iname);
  }

  std::string getName(){
    return name.getName();
  }

  modlist getMods(){
    return mods;
  }

  void addMod(Mod& m){
    mods.push_back(&m);
  }

  void xMLify(ostream& out){
    out << "      <car cartype=\"" << name.getName() << "\">" << endl;
    for(int i = 0; i < mods.size(); i++){
      mods[i]->xMLify(out);
    }
    out << "      </car>" << endl;
  }
};


class Player{
private:
  std::string name;
  std::string password; //look, it's private so it's secure :)
  std::string gang;
  carlist cars;
public:
  Player(std::string iname, std::string ipasswd){
    name = iname;
    password = ipasswd;
  }

  void setGang(std::string igang){
    gang = igang;
  }

  void changePassword(std::string npw){
     password = npw;
  }

  std::string getName(){
    return name;
  }

  std::string getPassword(){
    return password;
  }

  carlist getCars(){
    return cars;
  }

  void addCar(Car& c){
    cars.push_back(&c);
  }

  void xMLify(ostream& out){
    out << "    <player name=\"" << name << "\" password=\"" << password << "\" gang=\"" << gang << "\">" << endl;
    for(int i = 0; i < cars.size(); i++){
      cars[i]->xMLify(out);
    }
    out << "   </player>" << endl;
  }
  
};

class Gang{
private:
  std::string name;
  playerlist p;
public:
  Gang(std::string iname){
    name = iname;
  }
  void addPlayer(Player& i){
    p.push_back(&i);
	i.setGang(name);
  }

  playerlist getPlayerList(){
    return p;
  }

  std::string getName(){
    return name;
  }

  void xMLify(ostream& out){
   out << "  <gang name=\"" << name << "\">" << endl;
   for(int i = 0; i < p.size(); i++){
      p[i]->xMLify(out);
    }
   out << "  </gang>" <<endl;
  }
};


class Bdata{
private:
  ganglist gangs;
  cartypelist cars;

public:

  ganglist getGangList(){
    return gangs;
  }

  cartypelist getcartypes(){
    return cars;
  }

  void addCarType(Cartype& c){
    cars.push_back(&c);
  }

  void addGang(Gang& g){
    gangs.push_back(&g);
  }

  void xMLify(ostream& out){
    out << "<wbdata>" << endl;
    for(int i = 0; i < gangs.size(); i++){
      gangs[i]->xMLify(out);
    }
    for(int i = 0; i < cars.size(); i++){
      cars[i]->xMLify(out);
    }
	out << "</wbdata>";
  }

  Gang* getGangByName(std::string name){
    for(int i = 0; i < gangs.size(); i++){
	  if(gangs[i]->getName() == name){
	    return gangs[i];
	  }
	}
	throw "not found";
	return gangs[0];  //should never be reached.
  }
};

#endif