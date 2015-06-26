#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.1416

int nx=15;
int ny=20;
int nz=18;

int y = 0;

int fact=3;
int kd;

float sigma;

int n=8;

int arraylenx, arrayleny, arraylenz;

int ix, iy, iz;

int nhx, nhy, nhz;

int flipx, flipy, flipz;

int flag = 1;

float hdaf(int ndaf, float sigma, float Kxyz, float vec3d);


int main() {

  float dkx = (2*PI)/nx;       
  float dky = (2*PI)/ny;
  float dkz = (2*PI)/nz;

  int ndaf = n; 
 
  float fx, fy, fz;
  
  fx = round(PI/dkx);
  fy = round(PI/dky);
  fz = round(PI/dkz);
  
  arraylenx = fx;
  arrayleny = fy;
  arraylenz = fz;

  float  i;
  float kx [arraylenx];
  float ky [arrayleny];
  float kz [arraylenz];

  for(y = 0, i = 0; y < arraylenx; y++){
    kx[y]=i;
    i= i + dkx;
  }
  
  for(y = 0, i = 0; y <= arrayleny;i += dky, y++){
    ky[y]=i;
  }

  for(y = 0, i = 0; y <= arraylenz;i += dkz, y++){
    kz[y]=i;
  }

  

 float Kxyz[arraylenx][arrayleny][arraylenz];
 
 float vec3d[arraylenx][arrayleny][arraylenz];
 
  for( ix = 0; ix < arraylenx; ix++ ) {
    for( iy = 0; iy < arrayleny; iy++ ) {
      for( iz = 0; iz < arraylenz; iz++ ) {
	/*
	Kx[ix][iy][iz] = kx[ix];
	Ky[ix][iy][iz] = ky[iy];
	Kz[ix][iy][iz] = kz[iz];

	Kxyz[ix][iy][iz] =
	    Kx[ix][iy][iz]*Kx[ix][iy][iz] // (Kx^2)
	  + Ky[ix][iy][iz]*Ky[ix][iy][iz]
	  + Kz[ix][iy][iz]*Kz[ix][iy][iz];
	*/
	Kxyz[ix][iy][iz] =
	    kx[ix]*kx[ix]
	  + ky[iy]*ky[iy]
	  + kz[iz]*kz[iz];

      }
    }
  }

  
  kd=fact*PI;

  sigma=sqrt(2.0*ndaf+1)/kd;

  nhx=floor(nx/2)+1;
  nhy=floor(ny/2)+1;
  nhz=floor(nz/2)+1;
  
  flipx=nx%2;
  flipy=ny%2;
  flipz=nz%2;

  
  if(flag==1){
   
    int filt[nx][ny][nz]={0};

    //filt=zeros(nx,ny,nz);
    
    // filt(1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz).*Kxyz;

    
    for(ix=0;ix<nhx;ix++){
      for(iy=0;iy<nhy;iy++){
	for(iz=0;iz<nhz;iz++){
	  
	  filt[ix][iy][iz]= hdaf(ndaf,sigma,Kxyz,vec3d) * Kxyz[ix][iy][iz];

	}
      }
    }


    /*
    %filling the filter with replicas of the current filter
    filt(nhx+1:nx,:,:) = filt(nhx+flipx-1:-1:nhx+flipx-(nx-nhx),:,:);
    filt(:,nhy+1:ny,:) = filt(:,nhy+flipy-1:-1:nhy+flipy-(ny-nhy),:);
    filt(:,:,nhz+1:nz) = filt(:,:,nhz+flipz-1:-1:nhz+flipz-(nz-nhz));
    */
  }

  else if(flag==2){

    //filt=zeros(3,nx,ny,nz);
    
    int filt[3][nx][ny][nz];
    int j;

    for(j=0;j<3;j++){
      for(ix=0;ix<nhx;ix++){
	for (iy=0;iy<nhy;iy++){
	  for(iz=0;iz<nhz;iz++){
	    
	    filt[j][ix][iy][iz]=hdaf(ndaf,sigma,Kxyz,vec3d)*Kxyz[ix][iy][iz]
	                        *sqrt(-1);
	    
	  }
	}
      }  
    }
    
    /*
    filt(1,1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz).*Kx*sqrt(-1);
    filt(2,1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz).*Ky*sqrt(-1);
    filt(3,1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz).*Kz*sqrt(-1);
    */

    for(ix=0; i<nx-nhx; ix++){
      //  filt(:,nhx+i,:,:)=filt(:,nhx-i+flipx,:,:);
    }
    

    for(iy=0; iy<ny-nhy;iy++){
      //  filt(:,:,nhy+i,:)=filt(:,:,nhy-i+flipy,:);
    }

    for(iz=0; iz<nz-nhz;iz++){
      //  filt(:,:,:,nhz+i)=filt(:,:,:,nhz-i+flipz);
    }
  }

  else{

    int filt[nx][ny][nz]={0};

    //filt=zeros(nx,ny,nz);
        
    //filt(1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz);

    for(ix=0; ix<nx-nhx; ix++){
      
      
      //filt(nhx+i,:,:)=filt(nhx-i+flipx,:,:);
    }

    for(iy=0; iy<ny-nhy; iy++){
      //filt(:,nhy+i,:)=filt(:,nhy-i+flipy,:);
    }

    for(iz=0; iz<nz-nhz; iz++){
      //filt(:,:,nhz+i)=filt(:,:,nhz-i+flipz);
    }

  }
 
  //end of the program 

}



float hdaf(int ndaf, float  sigma, float Kxyz,float vec3d){

    int en = 1;
    int ft[ndaf][1]={0};
    
    
    ft(0)=1;
    if(n>1){
      
      for(y=1;y<ndaf;y++){
	
	ft[y] = ft[y-1] * y;
      }

    }
    
    for(y=0;y<ndaf;y++){
      for(ix=0;ix<arraylenx;ix++){
	for(iy=0;iy<arrayleny;iy++){
	  for(iz=0;iz<arraylenz;iz++){
      
	    en = en + (pow((((Kxyz[ix][iy][iz])*sigma*sigma)/2),y) / ft[y]);
    
	    vec3d[ix][iy][iz]=(en * exp((-1.0)*(Kxyz[ix][iy][iz])*(sigma*sigma)/2));
	 
	  }
	}
      }
    }
    
    return vec3d;
}
