#!/bin/bash
sudo mknod /dev/example c $1 $2
sudo chmod 666 /dev/example
ls -l /dev/example
