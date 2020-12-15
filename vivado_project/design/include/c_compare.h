// =====================================================================================
// 
//       Filename:  c_compare.h
// 
//    Description:  
// 
//        Version:  1.0
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Mathieu Lebon (ML), 
//        Company:  Thales Alenia Space
// 
// =====================================================================================

#ifndef __C_COMPARE__
#define __C_COMPARE__

// =====================================================================================
//        Class:  c_compare
//  Description:  
// =====================================================================================

struct c_compare {

#ifndef __SYNTHESIS__
  void fix_length(ostringstream & s, int size) {
    while(s.str().length() < size) s << " ";
  }
#endif

  template<typename T1, typename T2>
    bool chan( T1 & chan, T2 * ref) {
      bool err(0);
#ifndef __SYNTHESIS__
      ostringstream s;
      int size = chan.size();
      for ( int i = 0; i < size; i += 1 ) {
        ostringstream s2;
        T2 d = chan.read();
        T2 r = ref[i];
        s2 << i << ") ref = " << r << " / res = " << d;
        fix_length(s2,50);
        if(d != r) {
          s2 << "[ERR]\n";
          err = true;
        } else {
          s2 << "[OK]\n";
        }
        s << s2.str();
      }
      if(err) {
        s << "\n=> ERR\n";
      } else {
        s << "\n=> OK\n";
      }
      cout << s.str();
#endif
      return err;
    }

  template<typename T1, typename T2>
    bool array( T1 * res, T2 * ref, int size) {
      bool err(0);
#ifndef __SYNTHESIS__
      ostringstream s;
      for ( int i = 0; i < size; i += 1 ) {
        ostringstream s2;
        T2 d = res[i];
        T2 r = ref[i];
        s2 << i << ") ref = " << r << " / res = " << d;
        fix_length(s2,50);
        if(d != r) {
          s2 << "[ERR]\n";
          err = true;
        } else {
          s2 << "[OK]\n";
        }
        s << s2.str();
      }
      if(err) {
        s << "\n=> ERR\n";
      } else {
        s << "\n=> OK\n";
      }
      cout << s.str();
#endif
      return err;
    }



}; // -----  end of class compare  -----

#endif


