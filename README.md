# GlassWebClock
This all the design docs/source code for my glass web clock. 

The repo directories are separated by platform, they are:
*Design* - All design documents for the clock are stored here. EasyEDA, pcb layouts, etc. 
*ESP8266* - All code, build scripts, and design files are here for the actual clock. 
*Arduino* - certain clock designs don't need wifi capability, so a basic atmel is adequate for a clock
*Android* - The app for connecting/configuring the clock is here
*AWS* - Some components, like notifications, require a cloud connection. This is AWS configuration scripts
*Certificates* - Each device needs a signed certificate that can be installed on each device. This folder stores the scripts to generate the keys. 

