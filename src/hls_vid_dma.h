#ifndef HLS_VID_DMA_H_INCLUDE_GUARD_
#define HLS_VID_DMA_H_INCLUDE_GUARD_

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "axi_vid_bus_width.h"
#include "bit_width.h"

void D_TOP_
(
#if 1==D_VIDEO_DMA_WRITE_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_S2MM_AXIS_PPC_>::Value,1,1,1> >& Vid_In,
  ap_uint<2*D_DEPTH_*D_S2MM_AXI_PPC_> Vid_In_Axi[D_MAX_ROWS_*D_MAX_STRIDE_],
#endif

#if 1==D_VIDEO_DMA_READ_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_MM2S_AXIS_PPC_>::Value,1,1,1> >& Vid_Out,
  ap_uint<2*D_DEPTH_*D_MM2S_AXI_PPC_> Vid_Out_Axi[D_MAX_ROWS_*D_MAX_STRIDE_],
#endif

  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Height,
  ap_uint<Bit_Width<D_MAX_STRIDE_>::Value> Stride
);

#endif
