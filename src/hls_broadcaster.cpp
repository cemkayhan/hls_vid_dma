#include "hls_broadcaster.h"

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
){
#pragma HLS INTERFACE axis port=Vid_In

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

#pragma HLS INTERFACE s_axilite bundle=Ctrl             port=return
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=Width
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=Channel_En

  ap_uint<16> Width_=Width;
  ap_uint<16> Height_=Height;
  ap_uint<16> Channel_En_=Channel_En;

  loopRows: for(auto I=0;I<Height_;++I){
    loopCols: for(auto J=0;J<Width_;++J){
#pragma HLS PIPELINE II=1
      Broadcast<0,D_DEPTH_,D_PPC_>(
        Vid_In,
#if 0<D_CHANNELS_
        Vid_Out1,
#endif
#if 1<D_CHANNELS_
        Vid_Out2,
#endif
#if 2<D_CHANNELS_
        Vid_Out3,
#endif
#if 3<D_CHANNELS_
        Vid_Out4,
#endif
#if 4<D_CHANNELS_
        Vid_Out5,
#endif
#if 5<D_CHANNELS_
        Vid_Out6,
#endif
#if 6<D_CHANNELS_
        Vid_Out7,
#endif
#if 7<D_CHANNELS_
        Vid_Out8,
#endif
        Channel_En_
      );
    }
  }
}
