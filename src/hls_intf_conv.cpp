#include "hls_intf_conv.h"

void D_TOP_
(
#if 1==D_ENABLE_DEBUG_
  ap_uint<1>* Missing_Tuser,
  ap_uint<1>* Missing_Tlast,
  ap_uint<1>* Late_Tuser,
  ap_uint<1>* Early_Tlast,
#endif
  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Height,

#if 1==D_VID_OUT_AXIS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out,
#endif
#if 1==D_VID_OUT_AP_NONE_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out,
  ap_uint<1>* Vid_Out_Last,
  ap_uint<1>* Vid_Out_User,
#endif

  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In
){
#pragma HLS INTERFACE axis port=Vid_In
#if 1==D_VID_OUT_AXIS_
#pragma HLS INTERFACE axis port=Vid_Out
#endif
#if 1==D_VID_OUT_AP_NONE_
#pragma HLS INTERFACE ap_ovld port=Vid_Out
#pragma HLS INTERFACE ap_none port=Vid_Out_Last
#pragma HLS INTERFACE ap_none port=Vid_Out_User
#endif

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=Width
#pragma HLS INTERFACE ap_none port=Height

#if 1==D_ENABLE_DEBUG_
#pragma HLS INTERFACE ap_none port=Missing_Tuser
#pragma HLS INTERFACE ap_none port=Missing_Tlast
#pragma HLS INTERFACE ap_none port=Late_Tuser
#pragma HLS INTERFACE ap_none port=Early_Tlast
#endif

#pragma HLS PIPELINE II=1

  static ap_uint<Bit_Width<D_MAX_COLS_/D_PPC_>::Value> Pix_Cntr_ {0};
#pragma HLS RESET variable=Pix_Cntr_

  static ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Line_Cntr_ {0};
#pragma HLS RESET variable=Line_Cntr_

  const auto Width_ {Width};
  const auto Height_ {Height};

#if 1==D_VID_OUT_AXIS_
  ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> Vid_Out_;
#endif
#if 1==D_VID_OUT_AP_NONE_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value> Vid_Out_;
  ap_uint<1> Vid_Out_Last_;
  ap_uint<1> Vid_Out_User_;
#endif
  ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> Vid_In_;
  Vid_In>>Vid_In_;

#if 1==D_VID_OUT_AXIS_
  Vid_Out_.keep=-1;
  Vid_Out_.strb=-1;
  Vid_Out_.data=Vid_In_.data;
#endif
#if 1==D_VID_OUT_AP_NONE_
  Vid_Out_=Vid_In_.data;
#endif

#if 1==D_ENABLE_DEBUG_
  ap_uint<1> Missing_Tuser_ {0};
  ap_uint<1> Missing_Tlast_  {0};
  ap_uint<1> Late_Tuser_ {0};
  ap_uint<1> Early_Tlast_ {0};
#endif
  
  if(0==Pix_Cntr_&&0==Line_Cntr_){
#if 1==D_VID_OUT_AXIS_
    Vid_Out_.user=1;
    Vid_Out_.last=0;
#endif
#if 1==D_VID_OUT_AP_NONE_
    Vid_Out_User_=1;
    Vid_Out_Last_=0;
#endif
    ++Pix_Cntr_;
#if 1==D_ENABLE_DEBUG_
    if(!Vid_In_.user){
      Missing_Tuser_=1;
    }
    if(Vid_In_.last){
      Early_Tlast_=1;
    }
#endif
  } else if((Width_/D_PPC_-1)==Pix_Cntr_&&(Height_-1)==Line_Cntr_){
#if 1==D_VID_OUT_AXIS_
    Vid_Out_.user=0;
    Vid_Out_.last=1;
#endif
#if 1==D_VID_OUT_AP_NONE_
    Vid_Out_User_=0;
    Vid_Out_Last_=1;
#endif
    Pix_Cntr_=0;
    Line_Cntr_=0;
#if 1==D_ENABLE_DEBUG_
    if(Vid_In_.user){
      Late_Tuser_=1;
    }
    if(!Vid_In_.last){
      Missing_Tlast_=1;
    }
#endif
  } else if((Width_/D_PPC_-1)==Pix_Cntr_){
#if 1==D_VID_OUT_AXIS_
    Vid_Out_.user=0;
    Vid_Out_.last=1;
#endif
#if 1==D_VID_OUT_AP_NONE_
    Vid_Out_User_=0;
    Vid_Out_Last_=1;
#endif
    Pix_Cntr_=0;
    ++Line_Cntr_;
#if 1==D_ENABLE_DEBUG_
    if(Vid_In_.user){
      Late_Tuser_=1;
    }
    if(!Vid_In_.last){
      Missing_Tlast_=1;
    }
#endif
  } else {
#if 1==D_VID_OUT_AXIS_
    Vid_Out_.user=0;
    Vid_Out_.last=0;
#endif
    ++Pix_Cntr_;
#if 1==D_ENABLE_DEBUG_
    if(Vid_In_.user){
      Late_Tuser_=1;
    }
    if(Vid_In_.last){
      Early_Tlast_=1;
    }
#endif
  }

#if 1==D_VID_OUT_AXIS_
  Vid_Out<<Vid_Out_;
#endif
#if 1==D_VID_OUT_AP_NONE_
  *Vid_Out=Vid_Out_;
  *Vid_Out_Last=Vid_Out_Last_;
  *Vid_Out_User=Vid_Out_User_;
#endif
#if 1==D_ENABLE_DEBUG_
  *Missing_Tuser=Missing_Tuser_;
  *Missing_Tlast=Missing_Tlast_;
  *Late_Tuser=Late_Tuser_;
  *Early_Tlast=Early_Tlast_;
#endif
}
