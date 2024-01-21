#ifndef HLS_ECON_VID_CAP_H_INCLUDE_GUARD_
#define HLS_ECON_VID_CAP_H_INCLUDE_GUARD_

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "axi_vid_bus_width.h"
#include "bit_width.h"

template<int COLOR_CHANNELS_,int DEPTH_,int PPC_,int MAX_COLS_,int MAX_ROWS_>
inline static void Create_Pix(
  ap_uint<(DEPTH_*2)*PPC_> Vid_In,
  ap_axiu<Axi_Vid_Bus_Width<COLOR_CHANNELS_,DEPTH_,PPC_>::Value,1,1,1>& Vid_Out,
  ap_uint<Bit_Width<D_MAX_COLS_/D_PPC_>::Value>& Pix_Cntr,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value>& Line_Cntr,
  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Height,
  bool& Last_Pix
){
#pragma HLS INLINE

  ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> Vid_Out_;

  Vid_Out_.keep=-1;
  Vid_Out_.strb=-1;
  Vid_Out_.data((DEPTH_*2)*PPC_-1,0)=Vid_In((DEPTH_*2)*PPC_-1,0);
  
  if(0==Pix_Cntr&&0==Line_Cntr){
    Vid_Out_.user=1;
    Vid_Out_.last=0;
    Last_Pix=false;
    ++Pix_Cntr;
  } else if((Width/PPC_-1)==Pix_Cntr&&(Height-1)==Line_Cntr){
    Vid_Out_.user=0;
    Vid_Out_.last=1;
    Last_Pix=true;
    Pix_Cntr=0;
    Line_Cntr=0;
  } else if((Width/PPC_-1)==Pix_Cntr){
    Vid_Out_.user=0;
    Vid_Out_.last=1;
    Last_Pix=false;
    Pix_Cntr=0;
    ++Line_Cntr;
  } else {
    Vid_Out_.user=0;
    Vid_Out_.last=0;
    Last_Pix=false;
    ++Pix_Cntr;
  }

  Vid_Out=Vid_Out_;
}

#endif
