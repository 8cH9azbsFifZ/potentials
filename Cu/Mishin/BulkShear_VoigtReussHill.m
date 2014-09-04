#!/usr/bin/octave -q

printf ("Cu(Mishin1)\n");
c11=169.9; #[GPa]
c44=76.2;
c12=122.6;


s11= (c11 +c12) / (c11**2+c11*c12 - 2.*c12**2)
s12=c12/(-c11**2-c11*c12+ 2.*c12**2)
s44=1./c44


sreuss=15/(4*(s11*3-s12*3)+3*(3*s44));
svoigt=1/15*(c11*3+3*(3*c44)-3*c12);
shill=(sreuss+svoigt)*.5;
breuss=1/(s11*3+2*3*s12);
bvoigt=1/9*(3*c11+2*(3*c12));
bhill=(breuss+bvoigt)*.5;

printf ("\nShear Modulus:   %f (Reuss)   %f (Voigt)   %f (Hill)", sreuss, svoigt, shill)
printf ("\nBulk Modulus:    %f (Reuss)   %f (Voigt)   %f (Hill)", breuss, bvoigt, bhill)

