#include "hls_crop.h"
#include <fstream>

std::ofstream ofs {"log.txt"};

int main()
{
  ap_uint<Bit_Width<D_MAX_COLS_>::Value> In_Width=1920;
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> In_Height=1080;

  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Out_X=0;
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Out_Y=0;
  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Out_Width=1920;
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Out_Height=1080;

  ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> Vid_In_;
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_In;
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_Out;

  ap_uint<32> Pix_Cntr;
  loopRows: for(auto J=ap_uint<Bit_Width<D_MAX_ROWS_>::Value> {0};J<In_Height;++J){
    loopCols: for(auto K=ap_uint<Bit_Width<D_MAX_COLS_/D_PPC_>::Value> {0};K<In_Width/D_PPC_;++K){
      Vid_In_.keep=-1;
      Vid_In_.strb=-1;

      if(0==J&&0==K){
        Vid_In_.user=1;
      } else {
        Vid_In_.user=0;
      }

      if(In_Height-1==J&&In_Width/D_PPC_-1==K){
        Vid_In_.last=1;
      } else if(In_Width/D_PPC_-1==K) {
        Vid_In_.last=1;
      } else {
        Vid_In_.last=0;
      }

      Vid_In_.data=Pix_Cntr++;
      Vid_In<<Vid_In_;
    }
  }

  D_TOP_(
    Vid_In,
    Vid_Out,
    In_Width,
    In_Height,
    Out_X,
    Out_Y,
    Out_Width,
    Out_Height
  );

  ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_PPC_>::Value,1,1,1> Vid_Out_;

  Pix_Cntr=0;
  while(!Vid_Out.empty()) {
    Vid_Out>>Vid_Out_;
    ofs << "Index: " << Pix_Cntr++ << ", "
        << "Vid_Out.user: " << Vid_Out_.user << ", "
        << "Vid_Out.last: " << Vid_Out_.last << ", "
        << "Vid_Out.data: " << Vid_Out_.data << '\n';
  }
}
