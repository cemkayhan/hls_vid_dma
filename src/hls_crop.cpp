#include "hls_crop.h"

void D_TOP_
(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out,

  ap_uint<Bit_Width<D_MAX_COLS_>::Value> In_Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> In_Height,

  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Out_X,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Out_Y,
  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Out_Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Out_Height
){
#pragma HLS INTERFACE axis port=Vid_In

#pragma HLS INTERFACE axis port=Vid_In
#pragma HLS INTERFACE axis port=Vid_Out

#pragma HLS INTERFACE s_axilite bundle=Ctrl port=return
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=In_Width 
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=In_Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=Out_X
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x28 port=Out_Y
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x30 port=Out_Width 
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x38 port=Out_Height

  const auto In_Width_ {In_Width};
  const auto In_Height_ {In_Height};
  const auto Out_X_ {Out_X};
  const auto Out_Y_ {Out_Y};
  const auto Out_Width_ {Out_Width};
  const auto Out_Height_ {Out_Height};

  ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> Vid_In_;

  loopRows: for(auto J=ap_uint<Bit_Width<D_MAX_ROWS_>::Value> {0};J<In_Height_;++J){
#pragma HLS LOOP_TRIPCOUNT min=D_MAX_ROWS_ max=D_MAX_ROWS_

    loopCols: for(auto K=ap_uint<Bit_Width<D_MAX_COLS_>::Value> {0};K<In_Width_;K+=D_PPC_){
#pragma HLS PIPELINE II=1
#pragma HLS LOOP_TRIPCOUNT min=D_MAX_COLS_/D_PPC_ max=D_MAX_COLS_/D_PPC_

      Vid_In>>Vid_In_;

      if(K==Out_X_&&J==Out_Y_){
        Vid_In_.user=1;
      } else {
        Vid_In_.user=0;
      }

      if(K==Out_X_+Out_Width_-D_PPC_){
        Vid_In_.last=1;
      } else {
        Vid_In_.last=0;
      }

      if(K>=Out_X_&&K<(Out_X_+Out_Width_)&&J>=Out_Y_&&J<(Out_Y_+Out_Height_)){
        Vid_Out<<Vid_In_;
      }
    }
  }
}
