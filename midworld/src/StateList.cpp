#include "StateFactory.h"

#include "CreditsState.h"
#include "EndingState.h"
#include "GameOverState.h"
#include "GameState.h"
#include "IntroState.h"
#include "LoadState.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "StoryState.h"
#include "UnsupportedState.h"


#define DEFINE_STATE(name) StateCreatorImpl<name##State> creator##name (#name)


namespace mw
{
   DEFINE_STATE(Credits);
   DEFINE_STATE(Ending);
   DEFINE_STATE(GameOver);
   DEFINE_STATE(Game);
   DEFINE_STATE(Intro);
   DEFINE_STATE(Load);
   DEFINE_STATE(Menu);
   DEFINE_STATE(Options);
   DEFINE_STATE(Story);
   DEFINE_STATE(Unsupported);
}
