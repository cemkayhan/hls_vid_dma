#if !defined(HLS_BROADCASTER_H_INCLUDE_GUARD_)
#define HLS_BROADCASTER_H_INCLUDE_GUARD_

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "axi_vid_bus_width.h"

void D_TOP_(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out1,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out2,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out3,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out4,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out5,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out6,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out7,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out8,
  ap_uint<16> Width,
  ap_uint<16> Height,
  ap_uint<8> Channel_En
);

template<int ID_,int DEPTH_,int PPC_>
static void Broadcast(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_In,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out1,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out2,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out3,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out4,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out5,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out6,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out7,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> >& Vid_Out8,
  ap_uint<8> Channel_En
){
#pragma HLS PIPELINE II=1

  ap_axiu<Axi_Vid_Bus_Width<DEPTH_,PPC_>::Value,1,1,1> Pix;
  Vid_In>>Pix;

  if(Channel_En(0,0)){
    Vid_Out1<<Pix;
  }
  if(Channel_En(1,1)){
    Vid_Out2<<Pix;
  }
  if(Channel_En(2,2)){
    Vid_Out3<<Pix;
  }
  if(Channel_En(3,3)){
    Vid_Out4<<Pix;
  }
  if(Channel_En(4,4)){
    Vid_Out5<<Pix;
  }
  if(Channel_En(5,5)){
    Vid_Out6<<Pix;
  }
  if(Channel_En(6,6)){
    Vid_Out7<<Pix;
  }
  if(Channel_En(7,7)){
    Vid_Out8<<Pix;
  }
}

#endif
