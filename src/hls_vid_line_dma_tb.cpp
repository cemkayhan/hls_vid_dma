#include "hls_vid_line_dma.h"
#include <fstream>

std::ofstream ofs {"log.txt"};

int main()
{
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_S2MM_AXIS_PPC_>::Value,1,1,1> > Vid_In;
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_MM2S_AXIS_PPC_>::Value,1,1,1> > Vid_Out;

  static ap_uint<2*D_DEPTH_*D_S2MM_AXI_PPC_> Vid_In_Axi[D_MAX_ROWS_*D_MAX_STRIDE_];
  static ap_uint<2*D_DEPTH_*D_MM2S_AXI_PPC_> Vid_Out_Axi[D_MAX_ROWS_*D_MAX_STRIDE_];

  ap_uint<Bit_Width<D_MAX_COLS_>::Value> Width=1920;
  ap_uint<Bit_Width<D_MAX_ROWS_>::Value> Height=1080;
  ap_uint<Bit_Width<D_MAX_STRIDE_>::Value> Stride=2048;

  for(auto J=ap_uint<Bit_Width<D_MAX_ROWS_>::Value> {0};J<Height;++J){
    for(auto K=ap_uint<Bit_Width<D_MAX_COLS_/D_S2MM_AXIS_PPC_>::Value> {0};K<Width/D_S2MM_AXIS_PPC_;++K){
      ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_S2MM_AXIS_PPC_>::Value,1,1,1> Tmp_;
      Tmp_.data=K;
      Vid_In.write(Tmp_);
    }
  }

#if 1
  D_TOP_(
    Vid_In,
    Vid_Out,
    Vid_In_Axi,
    Vid_In_Axi,
    Width,
    Height,
    Stride
  );
#endif

  for(auto J=ap_uint<Bit_Width<D_MAX_ROWS_>::Value> {0};J<Height;++J){
    for(auto K=ap_uint<Bit_Width<D_MAX_COLS_/D_MM2S_AXIS_PPC_>::Value> {0};K<Width/D_MM2S_AXIS_PPC_;++K){
      ap_axiu<Axi_Vid_Bus_Width<D_COLOR_CHANNELS_,D_DEPTH_,D_MM2S_AXIS_PPC_>::Value,1,1,1> Tmp_;
      Vid_Out.read(Tmp_);

      ofs << "Index: " << J*Width+K << ", "
        << "Vid_Out.user: " << Tmp_.user << ", "
        << "Vid_Out.last: " << Tmp_.last << ", "
        << "Vid_Out.data: " << Tmp_.data << '\n';
    }
  }
}
