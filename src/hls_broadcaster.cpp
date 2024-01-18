#include "hls_broadcaster.h"

void D_TOP_
(
#if 0<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out1,
#endif
#if 1<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out2,
#endif
#if 2<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out3,
#endif
#if 3<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out4,
#endif
#if 4<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out5,
#endif
#if 5<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out6,
#endif
#if 6<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out7,
#endif
#if 7<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out8,
#endif

  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In,
  ap_uint<D_CHANNELS_> Channel_En
){
#if 0<D_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out1
#endif
#if 1<D_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out2
#endif
#if 2<D_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out3
#endif
#if 3<D_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out4
#endif
#if 4<D_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out5
#endif
#if 5<D_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out6
#endif
#if 6<D_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out7
#endif
#if 7<D_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out8
#endif

#pragma HLS INTERFACE axis port=Vid_In

#pragma HLS INTERFACE s_axilite bundle=Ctrl             port=return
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=Channel_En

#pragma HLS PIPELINE II=1

  auto Channel_En_ {Channel_En};
  ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> Pix_;
  Vid_In>>Pix_;

#if 0<D_CHANNELS_
  if(Channel_En_(0,0)){
    Vid_Out1<<Pix_;
  }
#endif
#if 1<D_CHANNELS_
  if(Channel_En_(1,1)){
    Vid_Out2<<Pix_;
  }
#endif
#if 2<D_CHANNELS_
  if(Channel_En_(2,2)){
    Vid_Out3<<Pix_;
  }
#endif
#if 3<D_CHANNELS_
  if(Channel_En_(3,3)){
    Vid_Out4<<Pix_;
  }
#endif
#if 4<D_CHANNELS_
  if(Channel_En_(4,4)){
    Vid_Out5<<Pix_;
  }
#endif
#if 5<D_CHANNELS_
  if(Channel_En_(5,5)){
    Vid_Out6<<Pix_;
  }
#endif
#if 6<D_CHANNELS_
  if(Channel_En_(6,6)){
    Vid_Out7<<Pix_;
  }
#endif
#if 7<D_CHANNELS_
  if(Channel_En_(7,7)){
    Vid_Out8<<Pix_;
  }
#endif
}
