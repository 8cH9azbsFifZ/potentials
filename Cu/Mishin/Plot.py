#!/usr/bin/python
from pylab import *
import matplotlib
import os

import os
os.popen ("cat Cu_Mishin1.eam| awk 'NR>6'>data.txt")

data = load("data.txt")

nrho=10001
rhomin=0
rhomax=4.961
drho=rhomax/nrho
rho=linspace(rhomin,rhomax,nrho)

nr=10001
rmin=0
rmax=4.961
dr=rmax/nr
r=linspace(rmin,rmax,nr)

embedding = data[:nrho]
density = data[nrho:nrho+nr]
pair = data[nrho+nr:]

figure()
ylabel(r"Embedding Energy [eV]")
xlabel(r"$\rho$")
plot(rho,embedding)
savefig("embedding.eps")

figure()
ylabel("Electron Density ")
xlabel(r"r [\AA]")
plot(r,density)
savefig("density.eps")

figure()
ylabel(r"Energy [$\Delta r$\AA eV]")
xlabel(r"r [\AA]")
plot(r,pair)
savefig("pair.eps")
