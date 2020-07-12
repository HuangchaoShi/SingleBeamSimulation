#!/bin/bash
mkdir logerr mac_htc subjobs output
#------------  create htcjon_Job_Acc*.sh---------- 
ID_start=100
ID_end=199
NUMinONESH=1
echo "create htcjon_Job.sh"

PACKAGEDIR="/ustcfs/bes3user/2017/shihc/MDIforSTCF/SingleBeamSimulation"
CURRENTPATH=`pwd`
MACHTCPATH="${CURRENTPATH}/mac_htc"
LOGERRPATH="${CURRENTPATH}/logerr"
OUTPUTPATH="${CURRENTPATH}/output"
npar=200

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
  ( ( time sad ${CURRENTPATH}/Tracking.sad T $npar $i ${PACKAGEDIR} ${OUTPUTPATH}/TousTracking_${i}.txt ) >> ${LOGERRPATH}/Job_${i}.log )>& ${LOGERRPATH}/Job_${i}.err
 ( ( time sad ${CURRENTPATH}/Tracking.sad B $npar $i ${PACKAGEDIR} ${OUTPUTPATH}/BremTracking_${i}.txt ) >> ${LOGERRPATH}/Job_${i}.log )>& ${LOGERRPATH}/Job_${i}.err
 ( ( time sad ${CURRENTPATH}/Tracking.sad C $npar $i ${PACKAGEDIR} ${OUTPUTPATH}/CoulTracking_${i}.txt ) >> ${LOGERRPATH}/Job_${i}.log )>& ${LOGERRPATH}/Job_${i}.err 
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
