#ifndef KEYBOARD_INCLUDED
#define KEYBOARD_INCLUDED

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "kqueue.h"
#include "DigitalDevice.h"

class Keyboard : public DigitalDevice
{
public:
   enum Key
   {
      nul = 0, soh = 1, stx = 2, etx = 3, eot = 4, enq = 5, ack = 6, 
      BELL = 7,
      BACKSPACE = 8, 
      TAB = 9,
      NEWLINE = 10,
      VERTTAB = 11, 
      FORMFEED = 12,
      CR = 13,
      so = 14, si = 15, dle = 16,
      dc1 = 17, dc2 = 18, dc3 = 19, dc4 = 20, nak = 21, syn = 22, etb = 23, 
      can = 24, em = 25, sub = 26, 
      ESC = 27, 
      fs = 28, gs = 29, rs = 30, us = 31,
      SPACE = 32,
      BANG = 33,
      DOUBLEQUOTES = 34,
      HASH = 35,
      DOLLAR = 36,
      PERCENT = 37,
      AMPERSAND = 38,
      RIGHTQUOTE = '\'',
      LEFTPAREN = 40,
      RIGHTPAREN = 41,
      ASTERISK = '*',
      POS = '+', 
      COMMA = ',', 
      NEG = '-', 
      PERIOD = '.',
      SLASH = '/',
      ZERO = '0', ONE = '1', TWO = '2', THREE = '3', FOUR = '4', FIVE = '5', 
      SIX = '6', SEVEN = '7', EIGHT = '8', NINE = '9', 
      COLON = ':',
      SEMICOLON = ';',
      LESSTHAN = '<',
      EQUALS = '=',
      GREATERTHAN = '>',
      QUESTION = '?',
      AT = '@',
      A = 'A',B = 'B',C = 'C',D = 'D',E = 'E',F = 'F',G = 'G',H = 'H',
      I = 'I',J = 'J',K = 'K',L = 'L',M = 'M',N = 'N',O = 'O',P = 'P',Q = 'Q',
      R = 'R',S = 'S',T = 'T',U = 'U',V = 'V',W = 'W',X = 'X',Y = 'Y',Z = 'Z',
      LEFTBRACKET = '[', 
      BACKSLASH = '\\',
      RIGHTBRACKET = ']',
      CARET = '^',
      UNDERSCORE = '_',
      LEFTQUOTE = '`',
      a = 'a',b = 'b',c = 'c',d = 'd',e = 'e',f = 'f',g = 'g',h = 'h',
      i = 'i',j = 'j',k = 'k',l = 'l',m = 'm',n = 'n',o = 'o',p = 'p',q = 'q',
      r = 'r',s = 's',t = 't',u = 'u',v = 'v',w = 'w',x = 'x',y = 'y',z = 'z',
      CURLYLEFT = '{',
      PIPE = '|',
      CURLYRIGHT = '}',
      TILDE = '~',
      DEL = 127,
      /////////////////////////////////////////////////////////////////
      PAGEUP = 256, 
      PAGEDOWN = 257, 
      HOME = 258, 
      END = 259, 
      INSERT = 260,
      UPARROW = 261, 
      DOWNARROW = 262, 
      LEFTARROW = 263, 
      RIGHTARROW = 264,
      CAPS = 265, 
      LSHIFT = 266, 
      LCTRL = 267, 
      RSHIFT = 268, 
      RCTRL = 269, 
      F1 = 270, F2 = 271, F3 = 272, F4 = 273, F5 = 274, F6 = 275, 
      F7 = 276, F8 = 277, F9 = 278, F10 = 279, F11 = 280, F12 = 281,
      NumberOfKeys = 282 // make sure this number is bigger than the others.
   };
      
   Keyboard() : DigitalDevice()
   {
      this->setNumInputs( NumberOfKeys );
      initialize_map();
   }
   
   kev::queue<Key>& queue() { return mQueue; }
   
private:
   kev::queue<Key> mQueue;

