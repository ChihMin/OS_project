#!/bin/bash
sudo mknod /dev/mydev c $1 $2
sudo chmod 666 /dev/mydev
ls -l /dev/mydev
