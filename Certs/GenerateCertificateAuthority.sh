
mkdir CA
mkdir CA/private
touch CA/certsdb

mkdir Device

openssl req -config DeviceCA.conf -new -out CA/device.ca.csr.pem
openssl ca -config DeviceCA.conf -create_serial -selfsign -extensions ca_extensions -in CA/device.ca.csr.pem -out CA/device.ca.pem

openssl genrsa -out CA/private/verificationCert.key 2048

aws2 iot get-registration-code

openssl req -config CAVerification.conf -new -out CA/verificationCert.csr
openssl ca -config CAVerification.conf -in CA/verificationCert.csr -out CA/verificationCert.pem

aws2 iot register-ca-certificate --set-as-active --allow-auto-registration --ca-certificate file://CA/device.ca.pem --verification-certificate file://CA/verificationCert.pem


#openssl x509 -in CA/device.ca.pem -outform DER -out CA/device.ca.crt
#openssl x509 -in CA/private/device.ca.key.pem -outform DER -out CA/private/device.ca.key.der
