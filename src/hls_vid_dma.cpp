#include "hls_vid_dma.h"

#if 1==D_ENABLE_S2MM_
template<int COLOR_CHANNELS_,int DEPTH_,int S2MM_AXIS_PPC_,int S2MM_AXI_PPC_,int MAX_ROWS_,int MAX_COLS_,int MAX_STRIDE_>
static void Func_S2mm
(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<COLOR_CHANNELS_,DEPTH_,S2MM_AXIS_PPC_>::Value,1,1,1> >& Axis,
  ap_uint<2*DEPTH_*S2MM_AXI_PPC_> Axi[MAX_ROWS_*MAX_STRIDE_],
#if 1==D_ENABLE_S2MM_ACTIVE_LINE_
  volatile ap_uint<Bit_Width<D_MAX_ROWS_>::Value>* Active_Line,
#endif
  ap_uint<Bit_Width<MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<MAX_ROWS_>::Value> Height,
  ap_uint<Bit_Width<MAX_STRIDE_>::Value> Stride
){
#pragma HLS INLINE off

  loopRows: for(auto J=ap_uint<Bit_Width<MAX_ROWS_>::Value> {0};J<Height;++J){
#pragma HLS LOOP_TRIPCOUNT min=MAX_ROWS_ max=MAX_ROWS_

#if 1==D_ENABLE_S2MM_ACTIVE_LINE_
    *Active_Line=J;
#endif

    loopCols: for(auto K=ap_uint<Bit_Width<MAX_COLS_/S2MM_AXI_PPC_>::Value> {0};K<Width/S2MM_AXI_PPC_;++K){
#pragma HLS PIPELINE II=S2MM_AXI_PPC_/S2MM_AXIS_PPC_
#pragma HLS LOOP_TRIPCOUNT min=MAX_COLS_/S2MM_AXI_PPC_ max=MAX_COLS_/S2MM_AXI_PPC_

      ap_uint<2*DEPTH_*S2MM_AXI_PPC_> Axi_;
      loopPix: for(auto M=0;M<S2MM_AXI_PPC_/S2MM_AXIS_PPC_;++M){
#pragma HLS UNROLL
        Axi_(M*2*DEPTH_*S2MM_AXIS_PPC_+2*DEPTH_*S2MM_AXIS_PPC_-1,M*2*DEPTH_*S2MM_AXIS_PPC_)=Axis.read().data;
      }

      Axi[Stride*J+K]=Axi_;
    }
  }
}
#endif

#if 1==D_ENABLE_MM2S_
template<int COLOR_CHANNELS_,int DEPTH_,int MM2S_AXIS_PPC_,int MM2S_AXI_PPC_,int MAX_ROWS_,int MAX_COLS_,int MAX_STRIDE_>
static void Func_Mm2s
(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<COLOR_CHANNELS_,DEPTH_,MM2S_AXIS_PPC_>::Value,1,1,1> >& Axis,
  ap_uint<2*DEPTH_*MM2S_AXI_PPC_> Axi[MAX_ROWS_*MAX_STRIDE_],
#if 1==D_ENABLE_MM2S_ACTIVE_LINE_
  volatile ap_uint<Bit_Width<D_MAX_ROWS_>::Value>* Active_Line,
#endif
  ap_uint<Bit_Width<MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<MAX_ROWS_>::Value> Height,
  ap_uint<Bit_Width<MAX_STRIDE_>::Value> Stride
){
#pragma HLS INLINE off
  
  loopRows: for(auto J=ap_uint<Bit_Width<MAX_ROWS_>::Value> {0};J<Height;++J){
#pragma HLS LOOP_TRIPCOUNT min=MAX_ROWS_ max=MAX_ROWS_

#if 1==D_ENABLE_MM2S_ACTIVE_LINE_
    *Active_Line=J;
#endif

    loopCols: for(auto K=ap_uint<Bit_Width<D_MAX_COLS_/MM2S_AXI_PPC_>::Value> {0};K<Width/MM2S_AXI_PPC_;++K){
#pragma HLS PIPELINE II=MM2S_AXI_PPC_/MM2S_AXIS_PPC_
#pragma HLS LOOP_TRIPCOUNT min=MAX_COLS_/MM2S_AXI_PPC_ max=MAX_COLS_/MM2S_AXI_PPC_

      ap_uint<2*DEPTH_*MM2S_AXI_PPC_> Axi_;
      Axi_=Axi[Stride*J+K];
      loopPix: for(auto M=0;M<MM2S_AXI_PPC_/MM2S_AXIS_PPC_;++M){
#pragma HLS UNROLL

        ap_axiu<Axi_Vid_Bus_Width<COLOR_CHANNELS_,DEPTH_,MM2S_AXIS_PPC_>::Value,1,1,1> Axis_;
        Axis_.keep=-1;
        Axis_.strb=-1;
        Axis_.data=Axi_(M*2*DEPTH_*MM2S_AXIS_PPC_+2*DEPTH_*MM2S_AXIS_PPC_-1,M*2*DEPTH_*MM2S_AXIS_PPC_);
        if(0==J&&0==K&&0==M){
          Axis_.user=1;
          Axis_.last=0;
        } else if(Width/MM2S_AXI_PPC_-1==K&&(MM2S_AXI_PPC_/MM2S_AXIS_PPC_-1)==M){
          Axis_.user=0;
          Axis_.last=1;
        } else {
          Axis_.user=0;
          Axis_.last=0;
        }

        Axis.write(Axis_);
      }
    }
  }
}
#endif

