void ApertSet(double z, double& rx, double& ry, double& dx){
  if(z<0.715){
    rx=0.0315;
    ry=0.0315;
  } 
  if(z>=0.715&&z<0.915){
    rx=0.0315+(z-0.715)*0.1175;
    ry=0.0315+(z-0.715)*0.1175;
  }
  if(z>=0.915&&z<1.865){
    rx=0.055;
    ry=0.055;
  }
  if(z>=1.865&&z<1.924){
    rx=0.054+(z-1.865)*6/59;
    ry=0.054+(z-1.865)*1/59;
  }
  if(z>=1.924&&z<2.019){
    rx=0.06;
    ry=0.055;
  }
  if(z>=2.019&&z<2.2){
    rx=0.0285;
    ry=0.038;
  }
  if(z>=2.2&&z<15.18){
  //为了与Geant4一致，在不添加R4ISPB的情况下，在坐标变换时将孔径设置为0.033m,防止正负电子真空盒重叠
  //但是在SAD的模拟中，孔径为0.48m
    rx=0.033;  
    ry=0.033;
  }
  if(z>=15.18){
    rx=0.055;
    ry=0.028;
  }
  if(z<0.909) dx=z*0.011;
  else if(z>=0.909&&z<1.509) dx=(z-0.909)*0.01854+0.01;
  else if(z>=1.509&&z<2.019) dx=(z-1.509)*0.026+0.021;
  else dx=0;  
}

void GetPosition(double xsad,double ysad, double zsad, double &xG4, double &yG4, double &zG4){

  double rx,ry,dx;
  ApertSet(fabs(zsad),rx,ry,dx); 
  if(fabs(zsad)>2.019){
    double theta=0.026;
    double cost=cos(theta);
    double sint=sin(theta);

    double deno = sqrt(xsad*xsad/(rx*rx)+ysad*ysad/(ry*ry));
    double x1 = xsad/deno;
    double y1 = ysad/deno;
    double z1 = zsad; 
    double x_midline,z_midline;
    if(z1>0){
      x_midline=(z1-1.509)*sint+0.021;
      z_midline=1.509+(z1-1.509)*cost;
    }
    else{
      x_midline=(z1+1.509)*sint-0.021;
      z_midline=-1.509+(z1+1.509)*cost;
    }
    xG4 = x1*cost+x_midline;
    yG4 = y1;
    zG4 = -x1*sint+z_midline; 
  } 
  else{
    double deno = sqrt(xsad*xsad/(rx*rx)+ysad*ysad/(ry*ry));
    xG4 = xsad/deno;
    yG4 = ysad/deno;
    zG4 = zsad;
  }
}
