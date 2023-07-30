#include "hls_vid_dbg.h"

void D_TOP_(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out,
  ap_uint<16>& Pixel_Cntr_Axi,
  ap_uint<16>& Line_Cntr_Axi,
  ap_uint<16>& Frame_Cntr_Axi,
  ap_uint<16>& Pixel_Cntr,
  ap_uint<16>& Line_Cntr,
  ap_uint<16>& Frame_Cntr
){
#pragma HLS INTERFACE axis port=Vid_In
#pragma HLS INTERFACE axis port=Vid_Out

#pragma HLS INTERFACE s_axilite bundle=Ctrl             port=return
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=Pixel_Cntr_Axi
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=Line_Cntr_Axi
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=Frame_Cntr_Axi

#pragma HLS INTERFACE ap_none port=Pixel_Cntr
#pragma HLS INTERFACE ap_none port=Line_Cntr
#pragma HLS INTERFACE ap_none port=Frame_Cntr

#pragma HLS PIPELINE II=1

  static ap_uint<16> Pix_Cntr_=0;
#pragma HLS RESET variable=Pix_Cntr_

  static ap_uint<16> Line_Cntr_=0;
#pragma HLS RESET variable=Line_Cntr_

  static ap_uint<16> Frame_Cntr_=0;
#pragma HLS RESET variable=Frame_Cntr_

  ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> Pix;
  Vid_In >> Pix;
  Vid_Out << Pix;

  if(Pix.last){
#if 1==D_ENABLE_PIXEL_CNTR_
    Pix_Cntr_=0;
#endif
#if 1==D_ENABLE_LINE_CNTR_
    ++Line_Cntr_;
#endif
  }else if(Pix.user){
#if 1==D_ENABLE_PIXEL_CNTR_
    ++Pix_Cntr_;
#endif
#if 1==D_ENABLE_LINE_CNTR_
    Line_Cntr_=0;
#endif
#if 1==D_ENABLE_FRAME_CNTR_
    ++Frame_Cntr_;
#endif
  }else{
#if 1==D_ENABLE_PIXEL_CNTR_
    ++Pix_Cntr_;
#endif
  }

  Pixel_Cntr=Pix_Cntr_;
  Pixel_Cntr_Axi=Pix_Cntr_;

  Line_Cntr=Line_Cntr_;
  Line_Cntr_Axi=Line_Cntr_;

  Frame_Cntr=Frame_Cntr_;
  Frame_Cntr_Axi=Frame_Cntr_;
}
