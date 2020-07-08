alias sad='/home/shihc/ustcfs/MDIforSTCF/workspace/oldsad/bin/gs'
npar=10000
for((count=100;count<101;count++))
do
  sad Generator.sad T $npar $count output/TousWsum$count output/TousW$count > output/TousOut${count}.out
  sad Generator.sad C $npar $count output/TousWsum$count output/TousW$count > output/CoulOut${count}.out
  sad Generator.sad B $npar $count output/TousWsum$count output/TousW$count > output/BremOut${count}.out
done

