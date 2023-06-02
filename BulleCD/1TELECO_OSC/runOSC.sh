#!/bin/sh
cd `dirname $0`
O_S_C=open-stage-control
if [ ! $(which open-stage-control) ]; then 
	O_S_C="node /mnt/mmcblk0p2/App/open-stage-control_1.25.0_node"
	fi

#node /mnt/mmcblk0p2/App/open-stage-control_1.25.0_node -s localhost:18080 -t ./theme-contrast.css -l ./teleco-OSC.json
${O_S_C} -s localhost:18080 -t ./theme-contrast.css -l ./teleco-OSC.json
# --read-only

