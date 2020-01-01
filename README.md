# GlassWebClock
This all the design docs/source code for my web enabled glass PCB binary clock. There are several different designs, and a number of technologies involved in its construction.

For my build report, visit my blog post: https://blog.equationoftime.space/2020/01/glass-printed-circuit-board.html

This is a highlevel overview of each component:
## Design
All design documents for the clock are stored here. EasyEDA, pcb layouts, etc. 
## ESP8266
All code and build scripts are here for the web enabled clock. 
## Arduino
Certain clock designs don't need wifi capability, so a basic atmel is adequate for a clock. Sourcecode for that exists here
## Android
The app for connecting/configuring the clock is here
## AWS
Some components, like notifications, require a cloud connection. This is AWS configuration scripts
## Certificates
AWS requires a certificate authority, and each device needs a  certificate signed by that CA installed on the device. This folder stores the scripts to generate the certificates and register them in AWS. 
