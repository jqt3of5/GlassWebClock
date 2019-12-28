openssl req -config DeviceCertificate.conf -new -out Device/device.csr.pem
openssl ca -config DeviceCertificate.conf -in Device/device.csr.pem
#openssl x509 -in Device/device.cert.pem -outform DER -out Device/device.cert.crt
#openssl x509 -in Device/private/device.key.pem -outform DER -out Device/private/device.key.der
