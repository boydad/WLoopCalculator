#include <iostream>
#include <math.h>
#include <memory>
#include <cstdlib>

#include "confUtils.h"
#include "obs.h"
#include "su2.h"


void calcWLoop_1x1(
  const char* ifName, 
  const char* ofName, 
  const int nConfs){

  const Params<float> rParams(16, 4, 4, 4);
  DataRWHeandler<float> rData(rParams.confSize);
  rData.open(ifName);

  const Params<float> wParams(rParams.Ns, rParams.Nt, 6, 1);
  DataRWHeandler<float> wData(wParams.confSize);
  wData.open(ofName, false);
  

  size_t counter = 0;
  for(int i = 0; i < nConfs; i++){
    const GField<float> iField(rData.readConf(), rParams);
    const WLoops<float, SU2_t<float>> wloop(iField);

    GField<float> wField(wData.getData(), wParams);
    
    for(size_t t = 0; t < rParams.Nt; t++){
      for(size_t x = 0; x < rParams.Ns; x++){
        for(size_t y = 0; y < rParams.Ns; y++){
          for(size_t z = 0; z < rParams.Ns; z++){   

            size_t wlDim = 0;       
            for(size_t mu = 0; mu < rParams.nDim; mu++){
              for(size_t nu = mu + 1; nu < rParams.nDim; nu++){
               
                float* val = wField.getFieldAt(t, x, y, z, wlDim);
                *val = wloop.calc_1x1_at(t, x, y, z, mu, nu);

                wlDim++;
                counter++;
              } 
            }
          }
        }
      }
    }
    wData.writeConf();

    std::cout << "conf = " << i << " Done!\n";   
  }
}

int main(int argc, char **argv)
{	
  if(argc < 3)
    throw std::logic_error("Usage: ./nConfs inputFile outputFile"); 

  const int nConfs = atoi(argv[1]);
  const char* ifName = argv[2];
  const char* ofName = argv[3];

  calcWLoop_1x1(ifName, ofName, nConfs);


  // const int nConfs = 20000;
  // "/mnt/shared/boyda/ML/SU2_ML/4d/w10_LearnData4x16^3_reim_ml5/beta0.5/mldata/beta0.5.ml5",
  // "/mnt/shared/boyda/ML/SU2_ML/4d/w10_LearnData4x16^3_reim_ml5/beta4.0_P/mldata/beta4.ml5",
}