#pragma once
#include "MouseState.h"

/**
* @brief Menyimpan perubahan dari MouseState sebelumnya ke sekarang.
*/
struct MouseDeltaState {
   int deltaX;
   int deltaY;
   int scrollDelta;

   bool leftDown;
   bool leftUp;

   bool rightDown;
   bool rightUp;

   bool middleDown;
   bool middleUp;

   bool mouse4Down;
   bool mouse4Up;

   bool mouse5Down;
   bool mouse5Up;

   bool moved;

   MouseDeltaState()
       : deltaX(0), deltaY(0), scrollDelta(0),
         leftDown(false), leftUp(false),
         rightDown(false), rightUp(false),
         middleDown(false), middleUp(false),
         mouse4Down(false), mouse4Up(false),
         mouse5Down(false), mouse5Up(false),
         moved(false) {}

   void compute(const MouseState& prev, const MouseState& curr) {
       deltaX = curr.x - prev.x;
       deltaY = curr.y - prev.y;
       scrollDelta = curr.scrollDelta;

       moved = (deltaX != 0 || deltaY != 0);

       leftDown   = !prev.leftButton   && curr.leftButton;
       leftUp     =  prev.leftButton   && !curr.leftButton;

       rightDown  = !prev.rightButton  && curr.rightButton;
       rightUp    =  prev.rightButton  && !curr.rightButton;

       middleDown = !prev.middleButton && curr.middleButton;
       middleUp   =  prev.middleButton && !curr.middleButton;

       mouse4Down = !prev.mouse4Button && curr.mouse4Button;
       mouse4Up   =  prev.mouse4Button && !curr.mouse4Button;

       mouse5Down = !prev.mouse5Button && curr.mouse5Button;
       mouse5Up   =  prev.mouse5Button && !curr.mouse5Button;
   }
};
