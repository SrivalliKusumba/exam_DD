cmd_/home/pi/DD_exam/Q2/modules.order := {   echo /home/pi/DD_exam/Q2/Q2.ko; :; } | awk '!x[$$0]++' - > /home/pi/DD_exam/Q2/modules.order
