#ifndef OBS
#define OBS

#include <vector>
namespace mw
{

class Subject;

class Observer
{
public:
   virtual ~Observer(){};
   virtual void Update(Subject* TheChangedSubject) = 0;
protected:
   Observer(){};
};


class Subject 
{
public:
   virtual ~Subject(){};

   virtual void Attach(Observer*);
   virtual void Detach(Observer*);
   virtual void Notify();
protected:
   Subject(){};
private:
   std::vector<Observer*> _Observers;
};

}

#endif
