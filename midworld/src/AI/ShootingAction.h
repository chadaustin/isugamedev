#include <iostream>

class ShootingAction : public ActionContainer
{
public:
   ShootingAction(){};

   virtual void Perform()
   {
      std::cout << "Shooting now" << std::endl;
   }

private:
};