   void initialize_map()
   {
      mMap["KEY_BS"] = Keyboard::BACKSPACE;
      mMap["KEY_TAB"] = Keyboard::TAB;
      mMap["KEY_NEWLINE"] = Keyboard::NEWLINE;
      mMap["KEY_VERTTAB"] = Keyboard::VERTTAB; 
      mMap["KEY_FORMFEED"] = Keyboard::FORMFEED;
      mMap["KEY_CR"] = Keyboard::CR;
      mMap["KEY_ESC"] = Keyboard::ESC;
      mMap["KEY_SPACE"] = Keyboard::SPACE;
      mMap["KEY_BANG"] = Keyboard::BANG;
      mMap["KEY_DOUBLEQUOTES"] = Keyboard::DOUBLEQUOTES;
      mMap["KEY_HASH"] = Keyboard::HASH;
      mMap["KEY_DOLLAR"] = Keyboard::DOLLAR;
      mMap["KEY_PERCENT"] = Keyboard::PERCENT;
      mMap["KEY_AMPERSAND"] = Keyboard::AMPERSAND;
      mMap["KEY_RIGHTQUOTE"] = Keyboard::RIGHTQUOTE;
      mMap["KEY_LEFTPAREN"] = Keyboard::LEFTPAREN;
      mMap["KEY_RIGHTPAREN"] = Keyboard::RIGHTPAREN;
      mMap["KEY_ASTERISK"] = Keyboard::ASTERISK;
      mMap["KEY_POS"] = Keyboard::POS;
      mMap["KEY_COMMA"] = Keyboard::COMMA; 
      mMap["KEY_NEG"] = Keyboard::NEG;
      mMap["KEY_PERIOD"] = Keyboard::PERIOD;
      mMap["KEY_SLASH"] = Keyboard::SLASH;
      mMap["KEY_ZERO"] = Keyboard::ZERO;
      mMap["KEY_ONE"] = Keyboard::ONE;
      mMap["KEY_TWO"] = Keyboard::TWO;
      mMap["KEY_THREE"] = Keyboard::THREE;
      mMap["KEY_FOUR"] = Keyboard::FOUR;
      mMap["KEY_FIVE"] = Keyboard::FIVE;
      mMap["KEY_SIX"] = Keyboard::SIX;
      mMap["KEY_SEVEN"] = Keyboard::SEVEN;
      mMap["KEY_EIGHT"] = Keyboard::EIGHT;
      mMap["KEY_NINE"] = Keyboard::NINE;
      mMap["KEY_COLON"] = Keyboard::COLON;
      mMap["KEY_SEMICOLON"] = Keyboard::SEMICOLON;
      mMap["KEY_LESSTHAN"] = Keyboard::LESSTHAN;
      mMap["KEY_EQUALS"] = Keyboard::EQUALS;
      mMap["KEY_GREATERTHAN"] = Keyboard::GREATERTHAN;
      mMap["KEY_QUESTION"] = Keyboard::QUESTION;
      mMap["KEY_AT"] = Keyboard::AT;
      mMap["KEY_A"] = Keyboard::A;
      mMap["KEY_B"] = Keyboard::B;
      mMap["KEY_C"] = Keyboard::C;
      mMap["KEY_D"] = Keyboard::D;
      mMap["KEY_E"] = Keyboard::E;
      mMap["KEY_F"] = Keyboard::F;
      mMap["KEY_G"] = Keyboard::G;
      mMap["KEY_H"] = Keyboard::H;
      mMap["KEY_I"] = Keyboard::I;
      mMap["KEY_J"] = Keyboard::J;
      mMap["KEY_K"] = Keyboard::K;
      mMap["KEY_L"] = Keyboard::L;
      mMap["KEY_M"] = Keyboard::M;
      mMap["KEY_N"] = Keyboard::N;
      mMap["KEY_O"] = Keyboard::O;
      mMap["KEY_P"] = Keyboard::P;
      mMap["KEY_Q"] = Keyboard::Q;
      mMap["KEY_R"] = Keyboard::R;
      mMap["KEY_S"] = Keyboard::S;
      mMap["KEY_T"] = Keyboard::T;
      mMap["KEY_U"] = Keyboard::U;
      mMap["KEY_V"] = Keyboard::V;
      mMap["KEY_W"] = Keyboard::W;
      mMap["KEY_X"] = Keyboard::X;
      mMap["KEY_Y"] = Keyboard::Y;
      mMap["KEY_Z"] = Keyboard::Z;
      mMap["KEY_LEFTBRACKET"] = Keyboard::LEFTBRACKET;
      mMap["KEY_BACKSLASH"] = Keyboard::BACKSLASH;
      mMap["KEY_RIGHTBRACKET"] = Keyboard::RIGHTBRACKET;
      mMap["KEY_CARET"] = Keyboard::CARET;
      mMap["KEY_UNDERSCORE"] = Keyboard::UNDERSCORE;
      mMap["KEY_LEFTQUOTE"] = Keyboard::LEFTQUOTE;
      mMap["KEY_a"] = Keyboard::a;
      mMap["KEY_b"] = Keyboard::b;
      mMap["KEY_c"] = Keyboard::c;
      mMap["KEY_d"] = Keyboard::d;
      mMap["KEY_e"] = Keyboard::e;
      mMap["KEY_f"] = Keyboard::f;
      mMap["KEY_g"] = Keyboard::g;
      mMap["KEY_h"] = Keyboard::h;
      mMap["KEY_i"] = Keyboard::i;
      mMap["KEY_j"] = Keyboard::j;
      mMap["KEY_k"] = Keyboard::k;
      mMap["KEY_l"] = Keyboard::l;
      mMap["KEY_m"] = Keyboard::m;
      mMap["KEY_n"] = Keyboard::n;
      mMap["KEY_o"] = Keyboard::o;
      mMap["KEY_p"] = Keyboard::p;
      mMap["KEY_q"] = Keyboard::q;
      mMap["KEY_r"] = Keyboard::r;
      mMap["KEY_s"] = Keyboard::s;
      mMap["KEY_t"] = Keyboard::t;
      mMap["KEY_u"] = Keyboard::u;
      mMap["KEY_v"] = Keyboard::v;
      mMap["KEY_w"] = Keyboard::w;
      mMap["KEY_x"] = Keyboard::x;
      mMap["KEY_y"] = Keyboard::y;
      mMap["KEY_z"] = Keyboard::z;
      mMap["KEY_CURLYLEFT"] = Keyboard::CURLYLEFT;
      mMap["KEY_PIPE"] = Keyboard::PIPE;
      mMap["KEY_CURLYRIGHT"] = Keyboard::CURLYRIGHT;
      mMap["KEY_TILDE"] = Keyboard::TILDE;
      mMap["KEY_DEL"] = Keyboard::DEL;
      mMap["KEY_PAGEUP"] = Keyboard::PAGEUP;
      mMap["KEY_PAGEDOWN"] = Keyboard::PAGEDOWN;
      mMap["KEY_HOME"] = Keyboard::HOME;
      mMap["KEY_END"] = Keyboard::END;
      mMap["KEY_INSERT"] = Keyboard::INSERT;
      mMap["KEY_UPARROW"] = Keyboard::UPARROW;
      mMap["KEY_DOWNARROW"] = Keyboard::DOWNARROW;
      mMap["KEY_LEFTARROW"] = Keyboard::LEFTARROW;
      mMap["KEY_RIGHTARROW"] = Keyboard::RIGHTARROW;
      mMap["KEY_CAPS"] = Keyboard::CAPS;
      mMap["KEY_LSHIFT"] = Keyboard::LSHIFT;
      mMap["KEY_LCTRL"] = Keyboard::LCTRL;
      mMap["KEY_RSHIFT"] = Keyboard::RSHIFT;
      mMap["KEY_RCTRL"] = Keyboard::RCTRL;
      mMap["KEY_F1"] = Keyboard::F1;
      mMap["KEY_F2"] = Keyboard::F2;
      mMap["KEY_F3"] = Keyboard::F3;
      mMap["KEY_F4"] = Keyboard::F4;
      mMap["KEY_F5"] = Keyboard::F5;
      mMap["KEY_F6"] = Keyboard::F6;
      mMap["KEY_F7"] = Keyboard::F7;
      mMap["KEY_F8"] = Keyboard::F8;
      mMap["KEY_F9"] = Keyboard::F9;
      mMap["KEY_F10"] = Keyboard::F10;
      mMap["KEY_F11"] = Keyboard::F11;
      mMap["KEY_F12"] = Keyboard::F12;
   }
};


#endif
