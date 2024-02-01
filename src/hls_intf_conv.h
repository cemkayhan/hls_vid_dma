#ifndef HLS_INTF_CONV_H_INCLUDE_GUARD_
#define HLS_INTF_CONV_H_INCLUDE_GUARD_

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "axi_vid_bus_width.h"
#include "bit_width.h"

void D_TOP_
(
#if 1==D_ENABLE_DEBUG_
  ap_uint<1>* Missing_Tuser,
  ap_uint<1>* Missing_Tlast,
  ap_uint<1>* Late_Tuser,
  ap_uint<1>* Early_Tlast,
#endif
  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Height,

#if 1==D_VID_OUT_AXIS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out,
#endif
#if 1==D_VID_OUT_AP_NONE_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out,
  ap_uint<1>* Vid_Out_Last,
  ap_uint<1>* Vid_Out_User,
#endif

  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In
);

#endif
