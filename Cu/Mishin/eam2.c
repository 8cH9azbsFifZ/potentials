#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#define E1  0.7366//eV
#define r0  2.325//A
#define a   1.919//1/A
#define b   4.043//1/A
#define rc  4.961//A

#define EOK 0
#define ERROR -1


double M (double r, double R0, double alpha) {
   return exp (-2.*alpha*(r-R0)) - 2.*exp (-alpha*(r-R0));
}

double V (double r) {
   return E1*M(r, r0, a);
}

double rho (double r) {
   return pow (r, 6.) * (exp (-b*r) + pow (2., 9.) * exp (-2.*b*r) );
}

double F (double rho_) {
#warning F(r) is not determined yet.
   return 0.;
}

int main (void) {
   int Nr = 10001;
   double rmax = 12.;
   double dr = rmax/(double)Nr;
   int Nrho = 10001;
   double rhomax = 2.5;
   double drho = rhomax/(double)Nrho;

   int atomic_number = 1;
   double mass = 63.55;
   double lattice_constant = 3.615;
   char lattice_type[] = "FCC";

   int i;

   char LAMMPSFilename[] = "EAM2.eam";
   FILE *LAMMPSFile = fopen (LAMMPSFilename, "w");
   if (!LAMMPSFile) exit (ERROR);

   // Header for setfl format
   fprintf (LAMMPSFile, \
         "#-> LAMMPS Potential File in DYNAMO 86 setfl Format <-#\n"\
         "# Mishin EAM1\n"\
         "# One more comment line\n"\
         "%d Cu\n"\
         "%d %f %d %f %f\n"\
         "%d %f %f %s\n",
         atomic_number, 
         Nrho, drho, Nr, dr, rc,
         atomic_number, mass, lattice_constant, lattice_type);

   // Embedding function
   for (i = 0; i < Nrho; i++) 
      fprintf (LAMMPSFile, "%f\n", F ((double)i*drho));
   // Density function
   for (i = 0; i < Nr; i++) 
      fprintf (LAMMPSFile, "%f\n", rho ((double)i*dr));
   // Pair potential
   for (i = 0; i < Nr; i++)   
      fprintf (LAMMPSFile, "%f\n", V ((double)i*dr) * (double)i*dr);

   printf ("#Pair Potential\n");
   for (i = 0; i < Nr; i++)
      printf ("%f %f\n", (double)i*dr, V ((double)i*dr));
   printf ("#Embedding Function\n");
   for (i = 0; i < Nrho; i++) 
      printf ("%f %f\n", (double)i*drho, F ((double)i*drho));
   printf ("#Density Function\n");
   for (i = 0; i < Nr; i++)
      printf ("%f %f\n", (double)i*dr, rho ((double)i*dr));

   fclose (LAMMPSFile);
   return (EOK);
}
