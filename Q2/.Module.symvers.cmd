cmd_/home/pi/DD_exam/Q2/Module.symvers := sed 's/ko$$/o/' /home/pi/DD_exam/Q2/modules.order | scripts/mod/modpost -m -a   -o /home/pi/DD_exam/Q2/Module.symvers -e -i Module.symvers   -T -
