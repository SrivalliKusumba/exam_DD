cmd_/home/pi/DD_exam/Q1/Module.symvers := sed 's/ko$$/o/' /home/pi/DD_exam/Q1/modules.order | scripts/mod/modpost -m -a   -o /home/pi/DD_exam/Q1/Module.symvers -e -i Module.symvers   -T -
