mkdir CA
mkdir CA/private
touch CA/certsdb

mkdir Device

openssl req -config DeviceCA.conf -new -out CA/device.ca.csr.pem
openssl ca -config DeviceCA.conf -create_serial -selfsign -extensions ca_extensions -in CA/device.ca.csr.pem -out CA/device.ca.pem

openssl genrsa -out CA/private/verificationCert.key 2048
openssl req -new -key CA/private/verificationCert.key -out CA/verificationCert.csr
openssl x509 -req -in CA/verificationCert.csr -CA CA/device.ca.pem -CAkey CA/private/device.ca.key.pem -CAcreateserial -out CA/verificationCert.crt -days 500 -sha256

#openssl x509 -in CA/device.ca.pem -outform DER -out CA/device.ca.crt
#openssl x509 -in CA/private/device.ca.key.pem -outform DER -out CA/private/device.ca.key.der
