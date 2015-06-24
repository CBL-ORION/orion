function filt=Makefilter(nx,ny,nz,n,fact,flag)

% Determine maximum kx and ky
kxmax=pi;
kymax=pi;
kzmax=pi;

% Determine kx and ky intervals
dkx=2*pi/nx;       
dky=2*pi/ny;
dkz=2*pi/nz;

% Make kx and ky arrays and grids
kx=0:dkx:kxmax;  
ky=0:dky:kymax; 
kz=0:dkz:kzmax; 

[Kx,Ky,Kz]=ndgrid(kx,ky,kz);                % create kx and ky grids
Kxyz = Kx.^2+Ky.^2+Kz.^2;                    % kx^2 + ky^2 + kz^2
%Kxyz = single(Kxyz);

%HDAF parameters
%Maximum degree for taylor approximation
ndaf=n;

%play with this value [10 80] - step 10
kd=fact*kxmax;
sigma=sqrt(2.0*ndaf+1)/kd;

%Generate filter
nhx=floor(nx/2)+1;
nhy=floor(ny/2)+1;
nhz=floor(nz/2)+1;


flipx=mod(nx,2);
flipy=mod(ny,2);
flipz=mod(nz,2);


if flag==1
    filt=zeros(nx,ny,nz);
    filt(1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz).*Kxyz;
    
    %filling the filter with replicas of the current filter
    filt(nhx+1:nx,:,:) = filt(nhx+flipx-1:-1:nhx+flipx-(nx-nhx),:,:);
    filt(:,nhy+1:ny,:) = filt(:,nhy+flipy-1:-1:nhy+flipy-(ny-nhy),:);
    filt(:,:,nhz+1:nz) = filt(:,:,nhz+flipz-1:-1:nhz+flipz-(nz-nhz));
    
elseif flag==2
    filt=zeros(3,nx,ny,nz);
    filt(1,1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz).*Kx*sqrt(-1);
    filt(2,1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz).*Ky*sqrt(-1);
    filt(3,1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz).*Kz*sqrt(-1);
    for i=1:nx-nhx
        filt(:,nhx+i,:,:)=filt(:,nhx-i+flipx,:,:);
    end
    

    for i=1:ny-nhy
        filt(:,:,nhy+i,:)=filt(:,:,nhy-i+flipy,:);
    end

    for i=1:nz-nhz
        filt(:,:,:,nhz+i)=filt(:,:,:,nhz-i+flipz);
    end
else
    filt=zeros(nx,ny,nz);
    filt(1:nhx,1:nhy,1:nhz)=hdaf(ndaf,sigma,Kxyz);
    for i=1:nx-nhx
        filt(nhx+i,:,:)=filt(nhx-i+flipx,:,:);
    end

    for i=1:ny-nhy
        filt(:,nhy+i,:)=filt(:,nhy-i+flipy,:);
    end

    for i=1:nz-nhz
        filt(:,:,nhz+i)=filt(:,:,nhz-i+flipz);
    end
end
    
end