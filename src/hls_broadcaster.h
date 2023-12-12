#ifndef HLS_BROADCASTER_H_INCLUDE_GUARD_
#define HLS_BROADCASTER_H_INCLUDE_GUARD_

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "axi_vid_bus_width.h"

void D_TOP_
(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In,
#if 0<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out1,
#endif
#if 1<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out2,
#endif
#if 2<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out3,
#endif
#if 3<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out4,
#endif
#if 4<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out5,
#endif
#if 5<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out6,
#endif
#if 6<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out7,
#endif
#if 7<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out8,
#endif
  ap_uint<16> Width,
  ap_uint<16> Height,
  ap_uint<8> Channel_En
);

template<int ID_,int DEPTH_,int PPC_>
static void Broadcast(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_In,
#if 0<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out1,
#endif
#if 1<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out2,
#endif
#if 2<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out3,
#endif
#if 3<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out4,
#endif
#if 4<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out5,
#endif
#if 5<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out6,
#endif
#if 6<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out7,
#endif
#if 7<D_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out8,
#endif
  ap_uint<8> Channel_En
){
#pragma HLS INLINE

  ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> Pix;
  Vid_In>>Pix;

#if 0<D_CHANNELS_
  if(Channel_En(0,0)){
    Vid_Out1<<Pix;
  }
#endif
#if 1<D_CHANNELS_
  if(Channel_En(1,1)){
    Vid_Out2<<Pix;
  }
#endif
#if 2<D_CHANNELS_
  if(Channel_En(2,2)){
    Vid_Out3<<Pix;
  }
#endif
#if 3<D_CHANNELS_
  if(Channel_En(3,3)){
    Vid_Out4<<Pix;
  }
#endif
#if 4<D_CHANNELS_
  if(Channel_En(4,4)){
    Vid_Out5<<Pix;
  }
#endif
#if 5<D_CHANNELS_
  if(Channel_En(5,5)){
    Vid_Out6<<Pix;
  }
#endif
#if 6<D_CHANNELS_
  if(Channel_En(6,6)){
    Vid_Out7<<Pix;
  }
#endif
#if 7<D_CHANNELS_
  if(Channel_En(7,7)){
    Vid_Out8<<Pix;
  }
#endif
}

#endif
