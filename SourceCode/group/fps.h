#ifndef _FPS_H_
#define _FPS_H_

#include <time.h>
#include <Mmsystem.h>
class FPS
{
public:
   FPS(int fixfps=60) {
      reset();
      fixFps(fixfps);
   }

   inline void fixFps(int fps) {
      fixedfps_ = fps;
      fixdt_ = (fps != 0) ? (DWORD)(1000.0f/fps) : 0;
   }

   inline void reset() {
      fps_ = cfps_ = dt_ = 0;
      t0_ = t0fps_ = timeGetTime();
   }

   inline DWORD difftime() {return dt_;}
   inline int fps() { return fps_; }

   inline int update() {
      DWORD tgt = timeGetTime();
      dt_ = tgt - t0_;
      if (dt_ >= fixdt_) {
         // Cap too large time steps usually caused by lost focus to avoid jerks
         if (dt_ > 200) dt_ = 10;

         t0_ = tgt;
         if (t0_ - t0fps_ <= 1000) cfps_++;
         else {
            t0fps_ = t0_; 
            fps_ = cfps_;
            cfps_ = 0;
         }
         return 0;
      }
      else {
         if (dt_ + 3 < fixdt_)
            return 1;
      }
      return 2;
   }

   int fps_;
   int fixedfps_, cfps_;
   DWORD t0_, t0fps_, dt_, fixdt_;
};

#endif // _FPS_H_
