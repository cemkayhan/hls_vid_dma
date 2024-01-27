#include "hls_econ_vid_cap.h"

void D_TOP_
(
#if 1==D_ENABLE_DEBUG_
  ap_uint<1>* Missed_Pix1_Error,
#if 1<D_PPC_
  ap_uint<1>* Missed_Pix2_Error,
#endif
#if 2<D_PPC_
  ap_uint<1>* Missed_Pix3_Error,
#endif
#if 3<D_PPC_
  ap_uint<1>* Missed_Pix4_Error,
#endif
#endif

  ap_uint<1> Test_Mode,
  ap_uint<32> Test_Data,

  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Width,
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Height,

  hls::stream<ap_uint<2+D_DEPTH_*2> >& Vid_In,
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> >& Vid_Out
){
#if 1==D_ENABLE_DEBUG_
#pragma HLS INTERFACE ap_none port=Missed_Pix1_Error
#if 1<D_PPC_
#pragma HLS INTERFACE ap_none port=Missed_Pix2_Error
#endif
#if 2<D_PPC_
#pragma HLS INTERFACE ap_none port=Missed_Pix3_Error
#endif
#if 3<D_PPC_
#pragma HLS INTERFACE ap_none port=Missed_Pix4_Error
#endif
#endif

#pragma HLS INTERFACE ap_none port=Test_Data 
#pragma HLS INTERFACE ap_fifo port=Vid_In
#pragma HLS INTERFACE axis port=Vid_Out

#pragma HLS INTERFACE s_axilite port=return bundle=Ctrl
#pragma HLS INTERFACE s_axilite port=Width bundle=Ctrl offset=0x10
#pragma HLS INTERFACE s_axilite port=Height bundle=Ctrl offset=0x18
#pragma HLS INTERFACE s_axilite port=Test_Mode bundle=Ctrl offset=0x20

#pragma HLS PIPELINE II=1

  enum class Mystate {
    Reset,
    Wait_Blanking,
#if 3<D_PPC_
    Wait_Data_Ppc4,
#endif
#if 2<D_PPC_
    Wait_Data_Ppc3,
#endif
#if 1<D_PPC_
    Wait_Data_Ppc2,
#endif
    Wait_Data_Ppc1
  };

  static Mystate Mystate_ {Mystate::Reset};
#pragma HLS RESET variable=Mystate_

  static ap_uint<Bit_Width<D_MAX_COLS_/D_PPC_>::Value> Pix_Cntr_ {0};
#pragma HLS RESET variable=Pix_Cntr_

  static ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Line_Cntr_ {0};
#pragma HLS RESET variable=Line_Cntr_

  static ap_uint<(D_DEPTH_*2)*D_PPC_> Vid_In_Ppc_;
#pragma HLS RESET variable=Vid_In_Ppc_ off

  const auto PIX1_ {1};
#if 1<D_PPC_
  const auto PIX2_ {2};
#endif
#if 2<D_PPC_
  const auto PIX3_ {3};
#endif
#if 3<D_PPC_
  const auto PIX4_ {4};
#endif

  const auto Test_Mode_ {Test_Mode};
  const auto Test_Data_ {Test_Data};
  const auto Width_ {Width};
  const auto Height_ {Height};

  ap_uint<2+D_DEPTH_*2> Vid_In_;
  ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> Vid_Out_;
  bool Last_Pix_;

#if 1==D_ENABLE_DEBUG_
  ap_uint<1> Missed_Pix1_Error_ {0};
#if 1<D_PPC_
  ap_uint<1> Missed_Pix2_Error_ {0};
#endif
#if 2<D_PPC_
  ap_uint<1> Missed_Pix3_Error_ {0};
#endif
#if 3<D_PPC_
  ap_uint<1> Missed_Pix4_Error_ {0};
#endif
#endif

  switch(Mystate_){
    case Mystate::Reset:
      Mystate_=Mystate::Wait_Blanking;
      break;

    case Mystate::Wait_Blanking:
      Vid_In>>Vid_In_;
      
      if(0==Vid_In_(D_DEPTH_*2+1,D_DEPTH_*2)){
        Mystate_=Mystate::Wait_Data_Ppc1;
      } else {
        Mystate_=Mystate::Wait_Blanking;
      }
      break;

    case Mystate::Wait_Data_Ppc1:
      Vid_In>>Vid_In_;
      if(Test_Mode_){
        Vid_In_Ppc_(PIX1_*D_DEPTH_*2-1,(PIX1_-1)*D_DEPTH_*2)=Test_Data_(D_DEPTH_*2-1,0);
      } else {
        Vid_In_Ppc_(PIX1_*D_DEPTH_*2-1,(PIX1_-1)*D_DEPTH_*2)=Vid_In_(D_DEPTH_*2-1,0);
      }
      if(3==Vid_In_(D_DEPTH_*2+1,D_DEPTH_*2)){
#if 1<D_PPC_
        Mystate_=Mystate::Wait_Data_Ppc2;
#else
        Create_Pix<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_,D_MAX_COLS_,D_MAX_ROWS_>(
          Vid_In_Ppc_,Vid_Out_,
          Pix_Cntr_,Line_Cntr_,Width_,Height_,Last_Pix_
        );
        Vid_Out<<Vid_Out_;
        if(Last_Pix_){
          Mystate_=Mystate::Wait_Blanking;
        } else {
          Mystate_=Mystate::Wait_Data_Ppc1;
        }
#endif
      }
#if 1==D_ENABLE_DEBUG_
      else if(0!=Pix_Cntr_){
        Missed_Pix1_Error_=1;
        Mystate_=Mystate::Wait_Data_Ppc1;
      }
#endif
      else{
        Mystate_=Mystate::Wait_Data_Ppc1;
      }
      break;

#if 1<D_PPC_
    case Mystate::Wait_Data_Ppc2:
      Vid_In>>Vid_In_;
      if(Test_Mode_){
        Vid_In_Ppc_(PIX2_*D_DEPTH_*2-1,(PIX2_-1)*D_DEPTH_*2)=Test_Data_(D_DEPTH_*2-1,0);
      } else {
        Vid_In_Ppc_(PIX2_*D_DEPTH_*2-1,(PIX2_-1)*D_DEPTH_*2)=Vid_In_(D_DEPTH_*2-1,0);
      }
      if(3==Vid_In_(D_DEPTH_*2+1,D_DEPTH_*2)){
#if 2<D_PPC_
        Mystate_=Mystate::Wait_Data_Ppc3;
#else
        Create_Pix<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_,D_MAX_COLS_,D_MAX_ROWS_>(
          Vid_In_Ppc_,Vid_Out_,
          Pix_Cntr_,Line_Cntr_,Width_,Height_,Last_Pix_
        );
        Vid_Out<<Vid_Out_;
        if(Last_Pix_){
          Mystate_=Mystate::Wait_Blanking;
        } else {
          Mystate_=Mystate::Wait_Data_Ppc1;
        }
#endif
      }
#if 1==D_ENABLE_DEBUG_
      else if(0!=Pix_Cntr_){
        Missed_Pix2_Error_=1;
        Mystate_=Mystate::Wait_Data_Ppc2;
      }
#endif
      else{
        Mystate_=Mystate::Wait_Data_Ppc2;
      }
      break;
#endif

#if 2<D_PPC_
    case Mystate::Wait_Data_Ppc3:
      Vid_In>>Vid_In_;
      if(Test_Mode_){
        Vid_In_Ppc_(PIX3_*D_DEPTH_*2-1,(PIX3_-1)*D_DEPTH_*2)=Test_Data_(D_DEPTH_*2-1,0);
      } else {
        Vid_In_Ppc_(PIX3_*D_DEPTH_*2-1,(PIX3_-1)*D_DEPTH_*2)=Vid_In_(D_DEPTH_*2-1,0);
      }
      if(3==Vid_In_(D_DEPTH_*2+1,D_DEPTH_*2)){
#if 3<D_PPC_
        Mystate_=Mystate::Wait_Data_Ppc4;
#else
        Create_Pix<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_,D_MAX_COLS_,D_MAX_ROWS_>(
          Vid_In_Ppc_,Vid_Out_,
          Pix_Cntr_,Line_Cntr_,Width_,Height_,Last_Pix_
        );
        Vid_Out<<Vid_Out_;
        if(Last_Pix_){
          Mystate_=Mystate::Wait_Blanking;
        } else {
          Mystate_=Mystate::Wait_Data_Ppc1;
        }
#endif
      }
#if 1==D_ENABLE_DEBUG_
      else if(0!=Pix_Cntr_){
        Missed_Pix3_Error_=1;
        Mystate_=Mystate::Wait_Data_Ppc3;
      }
#endif
      else{
        Mystate_=Mystate::Wait_Data_Ppc3;
      }
      break;
#endif

#if 3<D_PPC_
    case Mystate::Wait_Data_Ppc4:
      Vid_In>>Vid_In_;
      if(Test_Mode_){
        Vid_In_Ppc_(PIX4_*D_DEPTH_*2-1,(PIX4_-1)*D_DEPTH_*2)=Test_Data_(D_DEPTH_*2-1,0);
      } else {
        Vid_In_Ppc_(PIX4_*D_DEPTH_*2-1,(PIX4_-1)*D_DEPTH_*2)=Vid_In_(D_DEPTH_*2-1,0);
      }
      if(3==Vid_In_(D_DEPTH_*2+1,D_DEPTH_*2)){
        Create_Pix<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_,D_MAX_COLS_,D_MAX_ROWS_>(
          Vid_In_Ppc_,Vid_Out_,
          Pix_Cntr_,Line_Cntr_,Width_,Height_,Last_Pix_
        );
        Vid_Out<<Vid_Out_;
        if(Last_Pix_){
          Mystate_=Mystate::Wait_Blanking;
        } else {
          Mystate_=Mystate::Wait_Data_Ppc1;
        }
      }
#if 1==D_ENABLE_DEBUG_
      else if(0!=Pix_Cntr_){
        Missed_Pix4_Error_=1;
        Mystate_=Mystate::Wait_Data_Ppc4;
      }
#endif
      else{
        Mystate_=Mystate::Wait_Data_Ppc4;
      }
      break;
#endif
  }

#if 1==D_ENABLE_DEBUG_
  *Missed_Pix1_Error=Missed_Pix1_Error_;
#if 1<D_PPC_
  *Missed_Pix2_Error=Missed_Pix2_Error_;
#endif
#if 2<D_PPC_
  *Missed_Pix3_Error=Missed_Pix3_Error_;
#endif
#if 3<D_PPC_
  *Missed_Pix4_Error=Missed_Pix4_Error_;
#endif
#endif

}