void D_TOP_
(
#if 1==D_ENABLE_S2MM_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_S2MM_AXIS_PPC_>::Value,1,1,1> >& S2mm_Axis,
  ap_uint<2*D_DEPTH_*D_S2MM_AXI_PPC_> S2mm_Axi[D_MAX_ROWS_*D_MAX_STRIDE_],

#if 1==D_ENABLE_S2MM_ACTIVE_LINE_
  volatile ap_uint<Bit_Width<D_MAX_ROWS_>::Value>* S2mm_Active_Line,
#endif

  ap_uint<Bit_Width<D_MAX_COLS_>::Value> S2mm_Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> S2mm_Height,
#if 1==D_ENABLE_MM2S_
  ap_uint<Bit_Width<D_MAX_STRIDE_>::Value> S2mm_Stride,
#else
  ap_uint<Bit_Width<D_MAX_STRIDE_>::Value> S2mm_Stride
#endif
#endif

#if 1==D_ENABLE_MM2S_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_MM2S_AXIS_PPC_>::Value,1,1,1> >& Mm2s_Axis,
  ap_uint<2*D_DEPTH_*D_MM2S_AXI_PPC_> Mm2s_Axi[D_MAX_ROWS_*D_MAX_STRIDE_],

#if 1==D_ENABLE_MM2S_ACTIVE_LINE_
  volatile ap_uint<Bit_Width<D_MAX_ROWS_>::Value>* Mm2s_Active_Line,
#endif

  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Mm2s_Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Mm2s_Height,
  ap_uint<Bit_Width<D_MAX_STRIDE_>::Value> Mm2s_Stride
#endif
){
#pragma HLS INTERFACE s_axilite bundle=Ctrl port=return

#if 1==D_ENABLE_S2MM_
#pragma HLS INTERFACE axis port=S2mm_Axis
#pragma HLS INTERFACE m_axi port=S2mm_Axi offset=slave bundle=s2mm depth=D_MAX_ROWS_*D_MAX_STRIDE_ max_write_burst_length=D_S2MM_MAX_BURST_LENGTH_
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=S2mm_Width 
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=S2mm_Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=S2mm_Stride
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x28 port=S2mm_Axi
#if 1==D_ENABLE_S2MM_ACTIVE_LINE_
#pragma HLS INTERFACE ap_none port=S2mm_Active_Line register
#endif
#endif

#if 1==D_ENABLE_MM2S_
#pragma HLS INTERFACE axis port=Mm2s_Axis
#pragma HLS INTERFACE m_axi port=Mm2s_Axi offset=slave bundle=mm2s depth=D_MAX_ROWS_*D_MAX_STRIDE_ max_read_burst_length=D_MM2S_MAX_BURST_LENGTH_
#if 1==D_ENABLE_S2MM_
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x30 port=Mm2s_Width
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x38 port=Mm2s_Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x40 port=Mm2s_Stride
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x48 port=Mm2s_Axi
#else
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=Mm2s_Width
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=Mm2s_Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=Mm2s_Stride
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x28 port=Mm2s_Axi
#endif
#if 1==D_ENABLE_MM2S_ACTIVE_LINE_
#pragma HLS INTERFACE ap_none port=Mm2s_Active_Line register
#endif
#endif

#pragma HLS DATAFLOW

#if 1==D_ENABLE_S2MM_
  Func_S2mm<D_COLOR_CHANNELS_,D_DEPTH_,D_S2MM_AXIS_PPC_,D_S2MM_AXI_PPC_,D_MAX_ROWS_,D_MAX_COLS_,D_MAX_STRIDE_>(
    S2mm_Axis,
    S2mm_Axi,
#if 1==D_ENABLE_S2MM_ACTIVE_LINE_
    S2mm_Active_Line,
#endif
    S2mm_Width,
    S2mm_Height,
    S2mm_Stride
  );
#endif

#if 1==D_ENABLE_MM2S_
  Func_Mm2s<D_COLOR_CHANNELS_,D_DEPTH_,D_MM2S_AXIS_PPC_,D_MM2S_AXI_PPC_,D_MAX_ROWS_,D_MAX_COLS_,D_MAX_STRIDE_>(
    Mm2s_Axis,
    Mm2s_Axi,
#if 1==D_ENABLE_MM2S_ACTIVE_LINE_
    Mm2s_Active_Line,
#endif
    Mm2s_Width,
    Mm2s_Height,
    Mm2s_Stride
  );
#endif
}
