mkdir CA
mkdir CA/private
touch CA/serial
touch CA/certsdb

mkdir Device

openssl req -config DeviceCA.conf -new -out CA/device.ca.csr.pem
openssl ca -config DeviceCA.conf -create_serial -selfsign -extensions ca_extensions -in CA/device.ca.csr.pem
