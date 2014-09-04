#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

#define OK 0
#define ERROR -1

double *init_r () {
   int n = 25;
   double *r = calloc (n, sizeof (double));
   if (!r) exit (ERROR);
   r[0] = 2.;
   r[1] = 2.1786;
   r[2] = 2.3573;
   r[3] = 2.5359;
   r[4] = 2.7145;
   r[5] = 2.8932;
   r[6] = 3.0718;
   r[7] = 3.2504;
   r[8] = 3.4291;
   r[9] = 3.6077;
   r[10] = 3.7863;
   r[11] = 3.9650;
   r[12] = 4.1436;
   r[13] = 4.3222;
   r[14] = 4.5009;
   r[15] = 4.6795;
   r[16] = 4.8581;
   r[17] = 5.0368;
   r[18] = 5.2154;
   r[19] = 5.3940;
   r[20] = 5.5727;
   r[21] = 5.7513;
   r[22] = 5.9299;
   r[23] = 6.1086;
   r[24] = 6.2872;
   return r;
}

double *init_V () {
   int n = 25;
   double *V = calloc (n, sizeof (double));
   if (!V) exit (ERROR);
   V[0] = 1.3467;
   V[1] = 0.8365;
   V[2] = 0.4096;
   V[3] = 0.1386;
   V[4] = 0.0062;
   V[5] = -.0488;
   V[6] = -.0665;
   V[7] = -.0662;
   V[8] = -.0605;
   V[9] = -.0529;
   V[10] = -.0503;
   V[11] = -.0537;
   V[12] = -.0554;
   V[13] = -.0535;
   V[14] = -.0485;
   V[15] = -.0400;
   V[16] = -.0279;
   V[17] = -.0149;
   V[18] = -.0041;
   V[19] = 0.0025;
   V[20] = 0.0048;
   V[21] = 0.0034;
   V[22] = 0.0006;
   V[23] = -.0001;
   V[24] = 0.0000;
   return V;
}

double *init_rho () {
   int n = 25;
   double *rho = calloc (n, sizeof (double));
   if (!rho) exit (ERROR);
   rho[0] = .0808;
   rho[1] = .0835;
   rho[2] = .0832;
   rho[3] = .0847;
   rho[4] = .0808;
   rho[5] = .0724;
   rho[6] = .0602;
   rho[7] = .0463;
   rho[8] = .0328;
   rho[9] = .0220;
   rho[10] = .0145;
   rho[11] = .0096;
   rho[12] = .0066;
   rho[13] = .0048;
   rho[14] = .0036;
   rho[15] = .0029;
   rho[16] = .0025;
   rho[17] = .0022;
   rho[18] = .0018;
   rho[19] = .0015;
   rho[20] = .0011;
   rho[21] = .0006;
   rho[22] = .0001;
   rho[23] = .0000;
   rho[24] = .0000;
   return rho;
}

double *init_rho_ () {
   int n = 25;
   double *rho_ = calloc (n, sizeof (double));
   if (!rho_) exit (ERROR);
   rho_[0] = .000;
   rho_[1] = .050;
   rho_[2] = .100;
   rho_[3] = .150;
   rho_[4] = .200;
   rho_[5] = .250;
   rho_[6] = .300;
   rho_[7] = .350;
   rho_[8] = .400;
   rho_[9] = .450;
   rho_[10] = .500;
   rho_[11] = .550;
   rho_[12] = .600;
   rho_[13] = .650;
   rho_[14] = .700;
   rho_[15] = .750;
   rho_[16] = .800;
   rho_[17] = .850;
   rho_[18] = .900;
   rho_[19] = .950;
   rho_[20] = .975;
   rho_[21] = 1.000;
   rho_[22] = 1.025;
   rho_[23] = .1050;
   rho_[24] = 1.100;
   return rho_;
}

double *init_F () {
   int n = 25;
   double *F = calloc (n, sizeof (double));
   if (!F) exit (ERROR);
   F[0] = 0.0000;
   F[1] = -0.6192;
   F[2] = -1.0792;
   F[3] = -1.4100;
   F[4] = -1.6414;
   F[5] = -1.8033;
   F[6] = -1.9255;
   F[7] = -2.0330;
   F[8] = -2.1313;
   F[9] = -2.2209;
   F[10] = -2.3024;
   F[11] = -2.3764;
   F[12] = -2.4434;
   F[13] = -2.5038;
   F[14] = -2.5574;
   F[15] = -2.6039;
   F[16] = -2.6428;
   F[17] = -2.6737;
   F[18] = -2.6963;
   F[19] = -.27101;
   F[20] = -2.7136;
   F[21] = -2.7148;
   F[22] = -2.7137;
   F[23] = -2.7108;
   F[24] = -2.7016;
   return F;
}

int main (void) {
   int n = 25;
   double *r = init_r (), *V = init_V (), *rho = init_rho (), *rho_ = init_rho_ (), *F = init_F ();

   int atomic_number = 1;
   double mass = 26.982;
   double lattice_constant = 4.05;
   char lattice_type[] = "FCC";

   int Nrho = 20, Nr = 20;
   double rc = 6.287;
   double rmax = r[24];
   double dr = rmax/(double)Nr, drho = 0.0808/(double)Nrho;

   // Spline Interpolation using GSL
   gsl_interp_accel *acc1 = gsl_interp_accel_alloc (),
                    *acc2 = gsl_interp_accel_alloc (),
                    *acc3 = gsl_interp_accel_alloc ();
   gsl_spline *spline1 = gsl_spline_alloc (gsl_interp_cspline, n),
              *spline2 = gsl_spline_alloc (gsl_interp_cspline, n),
              *spline3 = gsl_spline_alloc (gsl_interp_cspline, n);
   gsl_spline_init (spline1, rho, F, n);
   gsl_spline_init (spline2, r, rho, n);
   gsl_spline_init (spline3, r, V, n);

   char LAMMPSFilename[] = "EAM1.eam";
   FILE *LAMMPSFile = fopen (LAMMPSFilename, "w");
   if (!LAMMPSFile) exit (ERROR);

   fprintf (LAMMPSFile, \
         "#-> LAMMPS Potential File in DYNAMO 86 setfl Format <-#\n"\
         "# Mishin Al PRB(1999)59:3393\n"\
         "# Implemented by G. Ziegenhain (2007)\n"\
         "%d Al\n"\
         "%d %f %d %f %f\n"\
         "%d %f %f %s\n",
         atomic_number,
         Nrho, drho, Nr, dr, rc,
         atomic_number, mass, lattice_constant, lattice_type);

   int i;
   // Embedding function
   for (i = 0; i < Nrho; i++) 
      fprintf (LAMMPSFile, "%f\n", gsl_spline_eval (spline1, (double)i*drho, acc1));
   // Density function
   for (i = 0; i < Nr; i++)
      fprintf (LAMMPSFile, "%f\n", gsl_spline_eval (spline2, (double)i*dr, acc2));
   // Pair potential
   for (i = 0; i < Nr; i++)
      fprintf (LAMMPSFile, "%f\n", gsl_spline_eval (spline3, (double)i*dr, acc3));


   fclose (LAMMPSFile);
   gsl_spline_free (spline1);
   gsl_spline_free (spline2);
   gsl_spline_free (spline3);
   gsl_interp_accel_free (acc1);
   gsl_interp_accel_free (acc2);
   gsl_interp_accel_free (acc3);
   free (r);
   free (V);
   free (rho);
   free (rho_);
   free (F);

   return OK;
}
