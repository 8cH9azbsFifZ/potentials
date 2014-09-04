#!/bin/zsh
zmodload zsh/mathfunc

echo Not working because of accuracy
exit

INFILE=cu
PAIRFILE=$INFILE.phit
DENSITYFILE=$INFILE.rhot
EMBEDDINGFILE=$INFILE.ft
OUTFILE=$INFILE.eam

echo "Voters File $INFILE" 
NRHO=`cat $EMBEDDINGFILE | sed 's/D/e/g' | head -n 1 | awk '{print$1}'`
RHOMIN=`cat $EMBEDDINGFILE | sed 's/D/e/g' | head -n 1 | awk '{print$2}'`
RHOMAX=`cat $EMBEDDINGFILE | sed 's/D/e/g' | head -n 1 | awk '{print$3}'`
DRHO=`cat $EMBEDDINGFILE | sed 's/D/e/g'  | head -n 1 | awk '{print 1./$4}'`
MRHO=$((RHOMIN/$DRHO))
echo "Density: nrho:$NRHO rhomin:$RHOMIN rhomax:$RHOMAX drho:$DHRO missing:$MRHO"

NR=`cat $PAIRFILE | sed 's/D/e/g'  | head -n 1 | awk '{print$1}'`
RMIN=`cat $PAIRFILE | sed 's/D/e/g'  | head -n 1 | awk '{print$2}'`
RMAX=`cat $PAIRFILE | sed 's/D/e/g'  | head -n 1 | awk '{print$3}'`
DR=`cat $PAIRFILE | sed 's/D/e/g'  | head -n 1 | awk '{print 1./$4}'`
MR=$(( floor($RMIN/$DR) ))
RMINDENSITY=`cat $DENSITYFILE | sed 's/D/e/g'  | awk -v f=27.211383 'NR>1{print$1;exit}'`
RMINPAIR=`cat $PAIRFILE | sed 's/D/e/g'  | awk -v f=27.211383 'NR>1{print$1;exit}'`
RCUT=$RMAX
echo "Radius: nr$NR rmin:$RMIN rmax:$RMAX dr:$DR missing:$MR"

MASS=63.55
LC=3.615

cat << eof > $OUTFILE
#-> LAMMPS Potential File in DYNAMO 86 setfl Format <-#
# Voter Cu EAM
# Implemented by G. Ziegenhain (2007)
1 Cu
$NRHO $DRHO $(($NR+$MR)) $DR $RCUT
1 $MASS $LC FCC
eof

cat $EMBEDDINGFILE | sed 's/D/e/g'  | awk -v f=27.211383 'NR>1{print$1*f;print$2*f;print$3*f;print$4*f}' >> $OUTFILE

for i in `seq 1 1 $MR`; do
   echo $RMINDENSITY >> $OUTFILE
done   
cat $DENSITYFILE | sed 's/D/e/g'  | awk -v f=27.211383 'NR>1{print$1;print$2;print$3;print$4}' >> $OUTFILE

for i in `seq 1 1 $MR`; do
   echo $(($RMINPAIR * $i * 27.211383 * $DR)) >> $OUTFILE
done
cat $PAIRFILE | sed 's/D/e/g'  | awk -v f=27.211383 -v r=$DR -v n=$NR ' 
   NR>1 {
      print$1*f*r*n;
      n++;
      print$2*f*r*n;
      n++;
      print$3*f*r*n;
      n++;
      print$4*f*r*n;
      n++;
   }' >> $OUTFILE

