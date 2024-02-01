#ifndef HLS_BROADCASTER_H_INCLUDE_GUARD_
#define HLS_BROADCASTER_H_INCLUDE_GUARD_

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
  ap_uint<D_N_CHANNELS_> Channel_En,

#if 1==D_VID_OUT_AXIS_
#if 0<D_N_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out1,
#endif
#if 1<D_N_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out2,
#endif
#if 2<D_N_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out3,
#endif
#if 3<D_N_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out4,
#endif
#endif
#if 1==D_VID_OUT_AP_NONE_
#if 0<D_N_CHANNELS_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out1,
  ap_uint<1>* Vid_Out_Last1,
  ap_uint<1>* Vid_Out_User1,
#endif
#if 1<D_N_CHANNELS_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out2,
  ap_uint<1>* Vid_Out_Last2,
  ap_uint<1>* Vid_Out_User2,
#endif
#if 2<D_N_CHANNELS_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out3,
  ap_uint<1>* Vid_Out_Last3,
  ap_uint<1>* Vid_Out_User3,
#endif
#if 3<D_N_CHANNELS_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out4,
  ap_uint<1>* Vid_Out_Last4,
  ap_uint<1>* Vid_Out_User4,
#endif
#endif

  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In
);

#endif
