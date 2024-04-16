#include "hls_vid_line_dma.h"

template<int COLOR_CHANNELS_,int DEPTH_,int S2MM_AXIS_PPC_,int S2MM_AXI_PPC_,int MAX_ROWS_,int MAX_COLS_,int MAX_STRIDE_>
static void Func_S2mm
(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<COLOR_CHANNELS_,DEPTH_,S2MM_AXIS_PPC_>::Value,1,1,1> >& Vid_In,
  ap_uint<2*DEPTH_*S2MM_AXI_PPC_> Vid_In_Axi[MAX_ROWS_*MAX_STRIDE_],
  ap_uint<Bit_Width<MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<MAX_ROWS_>::Value> Height,
  ap_uint<Bit_Width<MAX_STRIDE_>::Value> Stride,
  hls::stream<ap_uint<1> >& Hshake_Buffer
){
#pragma HLS INLINE off
  
  loopRows: for(auto J=ap_uint<Bit_Width<MAX_ROWS_>::Value> {0};J<Height;++J){
#pragma HLS LOOP_TRIPCOUNT min=MAX_ROWS_ max=MAX_ROWS_

    loopCols: for(auto K=ap_uint<Bit_Width<MAX_COLS_/S2MM_AXI_PPC_>::Value> {0};K<Width/S2MM_AXI_PPC_;++K){
#pragma HLS PIPELINE II=S2MM_AXI_PPC_/S2MM_AXIS_PPC_
#pragma HLS LOOP_TRIPCOUNT min=MAX_COLS_/S2MM_AXI_PPC_ max=MAX_COLS_/S2MM_AXI_PPC_

      ap_uint<2*DEPTH_*S2MM_AXI_PPC_> Vid_In_Axi_;
      loopPix: for(auto M=0;M<S2MM_AXI_PPC_/S2MM_AXIS_PPC_;++M){
#pragma HLS UNROLL
        Vid_In_Axi_(M*2*DEPTH_+2*DEPTH_-1,M*2*DEPTH_)=Vid_In.read().data;
      }

      Vid_In_Axi[Stride*J+K]=Vid_In_Axi_;
    }

    Hshake_Buffer.write(ap_uint<1> {0});
  }
}

template<int COLOR_CHANNELS_,int DEPTH_,int MM2S_AXIS_PPC_,int MM2S_AXI_PPC_,int MAX_ROWS_,int MAX_COLS_,int MAX_STRIDE_>
static void Func_Mm2s
(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<COLOR_CHANNELS_,DEPTH_,MM2S_AXIS_PPC_>::Value,1,1,1> >& Vid_Out,
  ap_uint<2*DEPTH_*MM2S_AXI_PPC_> Vid_Out_Axi[MAX_ROWS_*MAX_STRIDE_],
  ap_uint<Bit_Width<MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<MAX_ROWS_>::Value> Height,
  ap_uint<Bit_Width<MAX_STRIDE_>::Value> Stride,
  hls::stream<ap_uint<1> >& Hshake_Buffer
){
#pragma HLS INLINE off
  
  loopRows: for(auto J=ap_uint<Bit_Width<MAX_ROWS_>::Value> {0};J<Height;++J){
#pragma HLS LOOP_TRIPCOUNT min=MAX_ROWS_ max=MAX_ROWS_

    ap_uint<1> Tmp_;
    Hshake_Buffer.read(Tmp_);

    loopCols: for(auto K=ap_uint<Bit_Width<D_MAX_COLS_/MM2S_AXI_PPC_>::Value> {0};K<Width/MM2S_AXI_PPC_;++K){
#pragma HLS PIPELINE II=MM2S_AXI_PPC_/MM2S_AXIS_PPC_
#pragma HLS LOOP_TRIPCOUNT min=MAX_COLS_/MM2S_AXI_PPC_ max=MAX_COLS_/MM2S_AXI_PPC_

      ap_uint<2*DEPTH_*MM2S_AXI_PPC_> Vid_Out_Axi_;
      Vid_Out_Axi_=Vid_Out_Axi[Stride*J+K];
      loopPix: for(auto M=0;M<MM2S_AXI_PPC_/MM2S_AXIS_PPC_;++M){
#pragma HLS UNROLL

        ap_axiu<Axi_Vid_Bus_Width<COLOR_CHANNELS_,DEPTH_,MM2S_AXIS_PPC_>::Value,1,1,1> Vid_Out_;
        Vid_Out_.keep=-1;
        Vid_Out_.strb=-1;
        Vid_Out_.data=Vid_Out_Axi_(M*2*DEPTH_+2*DEPTH_-1,M*2*DEPTH_);
        if(0==J&&0==K&&0==M){
          Vid_Out_.user=1;
          Vid_Out_.last=0;
        } else if(Width/MM2S_AXI_PPC_-1==K&&(MM2S_AXI_PPC_/MM2S_AXIS_PPC_-1)==M){
          Vid_Out_.user=0;
          Vid_Out_.last=1;
        } else {
          Vid_Out_.user=0;
          Vid_Out_.last=0;
        }

        Vid_Out.write(Vid_Out_);
      }
    }
  }
}

void D_TOP_
(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_S2MM_AXIS_PPC_>::Value,1,1,1> >& Vid_In,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_MM2S_AXIS_PPC_>::Value,1,1,1> >& Vid_Out,

  ap_uint<2*D_DEPTH_*D_S2MM_AXI_PPC_> Vid_In_Axi[D_MAX_ROWS_*D_MAX_STRIDE_],
  ap_uint<2*D_DEPTH_*D_MM2S_AXI_PPC_> Vid_Out_Axi[D_MAX_ROWS_*D_MAX_STRIDE_],

  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Height,
  ap_uint<Bit_Width<D_MAX_STRIDE_>::Value> Stride
){
#pragma HLS INTERFACE axis port=Vid_In
#pragma HLS INTERFACE axis port=Vid_Out

#pragma HLS INTERFACE m_axi port=Vid_In_Axi offset=slave bundle=VidInAxi depth=D_MAX_ROWS_*D_MAX_STRIDE_
#pragma HLS INTERFACE m_axi port=Vid_Out_Axi offset=slave bundle=VidOutAxi depth=D_MAX_ROWS_*D_MAX_STRIDE_

#pragma HLS INTERFACE s_axilite bundle=Ctrl port=return
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=Width 
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=Stride
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x28 port=Vid_In_Axi
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x30 port=Vid_Out_Axi

#pragma HLS DATAFLOW

  hls::stream<ap_uint<1>> Hshake_Buffer;
#pragma HLS STREAM variable=Hshake_Buffer depth=D_HANDSHAKE_BUFFER_DEPTH_
 
#if 1
  Func_S2mm<D_COLOR_CHANNELS_,D_DEPTH_,D_S2MM_AXIS_PPC_,D_S2MM_AXI_PPC_,D_MAX_ROWS_,D_MAX_COLS_,D_MAX_STRIDE_>(
    Vid_In,
    Vid_In_Axi,
    Width,
    Height,
    Stride,
    Hshake_Buffer
  );
#endif

#if 1
  Func_Mm2s<D_COLOR_CHANNELS_,D_DEPTH_,D_MM2S_AXIS_PPC_,D_MM2S_AXI_PPC_,D_MAX_ROWS_,D_MAX_COLS_,D_MAX_STRIDE_>(
    Vid_Out,
    Vid_Out_Axi,
    Width,
    Height,
    Stride,
    Hshake_Buffer
  );
#endif
}
