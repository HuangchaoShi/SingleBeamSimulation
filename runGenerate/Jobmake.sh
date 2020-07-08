#!/bin/bash
mkdir logerr mac_htc subjobs
#------------  create htcjon_Job_Acc*.sh---------- 
ID_start=100
ID_end=200
NUMinONESH=10
echo "create htcjon_Job.sh"

OUTPUTPATH="/home/shihc/ustcfs/MDIforSTCF/SingleSimPackage/runBackStage/output"
CURRENTPATH=`pwd`
MACHTCPATH="${CURRENTPATH}/mac_htc"
LOGERRPATH="${CURRENTPATH}/logerr"
npar=3000

let numsh=0
let j=${NUMinONESH}
for i in `seq ${ID_start} ${ID_end}`
do
  if [[ ${j} -eq ${NUMinONESH} ]]; then
    let j=0
    let numsh=$numsh+1
    cat > ${MACHTCPATH}/htc_Job_${numsh}.sh<<EOF
#!/bin/bash
alias sad='/home/shihc/ustcfs/MDIforSTCF/workspace/oldsad/bin/gs'
cd ${MACHTCPATH}
EOF
  chmod 755 ${MACHTCPATH}/htc_Job_${numsh}.sh
  fi
  cat >> ${MACHTCPATH}/htc_Job_${numsh}.sh<<EOF
  rm -rf ${LOGERRPATH}/Job_${i}.log ${LOGERRPATH}/Job_${i}.err
  ( ( time sad ${CURRENTPATH}/Generator.sad T $npar $i ${OUTPUTPATH}/TousWsum${i}.txt ${OUTPUTPATH}/TousW${i}.txt ) >> ${LOGERRPATH}/Job_${i}.log )>& ${LOGERRPATH}/Job_${i}.err
 ( ( time sad ${CURRENTPATH}/Generator.sad B $npar $i ${OUTPUTPATH}/BremWsum${i}.txt ${OUTPUTPATH}/BremW${i}.txt ) >> ${LOGERRPATH}/Job_${i}.log )>& ${LOGERRPATH}/Job_${i}.err
 ( ( time sad ${CURRENTPATH}/Generator.sad C $npar $i ${OUTPUTPATH}/CoulWsum${i}.txt ${OUTPUTPATH}/CoulW${i}.txt ) >> ${LOGERRPATH}/Job_${i}.log )>& ${LOGERRPATH}/Job_${i}.err 
EOF
  let j=${j}+1
done
#-------------create runbash*.sh--------
for i in `seq 1 ${numsh}`
do
  cat > ${MACHTCPATH}/runbash_${i}.sh<<EOF
  sh ${MACHTCPATH}/htc_Job_${i}.sh
EOF
chmod 755 ${MACHTCPATH}/runbash_${i}.sh
done
#------------- create .cmd job -----------
subdir="${CURRENTPATH}/subjobs"

for i in `seq 1 ${numsh}`
do
  echo "create submit_${i}"
  cat > ${subdir}/submit_${i}.cmd<<EOF
Universe             = vanilla
Notification         = Never
GetEnv               = True
Executable           = ${MACHTCPATH}/runbash_${i}.sh
Output               = $subdir/${i}.out
Error                = $subdir/${i}.err
Log                  = $subdir/${i}.log
+Group               = "BESIII"
#should_transfer_files= yes
#transfer_input_files =
requirements         = (substr(Machine,0,4)!="bl-0"&&ARCH=="X86_64")
WhenToTransferOutput = ON_EXIT_OR_EVICT
OnExitRemove         = TRUE
Queue
EOF
done
