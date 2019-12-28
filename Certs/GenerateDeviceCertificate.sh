openssl req -config DeviceCertificate.conf -new -out Device/device.csr.pem
openssl ca -config DeviceCertificate.conf -in Device/device.csr.pem
