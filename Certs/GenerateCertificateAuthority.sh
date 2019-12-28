mkdir CA
mkdir CA/private
touch CA/serial
touch CA/certsdb

mkdir Device

openssl req -config DeviceCA.conf -new -out CA/device.ca.csr.pem
openssl ca -config DeviceCA.conf -create_serial -selfsign -extensions ca_extensions -in CA/device.ca.csr.pem -out CA/device.ca.pem
#openssl x509 -in CA/device.ca.pem -outform DER -out CA/device.ca.crt
#openssl x509 -in CA/private/device.ca.key.pem -outform DER -out CA/private/device.ca.key.der
