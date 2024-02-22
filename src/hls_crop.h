#ifndef HLS_CROP_H_INCLUDE_GUARD_
#define HLS_CROP_H_INCLUDE_GUARD_

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "axi_vid_bus_width.h"
#include "bit_width.h"

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
);

#endif
