#include "hls_vid_dma.h"

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
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> S2mm_Height,
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
){
#pragma HLS INTERFACE s_axilite bundle=Ctrl port=return

#if 1==D_ENABLE_S2MM_
#pragma HLS INTERFACE axis port=S2mm_Axis
#pragma HLS INTERFACE m_axi port=S2mm_Axi offset=slave bundle=s2mm depth=D_MAX_ROWS_*(D_MAX_STRIDE_/D_S2MM_AXI_PPC_) max_write_burst_length=D_S2MM_MAX_BURST_LENGTH_ num_read_outstanding=1 max_read_burst_length=2
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=S2mm_Width 
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=S2mm_Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=S2mm_Axi
#if 1==D_ENABLE_S2MM_STRIDE_
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x28 port=S2mm_Stride
#endif
#if 1==D_ENABLE_S2MM_ACTIVE_LINE_
#pragma HLS INTERFACE ap_none port=S2mm_Active_Line register
#endif
#endif

#if 1==D_ENABLE_MM2S_
#pragma HLS INTERFACE axis port=Mm2s_Axis
#pragma HLS INTERFACE m_axi port=Mm2s_Axi offset=slave bundle=mm2s depth=D_MAX_ROWS_*(D_MAX_STRIDE_/D_MM2S_AXI_PPC_) max_read_burst_length=D_MM2S_MAX_BURST_LENGTH_ num_write_outstanding=1 max_write_burst_length=2
#if 1==D_ENABLE_S2MM_
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x30 port=Mm2s_Width
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x38 port=Mm2s_Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x40 port=Mm2s_Axi
#if 1==D_ENABLE_MM2S_STRIDE_
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x48 port=Mm2s_Stride
#endif
#else
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=Mm2s_Width
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=Mm2s_Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=Mm2s_Axi
#if 1==D_ENABLE_MM2S_STRIDE_
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x28 port=Mm2s_Stride
#endif
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
#if 1==D_ENABLE_S2MM_STRIDE_
    S2mm_Stride,
#endif
    S2mm_Width,
    S2mm_Height
  );
#endif

#if 1==D_ENABLE_MM2S_
  Func_Mm2s<D_COLOR_CHANNELS_,D_DEPTH_,D_MM2S_AXIS_PPC_,D_MM2S_AXI_PPC_,D_MAX_ROWS_,D_MAX_COLS_,D_MAX_STRIDE_>(
    Mm2s_Axis,
    Mm2s_Axi,
#if 1==D_ENABLE_MM2S_ACTIVE_LINE_
    Mm2s_Active_Line,
#endif
#if 1==D_ENABLE_MM2S_STRIDE_
    Mm2s_Stride,
#endif
    Mm2s_Width,
    Mm2s_Height
  );
#endif
}
