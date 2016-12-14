#!/bin/sh
# DO NOT MERGE!
set -e
set -x

make bin/ipxe.usb DEBUG=virtio-net CONFIG=cloud EMBED=config/cloud/shell.ipxe
cp -f bin/ipxe.usb /tmp/disk.raw
( cd /tmp; tar Sczvf ipxe-shell-image.tar.gz disk.raw )
gsutil cp /tmp/ipxe-shell-image.tar.gz gs://suda-main

gcloud compute instances delete -q ipxe01 || true
gcloud compute images delete -q ipxe-shell || true
gcloud compute images create ipxe-shell --source-uri gs://suda-main/ipxe-shell-image.tar.gz
gcloud compute instances create ipxe01 --image ipxe-shell --metadata serial-port-enable=1

gcloud beta compute connect-to-serial-port ipxe01
