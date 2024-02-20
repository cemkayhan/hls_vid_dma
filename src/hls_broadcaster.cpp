#include "hls_broadcaster.h"

void D_TOP_
(
  ap_uint<D_N_CHANNELS_> Channel_En,

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

  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In
){
#pragma HLS INTERFACE axis port=Vid_In

#if 0<D_N_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out1
#endif
#if 1<D_N_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out2
#endif
#if 2<D_N_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out3
#endif
#if 3<D_N_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out4
#endif

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=Channel_En

#pragma HLS PIPELINE II=1

  const auto Channel_En_ {Channel_En};

  ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> Vid_In_;
  Vid_In>>Vid_In_;

#if 0<D_N_CHANNELS_
  if(Channel_En_(0,0)){
    Vid_Out1<<Vid_In_;
  }
#endif

#if 1<D_N_CHANNELS_
  if(Channel_En_(1,1)){
    Vid_Out2<<Vid_In_;
  }
#endif

#if 2<D_N_CHANNELS_
  if(Channel_En_(2,2)){
    Vid_Out3<<Vid_In_;
  }
#endif

#if 3<D_N_CHANNELS_
  if(Channel_En_(3,3)){
    Vid_Out4<<Vid_In_;
  }
#endif
}
