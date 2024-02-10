#include "hls_broadcaster.h"

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
  ap_uint<D_N_CHANNELS_> Channel_En,

#if 1==D_VID_OUT_AXIS_
#if 0<D_N_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out1,
#endif
#if 1<D_N_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out2,
#endif
#if 2<D_N_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out3,
#endif
#if 3<D_N_CHANNELS_
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out4,
#endif
#endif
#if 1==D_VID_OUT_AP_NONE_
#if 0<D_N_CHANNELS_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out1,
  ap_uint<1>* Vid_Out_Last1,
  ap_uint<1>* Vid_Out_User1,
#endif
#if 1<D_N_CHANNELS_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out2,
  ap_uint<1>* Vid_Out_Last2,
  ap_uint<1>* Vid_Out_User2,
#endif
#if 2<D_N_CHANNELS_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out3,
  ap_uint<1>* Vid_Out_Last3,
  ap_uint<1>* Vid_Out_User3,
#endif
#if 3<D_N_CHANNELS_
  ap_uint<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value>* Vid_Out4,
  ap_uint<1>* Vid_Out_Last4,
  ap_uint<1>* Vid_Out_User4,
#endif
#endif

  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_In
){
#pragma HLS INTERFACE axis port=Vid_In
#if 1==D_VID_OUT_AXIS_
#if 0<D_N_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out1
#endif
#if 1<D_N_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out2
#endif
#if 2<D_N_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out3
#endif
#if 3<D_N_CHANNELS_
#pragma HLS INTERFACE axis port=Vid_Out4
#endif
#endif
#if 1==D_VID_OUT_AP_NONE_
#if 0<D_N_CHANNELS_
#pragma HLS INTERFACE ap_ovld port=Vid_Out1
#pragma HLS INTERFACE ap_none port=Vid_Out_Last1
#pragma HLS INTERFACE ap_none port=Vid_Out_User1
#endif

#if 1<D_N_CHANNELS_
#pragma HLS INTERFACE ap_ovld port=Vid_Out2
#pragma HLS INTERFACE ap_none port=Vid_Out_Last2
#pragma HLS INTERFACE ap_none port=Vid_Out_User2
#endif

#if 2<D_N_CHANNELS_
#pragma HLS INTERFACE ap_ovld port=Vid_Out3
#pragma HLS INTERFACE ap_none port=Vid_Out_Last3
#pragma HLS INTERFACE ap_none port=Vid_Out_User3
#endif

#if 3<D_N_CHANNELS_
#pragma HLS INTERFACE ap_ovld port=Vid_Out4
#pragma HLS INTERFACE ap_none port=Vid_Out_Last4
#pragma HLS INTERFACE ap_none port=Vid_Out_User4
#endif
#endif

#if 1==D_RETURN_AP_CTRL_NONE_
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=Width
#pragma HLS INTERFACE ap_none port=Height
#pragma HLS INTERFACE ap_none port=Channel_En
#endif
#if 1==D_RETURN_AXILITE_
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE s_axilite port=Width offset=0x10
#pragma HLS INTERFACE s_axilite port=Height offset=0x18
#pragma HLS INTERFACE s_axilite port=Channel_En offset=0x20
#endif

#if 1==D_ENABLE_DEBUG_
#pragma HLS INTERFACE ap_ovld port=Missing_Tuser
#pragma HLS INTERFACE ap_ovld port=Missing_Tlast
#pragma HLS INTERFACE ap_ovld port=Late_Tuser
#pragma HLS INTERFACE ap_ovld port=Early_Tlast
#endif

#pragma HLS PIPELINE II=1

  static ap_uint<Bit_Width<D_MAX_COLS_/D_PPC_>::Value> Pix_Cntr_ {0};
#pragma HLS RESET variable=Pix_Cntr_

  static ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Line_Cntr_ {0};
#pragma HLS RESET variable=Line_Cntr_

  const auto Width_ {Width};
  const auto Height_ {Height};
  const auto Channel_En_ {Channel_En};

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
#if 1==D_VID_OUT_AP_NONE_
    Vid_Out_User_=0;
    Vid_Out_Last_=0;
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
#if 0<D_N_CHANNELS_
  if(Channel_En_(0,0)){
    Vid_Out1<<Vid_Out_;
  }
#endif
#if 1<D_N_CHANNELS_
  if(Channel_En_(1,1)){
    Vid_Out2<<Vid_Out_;
  }
#endif
#if 2<D_N_CHANNELS_
  if(Channel_En_(2,2)){
    Vid_Out3<<Vid_Out_;
  }
#endif
#if 3<D_N_CHANNELS_
  if(Channel_En_(3,3)){
    Vid_Out4<<Vid_Out_;
  }
#endif
#endif
#if 1==D_VID_OUT_AP_NONE_
#if 0<D_N_CHANNELS_
  if(Channel_En_(0,0)){
    *Vid_Out1=Vid_Out_;
    *Vid_Out_Last1=Vid_Out_Last_;
    *Vid_Out_User1=Vid_Out_User_;
  }
#endif
#if 1<D_N_CHANNELS_
  if(Channel_En_(1,1)){
    *Vid_Out2=Vid_Out_;
    *Vid_Out_Last2=Vid_Out_Last_;
    *Vid_Out_User2=Vid_Out_User_;
  }
#endif
#if 2<D_N_CHANNELS_
  if(Channel_En_(2,2)){
    *Vid_Out3=Vid_Out_;
    *Vid_Out_Last3=Vid_Out_Last_;
    *Vid_Out_User3=Vid_Out_User_;
  }
#endif
#if 3<D_N_CHANNELS_
  if(Channel_En_(3,3)){
    *Vid_Out4=Vid_Out_;
    *Vid_Out_Last4=Vid_Out_Last_;
    *Vid_Out_User4=Vid_Out_User_;
  }
#endif
#endif
#if 1==D_ENABLE_DEBUG_
  *Missing_Tuser=Missing_Tuser_;
  *Missing_Tlast=Missing_Tlast_;
  *Late_Tuser=Late_Tuser_;
  *Early_Tlast=Early_Tlast_;
#endif
}
