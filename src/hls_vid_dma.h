#ifndef HLS_VID_DMA_H_INCLUDE_GUARD_
#define HLS_VID_DMA_H_INCLUDE_GUARD_

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "axi_vid_bus_width.h"
#include "bit_width.h"

void D_TOP_
(
#if 1==D_ENABLE_S2MM_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_S2MM_AXIS_PPC_>::Value,1,1,1> >& S2mm_Axis,
  ap_uint<2*D_DEPTH_*D_S2MM_AXI_PPC_> S2mm_Axi[D_MAX_ROWS_*(D_MAX_STRIDE_/D_S2MM_AXI_PPC_)],

#if 1==D_ENABLE_S2MM_ACTIVE_LINE_
  volatile ap_uint<Bit_Width<D_MAX_ROWS_>::Value>* S2mm_Active_Line,
#endif

#if 1==D_ENABLE_S2MM_STRIDE_
  ap_uint<Bit_Width<D_MAX_STRIDE_>::Value> S2mm_Stride,
#endif
  ap_uint<Bit_Width<D_MAX_COLS_>::Value> S2mm_Width,
#if 1==D_ENABLE_MM2S_
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> S2mm_Height,
#else
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> S2mm_Height
#endif
#endif

#if 1==D_ENABLE_MM2S_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_MM2S_AXIS_PPC_>::Value,1,1,1> >& Mm2s_Axis,
  ap_uint<2*D_DEPTH_*D_MM2S_AXI_PPC_> Mm2s_Axi[D_MAX_ROWS_*(D_MAX_STRIDE_/D_MM2S_AXI_PPC_)],

#if 1==D_ENABLE_MM2S_ACTIVE_LINE_
  volatile ap_uint<Bit_Width<D_MAX_ROWS_>::Value>* Mm2s_Active_Line,
#endif

#if 1==D_ENABLE_MM2S_STRIDE_
  ap_uint<Bit_Width<D_MAX_STRIDE_>::Value> Mm2s_Stride,
#endif
  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Mm2s_Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Mm2s_Height
#endif
);

#if 1==D_ENABLE_S2MM_
template<int COLOR_CHANNELS_,int DEPTH_,int S2MM_AXIS_PPC_,int S2MM_AXI_PPC_,int MAX_ROWS_,int MAX_COLS_,int MAX_STRIDE_>
static void Func_S2mm
(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<COLOR_CHANNELS_,DEPTH_,S2MM_AXIS_PPC_>::Value,1,1,1> >& Axis,
  ap_uint<2*DEPTH_*S2MM_AXI_PPC_> Axi[MAX_ROWS_*MAX_STRIDE_],
#if 1==D_ENABLE_S2MM_ACTIVE_LINE_
  volatile ap_uint<Bit_Width<MAX_ROWS_>::Value>* Active_Line,
#endif
#if 1==D_ENABLE_S2MM_STRIDE_
  ap_uint<Bit_Width<MAX_STRIDE_>::Value> Stride,
#endif
  ap_uint<Bit_Width<MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<MAX_ROWS_>::Value> Height
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

#if 1==D_ENABLE_S2MM_STRIDE_
      Axi[Stride*J+K]=Axi_;
#else
      Axi[(MAX_STRIDE_/S2MM_AXI_PPC_)*J+K]=Axi_;
#endif
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
  volatile ap_uint<Bit_Width<MAX_ROWS_>::Value>* Active_Line,
#endif
#if 1==D_ENABLE_MM2S_STRIDE_
  ap_uint<Bit_Width<MAX_STRIDE_>::Value> Stride,
#endif
  ap_uint<Bit_Width<MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<MAX_ROWS_>::Value> Height
){
#pragma HLS INLINE off
  
  loopRows: for(auto J=ap_uint<Bit_Width<MAX_ROWS_>::Value> {0};J<Height;++J){
#pragma HLS LOOP_TRIPCOUNT min=MAX_ROWS_ max=MAX_ROWS_

#if 1==D_ENABLE_MM2S_ACTIVE_LINE_
    *Active_Line=J;
#endif

    loopCols: for(auto K=ap_uint<Bit_Width<MAX_COLS_/MM2S_AXI_PPC_>::Value> {0};K<Width/MM2S_AXI_PPC_;++K){
#pragma HLS PIPELINE II=MM2S_AXI_PPC_/MM2S_AXIS_PPC_
#pragma HLS LOOP_TRIPCOUNT min=MAX_COLS_/MM2S_AXI_PPC_ max=MAX_COLS_/MM2S_AXI_PPC_

      ap_uint<2*DEPTH_*MM2S_AXI_PPC_> Axi_;
#if 1==D_ENABLE_MM2S_STRIDE_
      Axi_=Axi[Stride*J+K];
#else
      Axi_=Axi[(MAX_STRIDE_/MM2S_AXI_PPC_)*J+K];
#endif

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

#endif
