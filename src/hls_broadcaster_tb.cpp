#include "hls_broadcaster.h"

int main()
{
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_In ("Vid_In");
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_Out1 ("Vid_Out1");
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_Out2 ("Vid_Out2");
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_Out3 ("Vid_Out3");
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_Out4 ("Vid_Out4");
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_Out5 ("Vid_Out5");
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_Out6 ("Vid_Out6");
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_Out7 ("Vid_Out7");
  hls::stream<ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1>> Vid_Out8 ("Vid_Out8");
  ap_uint<16> Width=100;
  ap_uint<16> Height=100;
  ap_uint<8> Channel_En=0b00010101;

  for(auto i=0;i<Width*Height;++i){
    Vid_In.write(ap_axiu<Axi_Vid_Bus_Width<D_DEPTH_,D_PPC_>::Value,1,1,1> {i,-1,-1,0,0,0,0});
  }
  
  D_TOP_(
    Vid_In,
    Vid_Out1,
    Vid_Out2,
    Vid_Out3,
    Vid_Out4,
    Vid_Out5,
    Vid_Out6,
    Vid_Out7,
    Vid_Out8,
    Width,
    Height,
    Channel_En
  );

  while(!Vid_Out1.empty()) Vid_Out1.read();
  while(!Vid_Out2.empty()) Vid_Out2.read();
  while(!Vid_Out3.empty()) Vid_Out3.read();
  while(!Vid_Out4.empty()) Vid_Out4.read();
  while(!Vid_Out5.empty()) Vid_Out5.read();
  while(!Vid_Out6.empty()) Vid_Out6.read();
  while(!Vid_Out7.empty()) Vid_Out7.read();
  while(!Vid_Out8.empty()) Vid_Out8.read();
}
