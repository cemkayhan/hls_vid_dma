#include "hls_broadcaster.h"

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
){
#pragma HLS INTERFACE axis port=Vid_In
#pragma HLS INTERFACE axis port=Vid_Out1
#pragma HLS INTERFACE axis port=Vid_Out2
#pragma HLS INTERFACE axis port=Vid_Out3
#pragma HLS INTERFACE axis port=Vid_Out4
#pragma HLS INTERFACE axis port=Vid_Out5
#pragma HLS INTERFACE axis port=Vid_Out6
#pragma HLS INTERFACE axis port=Vid_Out7
#pragma HLS INTERFACE axis port=Vid_Out8

#pragma HLS INTERFACE s_axilite bundle=Ctrl             port=return
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=Width
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=Channel_En

  loopRows: for(auto I=0;I<Height;++I){
    loopCols: for(auto J=0;J<Width;++J){
#pragma HLS DATAFLOW
      Broadcast<0,D_DEPTH_,D_PPC_>(
        Vid_In,
        Vid_Out1,
        Vid_Out2,
        Vid_Out3,
        Vid_Out4,
        Vid_Out5,
        Vid_Out6,
        Vid_Out7,
        Vid_Out8,
        Channel_En
      );
    }
  }
}
