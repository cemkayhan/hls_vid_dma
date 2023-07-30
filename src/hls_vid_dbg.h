#if !defined(HLS_VID_DBG_H_INCLUDE_GUARD_)
#define HLS_VID_DBG_H_INCLUDE_GUARD_

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "axi_vid_bus_width.h"

void D_TOP_(
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out,
  ap_uint<16>& Pixel_Cntr_Axi,
  ap_uint<16>& Line_Cntr_Axi,
  ap_uint<16>& Frame_Cntr_Axi,
  ap_uint<16>& Pixel_Cntr,
  ap_uint<16>& Line_Cntr,
  ap_uint<16>& Frame_Cntr
);

#endif
